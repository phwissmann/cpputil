#pragma once
#include <type_traits>

namespace cpputil {

/// Get type of the i-th element of an arg pack
template <int i, typename First, typename... Args>
struct n_th_type {
  using type = std::conditional_t<(i <= 0), First,
                                  typename n_th_type<i - 1, Args...>::type>;
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

}  // namespace cpputil