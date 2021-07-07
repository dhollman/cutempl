#pragma once

#include "cutempl/metafunctions/invoke.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

// a higher-order metafunction to create a curried version of some other metafunction

struct curry_mfc :
  lambda_mfc<(
    []<class Mfn, class... Ts>(wrap<Mfn>, wrap<Ts>...) {
      return lambda_mfc<(
        []<class... Us>(wrap<Us>...) {
          return invoke<Mfn, Ts..., Us...>{};
        }
      )>{};
    }
  )> {};
template <class... Ts>
using curry = curry_mfc::apply<Ts...>;
template <class... Ts>
using curry_t = typename curry<Ts...>::type;

}  // namespace cutempl
