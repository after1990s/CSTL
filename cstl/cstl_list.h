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


    iterator begin() {return node->next;}
    iterator end() {return node;}
    bool empty() const {return node->next == node->prev;}
    size_type size() const
    {
        size_type result;

        //result = distance(begin(), end());
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
        link_type n = get_node (); 
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
        erase(begin ());
    }
    void clear();
    void remove(const T & value) {

    }
    //清除数值相同的连续元素，只有“连续相同且相等的元素，才会被移除到剩余一个
    void unique() {

    }
    //将x连接到pos位置前
    void splice(iterator pos,list& x) {

    }

    //only transfer one item *i
    void splice(iterator pos, list& other, iterator i) {

    }
    void splice(iterator pos, list& other, iterator first, iterator last) {

    }
    void merge(self &other) {

    }
    void reverse() {

    }
    void sort() {
        
    }
protected:
    //将[first，last）元素移动到pos前
    void transfer(iterator pos, iterator first, iterator last) {

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
