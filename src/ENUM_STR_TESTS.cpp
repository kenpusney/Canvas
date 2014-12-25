
#include "utility.h"
#include "unittest.h"
#include "marco/enum.h"
#include <cstring>

define_literal_enum( Token, FCK, GOOG, JMEI);
define_literal_enum( Good, meat, brans, banana);

TestCase(STRING_ENUM){
    TestAssert( repr(Token::FCK) == __Token_dict[0] );
    TestAssert( repr(Token::GOOG) == __Token_dict[1] );
    TestAssert( repr(Token::JMEI) == __Token_dict[2] );
    TestAssert( std::strcmp(repr(Token::FCK),  "FCK")  == 0 );
    TestAssert( std::strcmp(repr(Good::meat),  "meat") == 0 );
    TestAssert( std::strcmp(repr(Token::JMEI), "JMEI") == 0 );
}
