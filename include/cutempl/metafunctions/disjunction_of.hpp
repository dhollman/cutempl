#pragma once

#include "cutempl/metafunctions/invoke.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

#include <type_traits>

namespace cutempl {

// Turns a unary metafunction class into a variadic metafunction class via a
// disjunction of the unary results
struct disjunction_of_mfc :
  lambda_mfc<(
    []<class MFC>(wrap<MFC>) {
      return lambda_mfc<class... Ts>(wrap<Ts>...) {
        return std::disjunction<invoke_t<MFC, Ts>...>{};
      }
    }
  )> {};
template <class... Ts>
using disjunction_of = typename disjunction_of_mfc::template apply<Ts...>;
template <class... Ts>
using disjunction_of_t = typename disjunction_of<Ts...>::type;

}  // namespace cutempl
