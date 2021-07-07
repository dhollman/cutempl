#pragma once

#include "cutempl/metafunctions/invoke.hpp"

#include "cutempl/utils/as_metafunction_class.hpp"
#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

#include <type_traits>

namespace cutempl {

// TODO there has got to be a cuter way to write this analogous to apply_of

// Turns a unary metafunction class into a variadic metafunction class via a
// conjunction of the unary results
struct conjunction_of_mfc :
  lambda_mfc<(
    []<class MFC>(wrap<MFC>) {
      return lambda_mfc<
        []<class... Ts>(wrap<Ts>...) {
          return std::conjunction<invoke_t<MFC, Ts>...>{};
        }
      >{};
    }
  )> {};
template <class... Ts>
using conjunction_of = typename conjunction_of_mfc::template apply<Ts...>;
template <class... Ts>
using conjunction_of_t = typename conjunction_of<Ts...>::type;

}  // namespace cutempl
