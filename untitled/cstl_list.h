#ifndef CSTL_LIST_H
#define CSTL_LIST_H
#include "cstl_iterator.h"
namespace cstl {

template<class T>
struct __list_node{
    typedef void* void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};

template<class T, class Ref, class Ptr>
struct __list_iterator{
    typedef __list_iterator<T, T&, T*> iterator;
    typedef __list_iterator<T, Ref, Ptr> self;

    typedef bidirectional_iterator_tag iterator_category;
    typedef T type_value;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef __list_node<T>* link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    link_type node;

    __list_iterator(link_type x) : node (x) {}
    __list_iterator() {}
    __list_iterator(const __list_iterator &x) : node(x.node){}

    bool operator== (const self &x) {return node == x.node;}
    bool operator!= (const self &x) {return node != x.node;}

    reference operator *() const { return (*node).data;}
    pointer operator->() const {return &(operator *());} // return ref of data.
    self& operator++() {
        node = (link_type)(node->next);
        return *this;
    }
    self operator++(int){
        self tmp = *this;
        ++(*this);
        return tmp;
    }
    self& operator--() {
        node = (link_type)(node->prev);
        return *this;
    }
    self operator --(int) {
        self tmp = *this;
        --*this;
        return tmp;
    }


};

//
class list
{
public:
    list();
};
}

#endif // CSTL_LIST_H
