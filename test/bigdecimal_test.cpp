//
//  bigdecimal_test.cpp
//  canvas
//
//  Created by Kimmy  on 3/20/16.
//  Copyright (c) 2016 TDCA. All rights reserved.
//

#include "../include/unittest.h"

#include <vector>
#include <cstdlib>

class decimal
{
    std::vector<long long> digits;
    enum class sig_t { positive = 0, negative = 1 };
    sig_t sig;
    int exponent;
public:
    template<class T>
    constexpr decimal(T value):
        digits({std::abs(value)}),
        sig (value < 0 ? sig_t::negative : sig_t::positive),
        exponent(0) {}
    
    decimal merge(const decimal& y) const
    {
        return decimal{( value<long long>() + y.value<long long>() ) };
    }
    
    template<class T>
    T value() const
    {
        long long value = *(end(digits) - 1) * signum();
        return static_cast<T>(value);
    }
    
private:
    int signum(const decimal& y) const
    {
        return this->signum() * y.signum();
    }
    
    int signum() const
    {
        return static_cast<int>(this->sig) == 0 ? 1 : -1;
    }
    
};

template<class T>
decimal operator+(const decimal& x, const T& y)
{
    
}

decimal operator+(const decimal& x, const decimal& y) {
    return x.merge(y);
}

template<class T>
bool operator==(const decimal& x, const T& y)
{
    return x.value<T>() == y;
}


TestCase(BigDecimal)
{
    decimal x {1};
    
    
    decimal y {-1};
    
    TestAssert(x + y == 0);
}