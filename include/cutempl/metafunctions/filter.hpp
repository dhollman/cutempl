#pragma once

#include "cutempl/containers/type_list.hpp"

#include "cutempl/metafunctions/invoke.hpp"
#include "cutempl/metafunctions/just.hpp"
#include "cutempl/metafunctions/select.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct filter_mfc :
  lambda_mfc<(
    []<class MFC, class... Ts>(wrap<MFC>, wrap<type_list<Ts...>>) {
      return (invoke_t<
        select_t<MFC, make_type_list_mfc, just_t<type_list<>>>, Ts
      >{} + ... + type_list<>{});
    }
  )> {};
template <class... Ts>
using filter = typename filter_mfc::template apply<Ts...>;
template <class... Ts>
using filter_t = typename filter<Ts...>::type;

}  // namespace cutempl
