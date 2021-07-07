#pragma once

#include "cutempl/cutempl_fwd.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct list_size_mfc :
  lambda_mfc<(
    []<template <class...> class TL, class... Ts>(wrap<TL<Ts...>>) {
      return wrap_value<sizeof...(Ts)>{};
    }
  )> {};
template <class... Ts>
using list_size = typename list_size_mfc::template apply<Ts...>;
template <class... Ts>
using list_size_t = typename list_size<Ts...>::type;
template <class... Ts>
inline constexpr auto list_size_v = list_size<Ts...>::type::value;

}  // namespace cutempl
