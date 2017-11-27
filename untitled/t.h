#ifndef T_H
#define T_H
struct _true_type{};
struct _false_type{};

template <class T>
bool traits(T , _true_type) {
    return true;
}

template <class T>
bool traits(T ,_false_type) {
    return false;
};


#endif // T_H
