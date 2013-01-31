
#include <stdio.h>
#include "core.h"

int main(){
    Integer i,j;
    Scalar<float> x = 1.0;
    x++;
    i = 1;
    j = 2;
    i = 'a'-i;
    i = i+1;
    i--;
    ++i;
    printf("%c",i.value());
    return 0;
}
