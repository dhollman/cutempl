#pragma once

#include "cutempl/utils/as_metafunction_class.hpp"

namespace cutempl {

namespace hooks {

// Metafunction equivalent of std::less (i.e., it operates on types, not values)
// Used by things like sorting algorithms as a default.

template <class, class>
struct less;  // user customizable

}  // namespace hooks

// The rest of these aren't directly customizable
using less_mfc = as_metafunction_class<hooks::less>;
template <class T, class U>
using less_t = typename hooks::less<T, U>::type;
template <class T, class U>
static constexpr auto less_v = less_t<T, U>::value;

}  // namespace cutempl
