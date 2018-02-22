#ifndef CSTL_ALLOC_H
#define CSTL_ALLOC_H
#include <cstddef>
#include <climits>
#include "cstl_api.h"
#include "cstl_type_traits.h"


namespace CSTL {
template <class T>
inline T * _allocate(ptrdiff_t size, T*){
    //std::set_new_handler(0);//we handle alloc failed.disable default one.

    T *tmp = reinterpret_cast<T*>((operator new ((size_t)(size * sizeof(T)))));
    if (tmp == nullptr){
        //std::cerr << "out of memory" << std::endl;
        //exit(1);
        DYNCALL(Sleep(INFINITE));
    }
    return tmp;
}

template <class T>
inline void _deallocate(T *buffer){
    operator delete (buffer);
}

template<class T1, class T2>
inline void _construct(T1 *p, const T2 &value){
    new(p) T1(value);//placement new.
}


template<class T>
inline void _destroy(T* ptr){
    ptr->~T();
}

template<class T1, class T2>
inline void construct(T1 *p, const T2 &value){
    _construct(p, value);//placement new.
}

template<class T>
inline void destroy(T* ptr){
    _destroy(ptr);
}

template<class T>
inline void destroy(T* first, T* last) {
    for (; first != last; first++) {
        _destroy(first);
    }
}

//begin uninitialized_copy
template<class InputItr, class ForwardItr>
ForwardItr uninitialized_copy(InputItr first, InputItr last, ForwardItr result) {
    return __uninitialized_copy(first , last, result, value_type(first));
}

template<class InputItr, class ForwardItr,class T1>
ForwardItr __uninitialized_copy(InputItr first, InputItr last, ForwardItr result, T1) {
    typedef typename __type_traits<T1>::is_POD_type is_POD;
    return __uninitialized_copy_aux(first, last, result, is_POD());
}

template<class InputItr, class ForwardItr,class T1>
ForwardItr __uninitialized_copy(InputItr first, InputItr last, ForwardItr result, T1*) {
    typedef typename __type_traits<T1>::is_POD_type is_POD;
    return __uninitialized_copy_aux(first, last, result, is_POD());
}

template<class InputItr, class ForwardItr>
inline ForwardItr __uninitialized_copy_aux(InputItr first, InputItr last, ForwardItr result, __false_type) {
    InputItr cur = first;
    for (; cur != last; ++cur, ++result) {
        _construct(result, *cur);
    }
    return cur;
}

template<class InputItr, class ForwardItr>
inline ForwardItr __uninitialized_copy_aux(InputItr first, InputItr last, ForwardItr result, __true_type) {
     copy(first, last, result);
     return result;
}

template<class InputItr, class ForwardItr>
inline ForwardItr __uninitialized_copy_aux(const char* fist, const char* last, char * result) {
    //memmove_s(first, last-first, result, last-first);
    DYNCALL(MoveMemory(first, result, last - first));

    return result + (last-first);
}

template<class InputItr, class ForwardItr>
inline ForwardItr __uninitialized_copy_aux(const wchar_t* fist, const wchar_t* last, wchar_t * result) {
    //memmove_s(first, last-first, result, last-first);
    DYNCALL(MoveMemory(first, result, (last - first) * sizeof(wchar_t)));
    return result + (last-first);
}
//end uninitialized_copy
//begin uninitialized_fill_n
template <class ForwardItr, class Size, class T>
inline ForwardItr uninitialized_fill_n(ForwardItr first, Size n, const T & x) {
    return __uninitialized_fill_n(first, n, x, value_type(first));
}

template <class ForwardItr, class Size, class T, class T1>
inline ForwardItr __uninitialized_fill_n(ForwardItr first, Size n, const T& x, T1*) {
    typedef typename __type_traits<T1>::is_POD_type is_POD;
    return __uninitialized_fill_n_aux(first, n, x, is_POD());
}

template <class ForwardItr, class Size, class T>
ForwardItr __uninitialized_fill_n_aux(ForwardItr first, Size n, const T& x, __true_type) {
    return fill_n(first, n, x);
}

template <class ForwardItr, class Size, class T>
ForwardItr __uninitialized_fill_n_aux(ForwardItr first, Size n, const T& x, __false_type) {
    ForwardItr cur = first;
    for (; n>0; --n, ++cur) {
        _construct(&*cur, x);
    }
    return cur;
}
//end uninitialized_fill_n


//begin uninitialized_fill
template <class ForwardItr, class Size, class T>
inline ForwardItr uninitialized_fill(ForwardItr first, ForwardItr last, const T & x) {
    return __uninitialized_fill(first, last, x, value_type(first));
}

template <class ForwardItr, class Size, class T, class T1>
inline ForwardItr __uninitialized_fill(ForwardItr first, ForwardItr last, const T& x, T1*) {
    typedef typename __type_traits<T1>::is_POD_type is_POD;
    return __uninitialized_fill_aux(first, last, x, is_POD());
}

template <class ForwardItr, class Size, class T>
ForwardItr __uninitialized_fill_aux(ForwardItr first, ForwardItr last, const T& x, __true_type) {
    return fill(first, last, x);
}

template <class ForwardItr, class Size, class T>
ForwardItr __uninitialized_fill_aux(ForwardItr first, ForwardItr last, const T& x, __false_type) {
    ForwardItr cur = first;
    for (; cur != last; ++cur) {
        _construct(&*cur, x);
    }
    return cur;
}
//end uninitialized_fill

template <class T>
class allocator{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    template<class U>
    struct rebind{//???
        typedef allocator<U> other;
    };

    pointer  allocate(size_type n, const void * hint = 0){
        hint=hint;
        return _allocate((difference_type)n, (pointer)0);
    }

    void deallocate(pointer p, size_type n){
        n=n;
        _deallocate(p);
    }

    void construct(pointer p, const T& value){
        _construct(p, value);
    }

    void destroy(pointer p){
        _destroy(p);
    }

    pointer address(reference x){
        return (pointer) &x;
    }
    size_type max_size() const{
        return size_type(UINT_MAX/ sizeof(T));
    }
};
}
#endif // CSTL_ALLOC_H
