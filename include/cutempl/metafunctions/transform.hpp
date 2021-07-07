#pragma once

#include "cutempl/utils/invoke.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct transform_mfc :
  lambda_mfc<(
    []<template <class...> class TL, class... Ts, class MFC>(
      wrap<TL<Ts...>>, wrap<MFC>
    ) {
      return wrap<TL<invoke_t<MFC, Ts...>>>{};
    }
  )> {};
template <class... Ts>
using transform = typename transform_mfc::template apply<Ts...>;
template <class... Ts>
using transform_t = typename transform<Ts...>::type;

}  // namespace cutempl
