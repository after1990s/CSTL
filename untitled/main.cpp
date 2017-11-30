#include "t.h"
#include <iostream>
#include <vector>
#include "cstl_vector.h"
class K{
public:
    K(int i): m_i(i){}
    ~K(){std::cout << m_i << " ";}
    int m_i;
};

int main(void)
{
    //std::cout << traits(1, int());
    /*std::vector<K> t0 = {1,2,3,4,5,6,7,8,9};
    std::vector<K>::iterator itr_begin = ++t0.begin ();
    std::vector<K>::iterator itr_end = itr_begin + 3;
    t0.erase (itr_begin, itr_end);*/
    CSTL::vector<K> t1;
    t1.push_back (K(1));
    t1.push_back (K(2));
    CSTL::vector<K>::iterator itr_begin = t1.begin ();
    itr_begin++;
    CSTL::vector<K>::iterator itr_end = itr_begin + 3;
    t1.erase (itr_begin, itr_end);
    int k ;
    std::cin >> k;
}

