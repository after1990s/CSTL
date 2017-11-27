#ifndef VECTOR_H
#define VECTOR_H
#include <inttypes.h>
namespace CSTL {
template<class T>
class vector
{
public:
    typedef T value_type;
    typedef value_type* pointer_type;
    typedef value_type* iterator;
    typedef value_type& reference;
    typedef uint32_t size_type;
    //typedef ptrdiff_t difference_type;
    vector();
protected:
    iterator start;
    iterator finish;
    iterator end_of_storage;

    void deallocate() {
        if (start) {
            delete [] start;
        }
    }
};

}
#endif // VECTOR_H
