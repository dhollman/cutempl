#pragma once

#include "cutempl/utils/wrap.hpp"

namespace cutempl {

template <auto F>
struct value_lambda_mfc {
  template <class... Ts>
  struct apply : std::integral_constant<
    decltype(F(wrap<Ts>{}...)), F(wrap<Ts>{}...)> {};
  template <class... Ts>
  using apply_t = typename apply<Ts...>::type;
  template <class... Ts>
  static constexpr auto apply_v = apply<Ts...>::value;
};

}  // namespace cutempl
