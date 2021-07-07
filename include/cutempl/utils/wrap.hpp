#pragma once

namespace cutempl {

// Usually we want to apply lambdas with a wrapper template so that we can work
// with non-regular types (like non-default constructible types, references,
// or even just `void`) or incomplete types.
template <class T> struct wrap {
  using type = T;
};

namespace short_aliases {

template <class T>
using w = wrap<T>;

}  // namespace short_aliases


}  // namespace cutempl
