#pragma once

#include "cutempl/hooks/less.hpp"
#include "cutempl/hooks/additive_identity.hpp"

#include <concepts>
#include <functional>
#include <type_traits>

namespace cutempl {

// in cases where we want to use the lambda to return a value instead, we can
// do this instead as a shorthand
template <auto V>
struct wrap_value {
  using type = wrap_value;
  using value_type = decltype(V);
  static constexpr auto value = V;
  template <auto V2>
  constexpr auto operator+(wrap_value<V2>) const {
    return wrap_value<V + V2>{};
  }
  template <auto V2>
  constexpr auto operator-(wrap_value<V2>) const {
    return wrap_value<V - V2>{};
  }
  template <auto V2>
  constexpr auto operator*(wrap_value<V2>) const {
    return wrap_value<V * V2>{};
  }
  template <auto V2>
  constexpr auto operator/(wrap_value<V2>) const {
    return wrap_value<V / V2>{};
  }
  template <auto V2>
  constexpr auto operator%(wrap_value<V2>) const {
    return wrap_value<V % V2>{};
  }
};

namespace hooks {

// Customize hooks::less if the types are the same and std::less is customized
template <auto V1, decltype(V1) V2>
  requires (requires {
    { std::less<decltype(V1)>{}(V1, V2) } -> std::convertible_to<bool>;
  })
struct less<wrap_value<V1>, wrap_value<V2>>
  : std::integral_constant<bool, bool{std::less<decltype(V1)>{}(V1, V2)}> {};

// Customize hooks::less if the types are not the same and operator<() is
// defined
template <auto V1, auto V2>
  requires (
    !std::same_as<decltype(V1), decltype(V2)>
    && requires {
      { V1 < V2 } -> std::convertible_to<bool>;
    })
struct less<wrap_value<V1>, wrap_value<V2>>
  : std::integral_constant<bool, bool{V1 < V2}> {};

// Customize hooks::additive_identity to be wrap_value<0>
template <auto Value>
struct additive_identity<wrap_value<Value>> {
  using type = wrap_value<decltype(Value){0}>;
};

}  // namespace hooks

namespace short_aliases {

template <auto V>
using wv = wrap_value<V>;

}  // namespace short_aliases

namespace literals {

namespace wrap_value_literal_impl {

constexpr int recursive_power(int i, int n) {
  if (n == 0) { return 1; }
  else { return i * recursive_power(i, n-1); }
}

template <class... Chars, size_t... Idxs>
constexpr int extract_value_impl(std::index_sequence<Idxs...>,
  Chars... chars
) {
  return (
    ((chars - '0') * recursive_power(10, sizeof...(Idxs) - Idxs - 1))
      + ... + 0
  );
}

template <class MaybeSign, class... Chars>
constexpr int extract_value(MaybeSign ms, Chars... chars) {
  if (ms == '-') {
    return -1 * extract_value_impl(
      std::make_index_sequence<sizeof...(Chars)>{}, chars...);
  } else {
    return extract_value_impl(
      std::make_index_sequence<sizeof...(Chars) + 1>{}, ms, chars...);
  }
}

}  // wrap_value_literal_impl

template <char... Chars>
constexpr wrap_value<
  wrap_value_literal_impl::extract_value(Chars...)
> operator ""_wv() { return {}; }

}  // namespace literals

}  // namespace cutempl
