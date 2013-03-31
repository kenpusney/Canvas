
#include <stdio.h>
#include "core.h"

using namespace Canvas;

int main(){
    Object i;
    const Object j(i);
    Ref<Object> m(i);
    Ref<Object> n(j);
    Scalar<int> integer(1);
    printf("Object i id is %d\n\tj id is %d\n",(++integer)(),integer());
    return 0;
}
