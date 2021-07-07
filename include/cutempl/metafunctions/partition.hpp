#pragma once

#include "cutempl/metafunctions/filter.hpp"
#include "cutempl/metafunctions/invoke.hpp"
#include "cutempl/metafunctions/negation_of.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct partition_mfc :
  lambda_mfc<(
    []<class UnaryPredMfc, class TL>(wrap<UnaryPredMfc>, wrap<TL>) {
      return TL<
        filter_t<UnaryPredMfc, TL>,
        filter_t<negation_of_t<UnaryPredMfc>, TL>
      >{};
    }
  )> {};
template <class... Ts>
using partition = typename partition_mfc::template apply<Ts...>;
template <class... Ts>
using partition_t = typename partition<Ts...>::type;

}  // namespace cutempl

