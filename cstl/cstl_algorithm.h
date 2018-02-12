#ifndef CSTL_ALGORITHM_H
#define CSTL_ALGORITHM_H
#include <windows.h>
#include "cstl_type_traits.h"
#include "cstl_iterator.h"
#include "cstl_api.h"
namespace CSTL {

template<class InputItr, class T>
InputItr find(InputItr first, InputItr last, const T& value)
{
    for (InputItr itr = first; itr != last; itr++)
    {
        if (*itr == value)
        {
            return itr;
        }
    }
}
template<class ForwardItr, class T>
void fill(ForwardItr first, ForwardItr last, const T& value) {
    for (; first != last; ++first) {
        *first = value;
    }
}

template<class OutputItr, class Size, class T>
OutputItr fill_n(OutputItr first, Size n, const T& value) {
    for (; n > 0; n--, first++) {
        *first = value;
    }
    return first;
}


template<class InputItr, class OutputItr>
inline OutputItr copy(InputItr first, InputItr last, OutputItr res) {
    return __copy_dispatch<InputItr, OutputItr>()(first, last, res);
}

template<>
inline const char* copy(const char *first, const char * last, const char *res) {
    MoveMemory((void*)res, (void*)first, last - first);
    return res;
}


template<>
inline const wchar_t* copy(const wchar_t *first, const wchar_t * last, const wchar_t *res) {
    MoveMemory((void*)res, (void*)first, sizeof(wchar_t) * (last - first));
    return res;
}

template<>
inline const int * copy(const int *first, const int * last, const int *res) {
    MoveMemory((void*)res, (void*)first, sizeof(int) * (last - first));
    return res;
}

template<>
inline int* copy(int *first, int * last, int *res) {
    MoveMemory((void*)res, (void*)first, sizeof(int) * (last - first));
    return res;
}
template<class InputItr, class OutputItr>
struct __copy_dispatch {
    OutputItr operator ()(InputItr first, InputItr last, OutputItr res) {
        static_assert(false);
        return OutputItr();

        //return __copy(first, last, res, iterator_category(first));
    }
};

template<class T>
void swap(T& t0, T& t1) {
    T tmp = t0;
    t0 = t1;
    t1 = tmp;
}

template<class T>
void swap(T*& t0, T*& t1) {
    T* tmp = t0;
    t0 = t1;
    t1 = tmp;
}
}
#endif // CSTL_ALGORITHM_H
