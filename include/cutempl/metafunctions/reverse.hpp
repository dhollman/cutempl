#pragma once

#include "cutempl/containers/type_list.hpp"

#include "cutempl/metafunctions/invoke.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/overloads.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct reverse_mfc :
  lambda_mfc<(
    overloads{
      []<class T, class... Ts>(wrap<type_list<T, Ts...>>) {
        return invoke_t<reverse_mfc, type_list<Ts...>>{} + type_list<T>{};
      },
      [](wrap<type_list<>> tl) { return tl; }
    }
  )> {};
template <class TL>
using reverse = typename reverse_mfc::template apply<TL>;
template <class TL>
using reverse_t = typename reverse<TL>::type;

}  // namespace cutempl
