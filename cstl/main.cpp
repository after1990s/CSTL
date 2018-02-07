#include "t.h"
#include <iostream>
#include <vector>
#include "cstl_vector.h"
#include "cstl_list.h"
class K{
public:
    K(int i): m_i(i){}
    K(const K& k) : m_i(k.m_i){}
    ~K(){
        //4std::cout << m_i << " ";
    }
    int m_i;
};

int main(void)
{
    //std::cout << traits(1, int());
    CSTL::vector<K> t0;
    int u, u1;
    t0.push_back (K(1));
    t0.push_back (K(2));
    t0.push_back (K(3));
    t0.push_back (K(4));
    t0.push_back (K(5));
    t0.push_back (K(6));
    t0.push_back (K(7));

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
    l0 = l0;
}

