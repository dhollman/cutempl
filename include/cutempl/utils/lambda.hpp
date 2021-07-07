#pragma once

#include "cutempl/utils/wrap.hpp"

namespace cutempl {

// C++20 lets us make metafunction classes on the fly quite easily
// "mfc" is short for "metafunction class", a convention dating back to Boost MPL
// that used many of the same nested naming conventions. Usually we want to apply
// the lambda with a wrapper template so that we can work with non-regular types
// (like non-default constructible types, references, or even just `void`) or
// incomplete types. `lambda_mfc` also expects the result of `F` to be wrapped
// for similar reasons.
// F() is expected to return a type that is semi-regular, complete, and has a
// nested type named `type` representing the result of the operation.
template <auto F>
struct lambda_mfc {
  // we need the wrap here in case the result type is final
  template <class... Ts>
  struct apply : wrap<typename decltype(F(wrap<Ts>{}...))::type> {};
  template <class... Ts>
  using apply_t = typename apply<Ts...>::type;
  // allow lambda_mfc's to be returned from lambdas without further wrapping
  using type = lambda_mfc;
};

}  // namespace cutempl
