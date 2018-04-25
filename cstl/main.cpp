#include "t.h"
#include <initializer_list>
#include "cstl_vector.h"
#include "cstl_list.h"
#include "cstl_memory.h"
class K{
public:
    K(int i): m_i(i){}
    K(const K& k) : m_i(k.m_i){}
    ~K(){
        //4std::cout << m_i << " ";
    }
    int m_i;
};
class A {
public:
    A() : m_i(0) {

    }
    int add() const & {
        return m_i + 1;
    }
    int add() && {
        return m_i + 2;
    }
private:
    int m_i;
};
#include <memory>
#include <iostream>

template<class T>
void is_array(T) {
    std::cout << "not array";
}


template<class T, int N>
void is_array(T(&)[N]) {
    std::cout << "array";
}

int main(int argc, char* argv[])
{
    A a;
    printf("%d\n", a.add());
    printf("%d\n", std::move(a).add());
    CSTL::shared_ptr<int> ct0(new int(7));
    auto ct1 = ct0;
    std::cout << ct1.use_count() << std::endl;
    int k0 = 1;
    int k[] = { 1,2,3 };
    is_array(k0);
    is_array(k);
    std::shared_ptr<int> s0(new int);
    std::shared_ptr<int> s1(new int);
    std::cout << s0.get() << std::endl;
    std::cout << s1.get() << std::endl;

    s1 = s0;

    std::cout << s0.get() << std::endl;
    std::cout << s1.get() << std::endl;
    CSTL::vector<K> t0;
    int u, u1;
    t0.push_back(K(1));
    t0.push_back(K(2));
    t0.push_back(K(3));
    t0.push_back(K(4));
    t0.push_back(K(5));
    t0.push_back(K(6));
    t0.push_back(K(7));
    //CSTL::vector<int> k1 = { 0,1,2,34,5,6 };
    //auto k0 = { 0,1,2,3,4,5 };
    
    //std::cout << traits(1, int());
    /*

    CSTL::vector<K>::iterator itr_begin = t0.begin ();
    CSTL::vector<K>::iterator itr_end = itr_begin + 3;
    t0.erase (itr_begin, itr_end);
    CSTL::vector<int> t1;
    t1.push_back (0);
    t1.push_back (2);
    t1.push_back (3);
    t1.pop_back ();
    //t1.erase (0);//not prevent at complied time.
    int k;
    CSTL::list<int> l0;
    l0.push_back (1);
    l0.push_back (2);
    l0.push_back (3);
    l0.push_back (4);
    l0.push_front(0);
    l0.push_front(-1);
    l0.push_front(-2);
    l0.pop_back ();
    l0.pop_back ();
    for (auto i = l0.begin (); i != l0.end (); i++) {
        std::cout << *i;
    }

    std::cin >> u;
    l0 = l0;*/
}

