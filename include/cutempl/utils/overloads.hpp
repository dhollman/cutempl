#pragma once

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

// a really useful helper for combining multiple overloads into one function for
// use with things like the lambda_mfc helper (but also just useful in general)
template <class... Callables>
struct overloads : Callables... {
  using Callables::operator()...;
};
template <class... Callables> overloads(Callables...) -> overloads<Callables...>;

}  // namespace cutempl
