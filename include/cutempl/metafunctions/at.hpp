#pragma once

#include "cutempl/cutempl_fwd.hpp"

#include "cutempl/metafunctions/curry.hpp"
#include "cutempl/metafunctions/invoke.hpp"
#include "cutempl/metafunctions/identity.hpp"
#include "cutempl/metafunctions/just.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/overloads.hpp"
#include "cutempl/utils/wrap.hpp"
#include "cutempl/utils/wrap_value.hpp"

namespace cutempl {

struct wrapped_at_mfc :
  lambda_mfc<(
    overloads{
      []<auto Idx, class T, class... Ts>(
        wrap<wrap_value<Idx>>, wrap<type_list<T, Ts...>>
      ) {
        return typename std::conditional_t<
          (Idx == 0),
          just_t<T>,
          curry_t<wrapped_at_mfc, wrap_value<Idx-1>>
        >::template apply<type_list<Ts...>>{};
      },
      []<auto Idx, template <class...> class TL, class T, class... Ts>(
        wrap<wrap_value<Idx>>, wrap<TL<T, Ts...>>
      ) {
        return invoke<wrapped_at_mfc, wrap_value<Idx>, type_list<T, Ts...>>{};
      }
    }
  )> {};
template <class... Ts>
using wrapped_at = typename wrapped_at_mfc::template apply<Ts...>;
template <class... Ts>
using wrapped_at_t = typename wrapped_at<Ts...>::type;

template <auto Idx, class TL>
using at = wrapped_at<wrap_value<Idx>, TL>;
template <auto Idx, class TL>
using at_t = typename at<Idx, TL>::type;

}  // namespace cutempl
