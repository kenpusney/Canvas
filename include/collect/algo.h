
#ifndef __COLLECT_ALGO_H
#define __COLLECT_ALGO_H

#include <functional>

namespace collect{
    namespace algo{
        // FUCK!!
        template<class Iter, class Ret = void>
        void foreach(Iter begin, Iter end, std::function<void(int&)> fn){
            for(; begin != end; ++begin){
                fn(*begin);
            }
        }
    }
}

#endif // __COLLECT_ALGO_H
