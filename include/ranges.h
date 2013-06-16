

#ifndef __RANGES_H
#define __RANGES_H

#include <vector>
#include <limits>
namespace Canvas{

    using namespace std;
    template<typename T>
    vector<T> range(const T& beginv,const T& endv){
        T beg = beginv;
        vector<T> vec;
        while(beg != endv)
            vec.push_back(beg++);
        return vec;
    }

    template<typename T>
    struct RangePos{
        RangePos():__interval(),__step(1){}
        RangePos(const T& i):__interval(i),__step(1){};
        RangePos(const T& i,const T& step):__interval(i),__step(step){};
        RangePos(const RangePos<T>& r):__interval(r.__interval),__step(r.__step){};
        RangePos next() const{
            /* FIXME: out of range */
            __interval= __interval + __step;
            return __interval;
        }
        RangePos operator++() const{
            return this->next();
        }
        T operator*() const{
            return this->__interval;
        }
        bool operator==(const RangePos<T>& r) const{
            return ! (*this != r);
        }
        bool operator!=(const RangePos<T>& r) const{
            if(__step < T(0)){
                return this->__interval > r.__interval;
            }
            return this->__interval < r.__interval;
        }

    private:
        mutable T   __interval;
        const T     __step;
    };
    template<typename T>
    struct RangeIter{
        RangeIter(const T& endv):__begin(),
                                 __end(endv),
                                 __step(T(1)){}
        RangeIter(const T& beginv, const T& endv, const T& step = T(1)):__begin(beginv,step),
                                                                        __end(endv),
                                                                        __step(step){}


        const RangePos<T> begin() const{
            return __begin;
        }

        const RangePos<T> end() const{
            return __end;
        }

        const T operator[](const T& index) const{
            return *__begin + __step * index;
        }
    private:
        RangePos<T> __begin;
        RangePos<T> __end;
        const T __step;
    };

    template<typename T>
    const RangeIter<T> xrange(const T& endv){
        return RangeIter<T>(endv);
    }

    template<typename T>
    const RangeIter<T> xrange(const T& beginv, const T& endv, const T& step = T(1)){
        return RangeIter<T>(beginv,endv,step);
    }
}

#endif // __RANGES_H
