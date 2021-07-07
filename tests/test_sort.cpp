#include "test_common.hpp"

#include "cutempl/containers/type_list.hpp"
#include "cutempl/metafunctions/sort.hpp"
#include "cutempl/utils/wrap_value.hpp"

#include <type_traits>

using namespace cutempl;
using namespace cutempl::testing;
using namespace cutempl::literals;

CUTEMPL_TEST(
  expect_same<
    quicksort_t<decltype_list<3_wv, 14_wv, 15_wv, 2_wv, 6_wv>>,
    decltype_list<2_wv, 3_wv, 6_wv, 14_wv, 15_wv>
  >
);
