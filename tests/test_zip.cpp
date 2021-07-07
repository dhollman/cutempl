#include "test_common.hpp"

#include "cutempl/containers/type_list.hpp"
#include "cutempl/metafunctions/zip.hpp"

#include <type_traits>

using namespace cutempl;
using namespace cutempl::testing;

CUTEMPL_TEST(
  expect_same<
    zip_t<type_list<int, float, double>, type_list<int, char[1], char[3]>>,
    type_list<
      type_list<int, int>, type_list<float, char[1]>, type_list<double, char[3]>
    >
  >
);

CUTEMPL_TEST(
  expect_same<
    zip_t<type_list<>, type_list<>, type_list<>, type_list<>>,
    type_list<>
  >
);

CUTEMPL_TEST(
  expect_same<
    zip_t<
      type_list<char[1], char[2], char[3]>,
      type_list<char[4], char[5], char[6]>,
      type_list<char[7], char[8], char[9]>
    >,
    type_list<
      type_list<char[1], char[4], char[7]>,
      type_list<char[2], char[5], char[8]>,
      type_list<char[3], char[6], char[9]>
    >
  >
);

CUTEMPL_TEST(
  expect_same<
    zip_t<
      type_list<char[1], char[2], char[3]>,
      type_list<char[4], char[5]>
    >,
    type_list<
      type_list<char[1], char[4]>,
      type_list<char[2], char[5]>
    >
  >
);
