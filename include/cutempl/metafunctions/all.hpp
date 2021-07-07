#pragma once

#include "cutempl/metafunctions/apply_of.hpp"

#include "cutempl/utils/as_metafunction_class.hpp"
#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

#include <type_traits>

namespace cutempl {

struct all_mfc : apply_of_t<as_metafunction_class<std::conjunction>> {};
template <class... Ts>
using all = typename all_mfc::template apply<Ts...>;
template <class... Ts>
using all_t = typename all<Ts...>::type;

}  // namespace cutempl
