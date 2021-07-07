#pragma once

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

// TODO default value version of front

struct front_mfc :
  lambda_mfc<(
    []<template <class...> class TL, class T, class... Ts>(wrap<TL<T, Ts...>>) {
      return wrap<T>{};
    }
  )> {};
template <class... Ts>
using front = typename front_mfc::template apply<Ts...>;
template <class... Ts>
using front_t = typename front<Ts...>::type;


}  // namespace cutempl
