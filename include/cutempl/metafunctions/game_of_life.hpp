#pragma once

#include "cutempl/cutempl_fwd.hpp"

#include "cutempl/containers/type_list.hpp"

#include "cutempl/metafunctions/apply_of.hpp"
#include "cutempl/metafunctions/at.hpp"
#include "cutempl/metafunctions/compose.hpp"
#include "cutempl/metafunctions/enumerate.hpp"
#include "cutempl/metafunctions/front.hpp"
#include "cutempl/metafunctions/just.hpp"
#include "cutempl/metafunctions/list_size.hpp"
#include "cutempl/metafunctions/map.hpp"
#include "cutempl/metafunctions/select.hpp"
#include "cutempl/metafunctions/sum.hpp"

#include "cutempl/utils/indexed.hpp"
#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/overloads.hpp"
#include "cutempl/utils/wrap.hpp"
#include "cutempl/utils/wrap_value.hpp"

namespace cutempl {

// TODO implement arbitrarily large game board

inline constexpr char game_of_life_dead_character = ' ';
inline constexpr char game_of_life_alive_character = '#';

template <class... Rows>
struct game_of_life_board {
  using type = game_of_life_board;
};

template <class... Cells>
struct game_of_life_row {
  using type = game_of_life_row;
  static constexpr auto size = sizeof...(Cells);
  // For input convenience
  template <class... Rows>
  friend constexpr auto operator,(game_of_life_board<Rows...>, game_of_life_row) {
    return game_of_life_board<Rows..., game_of_life_row>{};
  }
  template <class... OtherCells>
  friend constexpr auto operator,(game_of_life_row<OtherCells...>, game_of_life_row) {
    return game_of_life_board<game_of_life_row<OtherCells...>, game_of_life_row>{};
  }
};

template <char CellCharacter>
struct game_of_life_cell {
  static_assert(CellCharacter == game_of_life_dead_character
    || CellCharacter == game_of_life_alive_character,
    "Invalid game of life cell");
  static constexpr auto is_alive = (CellCharacter == game_of_life_alive_character);
  static constexpr auto is_dead = !is_alive;
};
using dead_cell_t = game_of_life_cell<game_of_life_dead_character>;
using alive_cell_t = game_of_life_cell<game_of_life_alive_character>;

namespace game_of_life_impl {

template <size_t N>
struct life_cell_string {
  static constexpr auto size = N;
  char data[N] = {};
  template <size_t NN>
  constexpr life_cell_string(const char(&chars)[NN]) {
    for(int i = 0; i < NN - 1; ++i) {
      data[i] = chars[i];
    }
  }
  constexpr life_cell_string(life_cell_string const&) = default;
};
template <size_t N>
life_cell_string(const char(&)[N]) -> life_cell_string<N - 1>;

struct neighbors_list_mfc :
  lambda_mfc<(
    []<class WrapRow, class WrapCol, class Board>(
      wrap<WrapRow>, wrap<WrapCol>, wrap<Board>
    ) {
      // the potential neighbors include horizontally, vertically, and
      // diagonally adjacent cells
      using namespace literals;
      using neighbor_idxs = type_list<
        decltype_list<WrapRow{} - 1_wv, WrapCol{} - 1_wv>,
        decltype_list<WrapRow{} - 1_wv, WrapCol{}>,
        decltype_list<WrapRow{} - 1_wv, WrapCol{} + 1_wv>,
        decltype_list<WrapRow{}, WrapCol{} - 1_wv>,
        decltype_list<WrapRow{}, WrapCol{} + 1_wv>,
        decltype_list<WrapRow{} + 1_wv, WrapCol{} - 1_wv>,
        decltype_list<WrapRow{} + 1_wv, WrapCol{}>,
        decltype_list<WrapRow{} + 1_wv, WrapCol{} + 1_wv>
      >;
      // wrap the index-based access into a single metafunction class that we
      // can use with `select_t` to collect the valid neighbor cells
      using lazy_get_cell_mfc =
        lambda_mfc<(
          []<class Wr, class Wc>(wrap<Wr>, wrap<Wc>) {
            return wrapped_at<Wc, wrapped_at_t<Wr, Board>>{};
          }
        )>;
      using safe_at_mfc = select_t<
        // check if the cell is over the edge so that we don't call an invalid
        // wrapped_at<>.
        lambda_mfc<([]<class Wr, class Wc>(wrap<Wr>, wrap<Wc>) {
          return wrap_value<(
            Wr::value < 0 ||
            Wc::value < 0 ||
            Wr::value >= list_size_v<Board> ||
            Wc::value >= list_size_v<front_t<Board>>
          )>{};
        })>,
        // if it is, just contribute an empty type list to the sum
        just_t<type_list<>>,
        // otherwise, get the cell and wrap it in a type_list so we can
        // contribute to the summation that makes the full neighbor list
        compose_t<make_type_list_mfc, lazy_get_cell_mfc>
      >;
      return sum<map_t<apply_of_t<safe_at_mfc>, neighbor_idxs>>{};
    }
  )> {};
template <class... Ts>
using neighbors_list = typename neighbors_list_mfc::template apply<Ts...>;
template <class... Ts>
using neighbors_list_t = typename neighbors_list<Ts...>::type;

}  // namespace game_of_life_impl

namespace literals {

template <game_of_life_impl::life_cell_string Str>
constexpr auto operator ""_life() {
  return []<size_t... Idxs>(std::index_sequence<Idxs...>) {
    return game_of_life_row<game_of_life_cell<Str.data[Idxs]>...>{};
  }(std::make_index_sequence<Str.size>{});
};

}  // namespace literals

struct game_of_life_mfc :
  lambda_mfc<(
    overloads{
      []<int Iterations, class... Rows>(
        wrap<wrap_value<Iterations>>, wrap<game_of_life_board<Rows...>>
      ) {
        // recurse, decrementing the iteration count
        return invoke<game_of_life_mfc, wrap_value<Iterations - 1>,
          // re-wrap the resulting list of in game_of_life_board<> (since map_t
          // outputs a type_list<>, and we really don't want to be generating
          // game_of_life_board<> intermediates anyway)
          apply_t<as_metafunction_class<game_of_life_board>,
            // map over rows
            map_t<lambda_mfc<(
              []<size_t RowIdx, class... Cells>(
                  wrap<indexed<RowIdx, game_of_life_row<Cells...>>>) {
                // re-wrap the resulting list of cells in game_of_life_row<>
                // (for similar reasons to the above)
                return apply<as_metafunction_class<game_of_life_row>,
                  // map over cells in the row
                  map_t<lambda_mfc<(
                    []<size_t ColIdx, class Cell>(wrap<indexed<ColIdx, Cell>>) {
                      // count the number of living neighbors
                      constexpr auto alive_count = sum_t<
                        // map to wrap_value<1> if the neighbor is alive,
                        // wrap_value<0> if it's dead. We can sum those directly
                        // since common binary operators are overloaded for
                        // wrap_value<>.
                        map_t<
                          lambda_mfc<([]<class Neighbor>(wrap<Neighbor>){
                            return wrap_value<int(Neighbor::is_alive)>{};
                          })>,
                          game_of_life_impl::neighbors_list_t<
                            wrap_value<RowIdx>, wrap_value<ColIdx>,
                            game_of_life_board<Rows...>
                          >
                        >
                      >::value;
                      // Now just follow the rules of the game to determine if
                      // the cell is alive or dead in the next generation
                      return std::conditional<
                        (
                          // Any alive cell with two or three neighbors lives
                          (Cell::is_alive && (alive_count == 2 || alive_count == 3))
                          // Any dead cell with exactly three neighbors lives
                          || (Cell::is_dead && alive_count == 3)
                          // Everything else is dead
                        ),
                        alive_cell_t, dead_cell_t>{};
                    }
                  )>, enumerate_t<type_list<Cells...>>>
                >{};
              }
            )>, enumerate_t<type_list<Rows...>>>
          >
        >{};
      },
      []<class... Rows>(
        wrap<wrap_value<0>>, wrap<game_of_life_board<Rows...>>
      ) {
        return wrap<game_of_life_board<Rows...>>{};
      }
    }
  )> {};
template <class... Ts>
using game_of_life = typename game_of_life_mfc::template apply<Ts...>;
template <class... Ts>
using game_of_life_t = typename game_of_life<Ts...>::type;

template <int Iterations, auto Board>
using make_game_of_life = game_of_life_t<wrap_value<Iterations>,
  std::remove_cvref_t<decltype(Board)>>;

}  // namespace cutempl
