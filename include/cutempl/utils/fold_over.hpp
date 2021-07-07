#pragma once

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

namespace fold_over_impl {

// The impl here is to allow definition of left_mfc and right_mfc intrusively
template <class MFC, class Initial>
struct impl {
  template <class T>
  friend auto operator|(impl, wrap<T>) {
    // it's part of a left-associative fold, so Initial (a.k.a CurrentResult) should
    // be the first (i.e., left) argument to the metafunction
    return impl<MFC, typename MFC::template apply_t<Initial, T>>{};
  }
  template <class T>
  friend auto operator|(wrap<T>, impl) {
    // the opposite of the above; Initial should be the second (right) argument
    return impl<MFC, typename MFC::template apply_t<T, Initial>>{};
  }
  // Depending on the context, it can be easier to use `type` with `typename` (e.g.,
  // so that this can be passed to functions that expect lazy evaluation) or do
  // decltype on the result() operation since there might already be a decltype()
  // operator at the call site for fold expression itself.
  using type = Initial;
  // most of our returns expect wrapped values for safety around non-regular types,
  // so the convention should be to return the wrapped result here also.
  static constexpr auto result() { return wrap<Initial>{}; };
};

}  // namespace fold_over_impl

template <class MFC, class Initial>
struct fold_over : fold_over_impl::impl<MFC, Initial> {
  // A convenience metafunction class that represents the action of performing
  // the left fold on a pack. We don't have to mess with `wrap` because it's already
  // done by lambda_mfc _and_ expected by the operator|().
  using left_mfc = lambda_mfc<(
    [](auto... vs) { return (vs | ... | fold_over_impl::impl<MFC, Initial>{}); }
  )>;
  // Same thing for right:
  using right_mfc = lambda_mfc<(
    [](auto... vs) { return (fold_over_impl::impl<MFC, Initial>{} | ... | vs); }
  )>;
};

}  // namespace cutempl
