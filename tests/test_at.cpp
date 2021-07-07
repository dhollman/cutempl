#include "test_common.hpp"

#include "cutempl/containers/type_list.hpp"

#include "cutempl/metafunctions/at.hpp"

#include <type_traits>

using namespace cutempl;
using namespace cutempl::testing;

CUTEMPL_TEST(
  expect_same<
    at_t<2, type_list<char[1], char[2], char[3]>>,
    char[3]
  >
);

CUTEMPL_TEST(
  expect_same<
    at_t<0, type_list<char[1], char[2], char[3]>>,
    char[1]
  >
);
