#pragma once

#include "cutempl/cutempl_fwd.hpp"

#include "cutempl/containers/type_list.hpp"

#include "cutempl/hooks/additive_identity.hpp"

#include "cutempl/metafunctions/invoke.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/overloads.hpp"
#include "cutempl/utils/wrap.hpp"
#include "cutempl/utils/wrap_value.hpp"

#include <utility>

namespace cutempl {

struct sum_mfc :
  lambda_mfc<(
    overloads{
      []<class... Ts, class Initial>(wrap<type_list<Ts...>>, wrap<Initial>) {
        return wrap<decltype((
          std::declval<Initial>() + ... + std::declval<Ts>()))>{};
      },
      // if a common additive identity exists, we can default Initial (and
      // this overload doesn't need to be constrained since if we don't
      // we want to fail to indicate to the user that a default is required)
      []<class... Ts>(wrap<type_list<Ts...>>) {
        return invoke<sum_mfc, type_list<Ts...>,
          common_additive_identity_t<Ts...>
        >{};
      }
    }
  )> {};
template <class... Ts>
using sum = typename sum_mfc::template apply<Ts...>;
template <class... Ts>
using sum_t = typename sum<Ts...>::type;

}  // namespace cutempl
