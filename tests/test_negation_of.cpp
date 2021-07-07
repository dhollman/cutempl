#include "test_common.hpp"

#include "cutempl/containers/type_list.hpp"
#include "cutempl/metafunctions/negation_of.hpp"
#include "cutempl/utils/std_type_traits.hpp"

#include <type_traits>

using namespace cutempl;
using namespace cutempl::testing;


CUTEMPL_TEST(
  expect_same<
    typename negation_of_t<
      stdmfc::is_scalar_mfc
    >::apply<int>::type,
    std::false_type
  >
);
