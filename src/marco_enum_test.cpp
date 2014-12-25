
#include "../include/utility.h"
#include "../include/unittest.h"
#include "../include/marco/enum.h"
#include <string.h>

define_literal_enum( Token, FCK, GOOG, JMEI);
define_literal_enum( Good, meat, brans, banana);

TestCase(STRING_ENUM){
    TestAssert( repr(Token::FCK) == __Token_dict[0] );
    TestAssert( repr(Token::GOOG) == __Token_dict[1] );
    TestAssert( repr(Token::JMEI) == __Token_dict[2] );
    TestAssert( strcmp(repr(Token::FCK),  "FCK")  == 0 );
    TestAssert( strcmp(repr(Good::meat),  "meat") == 0 );
    TestAssert( strcmp(repr(Token::JMEI), "JMEI") == 0 );
}
