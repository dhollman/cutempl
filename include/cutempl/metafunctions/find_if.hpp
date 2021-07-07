#pragma once

#include "cutempl/cutempl_fwd.hpp"

#include "cutempl/containers/type_list.hpp"

#include "cutempl/metafunctions/compose.hpp"
#include "cutempl/metafunctions/get_arg.hpp"
#include "cutempl/metafunctions/select.hpp"

#include "cutempl/utils/fold_over.hpp"
#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/not_a_type.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct find_if_mfc :
  lambda_mfc<(
    []<class PredMfc, class... Ts, class Default=wrap<not_a_type>>(
        wrap<PredMfc>, wrap<type_list<Ts...>>, Default dflt = {}) {
      return (fold_over<
        select_t<
          compose_t<apply_of_t<PredMfc>, pop_front_mfc, make_type_list_mfc>,
          make_get_arg<1>, make_get_arg<0>>,
          typename decltype(dflt)::type>{} | ... | wrap<Ts>{});
    }
  )> {};
template <class Mfn, class TL>
using find_if = typename find_if_mfc::template apply<Mfn, TL>;
template <class Mfn, class TL>
using find_if_t = typename find_if<Mfn, TL>::type;


}  // namespace cutempl

#include "cutempl/metafunctions/pop_front.hpp"
