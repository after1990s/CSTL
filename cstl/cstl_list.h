#ifndef CSTL_LIST_H
#define CSTL_LIST_H
#include "cstl_alloc.h"
#include "cstl_iterator.h"
namespace CSTL {

template<class T>
struct __list_node{
    typedef __list_node* __list_node_pointer;
    __list_node_pointer prev;
    __list_node_pointer next;
    T data;
};

template<class T, class Ref, class Ptr>
struct __list_iterator{
    typedef __list_iterator<T, T&, T*> iterator;
    typedef __list_iterator<T, Ref, Ptr> self;

    typedef bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef __list_node<T>* link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef __false_type is_POD_type;
    link_type node;

    __list_iterator(link_type x) : node (x) {}
    __list_iterator() {}
    __list_iterator(const __list_iterator &x) : node(x.node){}

    bool operator== (const self &x) const {return node == x.node;}
    bool operator!= (const self &x) const {return node != x.node;}

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

template<class T, class Alloc = allocator<__list_node<T>>>
class list
{
protected:
    typedef __list_node<T> list_node;
    typedef T& reference;
    typedef const T& const_reference;
    typedef __list_iterator<T, T&, Alloc> iterator;
    typedef unsigned int size_type;
    typedef list<T, Alloc> self;
    Alloc data_allocator;
public:
    typedef list_node* link_type;

    list() { empty_init(); }


    iterator begin() const {return node->next;}
    iterator end() const  {return node;}
    bool empty() const {return node->next == node->prev;}
    size_type size() const
    {
        size_type result;
        iterator b = begin();
        iterator e = end();
        result = distance(b,e);
        return result;
    }

    const_reference back() const {
        *node->prev;
    }
    reference back() {
        *node->prev;
    }
    const_reference front() const {
        *node->next;
    }
    reference front() {
        *node->next;
    }
    //在 pos 前插入 value
    iterator insert(iterator pos, const_reference value) {
        link_type n = get_node();
        link_type prev = pos.node->prev;

        n->next = pos.node;
        n->prev = prev;
        prev->next = n;
        pos.node->prev = n;

        (n->data) = value;
        return __list_iterator<T, T&, Alloc>(n);
    }

    void push_back(const_reference value) {
        insert(iterator(node), value);
    }

    void push_front(const_reference value) {
        node->next = insert(iterator(node->next), value).node;

    }

    //返回擦除的项目后一项的itr或者end()
    iterator erase(iterator pos) {
        if (pos == end()) {
            return end();
        }
        /*
        if (pos == begin()) {
            node->next = pos.node->next;
        } else {

        }*/
        link_type next = pos.node->next;
        link_type prev = pos.node->prev;

        next->prev = prev;
        prev->next = next;

        put_node(pos.node);
        return iterator(next);
    }
    //前闭后开区间, return (last).
    iterator erase(iterator first, iterator last) {
        if (first == last) {
            return first;
        }
        link_type prev = first.node->prev;
        link_type next = last.node;

        prev->next = next;
        next->prev = prev;

        for (iterator itr = first; itr != last; itr++) {
            data_allocator.destroy(itr.node->data);
            put_node(itr.node);
        }
    }
    void pop_back() {
        erase(--end());
    }

    void pop_front() {
        erase(begin());
    }
    void clear() {
        erase(begin(), end());
    }
    
    void remove(const T & value) {
        for (iterator itr = begin(); itr != end(); )
        {
            iterator next = itr;
            next++;
            if (itr.node->data == value)
            {
                erase(itr);
            }
            itr = next;
        }
    }
    //清除数值相同的连续元素，只有“连续相同且相等的元素，才会被移除到剩余一个
    void unique() {
        if (size() < 1)
        {
            return;
        }
        for (iterator itr = begin(); itr != --end(); itr++)
        {
            iterator itr_n = itr;
            itr_n++;
            if (*itr_n == *itr)
            {
                erase(itr_n);
            }
        }
    }
    //将x连接到pos位置前
    void splice(iterator pos,list& x) {
        transfer(pos, x.begin(), x.end());
    }

    //only transfer one item *i
    void splice(iterator pos, list&, iterator i) {
        iterator j = i;
        j++;
        transfer(pos, i, j);
    }

    void splice(iterator pos, list&, iterator first, iterator last) {
        if (first != last) {
            transfer(pos, first, last);
        }
    }
    void merge(self &other) {
        transfer(end(), other.begin(), other.end());
    }
    void reverse() {
        if (size() == 0 || size() == 1) {
            return;
        }
        iterator first = begin();
        while (first != end())
        {
            iterator second = first.node->next;
            ++first;
            transfer(begin(), second, first);
        }

    }
    void swap(self &other)
    {
        if (this == &other) {
            return;
        }
        if (size() == 0 && other.size() == 0) {
            return;
        }
        CSTL::swap(node, other.node);
        //->prevCSTL::swap(node->next, other.node->next);
    }

    void sort() {
        static_assert(false);
    }
protected:
    //将[first，last）元素移动到pos前
    void transfer(iterator pos, iterator first, iterator last) {
        if (pos != end())
        {
            link_type begin = first.node->prev;
            link_type end = last;

            begin->next = end;
            end->prev = begin;

            link_type pos_begin = pos.node->prev;
            link_type pos_end = pos.node->next;

            first.node.prev = pos_begin;
            pos_begin->next = first;
            last.node.prev = pos.node;
            pos.node->next = last.node;
        }
    }
    link_type get_node()
    {
        return reinterpret_cast<link_type>(data_allocator.allocate(sizeof(list_node)));
    }
    void put_node(link_type p)
    {
        data_allocator.deallocate(p, 0);
    }
    void empty_init()
    {
        node = get_node();
        node->next = node;
        node->prev = node;
    }
    link_type create_node(const T& x)
    {
        link_type p = get_node();
        p->data = x;
        data_allocator.construct(&p->data, x);
        return p;
    }

    void destroy_node(link_type p) {
        data_allocator.destroy(&p->data);
        put_node(p);
    }
protected:
    link_type node;
};
}

#endif // CSTL_LIST_H
