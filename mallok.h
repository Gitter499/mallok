#include <stdint.h>
#include <unistd.h>

#define w_size uint32_t

enum State {
    free = 0,
    taken = 1
};

typedef struct HeaderNode {
    w_size size;
    enum State state;
    struct HeaderNode* next;
    struct HeaderNode* prev;
} HeaderNode;


int brk(void *addr);

void *sbrk(intptr_t increment);

void* allocate_header(HeaderNode header);

void *my_nextfit_malloc(int size);

void my_free(void *ptr);

