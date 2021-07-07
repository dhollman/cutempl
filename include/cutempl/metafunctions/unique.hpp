#pragma once

#include "cutempl/cutempl_fwd.hpp"

#include "cutempl/containers/type_list.hpp"

#include "cutempl/utils/fold_over.hpp"
#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct unique_mfc :
  lambda_mfc<(
    []<class... Ts>(wrap<type_list<Ts...>>) {
      return (fold_over<set_insert_mfc, type_list<>>{} | ... | wrap<Ts>{});
    }
  )> {};

template <class TL>
using unique = unique_mfc::apply<TL>;
template <class TL>
using unique_t = typename unique<TL>::type;

}  // namespace cutempl

#include "cutempl/metafunctions/set_insert.hpp"
