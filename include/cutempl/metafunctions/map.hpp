#pragma once

#include "cutempl/metafunctions/invoke.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct map_mfc :
  lambda_mfc<(
    []<template <class... Ts> class TL, class MFC, class... Ts>(
        wrap<MFC>, wrap<TL<Ts...>>) {
      return wrap<TL<invoke_t<MFC, Ts>...>>{};
    }
  )> {};
template <class... Ts>
using map = typename map_mfc::template apply<Ts...>;
template <class... Ts>
using map_t = typename map<Ts...>::type;

}  // namespace cutempl
