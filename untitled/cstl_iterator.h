#ifndef CSTL_ITERATOR_H
#define CSTL_ITERATOR_H
#include <cstddef>
namespace CSTL {
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag: public input_iterator_tag {};
struct bidirectional_iterator_tag: public forward_iterator_tag {};
struct random_access_iterator_tag: public bidirectional_iterator_tag {};

template <class C, class T, class D = ptrdiff_t, class P = T*, class R = T&>
struct iterator {
    typedef C iterator_category;
    typedef T value_type;
    typedef D difference_type;
    typedef P pointer;
    typedef R reference;
};

template <class T>
struct iterator_traits{
    typedef typename T::iterator_category iterator_category;
    typedef typename T::value_type value_type;
    typedef typename T::difference_type difference_type; //count():
    typedef typename T::pointer pointer;
    typedef typename T::reference reference;
};

template <class T>
struct iterator_traits<T*>{
    typedef typename random_access_iterator_tag iterator_category;
    typedef typename T::value_type value_type;
    typedef typename ptrdiff_t difference_type;
    typedef typename T* pointer;
    typedef typename T& reference;
};

template <class T>
struct iterator_traits<const T*>{
    typedef typename random_access_iterator_tag iterator_category;
    typedef typename T::value_type value_type;
    typedef typename T::difference_type difference_type;
    typedef typename T* pointer;
    typedef typename T& reference;
};

//begin advance.将itr前进/后退n次， inputitr禁止n为负数
template<class InputItr, class Distance>
inline void __advance(InputItr& i, Distance n, input_iterator_tag) {
    static_assert ( n>= 0, "input itr n < 0");
    while (n--) i++;
}
template<class InputItr, class Distance>
inline void __advance(InputItr& i, Distance n, bidirectional_iterator_tag) {
    if (n >= 0)
        while (n--) i++;
    else
        while (n++) i--;
}
template<class InputItr, class Distance>
inline void __advance(InputItr& i, Distance n, random_access_iterator_tag) {
    i = i + n;
}

template<class InputItr, class Distance>
inline void advance(InputItr& i, Distance n) {
    __advance(i, n, iterator_traits<InputItr>::iterator_category());
}
//end advance
//begin distance
template<class InputItr>
inline typename iterator_traits<InputItr>::difference_type
__distance(InputItr first, InputItr last, random_access_iterator_tag) {
    typedef typename iterator_traits<InputItr>::difference_type difference_type;
    difference_type n = last - first;
    return n;
}
template<class InputItr>
inline typename iterator_traits<InputItr>::difference_type
__distance(InputItr first, InputItr last, input_iterator_tag) {
    typedef typename iterator_traits<InputItr>::difference_type difference_type;
    difference_type n = 0;
    while (first != last) {
        first++;
        n++;
    }
    return n;
}

template<class InputItr>
inline typename iterator_traits<InputItr>::difference_type
distance(InputItr first, InputItr last) {
    typedef typename iterator_traits<InputItr>::iterator_category category;
    return __distance(first, last, category());
}
//end distance

}
#endif // CSTL_ITERATOR_H
