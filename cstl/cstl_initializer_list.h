#pragma once
#include <inttypes.h>
namespace CSTL {

template <class T>
class initializer_list
{
public:
    typedef T value_type;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef T* pointer_type;
    typedef T& reference;
    typedef uint32_t size_type;

    constexpr initializer_list() : m_Ptr(nullptr), m_size(0) {

    }
    constexpr initializer_list(const pointer_type begin, const pointer_type end) :
        m_ptr_begin(begin), m_ptr_end(end) {

    }
    constexpr size_type size() const {
        return (size_t)(m_ptr_end - m_ptr_begin);
    }
    constexpr const_iterator begin() const {
        return m_ptr_begin;
    }
    constexpr const_iterator end() const {
        return m_ptr_end;
    }

private:
    T * m_ptr_begin;
    T * m_ptr_end;;
};
}