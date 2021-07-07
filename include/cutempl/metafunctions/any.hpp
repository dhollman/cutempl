#pragma once

#include "cutempl/metafunctions/apply_of.hpp"

#include "cutempl/utils/as_metafunction_class.hpp"
#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

#include <type_traits>

namespace cutempl {

struct any_mfc : apply_of_t<as_metafunction_class<std::disjunction>> {};
template <class... Ts>
using any = typename any_mfc::template apply<Ts...>;
template <class... Ts>
using any_t = typename any<Ts...>::type;

}  // namespace cutempl
