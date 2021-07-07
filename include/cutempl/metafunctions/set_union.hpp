#pragma once

#include "cutempl/cutempl_fwd.hpp"

#include "cutempl/metafunctions/unique.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct set_union_mfc :
  lambda_mfc<(
    []<class TL, class... Us>(wrap<TL>, wrap<type_list<Us...>>) {
      return (fold_over<set_insert_mfc, unique_t<TL>>{} | ... | wrap<Us>{});
    }
  )> {};
template <class TL, class UL>
using set_union = set_union_mfc::apply<TL, UL>;
template <class TL, class UL>
using set_union_t = typename set_union<TL, UL>::type;

}  // namespace cutempl

#include "cutempl/metafunctions/set_insert.hpp"
