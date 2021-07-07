#pragma once

#include "cutempl/cutempl_fwd.hpp"

#include "cutempl/metafunctions/apply.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

// A higher-order metafunction that turns a metafunction class that operates
// on `k` arguments to one that operates on `n` arguments (with n > k) by
// selected the positional arguments indicated by the wrapped values

struct on_args_mfc :
  lambda_mfc<(
    []<class MFC, auto... Idxs>(wrap<MFC>, wrap<wrap_value<Idxs>>...) {
      return lambda_mfc<(
        []<class... Ts>(wrap<Ts>...) {
          return apply<MFC, filter_t<

        }
      )>{};
      return compose<
        apply_of_t<MFC>,
        map_t<
          curry_t<curry_mfc, wrapped_at_mfc>,
          type_list<wrap_value<Idxs>...>
        >

        enumerate_mfc,
        make_type_list_mfc
      >
    }
  )> {};
template <class... Ts>
using  = typename _mfc::template apply<Ts...>;
template <class... Ts>
using _t = typename <Ts...>::type;

}  // namespace cutempl
