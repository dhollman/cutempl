#pragma once

#include "cutempl/cutempl_fwd.hpp"

#include "cutempl/containers/type_list.hpp"

#include "cutempl/metafunctions/apply.hpp"
#include "cutempl/metafunctions/compose.hpp"
#include "cutempl/metafunctions/curry.hpp"
#include "cutempl/metafunctions/invoke.hpp"
#include "cutempl/metafunctions/just.hpp"
#include "cutempl/metafunctions/map.hpp"
#include "cutempl/metafunctions/select.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

// TODO there has got to be a cuter way to write this

struct zip_mfc :
  lambda_mfc<(
    []<class... TLs>(wrap<TLs>...) {
      return invoke_t<select_t<
        compose_t<any_mfc, curry_t<map_mfc, is_empty_mfc>, make_type_list_mfc>,
        just_t<type_list<>>,
        lambda_mfc<([]<class... NonEmptyTLs>(wrap<NonEmptyTLs>...) {
          return type_list<type_list<invoke_t<front_mfc, NonEmptyTLs>...>>{} +
            invoke_t<zip_mfc, invoke_t<pop_front_mfc, NonEmptyTLs>...>{};
        })>
      >, TLs...>{};
    }
  )> {};
template <class... Ts>
using zip = typename zip_mfc::template apply<Ts...>;
template <class... Ts>
using zip_t = typename zip<Ts...>::type;

}  // namespace cutempl

#include "cutempl/metafunctions/any.hpp"
#include "cutempl/metafunctions/front.hpp"
#include "cutempl/metafunctions/is_empty.hpp"
#include "cutempl/metafunctions/pop_front.hpp"
