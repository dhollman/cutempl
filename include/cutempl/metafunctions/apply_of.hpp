#pragma once

#include "cutempl/cutempl_fwd.hpp"

#include "cutempl/metafunctions/curry.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct apply_of_mfc : curry_t<curry_mfc, apply_mfc> {};
template <class... Ts>
using apply_of = typename apply_of_mfc::template apply<Ts...>;
template <class... Ts>
using apply_of_t = typename apply_of<Ts...>::type;

}  // namespace cutempl

#include "cutempl/metafunctions/apply.hpp"
