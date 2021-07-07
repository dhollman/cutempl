#pragma once

// Note: most of these aren't in a namespace to reduce verbosity of the test
// failure output.

// Since multiple underscores aren't standard, we provide a way to opt out of it
// (but a bunch of underscores is easier to find in the compiler output, so
// that's the default)
#ifndef CUTEMPL_PREFIXED_OUTPUT_NAME
#define CUTEMPL_PREFIXED_OUTPUT_NAME(name) /* SEE ABOVE FOR MESSAGE */ ____##name##____
#endif

// all of these are intentionally not defined
template <class...>
struct CUTEMPL_PREFIXED_OUTPUT_NAME(CUTEMPL_TEST_FAILURE);

struct CUTEMPL_PREFIXED_OUTPUT_NAME(EXPECTED_TYPE) {};

struct CUTEMPL_PREFIXED_OUTPUT_NAME(TO_BE_THE_SAME_AS) {};
