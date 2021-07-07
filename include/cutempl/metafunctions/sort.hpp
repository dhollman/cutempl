#pragma once

#include "cutempl/containers/type_list.hpp"

#include "cutempl/hooks/less.hpp"

#include "cutempl/metafunctions/curry.hpp"
#include "cutempl/metafunctions/filter.hpp"
#include "cutempl/metafunctions/invoke.hpp"
#include "cutempl/metafunctions/negation_of.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/overloads.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

namespace sort_impl {

struct sort_function_with_default_mfc :
  lambda_mfc<(
    []<class MFC>(wrap<MFC>) {
      return lambda_mfc<(
        overloads{
          []<class... Ts>(wrap<type_list<Ts...>>) {
            return invoke_t<MFC, type_list<Ts...>, less_mfc>{};
          },
          // Default the comparator argument to hooks::less
          []<class... Ts, class Cmp>(wrap<type_list<Ts...>>, wrap<Cmp>) {
            return invoke_t<MFC, type_list<Ts...>, Cmp>{};
          }
        }
      )>{};
    }
  )> {};
template <class... Ts>
using sort_function_with_default =
  typename sort_function_with_default_mfc::template apply<Ts...>;
template <class... Ts>
using sort_function_with_default_t =
  typename sort_function_with_default<Ts...>::type;

}  // sort_impl

// All of the sorting algorithms! Because that's cuter than just one.

// Based loosely on the Cute C++ trick of the day on 2021/04/29
// https://twitter.com/The_Whole_Daisy/status/1387798831912439809?s=20
struct quicksort_mfc :
  sort_impl::sort_function_with_default_t<lambda_mfc<(
    overloads{
      []<class Pivot, class... Ts, class LessMFC>(
          wrap<type_list<Pivot, Ts...>>, wrap<LessMFC>) {
        using pivot_less_mfc = curry_t<LessMFC, Pivot>;
        return
          // Sort the elements the pivot is not less than
          invoke_t<quicksort_mfc,
            filter_t<negation_of_t<pivot_less_mfc>, type_list<Ts...>>, LessMFC>{}
          // insert the pivot in the middle
            + type_list<Pivot>{}
          // Sort the elements that the pivot is less than
            + invoke_t<quicksort_mfc,
                filter_t<pivot_less_mfc, type_list<Ts...>>, LessMFC>{};
      },
      // Base case
      []<class LessMFC>(wrap<type_list<>>, wrap<LessMFC>) {
        return type_list<>{};
      }
    }
  )>> {};
template <class... Ts>
using quicksort = typename quicksort_mfc::template apply<Ts...>;
template <class... Ts>
using quicksort_t = typename quicksort<Ts...>::type;

// Use quicksort by default
using sort_mfc = quicksort_mfc;
template <class... Ts>
using sort = typename sort_mfc::template apply<Ts...>;
template <class... Ts>
using sort_t = typename sort<Ts...>::type;

}  // namespace cutempl
