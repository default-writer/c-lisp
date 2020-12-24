#define DEBUG

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "lisp.h"
#include "list.h"

typedef long long unsigned int ADDR;

void list_alloc(list_ptr ctx) {
    
}

void list_parse(list_ptr ctx) {
    
}

void list_free(list_ptr ctx) {
    
}

/* list vtable */
const struct list_vtable list_vt = {
    .init = list_init,
    .push = list_push,
    .pop = list_pop,
    .destroy = list_destroy,
    .print_head = list_print_head,
    .print = list_print
};

/* special version of list_ptr for mutations (removed *const, allowing pointer assiment operator) */
typedef struct mutable_list * mutable_list_ptr;

/* special version of list for mutations (removed *const, allowing pointer assiment operator) */
typedef struct mutable_list {
    /* points to previous node */
    mutable_list_ptr prev;
    /* payload */
    void*  payload;
} mutation_list;

/* initializes the new context's head element */
/* as a result, new memory block will be allocated */
/* current context pointer set to zero */
void list_init(list_ptr* const current) {
    /* sets current context's head element */
    *((mutable_list_ptr*)current) = calloc(1, sizeof(struct list));
    /* sets current context's counter to zero */
}

/* allocates a memory for provided payload  */
/* at current context, data payload stored at allocated memory buffer */
/* as a result, items counter will increase */
void list_push(list_ptr* const current, void* payload) {
    /* stores into pre-allocated value newly allocated memory buffer pointer */
    mutable_list_ptr item = calloc(1, sizeof(struct list));
    /* sets the new data into allocated memory buffer */
    item->payload = payload;
    /* pushes new item on top of the stack in current context */
    /* get current context's head */
    mutable_list_ptr head = *((mutable_list_ptr*)current);
    /* assigns item's prev pointer to head pointer */
    item->prev = *((mutable_list_ptr*)current);
    /* advances position of head pointer to the new head */
    *((mutable_list_ptr*)current) = item;
}

/* pop existing element at the top of the stack/queue/list */
/* at current context, existing head will be removed out of stack */
/* for the new stack header, correcponding values will be fixed */
/* as a result, header will be set to previous position, represented as head's reference to previos head */
void* list_pop(list_ptr* const current) {
    /* get current context's head */
    mutable_list_ptr head = *((mutable_list_ptr*)current);
    /* if we call method on empty stack, do not return head element, return null element by convention */
    if (head == 0 || head->prev == 0) {
        /* returns default element as null element */
        return 0;
    }
    /* gets previos pointer */
    mutable_list_ptr prev = head->prev;
    /* rewinds head pointer to previous pointer value */
    *((mutable_list_ptr*)current) = prev;
    /* assigns current stack head pointer to temporary */
    mutable_list_ptr ptr = head;
    /* gets temporary pointer value */
    void* payload = ptr->payload;
    /* detouches the pointer from the list */
#ifndef DIRTY
    ptr->prev = 0;
    ptr->payload = 0;
#endif
    /* free temporary pointer value */
    free(ptr);
    /* returns removed element */
    return payload;
}

/* destroys the memory stack */
/* frees all memory elements */
/* as a result, memory will be freed */
void list_destroy(list_ptr* const current) {
    /* get current context's head */
    /* assigns currently selected item pointer to temporary */
    mutable_list_ptr tmp = *((mutable_list_ptr*)current);
    /* if not already freed */
    if (tmp != 0) {
        /* until we found element with no parent (previous) node */
        do {
            /* gets temporary pointer value */
            mutable_list_ptr ptr = tmp;
            /* gets prev pointer value */
            mutable_list_ptr prev = tmp->prev;
#ifndef DIRTY
            /* zero all pointers */
            ptr->prev = 0;
            ptr->payload = 0;
#endif
            /* free temporary pointer value */
            free(ptr);
            /* advances temporary pointer value to the next item */
            tmp = prev;
        } while (tmp != 0);
        /* all stack items are processed */
        *((mutable_list_ptr*)current) = 0;
    }
}


// print head on current context (stack)
void list_print_head(list_ptr* const current) {
    // get current context's head
    list_ptr tmp = *current;
#ifdef DEBUG
    // visualise item
    printf("alloc: 0x%llx 0x%llx\n", (ADDR)tmp, (ADDR)tmp->payload);
#endif
}

// print all stack trace to output
// in a single loop, print out all elements except root element (which does not have a payload)
// as a result, all stack will be printed in last-to-first order (reverse)
void list_print(list_ptr* const current) {
    // get current context's head
    mutable_list_ptr head = *((mutable_list_ptr*)current);
    // get root element
    // struct list *root = ctx->root;
    // sets the counter
    int i = 0; 
    // assigns current's head pointer to the temporary
    mutable_list_ptr tmp = head;
    if (tmp != 0)
    {
        // until we found root element (element with no previous element reference)
        do {
#ifdef DEBUG
            // debug output of memory dump
            printf("%d: 0x%llx 0x%llx\n", ++i, (ADDR)tmp, (ADDR)tmp->payload);
#endif
            // remember temprary's prior pointer value to temporary
            tmp = tmp->prev;
        } while (tmp != 0/*root*/);
    }
    // stop on root element
}