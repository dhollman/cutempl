#pragma once

#include "cutempl/cutempl_fwd.hpp"

#include "cutempl/metafunctions/curry.hpp"
#include "cutempl/metafunctions/invoke.hpp"
#include "cutempl/metafunctions/select.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct set_insert_if_mfc :
  lambda_mfc<([]<class PredMfc, class TL, class U>(
      wrap<PredMfc>, wrap<TL>, wrap<U>) {
    return invoke<select_t<
      PredMfc, curry_t<set_insert_mfc, TL>, curry_t<identity_mfc, TL>
    >, U>{};
  })> {};
template <class TL, class U>
using set_insert_if = set_insert_if_mfc::apply<TL, U>;
template <class TL, class U>
using set_insert_if_t = typename set_insert_if<TL, U>::type;

}  // namespace cutempl

#include "cutempl/metafunctions/identity.hpp"
#include "cutempl/metafunctions/set_insert.hpp"
