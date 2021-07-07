#pragma once

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct append_mfc :
  lambda_mfc<(
    []<class... Ts, class U>(wrap<type_list<Ts...>>, wrap<U>) {
      return wrap<type_list<Ts..., U>>{};
    }
  )> {};
template <class TL, class U>
using append = append_mfc::apply<TL, U>;
template <class TL, class U>
using append_t = typename append<TL, U>::type;

}  // namespace cutempl
