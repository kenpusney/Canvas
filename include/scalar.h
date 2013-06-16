
#ifndef __SCALAR_H
#define __SCALAR_H

#define __SCALAR_MATH_EXTENSION

#include <iostream>
#include <cmath>
namespace Canvas{
    using namespace std;
    namespace type {
        /* Common scalar types under 32-bit x86 Machine */
        typedef             char                int8;
        typedef unsigned    char                uint8;
        typedef             short               int16;
        typedef unsigned    short               uint16;
        typedef             int                 int32;
        typedef unsigned    int                 uint32;
        typedef             long long           int64;
        typedef unsigned    long long           uint64;
        typedef             float               float32;
        typedef             double              float64;
        /* sizeof(long double) == 12 */
        typedef             long double         float96;
    }
    /* immutable */
    template<typename T>
    struct Scalar{
        typedef T type;
        Scalar(): __interval(){
        }
        Scalar(const T& i): __interval(i){
        }
        Scalar(const Scalar<T>& t):__interval(t.get()){
        }

        T get() const{
            return this->__interval;
        }

        template <typename CT>
        CT get() const{
            return static_cast<CT>(this->__interval);
        }
#ifdef __SCALAR_MATH_EXTENSION

        inline Scalar<double> sqrt() const{
            return Scalar<double>(std::sqrt(__interval));
        }
        inline Scalar<double> sin() const{
            return Scalar<double>(std::sin(__interval));
        }
        inline Scalar<double> cos() const{
            return Scalar<double>(std::cos(__interval));
        }
        inline Scalar<double> tan() const{
            return Scalar<double>(std::tan(__interval));
        }
        inline Scalar<double> asin() const{
            return Scalar<double>(std::asin(__interval));
        }
        inline Scalar<double> acos() const{
            return Scalar<double>(std::acos(__interval));
        }
        inline Scalar<double> atan() const{
            return Scalar<double>(std::atan(__interval));
        }

        inline Scalar<double> log() const{
            return Scalar<double>(std::log(__interval));
        }
        inline Scalar<double> exp() const{
            return Scalar<double>(std::exp(__interval));
        }
        Scalar<T>& operator=(const T& i){
            this->__interval = i;
            return *this;
        }
        Scalar<T>& operator=(const Scalar<T>& t){
            this->__interval = t.__interval;
            return *this;
        }
#endif
    private:
        T __interval;

    };

    template<typename T>
    ostream& operator<<(ostream& ost,const Scalar<T>& ct){
        ost << ct.get();
        return ost;
    }

    /* type safe */
    template<typename T>
    const Scalar<T> operator+(const Scalar<T>& t1,const Scalar<T>& t2){
        return Scalar<T>(t1.get() + t2.get());
    }
    template<typename T>
    const Scalar<T> operator-(const Scalar<T>& t1,const Scalar<T>& t2){
        return Scalar<T>(t1.get() - t2.get());
    }
    template<typename T>
    const Scalar<T> operator*(const Scalar<T>& t1,const Scalar<T>& t2){
        return Scalar<T>(t1.get() * t2.get());
    }
    template<typename T>
    const Scalar<T> operator/(const Scalar<T>& t1,const Scalar<T>& t2){
        return Scalar<T>(t1.get() / t2.get());
    }
    template<typename T>
    const bool operator<(const Scalar<T>& t1,const Scalar<T>& t2){
        return t1.get() < t2.get();
    }
    template<typename T>
    const bool operator>(const Scalar<T>& t1,const Scalar<T>& t2){
        return t1.get() > t2.get();
    }
    template<typename T>
    const bool operator<=(const Scalar<T>& t1,const Scalar<T>& t2){
        return t1.get() <= t2.get();
    }
    template<typename T>
    const bool operator>=(const Scalar<T>& t1,const Scalar<T>& t2){
        return t1.get() >= t2.get();
    }
    template<typename T>
    const bool operator==(const Scalar<T>& t1,const Scalar<T>& t2){
        return t1.get() == t2.get();
    }
    template<typename T>
    const bool operator!=(const Scalar<T>& t1,const Scalar<T>& t2){
        return t1.get() != t2.get();
    }


    typedef const Scalar<type::int8>      Integer8;
    typedef const Scalar<type::uint8>     UInteger8;
    typedef const Scalar<type::int16>     Integer16;
    typedef const Scalar<type::uint16>    UInteger16;
    typedef const Scalar<type::int32>     Integer;
    typedef const Scalar<type::int32>     Integer32;
    typedef const Scalar<type::uint32>    UInteger;
    typedef const Scalar<type::uint32>    UInteger32;
    typedef const Scalar<type::int64>     Integer64;
    typedef const Scalar<type::uint64>    UInteger64;
    typedef const Scalar<type::float32>   Float32;
    typedef const Scalar<type::float64>   Float;
    typedef const Scalar<type::float64>   Float64;
    typedef const Scalar<type::float96>   Float96;

    using namespace type;

}


namespace Canvas{
#ifdef __SCALAR_MATH_EXTENSION
    namespace Math{
        using namespace ::Canvas;
    }
#endif

}

#endif // __SCALAR_H
