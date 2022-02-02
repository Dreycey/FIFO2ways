#include <stdio.h>
#include "test_llfifo.h"
#include "test_cbfifo.h"

int main(){
    printf("main is printing \n");
    test_llfifo();
    test_cbfifo();
}