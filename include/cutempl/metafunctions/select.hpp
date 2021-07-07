#pragma once

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

// a higher-order metafunction to select betweem two metafunction classes
// based on a conditional metafunction class and return the result of applying
// the selected metafunction class

struct select_mfc :
  lambda_mfc<(
    []<class CondMfc, class TrueMfc, class FalseMfc>(
        wrap<CondMfc>, wrap<TrueMfc>, wrap<FalseMfc>) {
      return lambda_mfc<(
        []<class... Ts>(wrap<Ts>...) {
          return typename std::conditional_t<
            CondMfc::template apply_t<Ts...>::value,
            TrueMfc, FalseMfc
          >::template apply<Ts...>{};
        })
      >{};
    }
  )> {};
template <class... Ts>
using select = select_mfc::apply<Ts...>;
template <class... Ts>
using select_t = typename select<Ts...>::type;

}  // namespace cutempl
