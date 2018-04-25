#pragma once

namespace CSTL{

    namespace detail {
        template<class T> struct sp_element {
            typedef T type;
        };
        template<class T> struct sp_element<T[]> {
            typedef T type;
        };
        template<class T, int N> struct sp_element< T[N] >
        {
            typedef T type;
        };

        template<class T> struct sp_dereference {
            typedef T type;
        };
        template<> struct sp_dereference<void> {
            typedef void type;
        };
        template<> struct sp_dereference<void volatile> {
            typedef void type;
        };
        template<> struct sp_dereference<void const> {
            typedef void type;
        };
        template<> struct sp_dereference<void const volatile> {
            typedef void type;
        };

        template<class T> struct sp_member_access{
            typedef T * type;
        };
        template<class T> struct sp_member_access<T[]> {
            typedef void type;
        };
        template<class T, int N> struct sp_member_access<T[N]> {
            typedef void type;
        };

        template<class T> struct sp_array_access {
            typedef void type;
        };
        template<class T> struct sp_array_access<T[]> {
            typedef T& type;
        };
        template<class T, int N> struct sp_array_access<T[N]> {
            typedef T& type;
        };

        //check array index
        template<class T> struct sp_extend {
            enum _vt {
                value = 0
            };
        };
        template<class T, int N> struct sp_extend<T[N]> {
            enum _vt {
                value = N
            };
        };

        /*todo: ignore sp_enable_shared_from_this, don't know what it is.*/

        /*ignore auto_ptr convert facility*/


    } //end namespace detail

    
class shared_ptr
{
public:
    shared_ptr();
    ~shared_ptr();
};

}

