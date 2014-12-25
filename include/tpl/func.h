
#ifndef __TPL_FUNC_H__
#define __TPL_FUNC_H__

#include "natural.h"

namespace tpl{
    namespace func {
        namespace arg {
            template<class arg,class... args>
            struct arg_list{
                using head = arg;
                using tail = arg_list<args...>;
                using length = tpl::nat::succ<typename tail::length>;
            };
            template<class arg>
            struct arg_list<arg>{
                using head = arg;
                using tail = void;
                using length = typename tpl::nat::prim::one;
            };
            template<>
            struct arg_list<void>{
                using head = void;
                using tail = void;
                using length = typename tpl::nat::prim::zero;
            };
        }
        namespace prototype{
            template<class T>
            struct Generator{
                using argument_type = void;
                using result_type   = T;
            };

            template<class T>
            struct Consumer{
                using result_type   = void;
                using argument_type = T;
            };

            template<class Ret, class... Args>
            struct Func{
                using result_type   = Ret;
                using argument_type = arg::arg_list<Args...>;
            };
        }
    }
}

#endif
