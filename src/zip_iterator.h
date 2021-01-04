#include <tuple>
#include <utility>
#include <vector>

#include <functional>

#include "utils.h"

namespace cpputil {

template <typename... Iterators>
class TupleIterator {
 public:
  using IteratorTupleRef = std::tuple<Iterators&...>;
  using IteratorTuple = std::tuple<Iterators...>;

  TupleIterator(Iterators... iterators) : m_Iterators(iterators...) {}

  template <std::size_t i>
  auto& get() {
    return *std::get<i>(m_Iterators);
  }

  template <std::size_t i>
  auto const& get() const& {
    return *std::get<i>(m_Iterators);
  }

  template <std::size_t i>
  auto const&& get() const&& {
    return std::move(*std::get<i>(m_Iterators));
  }

  template <std::size_t... Is>
  constexpr TupleIterator<Iterators...> create(std::index_sequence<Is...>) {
    return TupleIterator(std::move(std::get<Is>(m_Iterators))...);
  }

  TupleIterator<Iterators...> operator++(int) {
    std::apply([](auto&... iterator) { (..., ++iterator); }, m_Iterators);
    return create(std::index_sequence_for<Iterators...>());
  }

  TupleIterator<Iterators...> operator++() {
    std::apply([](auto&... iterator) { (..., iterator++); }, m_Iterators);
    return create(std::index_sequence_for<Iterators...>());
  }

  bool operator!=(const TupleIterator<Iterators...>& other) const {
    return std::get<0>(m_Iterators) != std::get<0>(other.m_Iterators);
  }

  TupleIterator<Iterators...>& operator*() { return *this; }

  IteratorTuple m_Iterators;
};

/* This class stores tuples to all iterators of given containers
*/
template <typename... Containers>
class Zip {
 public:
  template<typename Container>
  using IteratorType = std::conditional_t<any_of_v<std::is_const, Containers...>, const_iterator_selector<Container>, iterator_selector<Container>>;
  using Iterators = TupleIterator<typename IteratorType<Containers>::type...>;

  Zip(Containers&... containers)
      : m_BeginIterators(std::begin(containers)...),
        m_EndIterators(std::end(containers)...) {
    assert(same_size(containers...) &&
           "All containers must have the same size.");
  }

  /// @return reference to tuple of begin iterators to all containers
  Iterators& begin() { return m_BeginIterators; }
  /// @return reference to tuple of end iterators to all containers
  Iterators& end() { return m_EndIterators; }

 private:
  /// Tuple of begin interators to all containers
  Iterators m_BeginIterators;
  /// Tuple of end interators to all containers
  Iterators m_EndIterators;
};

}  // namespace cpputil

namespace std {
template <typename... Iterators>
struct tuple_size<cpputil::TupleIterator<Iterators...>> {
  static const int value = sizeof...(Iterators);
};

template <size_t i, typename... Iterators>
struct tuple_element<i, cpputil::TupleIterator<Iterators...>> {
  using iterator_type = typename cpputil::n_th_type<i, Iterators...>::type;
  using type = typename std::iterator_traits<iterator_type>::value_type;
};
}  // namespace std