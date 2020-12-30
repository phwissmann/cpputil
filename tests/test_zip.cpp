#include <gtest/gtest.h>
#include <map>

#include "zip_iterator.h"

using namespace cpputil;

TEST(Zip, TupleIterator) {
  using valtype1 = int;
  std::vector<int> v1(4);
  std::vector<int> v2(4);
  using IterType1 = std::vector<int>::iterator;
  using IterType2 = std::vector<int>::iterator;

  TupleIterator<IterType1, IterType2> tuple_iterator(v1.begin(), v2.begin());

  auto& val_ref = tuple_iterator.get<0>();
  EXPECT_EQ(val_ref, v1[0]);
  val_ref = 11;
  EXPECT_EQ(val_ref, 11);

  const auto& const_val_ref = tuple_iterator.get<0>();
  EXPECT_EQ(const_val_ref, v1[0]);

  static_assert(
      std::is_const_v<std::remove_reference_t<decltype(const_val_ref)>>,
      "is const");

  const auto& [const_a, const_b] = tuple_iterator;
  EXPECT_EQ(const_a, v1[0]);

  static_assert(std::is_const_v<std::remove_reference_t<decltype(const_a)>>,
                "is const");

  auto& [a, b] = tuple_iterator;
  static_assert(!std::is_const_v<std::remove_reference_t<decltype(a)>>,
                "is const");
  ++a;
  EXPECT_EQ(a, v1[0]);

  const auto& [const_c, const_d] = *tuple_iterator;
  static_assert(std::is_const_v<std::remove_reference_t<decltype(const_c)>>,
                "is const");

  auto& [c, d] = *tuple_iterator;
  static_assert(!std::is_const_v<std::remove_reference_t<decltype(c)>>,
                "is const");
  ++c;
  std::cout << c << " " << v1[0] << std::endl;
  EXPECT_EQ(c, v1[0]);
}

TEST(Zip, vector_array) {
  std::vector<int> v1(4);
  v1[0] = 1;
  v1[1] = 2;
  v1[2] = 3;
  v1[3] = 1;

  std::array<float, 4> v2;
  // std::vector<float> v2(4);
  v2[0] = 1.1f;
  v2[1] = 2.1f;
  v2[2] = 3.1f;
  v2[3] = 1.1f;

  using asf = n_th_type<1, double, int, char>::type;

  static_assert(std::is_same_v<asf, int>, "same type");

  // static_assert(std::is_same_v<decltype(std::begin(v2)), int>, "asdf");
  //   std::vector<int>::iterator it = v1.begin();
  //   *it = 1;
  //   int& val = *it;

  //   std::tuple<std::vector<int>::iterator> t(it);
  //   int& r = *std::get<std::vector<int>::iterator>(t);
  //   r = 100;
  //   EXPECT_EQ(v1[0], 100);

  //   ZipImpl zipiter(v1, v2);
  //   auto& [a, b] = zipiter.begin();
  int i = 0;
  for (auto& [a, b] : Zip(v1, v2)) {
    EXPECT_EQ(v2[i], b);

    a += 1;
    b *= 2;

    EXPECT_EQ(v1[i], a);

    std::cout << i << ":\t" << v1[i] << "\t" << a << "\t" << v2[i] << "\t" << b
              << std::endl;
    ++i;
  }
}

TEST(Zip, vector_set) {
  std::vector<int> v(3);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  std::set<int> s(std::begin(v), std::end(v));

  const bool b = same_size(v, s);
  EXPECT_TRUE(b);

  for (const auto& [a, b] : Zip(v, s)) {
    EXPECT_EQ(b, a);
  }
}

TEST(Zip, vector_different_size) {
  std::vector<int> v(3);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  std::vector<int> s(std::begin(v), std::end(v) - 1);

  EXPECT_FALSE(same_size(v, s));
}