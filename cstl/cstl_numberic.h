#pragma once
#include "cstl_iterator.h"
namespace CSTL {
template<class T, class InputItr>
T accumulate(InputItr first, InputItr last, T init) {
    for (InputItr i = first; i != last; i++) {
        init = init + *i;
    }
    return init;
}
}