#pragma once

#include "cutempl/utils/value_lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct is_empty_mfc :
  value_lambda_mfc<(
    []<template <class...> class TL, class... Ts>(wrap<TL<Ts...>>) {
      return sizeof...(Ts) == 0;
    }
  )> {};
template <class... Ts>
using is_empty = typename is_empty_mfc::template apply<Ts...>;
template <class... Ts>
using is_empty_t = typename is_empty<Ts...>::type;
template <class... Ts>
inline constexpr auto is_empty_v = is_empty<Ts...>::value;

}  // namespace cutempl
