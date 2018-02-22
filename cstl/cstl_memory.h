#pragma once
#include "cstl_api.h"
#include "cstl_algorithm.h"
namespace CSTL {
class shared_ptr_count {
public:
    shared_ptr_count() :
        pn(nullptr)
    {
    }
    shared_ptr_count(const shared_ptr_count& count) :
        pn(count.pn)
    {
    }
    shared_ptr_count(shared_ptr_count&& count) :
        pn(count.pn)
    {
        count.pn = nullptr;
    }

    void swap(shared_ptr_count& pn) {
        CSTL::swap(this->pn, pn.pn);
    }

    long use_count() const {
        if (nullptr != pn) {
            return *pn;
        }
        return 0;
    }

    /// @brief reset pn.delete t.
    template<class T, class D>
    void reset(T *t, D *d = nullptr)
    {
        if (t != nullptr) {
            if (d != nullptr) {
                (*d)(t);
            }
            else {
                delete t;
            }
        }
        DYNCALL(InterlockedExchange64(pn, 0));
    }

    /// @brief acquire/share the ownership of the pointer, initializing the reference counter
    template<class U>
    void acquire(U* p) 
    {
        if (NULL != p)
        {
            if (NULL == pn)
            {                
                pn = new long(1); 
                if (pn == NULL) {
                    DBG_ASSERT(true);
                    DYNCALL(Sleep(INFINITE));
                }
            }
            else
            {
                DYNCALL(InterlockedIncrement(pn));
            }
        }
    }
    /// @brief release the ownership of the px pointer, destroying the object when appropriate
    template<class U, class D>
    void release(U* p, D *d = nullptr) // never throws
    {
        if (nullptr != pn)
        {
            DYNCALL(InterlockedDecrement(pn));
            if (0 == *pn)
            {
                if (d==nullptr) {
                    delete p;
                }
                else {
                    (*d)(p);
                }
                delete pn;
            }
            pn = nullptr;
        }
    }

    /// @brief release the ownership of the px pointer, destroying the object when appropriate
    template<class U, class D, int N>
    void release(U(&) p[N], D *d = nullptr)
    {
        if (0 == *pn)
        {
            if (d == nullptr) {
                delete[] p;
            }
            else {
                (*d)(p);
            }
            delete pn;
        }
        pn = nullptr;
    }
    
private:
    long *pn;
};

template<class T, class D>
class shared_ptr {
    using value_type = T;
    using deleter_type = D;
public:
    shared_ptr() : m_t(nullptr), m_d(nullptr) {
    }

    ~shared_ptr() {
        release();
    }

    explicit shared_ptr(value_type *t, deleter_type* d = nullptr) : /*m_t(t),*/ m_d(d) {
        acquire(t);
    }

    template<class U>
    shared_ptr(shared_ptr<U> &u) {
        static_assert(false, "prevent!");
    }

    template<class U>
    shared_ptr(shared_ptr<U> &&u) {
        static_assert(false, "prevent!");
        m_pn.reset(m_t, m_d);
        //m_t = static_cast<typename shared_ptr<T>::value_type*>(u.m_t);
        m_d = u.m_d;
        acquire(static_cast<typename shared_ptr<T>::value_type*>(u.m_t);
        u.m_t = nullptr;
        u.m_d = nullptr;
        u.m_pn.reset(u.m_t, u.m_d);
    }

    shared_ptr(const shared_ptr & p) :
        m_pn(p.m_pn), m_d(p.m_d) {
        DBG_ASSERT(p.use_count() != 0 && p.m_t != nullptr);
        acquire(p.m_t);
    }

    /// @brief Assignment operator using the copy-and-swap idiom (copy constructor and swap method)
    shared_ptr& operator=(const shared_ptr& ptr) throw() // never throws
    {
        shared_ptr(ptr).swap(*this);
        return *this;
    }

    inline operator bool() const {
        return 0 < m_pn.use_count();
    }

    inline long use_count() const {
        return m_pn.use_count();
    }

    inline bool unique() const {
        return 1 == use_count();
    }

    void reset() {
        release();
    }

    void reset(T *p) {
        reset();
        acquire(p);
    }

    void swap(shared_ptr &rhs) {
        CSTL::swap(m_t, rhs.m_t);
        m_pn.swap(rhs.m_pn);
    }

    inline T& operator*() const {
        DBG_ASSERT(m_t != nullptr);
        return *m_t;
    }

    inline T* operator*() const {
        DBG_ASSERT(m_t != nullptr);
        return m_t;
    }

    inline T* get() const {
        DBG_ASSERT(m_t != nullptr);
        return m_t;        
    }

private:
    /// @brief acquire/share the ownership of the px pointer, initializing the reference counter
    inline void acquire(T* p) //
    {
        pn.acquire(p); // 
        px = p; // here it is safe to acquire the ownership of the provided raw pointer, where exception cannot be thrown any more
    }
private:
    value_type *m_t;
    deleter_type *m_d;
    shared_ptr_count m_pn;
};


}//end namespace CSTL