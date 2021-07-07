#pragma once

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct invoke_mfc :
  lambda_mfc<(
    []<class MFC, class... Ts>(wrap<MFC>, wrap<Ts>...) {
      return typename MFC::template apply<Ts...>{};
    }
  )> {};
template <class... Ts>
using invoke = typename invoke_mfc::template apply<Ts...>;
template <class... Ts>
using invoke_t = typename invoke<Ts...>::type;

}  // namespace cutempl
