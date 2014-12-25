
#ifndef __TPL_PROP_H__
#define __TPL_PROP_H__

#include "boolean.h"
namespace tpl {
    namespace prop {
        struct $false {};

        template<class T>
        struct $var {};

        using $undefined = $var<$false>;

        template <class Prop1, class Prop2>
        struct $and {
        };

        template<class T>
        struct $not {
        };

        using $true = $not<$false>;

        template<class Var, class Prop>
        struct $exists {
        };

        template <class Prop1, class Prop2>
        using $or = $not<$and<$not<Prop1>, $not<Prop2>>>;

        template <class Prop1, class Prop2>
        using $iff = $or<$and<Prop1, Prop2>, $and<$not<Prop1>, $not<Prop2>>>;

        template <class Prop1, class Prop2>
        using $implies = $or<$not<Prop1>, Prop2>;

        template <class Var, class Prop>
        using $forall = $not<$exists<Var, $not<Prop>>>;

        namespace eval{
                template<class A, class B>
                struct $entry{
                    using first = A;
                    using next = B;
                };

                template<class Var = $undefined, class Val = $false, class List = list::nil>
                struct $env {
                    using value = typename list::pair<$entry<Var,Val>, List>;
                };

                template <class Env, class Prop>
                struct $eval{
                    using $value = boolean::$false;
                };

                template <class Env, class Var, class Prop>
                struct $eval<Env, $exists<Var, Prop>>{
                    using value = typename boolean::$or<
                                            typename $eval<$env<Var,$false,typename Env::value>,Prop>::value,
                                            typename $eval<$env<Var,$true,typename Env::value>,Prop>::value
                                        >::value;
                };

                template<class Env>
                struct $eval<Env, $false>{
                    using value = boolean::$false;
                };

                template<class Env, class Prop1, class Prop2>
                struct $eval<Env, $and<Prop1, Prop2>>{
                    using value = typename boolean::$and<
                                                         typename $eval<Env, Prop1>::value,
                                                         typename $eval<Env, Prop2>::value
                                                         >::value;
                };

                template<class Env, class Prop>
                struct $eval<Env, $not<Prop>> {
                    using value = typename boolean::$not<
                                                         typename $eval<Env, Prop>::value
                                                         >::value;
                };

                template<class Env,class Val>
                struct $env_lookup{
                    template<class Var>
                    struct helper{
                        using value = typename boolean::same<Val, typename Var::first>::value;
                    };

                    using value = typename list::iter::find<helper, typename Env::value>::value::next;
                };

                template<class Env, class Var>
                struct $eval<Env, $var<Var>>{
                    using value = typename $eval<Env, typename $env_lookup<Env, $var<Var>>::value >::value;
                };
        }

        using eval::$eval;
        using eval::$env;
    }
}

#endif // __TPL_PROP_H__
