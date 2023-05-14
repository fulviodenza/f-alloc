/*
This allocator maintains a linked list of allocated memory blocks. 
When malloc is called, it first checks if there is a block in 
the list that is large enough to satisfy the request. If so, it 
simply updates the size of that block and returns a pointer to 
the start of the memory block. If not, it uses mmap to request 
a new block of memory from the operating system and adds it to 
the linked list.

When free is called, it first calculates the start address of 
the memory block by subtracting the size of the block_header_t 
structure from the pointer passed to it. It then uses munmap to
release the memory back to the operating system. Finally, it 
updates the block header and adds the block to the head of 
the linked list.
*/
#include <unistd.h>
#include <sys/mman.h>

#define BLOCK_SIZE 4096
#define MAP_ANONYMOUS 0x20

typedef struct block_header {
    size_t size;
    struct block_header *next;
} block_header_t;

block_header_t *head = NULL;

void *falloc(size_t size) {
    block_header_t *block, *tmp;

    size_t total_size;
    void *block_start;

    if (size == 0) {
        return NULL;
    }

    total_size = sizeof(block_header_t) + size;
    if (total_size < BLOCK_SIZE) {
        total_size = BLOCK_SIZE;
    }

    // find for a block that fits the user-requested space
    block = head;
    while (block) {
        if (block->size >= size) {
            block->size = size;
            return (void *)(block + 1);
        }
        tmp = block->next;
        block = tmp;
    }

    block_start = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (block_start == MAP_FAILED) {
        return NULL;
    }

    block = (block_header_t *)block_start;
    block->size = size;
    block->next = head;
    head = block;

    return (void *)(block + 1);
}

void ffree(void *ptr) {
    block_header_t *block;

    if (ptr == NULL) {
        return;
    }

    block = (block_header_t *)ptr - 1;

    munmap(block, block->size + sizeof(block_header_t));

    block->size = 0;
    block->next = head;
    head = block;
}
