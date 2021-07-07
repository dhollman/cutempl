#pragma once

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct extract_type_mfc :
  lambda_mfc<(
    []<class T>(wrap<T>) { return wrap<typename T::type>{}; }
  )> {};
template <class... Ts>
using extract_type = typename extract_type_mfc::template apply<Ts...>;
template <class... Ts>
using extract_type_t = typename extract_type<Ts...>::type;

}  // namespace cutempl
