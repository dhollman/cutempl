#pragma once

#include "cutempl/metafunctions/invoke.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

#include <type_traits>

namespace cutempl {

// TODO there has got to be a cuter way to write this analogous to apply_of

// Turns any predicate metafunction class MFC into a predicate metafunction
// class that returns the negation of the result of applying MFC
struct negation_of_mfc :
  lambda_mfc<(
    []<class MFC>(wrap<MFC>) {
      return lambda_mfc<([]<class... Ts>(wrap<Ts>...) {
        return std::negation<invoke_t<MFC, Ts...>>{};
      })>{};
    }
  )>
  {};
template <class... Ts>
using negation_of = typename negation_of_mfc::template apply<Ts...>;
template <class... Ts>
using negation_of_t = typename negation_of<Ts...>::type;

}  // namespace cutempl
