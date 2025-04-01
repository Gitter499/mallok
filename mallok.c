#include "mallok.h"
#include <stdio.h>

static HeaderNode *head = NULL;
static HeaderNode *tail = NULL;
static HeaderNode *last = NULL;

void *allocate_header(HeaderNode header)
{
    // Increment _brk by requested size plus some space for our header
    void *brkp;
    if ((void *)-1 == (brkp = sbrk(header.size + sizeof(HeaderNode))))
    {
        // handle error here
        fprintf(stderr, "Error allocating memory (ran out of heap space)\n");
        return (void *)-1;
    }

    // Casts to header pointer and derefs to set it the new header
    *((HeaderNode *)brkp) = *head;

    // The pointer to return to user
    return brkp + sizeof(HeaderNode);
}

/*
 *
 *
 *
 *
 *
 */
void *my_nextfit_malloc(int size)
{

    // First node we have to allocate
    if (NULL == head)
    {
        // Create our header
        HeaderNode new_head = {
            .size = size,
            .state = (enum State)taken,
            .next = NULL,
            .prev = NULL};

        // Update head and tail
        *tail = new_head;
        *head = new_head;

        // Update the last touched node (for next fit)
        *last = new_head;

        // Allocate the header and return the pointer
        return allocate_header(new_head);
    }

    /*
        do next fit stuff here
    */

    // Loop starting from our last updated node until we find enough space (peeking forwards and backwards)
    HeaderNode *curr = last;

    // TODO: Create a macro for checking if we fit since there is a lot of redudancy
    // Peek forwards
    while (curr->size < size && curr->next != NULL)
        curr = curr->next;

    // Peek from tail if haven't found yet (alternatively peek backwards?)
    if (curr->size < size)
        curr = tail;

    while (curr->size < size && curr->next != NULL)
        curr = curr->next;

    // if we haven't found a block yet we can allocate
    if (curr->size < size) {
        HeaderNode new = {
            .size = size,
            .state = taken,
            .next = NULL,
            .prev = head
        };

        *head->next = new;

        return allocate_header(new);
        
    }

    // TODO: Otherwise allocate the block


    return (void*) 0;
}

void my_free(void *ptr)
{
}

int main(void) { return 0; }