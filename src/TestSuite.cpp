#include "utility.h"
#include "unittest.h"
#include "certainly.h"

TestCase(SHOULD_ACCEPT_THIS_SYNTAX){
    cond when(1){
        
    }when(5){
    
    }except{
        
    }
back:
    repeat{
        unless(1)
            last;
    }until(1);
    if(false)
        jump back;
    int x = 3;
    match (x) {
        case 1: break;
        default: break;
    }
}

TestRunner();
