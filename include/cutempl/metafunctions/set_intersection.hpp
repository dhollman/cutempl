#pragma once

#include "cutempl/cutempl_fwd.hpp"

#include "cutempl/containers/type_list.hpp"

#include "cutempl/metafunctions/curry.hpp"
#include "cutempl/metafunctions/compose.hpp"

#include "cutempl/utils/fold_over.hpp"
#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct set_intersection_mfc :
  compose_t<unique_mfc, lambda_mfc<(
    []<class... Ts, class UL>(wrap<type_list<Ts...>>, wrap<UL>) {
      return (fold_over<
        curry_t<set_insert_if_mfc, curry_t<contains_mfc, UL>>,
        type_list<>
      >{} | ... | wrap<Ts>{});
    }
  )>> {};
template <class TL, class UL>
using set_intersection = set_intersection_mfc::apply<TL, UL>;
template <class TL, class UL>
using set_intersection_t = typename set_intersection<TL, UL>::type;

}  // namespace cutempl

#include "cutempl/metafunctions/set_insert_if.hpp"
#include "cutempl/metafunctions/contains.hpp"
#include "cutempl/metafunctions/unique.hpp"
