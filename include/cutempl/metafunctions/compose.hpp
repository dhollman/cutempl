#pragma once

#include "cutempl/cutempl_fwd.hpp"

#include "cutempl/metafunctions/apply.hpp"
#include "cutempl/metafunctions/front.hpp"
#include "cutempl/metafunctions/compose.hpp"
#include "cutempl/metafunctions/invoke.hpp"

#include "cutempl/utils/fold_over.hpp"
#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/overloads.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

// A higher-order metafunction that takes an arbitrary number of metafunction
// classes and returns a metafunction class that applies the last argument, then
// applies the result of that to the second to last argument, and so on.
struct compose_mfc :
  lambda_mfc<(
    []<class... MFCs>(wrap<MFCs>...) {
      return lambda_mfc<(
        []<class... Ts>(wrap<Ts>...) {
          return front<invoke_t<
            typename fold_over<lambda_mfc<(
              []<class MFC, class TL>(wrap<MFC>, wrap<TL>) {
                return type_list<apply_t<MFC, TL>>{};
              })>, type_list<Ts...>
            >::left_mfc,
            MFCs...
          >>{};
        })>{};
    }
  )> {};

template <class... Ts>
using compose = typename compose_mfc::template apply<Ts...>;
template <class... Ts>
using compose_t = typename compose<Ts...>::type;

}  // namespace cutempl

#include "cutempl/metafunctions/front.hpp"
