#pragma once

#include "cutempl/containers/type_list.hpp"

#include "cutempl/utils/lambda.hpp"
#include "cutempl/utils/overloads.hpp"
#include "cutempl/utils/wrap.hpp"

namespace cutempl {

struct pop_front_mfc :
  lambda_mfc<(
    overloads{
      []<class T, class... Ts>(wrap<type_list<T, Ts...>>) {
        return type_list<Ts...>{};
      },
      [](wrap<type_list<>>) {
        return type_list<>{};
      }
    }
  )> {};
template <class... Ts>
using pop_front = typename pop_front_mfc::template apply<Ts...>;
template <class... Ts>
using pop_front_t = typename pop_front<Ts...>::type;

}  // namespace cutempl
