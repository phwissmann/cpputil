#include <iostream>
#include <set>
#include <tuple>
#include <vector>

#include "zip_iterator.h"

int main()
{
  std::vector<int> v1(4);
  std::set<int> v2;
  v1[0] = 1;
  v1[1] = 2;
  v1[2] = 3;
  v1[3] = 1;

  v2.insert({4, 5, 6, 7});

  // v2[0] = 4;
  // v2[1] = 5;
  // v2[2] = 6;
  // v2[3] = 7;

  auto zipiter = Zip(v1, v2);
  auto [a, b] = zipiter.begin();
  int i = 0;
  for (auto [a, b, c] : Zip(v1, v2, v1)) {
    std::cout << i++ << ":\t" << a << "\t" << b << "\t" << c << std::endl;
  }
}