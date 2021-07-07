#pragma once

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct push_back_mfc :
  lambda_mfc<(
    []<template <class...> class TL, class... Ts, class... Us>(
        wrap<TL<Ts...>, wrap<Us>...) {
      return wrap<TL<Ts..., Us...>>{};
    }
  )> {};
template <class... Ts>
using push_back = typename push_back_mfc::template apply<Ts...>;
template <class... Ts>
using push_back_t = typename push_back<Ts...>::type;

}  // namespace cutempl
