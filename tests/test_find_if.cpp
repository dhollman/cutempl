#include "test_common.hpp"

#include "cutempl/containers/type_list.hpp"
#include "cutempl/metafunctions/find_if.hpp"
#include "cutempl/utils/std_type_traits.hpp"

#include <type_traits>

using namespace cutempl;
using namespace cutempl::testing;

CUTEMPL_TEST(
  expect_same<
    find_if_t<
      curry_t<stdmfc::is_same_mfc, char[3]>,
      type_list<char[0], char[1], char[2], char[3], char[4]>
    >,
    char[3]
  >
);
