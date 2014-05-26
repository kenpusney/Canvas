#include "utility.h"
#include "unittest.h"
#include "certainly.h"
#include "marco.h"
#include <cstdio>
#include <functional>
#include <cstring>

template<typename Ret, typename... Args>
struct Builder{
    Ret operator()(Args... args) const{
        return lambda(
                [this](Args... args){
                    return this->operator ()(args...);
                }, args...);
    }
    Builder(std::function<Ret(std::function<Ret(Args...)>, Args...)> _lambda):lambda(_lambda){}
    
private:
    std::function<Ret(std::function<Ret(Args...)>, Args...)> lambda;
};

template<class Lambda>
struct LambdaTraits{
    typedef void func_type;
    typedef void lambda_type;
    typedef void builder_type;
};

template<class Ret, typename... Args>
struct LambdaTraits<Ret(Args...)>{
    typedef Ret func_type(Args...);
    typedef Ret lambda_type(std::function<Ret(Args...)>, Args...);
    typedef Builder<Ret, Args...> builder_type; 
};

template<class Lambda>
std::function<typename LambdaTraits<decltype(&Lambda::operator())>::func_type > Y(Lambda lambda){
    return typename LambdaTraits<decltype(&Lambda::operator())>::builder_type(lambda);
}

TestCase(RECURSIVE_LAMBDA){
    std::function<int(int)> f = Y([](std::function<int(int)> self,int i)->int{
        return index < 2? 
            1 : self(index-1) + self(index - 2) ;
    });
}

#define __TOK_DICT(e) __##e##_dict

#define define_literal_enum(E, args...) \
    enum class E : unsigned int {\
        args\
    };\
    constexpr const char* __TOK_DICT(E)[] = { __STRINGIFY_ALL(args) };\
    inline constexpr const char * repr(const E& token){ \
        return __TOK_DICT(E)[static_cast<unsigned int>(token)];  \
    }

define_literal_enum( Token, FCK, GOOG, JMEI);

TestCase(STRING_ENUM){
    TestAssert( repr(Token::FCK) == __Token_dict[0] );
    TestAssert( repr(Token::GOOG) == __Token_dict[1] );
    TestAssert( repr(Token::JMEI) == __Token_dict[2] );
    TestAssert( std::strcmp(repr(Token::FCK),  "FCK")  == 0 );
    TestAssert( std::strcmp(repr(Token::GOOG), "GOOG") == 0 );
    TestAssert( std::strcmp(repr(Token::JMEI), "JMEI") == 0 );
}

TestRunner();
