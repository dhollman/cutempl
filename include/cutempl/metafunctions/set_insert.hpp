#pragma once

#include "cutempl/cutempl_fwd.hpp"

#include "cutempl/metafunctions/select.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct set_insert_mfc :
  select_t<contains_mfc, identity_mfc, append_mfc> {};
template <class TL, class U>
using set_insert = set_insert_mfc::apply<TL, U>;
template <class TL, class U>
using set_insert_t = typename set_insert<TL, U>::type;

}  // namespace cutempl

#include "cutempl/metafunctions/append.hpp"
#include "cutempl/metafunctions/contains.hpp"
#include "cutempl/metafunctions/identity.hpp"
