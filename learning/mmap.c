#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

int main() {
    /*
    parameters description:
    - I don't where it comes from, 
      just give me a bunch of bytes
    - the amount of bytes
    - I want it read/write protected
      (with sbrk you cannot control
      the access type to the memory)
    - copy/write protected
    - it comes back only to my process
      is not meant for different file
    - FD
    - don't give a ****
    */
    void *newMemory = mmap(NULL, 0x1000,
        PROT_READ|PROT_WRITE, MAP_PRIVATE |
        MAP_ANONYMOUS, 0, 0);

    if (newMemory == NULL) {
        perror("mmap: ");
        return -1;
    }

    printf("newly allocated memory %p\n",
        newMemory);
        
    int *newArray = (int *)newMemory;

    newArray[100] = 2;
    newArray[101] = 3;
    newArray[102] = 4;

    printf("%d, %d, %d\n", newArray[100], newArray[101], newArray[102]);

    // return the memory 
    // back to the kernel
    munmap(newMemory, 0x1000);
    return 0;
}