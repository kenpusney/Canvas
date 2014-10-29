
#include "utility.h"
#include "unittest.h"
#include "marco.h"
#include <cstring>

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
