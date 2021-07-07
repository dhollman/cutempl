#pragma once

#include "cutempl/hooks/additive_identity.hpp"

#include "cutempl/utils/lambda.hpp"

#include <type_traits>

namespace cutempl {

// This type should be mostly empty to reduce instantiation cost.
template <class... Ts>
struct type_list {
  // use + for concatination (for readability; we don't want to go too
  // far with this though, since readability falls off pretty quickly for
  // just about anything else). We want this to be a hidden friend, though,
  // to reduce ADL-related costs
  template <class... Us>
  friend constexpr auto operator+(type_list, type_list<Us...>) {
    return type_list<Ts..., Us...>{};
  }

  // Use == for sameness (in the std::is_same sense)
  template <class... Us>
  friend constexpr auto operator==(type_list, type_list<Us...>) {
    return std::is_same<type_list, type_list<Us...>>{};
  }
  template <class... Us>
  friend constexpr auto operator!=(type_list, type_list<Us...>) {
    return std::negation<std::is_same<type_list, type_list<Us...>>>{};
  }

  // Save on a few calls to wrap<> in several places
  using type = type_list;
};

struct make_type_list_mfc :
  lambda_mfc<(
    []<class... Ts>(wrap<Ts>...) {
      return type_list<Ts...>{};
    }
  )> {};
template <class... Ts>
using make_type_list = typename make_type_list_mfc::template apply<Ts...>;
template <class... Ts>
using make_type_list_t = typename make_type_list<Ts...>::type;

template <auto... Vs>
using decltype_list = type_list<std::remove_const_t<decltype(Vs)>...>;

namespace hooks {

template <class... Ts>
struct additive_identity<type_list<Ts...>> {
  using type = type_list<>;
};

}  // namespace hooks

namespace short_aliases {

template <class... Ts>
using tl = type_list<Ts...>;

template <auto... Vs>
using dtl = decltype_list<Vs...>;

}  // namespace short_aliases

}  // namespace cutempl
