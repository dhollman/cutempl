#pragma once

#include "cutempl/testing/result_output_helpers.hpp"

namespace cutempl::testing {

template <class T, class U>
struct expect_same {
  CUTEMPL_PREFIXED_OUTPUT_NAME(CUTEMPL_TEST_FAILURE)<
    CUTEMPL_PREFIXED_OUTPUT_NAME(EXPECTED_TYPE),
    T,
    CUTEMPL_PREFIXED_OUTPUT_NAME(TO_BE_THE_SAME_AS),
    U
  > _test_failure_see_below_for_message_ = {};
};

template <class T>
struct expect_same<T, T> { };

}  // namespace cutempl::testing
