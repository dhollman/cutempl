#include "test_common.hpp"

#include "cutempl/containers/type_list.hpp"
#include "cutempl/metafunctions/curry.hpp"
#include "cutempl/utils/std_type_traits.hpp"

#include <type_traits>

using namespace cutempl;
using namespace cutempl::testing;

CUTEMPL_TEST(
  expect_same<
    curry_t<stdmfc::is_same_mfc, char[3]>::apply<char[3]>::type,
    std::true_type
  >
);

CUTEMPL_TEST(
  expect_same<
    curry_t<stdmfc::is_same_mfc, char[3]>::apply<char[18]>::type,
    std::false_type
  >
);
