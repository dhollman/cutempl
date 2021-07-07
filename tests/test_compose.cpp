#include "test_common.hpp"

#include "cutempl/containers/type_list.hpp"
#include "cutempl/metafunctions/compose.hpp"
#include "cutempl/utils/std_type_traits.hpp"

#include <type_traits>

using namespace cutempl;
using namespace cutempl::testing;


CUTEMPL_TEST(
  expect_same<
    typename compose_t<
      stdmfc::add_lvalue_reference_mfc,
      stdmfc::add_const_mfc,
      stdmfc::remove_extent_mfc
    >::apply<int[3]>::type,
    int const&
  >
);

CUTEMPL_TEST(
  expect_same<
    typename compose_t<
      stdmfc::remove_extent_mfc
    >::apply<int[3]>::type,
    int
  >
);
