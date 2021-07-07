#pragma once

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct identity_mfc :
  lambda_mfc<([](auto wrapped) { return wrapped; })> {};
template <class T>
using identity = identity_mfc::apply<T>;
template <class T>
using identity_t = typename identity<T>::type;

}  // namespace cutempl
