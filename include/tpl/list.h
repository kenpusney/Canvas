
#ifndef __TPL_LIST_H__
#define __TPL_LIST_H__

#include "natural.h"
#include "boolean.h"

namespace tpl{
    namespace list{
        using tpl::nat::zero;
        struct undefined {};
        struct nil {using length = zero;};
        namespace predicate{
            using namespace tpl::boolean::prim;
            template<class Lst>
            struct is_nil{
                using value = $false;
            };
            template<>
            struct is_nil<nil>{
                using value = $true;
            };
        }

        namespace cons{
            using tpl::nat::succ;
            using tpl::nat::one;
            template<class First, class Rest>
            struct pair{
                using first = First;
                using rest = Rest;
                using length = succ<typename Rest::length>;
            };
            template<class First>
            struct pair<First,nil>{
                using first = First;
                using rest = nil;
                using length = one;
            };
            template<class First = nil, class... Rest>
            struct list{
                using value = pair<First, typename list<Rest...>::value>;
                using length = succ<typename list<Rest...>::length>;
            };
            template<>
            struct list<nil>{
                using value = nil;
                using length = typename value::length;
            };
        }
        using namespace cons;

        namespace util
        /**
            concat      [t] -> [t] -> [t]
            take        Num -> [t] -> [t]
            drop        Num -> [t] -> [t]
        */{
            using tpl::nat::operators::min;
            template<class List1, class List2>
            struct concat{
                using value = pair<
                            typename List1::first,
                            typename concat<typename List1::rest, List2>::value>;
                using length = typename value::length;
            };
            template<class List2>
            struct concat<nil, List2>{
                using value = List2;
                using length = typename List2::length;
            };

            template<class Num1, class List1>
            struct take{
                using value = pair<
                        typename List1::first,
                        typename take<typename Num1::pred, typename List1::rest>::value
                        >;
                using length = typename value::length;
            };
            template<class Num1>
            struct take<Num1, nil>{
                using value = nil;
                using length = zero;
            };
            template<class List1>
            struct take<zero, List1>{
                using value = nil;
                using length = zero;
            };

            template<class Num1, class List1>
            struct drop{
                using value = typename drop<typename Num1::pred, typename List1::rest>::value;
                using length = typename value::length;
            };
            template<class Num1>
            struct drop<Num1, nil>{
                using value = nil;
                using length = zero;
            };
            template<class List1>
            struct drop<zero, List1>{
                using value = nil;
                using length = zero;
            };
        }
        using namespace util;

        namespace iter
        /**
            map         (a -> b) -> [a] -> [b]
            fold_left   (b -> a -> b) -> b -> [a] -> b
            find        (a -> boolean) -> [a] -> a

        */{
            template<template <class Elem> class Fn, class List>
            struct map{
                using value = pair<
                                typename Fn<typename List::first>::value,
                                typename map<Fn, typename List::rest >::value
                            >;
                using length = typename value::length;
            };
            template<template <class Elem> class Fn>
            struct map<Fn, nil>{
                using value = nil;
                using length = zero;
            };
            template<template <class Elem1, class Elem2> class Fn, class Init, class List>
            struct fold_left{
                using value = typename fold_left<
                                    Fn,
                                    typename Fn<Init, typename List::first>::value,
                                    typename List::rest
                                > :: value;
            };
            template<template <class Elem1, class Elem2> class Fn, class Init>
            struct fold_left<Fn, Init, nil>{
                using value = Init;
            };
            template<template <class Elem1> class Pred, class List>
            struct find{
                using value = typename boolean::$if< typename Pred<typename List::first>::value,
                                            typename List::first,
                                            typename find<Pred, typename List::rest>::value>::value;
            };

            template<template <class Elem> class Pred>
            struct find<Pred, nil>{
                using value = undefined;
            };
        }
    }
}

#endif // __TPL_LIST_H__
