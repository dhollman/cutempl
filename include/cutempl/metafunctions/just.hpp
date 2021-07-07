#pragma once

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct just_mfc :
  lambda_mfc<(
    []<class T>(wrap<T>) {
      return lambda_mfc<[]<class... Ts>(wrap<Ts>...) { return wrap<T>{}; }>{};
    }
  )> {};
template <class... Ts>
using just = typename just_mfc::template apply<Ts...>;
template <class... Ts>
using just_t = typename just<Ts...>::type;

}  // namespace cutempl
