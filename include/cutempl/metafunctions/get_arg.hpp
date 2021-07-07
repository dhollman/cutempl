#pragma once

#include "cutempl/containers/type_list.hpp"

#include "cutempl/metafunctions/at.hpp"
#include "cutempl/metafunctions/apply_of.hpp"
#include "cutempl/metafunctions/compose.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"
#include "cutempl/utils/wrap_value.hpp"

namespace cutempl {

struct wrapped_get_arg_mfc :
  lambda_mfc<(
    []<auto ArgNum>(wrap<wrap_value<ArgNum>>) {
      return compose<
        curry_t<wrapped_at_mfc, wrap_value<ArgNum>>,
        make_type_list_mfc
      >{};
    }
  )> {};
template <class... Ts>
using wrapped_get_arg = typename wrapped_get_arg_mfc::template apply<Ts...>;
template <class... Ts>
using wrapped_get_arg_t = typename wrapped_get_arg<Ts...>::type;

template <auto ArgNum>
using make_get_arg = wrapped_get_arg_t<wrap_value<ArgNum>>;

}  // namespace cutempl
