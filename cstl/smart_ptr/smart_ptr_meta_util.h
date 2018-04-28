#pragma once
#define PRAGMA_STR1(x)  #x
#define PRAGMA_STR2(x)  PRAGMA_STR1 (x)
#define NOTE(x)  message (__FILE__ "(" PRAGMA_STR2(__LINE__) ") : \
		-NOTE- " #x)
#define NOTE_wARG(x,y)  message \
   (__FILE__ "(" PRAGMA_STR2(__LINE__) ") : \
   -NOTE- " #x PRAGMA_STR2(y))
namespace CSTL {

    template <class T>
    struct remove_reference {
        typedef T type;
    };

    template <class T>
    struct remove_reference<T&> {
        typedef T type;
    };
    template <class T>
    struct remove_reference<T&&> {
        typedef T type;
    };

    template <class T>
    struct remove_const {
        typedef T type;
    };

    template <class T>
    struct remove_const<const T> {
        typedef T type;
    };

    template <class T>
    struct remove_volatile {
        typedef T type;
    };

    template <class T>
    struct remove_volatile<volatile T> {
        typedef T type;
    };

    template <class T>
    struct remove_cv {
        typedef typename remove_const<typename remove_volatile<T>::type>::type type;
    };

    template <class T>
    struct remove_extent {
        typedef T type;
    };

    template <class T>
    struct remove_extent<T[]> {
        typedef T type;
    };

    template <class T, int N>
    struct remove_extent<T[N]> {
        typedef T type;
    };

    template <class T>
    struct extent {
        static const int value = 0;
    };

    template <class T, int N>
    struct extent<T[N]> {
        static const int value = N;
    };
    /*
    template <class T, int N>
    struct extent<T[], N> {
        static const int value = 0;
    };*/
    //addtional extent not used.

    template <class T>
    struct add_lvalue_reference {
        typedef T& type;
    };

    template <class T>
    struct add_lvalue_reference<T&> {
        typedef T& type;
    };

    template <class T>
    struct add_lvalue_reference<T&&> {
        typedef T& type;
    };

    template <>
    struct add_lvalue_reference<void> {
        typedef void type;
    };

    template <>
    struct add_lvalue_reference<const void> {
        typedef const void type;
    };

    template <>
    struct add_lvalue_reference<volatile void> {
        typedef volatile void type;
    };

    template <>
    struct add_lvalue_reference<const volatile void> {
        typedef const volatile void type;
    };

    template <class T>
    struct add_const_lvalue_reference {
        typedef typename remove_reference<T>::type unreference_type;
        typedef const unreference_type cunreference_type;
        typedef typename add_lvalue_reference<cunreference_type>::type type;
    };

    template <class T, class U>
    struct is_same {
        static const bool value = false;
    };

    template <class T>
    struct is_same<T, T> {
        static const bool value = true;
    };

    template <class T>
    struct is_reference {
        static const bool value = false;
    };

    template <class T>
    struct is_reference<T&> {
        static const bool value = true;
    };

    template <class T>
    struct is_reference<T&&> {
        static const bool value = true;
    };

    template <class T>
    struct is_lvalue_reference {
        static const bool value = false;
    };

    template <class T>
    struct is_lvalue_reference<T&> {
        static const bool value = true;
    };

    template <class T>
    struct is_lvalue_reference<T&&> {
        static const bool value = false;
    };

    /*check if T::pointer exists*/
    template <class T>
    struct has_pointer_type {
        struct two { char c[2]; };
        template <class U> static two test(U u);
        template <class U> static char test(typename U::pointer* = 0);
        static const bool value = (sizeof(test<T>(0)) == 1);
    };
    
    //todo:pointer type.
    template <class T, class U>
    struct is_covertible {
        static const bool value = __is_convertible_to(T, U);
    };
    
    template <class R>
    struct is_unary_function_impl {
        #pragma message ( "is_unary_function_impl")
        #pragma message (std::typeid(R).name())
        static const bool value = false;
    };
   
    template <class R>
    struct is_unary_function_impl<R&> {
        static const bool value = false;
    };

#if defined(_MSC_EXTENSIONS) && !defined(__BORLAND__) && !defined(_WIN64) && !defined(_M_ARM) && !defined(UNDER_CE)
#define BOOST_MOVE_TT_TEST_MSC_FUNC_SIGS
#endif
#ifndef  BOOST_MOVE_TT_TEST_MSC_FUNC_SIGS
    template <class R>
    struct is_unary_function_impl<R(*)()> {
        static const bool value = true;
    };
    template <class R>
    struct is_unary_function_impl<R(*)(...)> {
        static const bool value = true;
    };
#else
    int xxx;
#endif

    template <typename R>
    struct is_unary_function_impl<R(__fastcall*)()>
    {
        static const bool value = true;
    };

    template <typename R>
    struct is_unary_function_impl<R(__cdecl*)()>
    {
        static const bool value = true;
    };
    template <typename R>
    struct is_unary_function_impl<R(__cdecl*)(...)>
    {
        static const bool value = true;
    };

    template <typename R, class T0>
    struct is_unary_function_impl<R(__stdcall*)(T0)>
    {
        static const bool value = true;
    };

#ifndef _MANAGED

    template <typename R, class T0>
    struct is_unary_function_impl<R(__fastcall*)(T0)>
    {
        static const bool value = true;
    };

#endif

    template <typename R, class T0>
    struct is_unary_function_impl<R(__cdecl*)(T0)>
    {
        static const bool value = true;
    };

    template <typename R, class T0>
    struct is_unary_function_impl<R(__cdecl*)(T0...)>
    {
        static const bool value = true;
    };

    /*void (_stdcall)(void) -> false MSVC bug.*/
    template <class R>
    struct is_unary_function {
        static const bool value = is_unary_function_impl<R>::value;
    };
}