#pragma once

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/indexed.hpp"
#include "cutempl/utils/wrap.hpp"

#include <utility>

namespace cutempl {

struct enumerate_mfc :
  lambda_mfc<(
    []<template <class...> class TL, class... Ts>(wrap<TL<Ts...>>) {
      return []<std::size_t... Idxs>(std::index_sequence<Idxs...>) {
        return TL<indexed<Idxs, Ts>...>{};
      }(std::index_sequence_for<Ts...>{});
    }
  )> {};
template <class TL>
using enumerate = typename enumerate_mfc::template apply<TL>;
template <class TL>
using enumerate_t = typename enumerate<TL>::type;

}  // namespace cutempl
