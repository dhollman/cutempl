#include "test_common.hpp"

#include "cutempl/containers/type_list.hpp"
#include "cutempl/metafunctions/reverse.hpp"

#include <type_traits>

using namespace cutempl;
using namespace cutempl::testing;

CUTEMPL_TEST(
  expect_same<
    reverse_t<type_list<char[1], char[2], char[3], char[4], void, char[6]>>,
    type_list<char[6], void, char[4], char[3], char[2], char[1]>
  >
);

CUTEMPL_TEST(
  expect_same<
    reverse_t<type_list<>>,
    type_list<>
  >
);

CUTEMPL_TEST(
  expect_same<
    reverse_t<type_list<void>>,
    type_list<void>
  >
);
