#pragma once

#include "cutempl/metafunctions/compose.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

// This is inefficient, but it's so freaking cute that I couldn't resist

struct pop_back_mfc :
  compose_t<reverse_mfc, pop_front_mfc, reverse_mfc> {};
template <class... Ts>
using pop_back = typename pop_back_mfc::template apply<Ts...>;
template <class... Ts>
using pop_back_t = typename pop_back<Ts...>::type;

}  // namespace cutempl

#include "cutempl/metafunctions/pop_front.hpp"
#include "cutempl/metafunctions/reverse.hpp"
