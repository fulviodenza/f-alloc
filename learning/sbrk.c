#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    /* 
    sbrk increases the allocated memory for the program and returns
    the pointer to the location. sbrk(0) returns only the value of
    program break by default
    */
    void *firstEnd = sbrk(0);
    printf("current program break: %p\n",
        firstEnd);
    /*
    sbrk(0x1000) allocates 4096 bytes of space for the program 
    */
    void *currentEnd = sbrk(0x1000);
    printf("new program break: %p\n",
        currentEnd);
    
    int *array = (int *)firstEnd;
    array[100] = 2;
    array[101] = 3;
    array[102] = 4;

    printf("%d, %d, %d\n", array[100], array[101], array[102]);
    return 0;
}