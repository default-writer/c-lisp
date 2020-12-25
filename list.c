#define DEBUG

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "lisp.h"
#include "list.h"

typedef long long unsigned int ADDR;

void list_alloc(readonly_list_ptr ctx) {
    
}

void list_parse(readonly_list_ptr ctx) {
    
}

void list_free(readonly_list_ptr ctx) {
    
}

typedef void * assignable_ptr;
typedef struct list * assignable_list_ptr;

#define MUTATE_PTR(a, b) *((assignable_ptr*)&a) = b
#define MUTATE_LIST_PTR(a, b) *((assignable_list_ptr*)&a) = b

/* list vtable */
const struct list_vtable list_vt = {
    .init = list_init,
    .push = list_push,
    .pop = list_pop,
    .destroy = list_destroy,
    .print_head = list_print_head,
    .print = list_print
};

/* initializes the new context's head element */
/* as a result, new memory block will be allocated */
/* current context pointer set to zero */
readonly_list_ptr list_init() {
    /* sets current context's head element */
    return (readonly_list_ptr)calloc(1, sizeof(struct list));
}

/* allocates a memory for provided payload  */
/* at current context, data payload stored at allocated memory buffer */
/* as a result, items counter will increase */
void list_push(readonly_list_ptr* const current, void* payload) {
    /* stores into pre-allocated value newly allocated memory buffer pointer */
    readonly_list_ptr item = (readonly_list_ptr)calloc(1, sizeof(struct list));
    /* sets the new data into allocated memory buffer */
    MUTATE_PTR(item->payload, payload);
    /* pushes new item on top of the stack in current context */
    /* assigns item's prev pointer to head pointer */
    MUTATE_LIST_PTR(item->prev, *current);
    /* advances position of head pointer to the new head */
    MUTATE_LIST_PTR(*current, item);
}

/* pop existing element at the top of the stack/queue/list */
/* at current context, existing head will be removed out of stack */
/* for the new stack header, correcponding values will be fixed */
/* as a result, header will be set to previous position, represented as head's reference to previos head */
void* list_pop(readonly_list_ptr* const current) {
    /* get current context's head */
    readonly_list_ptr head = *current;
    /* if we call method on empty stack, do not return head element, return null element by convention */
    if (head == 0 || head->prev == 0) {
        /* returns default element as null element */
        return 0;
    }
    /* gets previos pointer */
    readonly_list_ptr prev = head->prev;
    /* rewinds head pointer to previous pointer value */
    MUTATE_LIST_PTR(*current, prev);
    /* assigns current stack head pointer to temporary */
    readonly_list_ptr ptr = head;
    /* gets temporary pointer value */
    void* payload = ptr->payload;
    /* detouches the pointer from the list */
#ifndef DIRTY
    MUTATE_LIST_PTR(ptr->prev, 0);
    MUTATE_LIST_PTR(ptr->payload, 0);
#endif
    /* free temporary pointer value */
    free(ptr);
    /* returns removed element */
    return payload;
}

/* destroys the memory stack */
/* frees all memory elements */
/* as a result, memory will be freed */
void list_destroy(readonly_list_ptr* const current) {
    /* get current context's head */
    /* assigns currently selected item pointer to temporary */
    readonly_list_ptr tmp = *current;
    /* if not already freed */
    if (tmp != 0) {
        /* until we found element with no parent (previous) node */
        do {
            /* gets temporary pointer value */
            readonly_list_ptr ptr = tmp;
            /* gets prev pointer value */
            readonly_list_ptr prev = tmp->prev;
#ifndef DIRTY
            /* zero all pointers */
            MUTATE_LIST_PTR(ptr->prev, 0);
            MUTATE_PTR(ptr->payload, 0);
#endif
            /* free temporary pointer value */
            free(ptr);
            /* advances temporary pointer value to the next item */
            MUTATE_LIST_PTR(tmp, prev);
        } while (tmp != 0);
        /* all stack items are processed */
        MUTATE_LIST_PTR(*current, 0);
    }
}


// print head on current context (stack)
void list_print_head(readonly_list_ptr* const current) {
    // get current context's head
    readonly_list_ptr tmp = *current;
#ifdef DEBUG
    // visualise item
    printf("alloc: 0x%llx 0x%llx\n", (ADDR)tmp, (ADDR)tmp->payload);
#endif
}

// print all stack trace to output
// in a single loop, print out all elements except root element (which does not have a payload)
// as a result, all stack will be printed in last-to-first order (reverse)
void list_print(readonly_list_ptr* const current) {
    // get current context's head
    readonly_list_ptr head = *current;
    // get root element
    // struct list *root = ctx->root;
    // sets the counter
    int i = 0; 
    // assigns current's head pointer to the temporary
    readonly_list_ptr tmp = head;
    if (tmp != 0)
    {
        // until we found root element (element with no previous element reference)
        do {
#ifdef DEBUG
            // debug output of memory dump
            printf("%d: 0x%llx 0x%llx\n", ++i, (ADDR)tmp, (ADDR)tmp->payload);
#endif
            // remember temprary's prior pointer value to temporary
            MUTATE_LIST_PTR(tmp, tmp->prev);
        } while (tmp != 0/*root*/);
    }
    // stop on root element
}