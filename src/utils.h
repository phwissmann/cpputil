#pragma once
#include <type_traits>

namespace cpputil {

/// Get type of the n-th element of an arg pack
template <int n, typename First, typename... Args>
struct n_th_type {
  using type = std::conditional_t<(n <= 0), First,
                                  typename n_th_type<n - 1, Args...>::type>;
};

/// Get type of the first element of an arg pack
template <typename First, typename... Args>
struct n_th_type<0, First, Args...> {
  using type = First;
};

/// Return size of first container
template <typename FirstContainer, typename... Containers>
constexpr size_t first_size(const FirstContainer &first,
                            const Containers &...) {
  return first.size();
}

/// Check for all containers to have the same size
template <typename... Containers>
bool same_size(const Containers &... containers) {
  bool b = true;
  ((b &= first_size(containers...) == containers.size()), ...);
  return b;
}

/// Check a predicate to be true of one of the given types
template<template<typename> typename predicate, typename... Args>
struct any_of{
  constexpr static bool value = (( predicate<Args>::value) || ...);
};
template<template<typename> typename predicate, typename... Args>
constexpr bool any_of_v = any_of<predicate, Args...>::value;

/// Select the const iterator of a container
template<typename Container>
struct const_iterator_selector{
  using type = typename Container::const_iterator;
};

template<typename Container>
using const_iterator_selector_t = typename const_iterator_selector<Container>::type;

/// Select the non-const iteartor of a container
template<typename Container>
struct iterator_selector{
  using type = typename Container::iterator;
};

template<typename Container>
using iterator_selector_t = typename iterator_selector<Container>::type;


}  // namespace cpputil