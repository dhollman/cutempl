#pragma once

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct apply_mfc :
  lambda_mfc<(
    []<class Mfc, class... Ts>(wrap<Mfc>, wrap<type_list<Ts...>>) {
      return typename Mfc::template apply<Ts...>{};
    }
  )> {};
template <class Mfc, class TL>
using apply = typename apply_mfc::template apply<Mfc, TL>;
template <class Mfc, class TL>
using apply_t = typename apply<Mfc, TL>::type;

}  // namespace cutempl
