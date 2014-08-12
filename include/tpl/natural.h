
#ifndef __TPL_NATURAL_H__
#define __TPL_NATURAL_H__

#include "boolean.h"

namespace tpl
{
    namespace nat
    {
        struct nat{};

        template<class Num>
        struct succ : nat{
            using pred = Num;
        };
        struct undefined : nat { using pred = undefined;};

        template<>
        struct succ<undefined> : nat{
            using pred = undefined;
        };

        namespace prim /** zero one two three */{
            struct zero : nat{};
            using one = succ<zero>;
            using two = succ<one>;
            using three = succ<two>;
        }
        using prim::zero;

        namespace relation  /** eq le lt ge gt */ {
            using namespace tpl::boolean::prim;
            using namespace tpl::boolean::logic;
            template<class T1, class T2>
            struct is_equal
            {
                using value = $false;
            };

            template<class T1>
            struct is_equal<T1,T1>
            {
                using value = $true;
            };

            using namespace tpl::boolean::logic;
            template<class Num1, class Num2>
            struct is_less_than
            {
                using value = typename is_less_than<typename Num1::pred, typename Num2::pred>::value;
            };

            template<class Num1>
            struct is_less_than<Num1,zero>
            {
                using value = $false;
            };

            template<class Num1>
            struct is_less_than<zero,Num1>
            {
                using value = $true;
            };

            template<>
            struct is_less_than<zero,zero>
            {
                using value = $false;
            };


            template<class Num1, class Num2>
            struct is_less_equal{
                using value = typename $or<
                                    typename is_equal<Num1,Num2>::value,
                                    typename is_less_than<Num1,Num2>::value
                                >::value;
            };

            template<class Num1, class Num2>
            struct is_greater_than{
                using value = typename $not<typename is_less_equal<Num1,Num2>::value>::value;
            };

            template<class Num1, class Num2>
            struct is_greater_equal{
                using value = typename $not<typename is_less_than<Num1,Num2>::value>::value;
            };

            namespace abbrv{
                template<class Num1, class Num2>
                using eq = is_equal<Num1, Num2>;
                template<class Num1, class Num2>
                using lt = is_less_than<Num1, Num2>;
                template<class Num1, class Num2>
                using le = is_less_equal<Num1, Num2>;
                template<class Num1, class Num2>
                using gt = is_greater_than<Num1, Num2>;
                template<class Num1, class Num2>
                using ge = is_greater_equal<Num1, Num2>;
            }
            using namespace abbrv;
        }

        namespace operators
        /**
            add mul sub div
        */ {
            template<class Num1,class Num2>
            struct add
            {
                using value = typename add<succ<Num1>, typename Num2::pred>::value;
            };

            template<class Num1>
            struct add<Num1, zero>
            {
                using value = Num1;
            };

            template<class Num1, class Num2, class Acc = zero>
            struct mul_impl
            {
                using value = typename mul_impl<
                               Num1,
                               typename Num2::pred,
                               typename add<Acc, Num1>::value
                               >::value;
            };

            template<class Num1, class Acc>
            struct mul_impl<Num1, zero, Acc>
            {
                using value = Acc;
            };


            template<class Num1, class Num2>
            struct mul{
                using value = typename mul_impl<Num1, Num2, zero>::value;
            };

            template<class Num1, class Num2, class Cmp = typename relation::ge<Num1,Num2>::value>
            struct sub_impl{
                using value = typename sub_impl<typename Num1::pred, typename Num2::pred, Cmp>::value;
            };
            using namespace tpl::boolean::prim;
            template<class Num1, class Num2>
            struct sub_impl<Num1, Num2, $false>{
                using value = undefined;
            };
            template<class Num1>
            struct sub_impl<Num1, zero, $true>{
                using value = Num1;
            };

            template<class Num1, class Num2>
            struct sub{
                using value = typename sub_impl<Num1, Num2>::value;
            };

            template<class Num1, class Num2, class Acc = zero, class Cmp = typename relation::ge<Num1,Num2>::value>
            struct div_impl{
                using value = typename div_impl<Num1, Num2, Acc, Cmp>::value;
                using rem = typename div_impl<Num1, Num2, Acc, Cmp>::rem;
            };
            template<class Num1, class Acc, class Cmp>
            struct div_impl<Num1, zero, Acc, Cmp>{
                using value = undefined;       /// divide by zero
                using rem = undefined;
            };
            template<class Num1, class Num2, class Acc>
            struct div_impl<Num1, Num2, Acc, $true>{
                using value = typename div_impl<typename sub<Num1,Num2>::value, Num2, succ<Acc>>::value;
                using rem = typename div_impl<typename sub<Num1,Num2>::value, Num2, succ<Acc>>::rem;
            };
            template<class Num1, class Num2, class Acc>
            struct div_impl<Num1, Num2, Acc, $false>{
                using value = Acc;
                using rem = Num1;
            };
            template <class Num1, class Num2>
            struct div{
                using value = typename div_impl<Num1, Num2>::value;
                using rem = typename div_impl<Num1, Num2>::rem;
            };
        }
        using namespace operators;

        namespace operators /** max min */ {
            using namespace relation;
            template<class Num1, class Num2, class Rel = typename le<Num1, Num2>::value>
            struct min{
                using value = typename min<Num1, Num2, Rel>::value;
            };
            template<class Num1, class Num2>
            struct min<Num1, Num2, $true>{
                using value = Num1;
            };
            template<class Num1, class Num2>
            struct min<Num1, Num2, $false>{
                using value = Num2;
            };
            template<class Num1, class Num2, class Rel = typename ge<Num1, Num2>::value>
            struct max{
                using value = typename max<Num1, Num2, Rel>::value;
            };
            template<class Num1, class Num2>
            struct max<Num1, Num2, $true>{
                using value = Num1;
            };
            template<class Num1, class Num2>
            struct max<Num1, Num2, $false>{
                using value = Num2;
            };
        }

        namespace prim /** five ten */ {
            using five = typename add<two,three>::value;
            using ten = typename add<five, five>::value;
        }
        using prim::ten;

        namespace cons
        /**
            decimal     Num -> ...Num -> Num
         */{
            template<class First, class Second, class... Rest>
            struct decimal{
                using value = typename decimal<
                        typename add<
                            typename mul<First,ten>::value,
                            Second
                        >::value, Rest...>::value;
            };

            template<class First, class Second>
            struct decimal<First, Second>{
                using value = typename add<
                            typename mul<First,ten>::value,
                            Second
                        >::value;
            };
        }
        using namespace cons;

        namespace prim /** 01 ~ 0F, 10, 100, 0x10, 0x100 */ {
            using i0 = zero;
            using i1 = one;
            using i2 = two;
            using i3 = three;
            using i4 = succ<i3>;
            using i5 = five;
            using i6 = succ<i5>;
            using i7 = succ<i6>;
            using i8 = succ<i7>;
            using i9 = succ<i8>;
            using i10 = ten;

            using iA = ten;
            using iB = succ<iA>;
            using iC = succ<iB>;
            using iD = succ<iC>;
            using iE = succ<iD>;
            using iF = succ<iE>;

            using i50 = typename mul<i5,i10>::value;
            using i100 = typename mul<i10,i10>::value;
            using ix10 = succ<iF>;
            using ix100 = typename mul<ix10,ix10>::value;

            // -ftemplate-depth=100000000
            //using i1000 = typename mul<i100,i10>::value;
            //using i10000 = typename mul<i1000,i10>::value;
        }
        using namespace prim;
    }
}

#endif // __TPL_NATURAL_H__
