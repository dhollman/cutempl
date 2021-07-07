#pragma once

#include "cutempl/utils/as_metafunction_class.hpp"
#include "cutempl/utils/wrap.hpp"

#include <type_traits>
#include <utility>  // declval

namespace cutempl {

namespace hooks {

// Identity type for operator+(). When partially specialized,
// Used by things like the sum algorithm as a default. This customization
// point is intended to make the following expression `true` for all `T` where
// `additive_identity` is specialized:
//
// ```
//   std::is_same_v<
//     std::remove_const_t<decltype(
//       std::declval<typename additive_identity<T>::type>() + std::declval<T>()
//     )>, T
//   >
// ```

template <class>
struct additive_identity;  // user customizable

}  // namespace hooks

// The rest of these aren't directly customizable
using additive_identity_mfc = as_metafunction_class<hooks::additive_identity>;
template <class T>
using additive_identity_t = typename hooks::additive_identity<T>::type;

struct common_additive_identity_mfc :
  lambda_mfc<(
    []<class T, class... Ts>(wrap<T>, wrap<Ts>...) {
      return wrap<std::remove_const_t<decltype(
        (std::declval<additive_identity_t<T>>() + ... +
          std::declval<additive_identity_t<Ts>>())
      )>>{};
    }
  )> {};
template <class... Ts>
using common_additive_identity = typename common_additive_identity_mfc::template apply<Ts...>;
template <class... Ts>
using common_additive_identity_t = typename common_additive_identity<Ts...>::type;


}  // namespace cutempl
