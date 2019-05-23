#include <tuple>
#include <utility>
#include <vector>

#include <functional>
#include <iostream>

template <typename... Iterators>
class TupleIterator
{
 public:
  using IteratorTuple = std::tuple<Iterators...>;
  using TupleType = std::tuple<typename Iterators::value_type...>;

  TupleIterator(Iterators&&... iterators) : m_Iterators(iterators...) {}

  template <std::size_t i>
  int get()
  {
    return *std::get<i>(m_Iterators);
  }

  template <std::size_t... Is>
  TupleIterator<Iterators...> create(std::index_sequence<Is...>)
  {
    return TupleIterator(std::move(std::get<Is>(m_Iterators))...);
  }

  template <std::size_t... Is>
  TupleType createTuple(std::index_sequence<Is...>)
  {
    return TupleType((*std::get<Is>(m_Iterators))...);
  }

  TupleIterator<Iterators...> operator++(int)
  {
    std::apply([](auto&... iterator) { (..., iterator.operator++()); },
               m_Iterators);
    return create(std::index_sequence_for<Iterators...>());
  }

  TupleIterator<Iterators...> operator++()
  {
    std::apply([](auto&... iterator) { (..., iterator.operator++()); },
               m_Iterators);
    return create(std::index_sequence_for<Iterators...>());
  }

  bool operator!=(const TupleIterator<Iterators...>& other) const
  {
    return std::get<0>(m_Iterators) != std::get<0>(other.m_Iterators);
  }

  TupleType operator*()
  {
    return createTuple(std::index_sequence_for<Iterators...>());
  }

  IteratorTuple m_Iterators;
};
namespace std
{
template <typename... Iterators>
struct tuple_size<TupleIterator<Iterators...>> {
  static const int value = sizeof...(Iterators);
};

template <size_t i, typename... Iterators>
struct tuple_element<i, TupleIterator<Iterators...>> {
  using type = vector<int>::value_type;
};
}  // namespace std

template <typename... Containers>
class Zip
{
 public:
  using Iterators = TupleIterator<typename Containers::iterator...>;

  Zip(Containers&... containers)
      : m_BeginIterators(std::begin(containers)...),
        m_EndIterators(std::end(containers)...)
  {
  }

  Iterators& begin() { return m_BeginIterators; }
  Iterators& end() { return m_EndIterators; }

  Iterators m_BeginIterators;
  Iterators m_EndIterators;
};
