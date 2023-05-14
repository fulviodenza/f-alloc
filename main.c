#include <stdio.h>

#include "allocator.h"
int main() {
    void *a = (int *)falloc(sizeof(char *) * 1000);
    a = "Hello World!";
    printf("%s\n", a);
    ffree(a);
}