/*
 * File:   utility.h
 * Author: kimmyleo
 *
 * Created on April 21, 2014, 2:11 AM
 */

#ifndef UTILITY_H
#define	UTILITY_H

namespace ref {

    template<typename T>
    struct left {
        typedef T& type;
    };

    template<typename T>
    struct left<T&> {
        typedef T& type;
    };

    template<typename T>
    struct left<T&&> {
        typedef T& type;
    };

    template<typename T>
    struct right {
        typedef T&& type;
    };

    template<typename T>
    struct right<T&> {
        typedef T&& type;
    };

    template<typename T>
    struct right<T&&> {
        typedef T&& type;
    };

    template<typename T>
    struct remove {
        typedef T type;
    };

    template<typename T>
    struct remove<T&> {
        typedef T type;
    };

    template<typename T>
    struct remove<T&&> {
        typedef T type;
    };

}

namespace interface {

    template<typename T>
    struct iforward {
        virtual T* operator->() = 0;
    };

    template<typename T>
    struct irefer {
        virtual typename ref::left<T>::type operator*() = 0;
    };

    template<typename T, template<class> class plc, template<class> class... plcs>
    struct policy : plc<T>, policy<T, plcs...> {
    };

    template<typename T, template<class> class plc>
    struct policy<T, plc> : plc<T> {
    };
}

namespace traits {

    struct null_type {
    };

    struct __one { //sizeof(__one) == 1
        char c;
    };

    struct __two { //sizeof(__two) == 2
        char c[2];
    };

    template<bool, class ifTrue, class ifFalse = null_type>
    struct type_if {
    };

    template<class ifTrue, class ifFalse>
    struct type_if<true, ifTrue, ifFalse> {
        typedef ifTrue type;
    };

    template<class ifTrue>
    struct type_if<true, ifTrue> {
        typedef ifTrue type;
    };

    template<class ifTrue>
    struct type_if<false, ifTrue> {
        typedef null_type type;
    };

    template<class ifTrue, class ifFalse>
    struct type_if<false, ifTrue, ifFalse> {
        typedef ifFalse type;
    };

    template<class T>                           /** abstract */
    inline typename ref::right<T>::type declval();

    template<class From, class To>
    class is_convertible {
        template<typename To1>                  /** abstract */
        static void __test_aux(const To1&);

        template<typename From1, typename To1>  /** abstract */
        static decltype(__test_aux<To1>(declval<From1>()), __one())
        __test(int);

        template<typename, typename>            /** abstract */
        static __two __test(...);
    public:
        static constexpr bool value = sizeof (__test<From, To>(0)) == 1;
    };

    template<class T1, class T2>
    struct is_same {
        static constexpr bool value = false;
    };

    template<class T>
    struct is_same<T, T> {
        static constexpr bool value = true;
    };
}

namespace concept {
    using traits::type_if;
    using traits::is_same;
    using traits::is_convertible;

    template<bool> struct ConstraintsError;

    template<>
    struct ConstraintsError<true> {
        static constexpr bool value = true;
    };

    template<typename T, typename Constraint, typename... Constraints>
    struct requires {
        typedef typename type_if<
        is_convertible<T, Constraint>::value,
        typename requires<T, Constraints...>::type
        >::type type;
        static constexpr bool value =
                ConstraintsError<is_same<T, type>::value>::value;
    };

    template<typename T, typename Constraint>
    struct requires<T, Constraint> {
        typedef typename type_if<
        is_convertible<T, Constraint>::value,
        T
        >::type type;
        static constexpr bool value =
                ConstraintsError<is_same<T, type>::value>::value;
    };
}

#endif	/* UTILITY_H */
