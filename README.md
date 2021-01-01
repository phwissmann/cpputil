# cpputil
Library of utilities for C++ development


## Zip function

This adds support range-based for loops of the form

```
  const std::vector<int> v{1,2,3};
  const std::set<int> s(std::begin(v), std::end(v);
  for (const auto& [a, b] : Zip(v, s)) {
    assert(a==b);
  }
  ```
  The result of `Zip` decays directly into structured bindings which allows easy iteration of multiple iteratiors of the same size
