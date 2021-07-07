#pragma once

#include "cutempl/cutempl_fwd.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

// a higher-order metafunction to create a metafunction class that returns true if
// all of the input metafunction classes return something with a `::type::value` that's
// equal to `true`
struct predicate_conjunction_mfc :
  lambda_mfc<(
    []<class... Mfcs>(wrap<Mfcs>...) {
      return value_lambda_mfc<(
        []<class... Ts>(wrap<Ts>...) {
          return (Mfcs::template apply<Ts>::type::value && ...);
        }
      )>{};
    }
  )> {};
template <class... Mfcs>
using predicate_conjunction = typename predicate_conjunction_mfc::template apply<Mfcs...>;
template <class... Mfcs>
using predicate_conjunction_t = typename predicate_conjunction<Mfcs...>::type;


}  // namespace cutempl
