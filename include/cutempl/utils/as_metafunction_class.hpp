#pragma once

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

template <template <class...> class Mfn>
struct as_metafunction_class :
  lambda_mfc<(
    []<class... Ts>(wrap<Ts>...) {
      // just in case the metafunction itself isn't regular:
      return wrap<typename Mfn<Ts...>::type>{};
    }
  )> {};

}  // namespace cutempl
