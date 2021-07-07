#pragma once

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct contains_mfc :
  lambda_mfc<(
    []<class... Ts, class U>(wrap<type_list<Ts...>>, wrap<U>) {
      return std::disjunction<std::is_same<Ts, U>...>{};
    }
  )> {};
template <class TL, class U>
using contains = contains_mfc::apply<TL, U>;
template <class TL, class U>
using contains_t = typename contains<TL, U>::type;
template <class TL, class U>
inline constexpr auto contains_v = contains<TL, U>::value;

}  // namespace cutempl
