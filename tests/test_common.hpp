#pragma once

#include "cutempl/cutempl_testing.hpp"

#include <type_traits>

#pragma once

#define CUTEMPL_PP_CAT_IMPL(x, y) x ## y
#define CUTEMPL_PP_CAT(x, y) CUTEMPL_PP_CAT_IMPL(x, y)
#define CUTEMPL_TEST(...) \
  __VA_ARGS__ CUTEMPL_PP_CAT(test_failure_at_line_, __LINE__) = {};

// All tests need a main so that they'll link
int main() { }
