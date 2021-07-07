#include "test_common.hpp"

#include "cutempl/containers/type_list.hpp"
#include "cutempl/metafunctions/game_of_life.hpp"
#include "cutempl/utils/std_type_traits.hpp"

#include <type_traits>

using namespace cutempl;
using namespace cutempl::testing;
using namespace cutempl::literals;

// Block is stable
CUTEMPL_TEST(
  expect_same<
    make_game_of_life<
      2,  // iterations
      (
        "    "_life,
        " ## "_life,
        " ## "_life,
        "    "_life
      )
    >,
    decltype((
      "    "_life,
      " ## "_life,
      " ## "_life,
      "    "_life
    ))
  >
);

// Toad oscillates
CUTEMPL_TEST(
  expect_same<
    make_game_of_life<
      1,  // iterations
      (
        "    "_life,
        " ###"_life,
        "### "_life,
        "    "_life
      )
    >,
    decltype((
      "  # "_life,
      "#  #"_life,
      "#  #"_life,
      " #  "_life
    ))
  >
);

CUTEMPL_TEST(
  expect_same<
    make_game_of_life<
      2,  // iterations
      (
        "    "_life,
        " ###"_life,
        "### "_life,
        "    "_life
      )
    >,
    decltype((
      "    "_life,
      " ###"_life,
      "### "_life,
      "    "_life
    ))
  >
);

CUTEMPL_TEST(
  expect_same<
    make_game_of_life<
      3,  // iterations
      (
        "    "_life,
        " ###"_life,
        "### "_life,
        "    "_life
      )
    >,
    decltype((
      "  # "_life,
      "#  #"_life,
      "#  #"_life,
      " #  "_life
    ))
  >
);

// R-pentomino
CUTEMPL_TEST(
  expect_same<
    make_game_of_life<
      6,  // iterations
      (
        "     "_life,
        "  ## "_life,
        " ##  "_life,
        "  #  "_life
      )
    >,
    decltype((
      " ### "_life,
      "## ##"_life,
      "#  ##"_life,
      " ##  "_life
    ))
  >
);
