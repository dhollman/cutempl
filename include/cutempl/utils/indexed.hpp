#pragma once

#include <cstdint>

namespace cutempl {

template <std::size_t I, class T>
struct indexed {
  static constexpr auto index = I;
  using type = T;
};

}  // namespace cutempl
