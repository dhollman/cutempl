#pragma once

#include "cutempl/containers/type_list.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct push_front_mfc :
  lambda_mfc<(
    []<class... Ts, class... Us>(
      wrap<type_list<Ts...>>, wrap<Us>...
    ) {
      return wrap<TL<Us..., Ts...>>{};
    }
  )> {};
template <class... Ts>
using push_front = typename push_front_mfc::template apply<Ts...>;
template <class... Ts>
using push_front_t = typename push_front<Ts...>::type;

}  // namespace cutempl
