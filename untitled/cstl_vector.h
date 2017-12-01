#ifndef VECTOR_H
#define VECTOR_H
#include "cstl_alloc.h"
#include "cstl_algorithm.h"
#include <inttypes.h>

namespace CSTL {
template<class T,class Alloc = allocator<T>>
class vector
{
public:
    typedef T value_type;
    typedef value_type* pointer_type;
    typedef value_type* iterator;
    typedef value_type& reference;
    typedef uint32_t size_type;
    typedef ptrdiff_t difference_type;
protected:
    //Alloc<value_type> data_allocator;
    Alloc data_allocator;
    iterator start;
    iterator finish;
    iterator end_of_storage;

    void insert_aux(iterator pos, const T & x) {
        if (pos + 1 > end_of_storage|| end_of_storage == 0) {
            size_type origsize= finish-start;
            size_type newsize = end_of_storage - start;
            newsize = newsize * 2;
            T* newmem = data_allocator.allocate(newsize);
            uninitialized_copy(start, finish, (T*)newmem);
            data_allocator.deallocate(start, finish-start);
            start = newmem;
            end_of_storage = newmem + newsize;
            finish = newmem + origsize;
            construct(start+origsize, x);
            finish++;
        } else if (pos==finish){
            construct(pos, x);
            finish++;
        } else {

        }
    }

    void deallocate() {
        if (start) {

            data_allocator.deallocate(start, end_of_storage - start);
        }
    }
    void fill_initialize(size_type n, const T & value) {
        start = allocate_and_fill(n, value);
        finish = start + n;
        end_of_storage = finish;
    }
public:
    iterator begin() const{
        return start;
    }
    iterator end() const{
        return finish;
    }
    size_t size() const {
        return size_type(end() - bein());
    }
    size_type capacity() const{
        return size_type(end_of_storage - start);
    }
    bool empty() const {
        return begin() == end();
    }
    reference operator[] (size_type n) {
        return *(begin() + n);
    }

    vector() : start(0), finish(0), end_of_storage(0) { }
    vector(size_type n, const T & value) {
        fill_initialize (n, value);
    }
    vector(int n, const T & value) {
        fill_initialize (n, value);
    }
    vector(long n, const T & value) {
        fill_initialize (n, value);
    }
    explicit vector(size_type n) {
        fill_initialize (n, T());
    }
    ~vector() {
        destroy(start, finish);
        deallocate ();
    }
    reference fron() {
        return *begin();
    }
    reference back() {
        return *(end() -1);
    }
    void push_back(const T& x) {
        if (finish != end_of_storage) {
            construct(finish, x);
            finish++;
        } else {
            insert_aux (finish, x);            
        }
    }

    void pop_back() {
        if (empty()) {
            return;
        }
        --finish;
        destroy(finish);
    }
    //erase [first, last) elements
    iterator erase(iterator first, iterator last) {
        if (first < begin ()) {
            return first;
        }
        if (last > end()) {
            return first;
        }
        for (iterator i = first; i!=last; ++i) {
            destroy(i);
        }
        for (iterator i = first, j = last; j != end(); ++j, ++i) {
            *i = (*j); // todo: move is correct way.
            //*i = std::move(*j);
        }
        return first;
    }

    iterator erase(iterator pos) {
        if (pos + 1 != end()) {
            copy(pos + 1, finish, pos);
        }
        --finish;
        destroy(finish);
        return pos;
    }

    void resize(size_type new_size, const T & x) {
        if (new_size < size()) {
            erase (begin() + new_size, end());
        } else {
            insert(end(), new_size - size(), x);
        }
    }

    void resize(size_type new_size) {
        resize(new_size, t());
    }
    void clear() {
        erase (begin(), end());
    }
protected:
    iterator allocate_and_fill(size_type n, const T & x) {
        iterator res = data_allocator.allocate(n);
        uninitialized_fill_n(res, n, x);
        return res;
    }
};

}
#endif // VECTOR_H
