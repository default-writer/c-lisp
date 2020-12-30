#define DEBUG

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "new_list.h"

typedef long long unsigned int ADDR;
typedef void * assignable_ptr;

typedef struct new_list * assignable_list_ptr;
typedef struct new_list_item * assignable_list_item_ptr;

#define MUTATE_PTR(a, b) *((assignable_ptr*)&a) = b
#define MUTATE_LIST_ITEM_PTR(a, b) *((assignable_list_item_ptr*)&a) = b

readonly_list_ptr new_list_init();
void new_list_item_push(readonly_list_ptr* const current, void* payload);
void new_list_item_pop(readonly_list_ptr* const current);
void new_list_destroy(readonly_list_ptr* const current);

void new_list_print_head(readonly_list_ptr const current);
void new_list_print_tail(readonly_list_ptr const current);
void new_list_print(readonly_list_ptr* const current);

/* list vtable */
const struct new_list_vtable new_list_vt = {
    .init = new_list_init,
    .destroy = new_list_destroy
};

/* list item vtable */
const struct new_list_item_vtable new_list_item_vt = {
    .push = new_list_item_push,
    .pop = new_list_item_pop
};


/* initializes the new context's head element */
/* as a result, new memory block will be allocated */
/* current context pointer set to zero */
readonly_list_ptr new_list_init() {
    /* sets current context's head element */
    /* stores into pre-allocated value newly allocated memory buffer pointer */
    readonly_list_ptr ptr = (readonly_list_ptr)calloc(1, sizeof(struct new_list));
#ifdef DEBUG
    printf("alloc: 0x%llx\n", (ADDR)ptr);
#endif
    /* returns current head pointer */
    return ptr;
}

/* initializes the new context's head element */
/* as a result, new memory block will be allocated */
/* current context pointer set to zero */
readonly_list_item_ptr new_list_item_init() {
    /* sets current context's head element */
    /* stores into pre-allocated value newly allocated memory buffer pointer */
    readonly_list_item_ptr ptr = (readonly_list_item_ptr)calloc(1, sizeof(struct new_list_item));
#ifdef DEBUG
    printf("alloc: 0x%llx\n", (ADDR)ptr);
#endif
    /* returns current head pointer */
    return ptr;
}
/* allocates a memory for provided payload  */
/* at current context, data payload stored at allocated memory buffer */
/* as a result, items counter will increase */
void new_list_item_push(readonly_list_ptr* const current, void* payload) {
    /* stores into pre-allocated value newly allocated memory buffer pointer */
    readonly_list_item_ptr ptr = new_list_item_init();
    /* sets the new data into allocated memory buffer */
    MUTATE_PTR(ptr->payload, payload);
    /* pushes new item on top of the stack in current context */
    /* assigns item's prev pointer to head pointer */
    MUTATE_LIST_ITEM_PTR(ptr->prev, (*current)->tail);
    /* advances position of head pointer to the new head */
    MUTATE_LIST_ITEM_PTR((*current)->tail, ptr);
#ifdef DEBUG
    new_list_print(current);
#endif
}


/* free memory block */
void new_list_item_free(readonly_list_item_ptr ptr) {
#ifdef DEBUG
    printf("free: 0x%llx\n", (ADDR)ptr);
#endif
#ifndef DIRTY
    /* zero all pointers */
    MUTATE_LIST_ITEM_PTR(ptr->prev, 0);
    MUTATE_PTR(ptr->payload, 0);
#endif
    /* free pointer */
    free(ptr);
}

/* free memory block */
void new_list_free(readonly_list_ptr ptr) {
#ifdef DEBUG
    printf("free: 0x%llx\n", (ADDR)ptr);
#endif
#ifndef DIRTY
    /* zero all pointers */
    MUTATE_PTR(ptr->head, 0);
    MUTATE_PTR(ptr->tail, 0);
#endif
    /* free pointer */
    free(ptr);
}

/* pop existing element at the top of the stack/queue/list */
/* at current context, existing head will be removed out of stack */
/* for the new stack header, correcponding values will be fixed */
/* as a result, header will be set to previous position, represented as head's reference to previos head */
void new_list_item_pop(readonly_list_ptr* const current) {
    /* get current context's head */
    readonly_list_item_ptr tail = (*current)->tail;
    /* if we call method on empty stack, do not return head element, return null element by convention */
    if (tail != 0) {
        /* gets previos pointer */
        readonly_list_item_ptr prev = tail->prev;
        /* free current pointer */
        new_list_item_free(tail);    
        /* rewinds head pointer to previous pointer value */
        MUTATE_LIST_ITEM_PTR((*current)->tail, prev);
    }
}

/* destroys the memory stack */
/* frees all memory elements */
/* as a result, memory will be freed */
void new_list_destroy(readonly_list_ptr* const current) {
    /* get current context's head */
    if (*current != 0) {
        /* assigns currently selected item pointer to temporary */
        readonly_list_item_ptr tail = (*current)->tail;
        /* if not already freed */
        if (tail != 0) {
            /* until we found element with no parent (previous) node */
            do {
                readonly_list_item_ptr prev = tail->prev;
                new_list_item_free(tail);
                /* rewinds head pointer to previous pointer value */
                MUTATE_LIST_ITEM_PTR(tail, prev);
            } while (tail != 0);
        }
        /* remove list struct */
        new_list_free(*current);
        /* all stack items are processed */
        MUTATE_LIST_ITEM_PTR(*current, 0);
    }
}


// print head on current context (stack)
void new_list_print_head(readonly_list_ptr const current) {
    // visualise item
    printf("[0x%llx]: 0x%llx\n", (ADDR)current->head, (ADDR)current->head->payload);
}

// print head on current context (stack)
void new_list_print_tail(readonly_list_ptr const current) {
    // visualise item
    printf("[0x%llx]: 0x%llx\n", (ADDR)current->tail, (ADDR)current->tail->payload);
}

// print all stack trace to output
// in a single loop, print out all elements except root element (which does not have a payload)
// as a result, all stack will be printed in last-to-first order (reverse)
void new_list_print(readonly_list_ptr* const current) {
    // get current context's head
    // get root element
    // struct list *root = ctx->root;
    // sets the counter
    int i = 0; 
    // assigns current's head pointer to the temporary
    readonly_list_item_ptr tmp = (*current)->tail;
    if (tmp != 0)
    {
        // until we found root element (element with no previous element reference)
        do {
#ifdef DEBUG
            // debug output of memory dump
            printf("%d: 0x%llx 0x%llx\n", ++i, (ADDR)tmp, (ADDR)tmp->payload);
#endif
            // remember temprary's prior pointer value to temporary
            MUTATE_LIST_ITEM_PTR(tmp, tmp->prev);
        } while (tmp != 0);
    }
    // stop on root element
}

void new_print_list_node(readonly_list_ptr* current) {
    const struct new_list_item_vtable* list = &new_list_item_vt;
    /* get current context's head */
    char *str = (*current)->tail->payload;
    list->pop(current);
    char *format = (*current)->tail->payload;
    list->pop(current);
    printf(format, str);
}

void new_list_demo() {
    // create list
    const struct new_list_vtable* list_memory = &new_list_vt;
    const struct new_list_item_vtable* list = &new_list_item_vt;

    // initialize list
    readonly_list_ptr new_list = list_memory->init();

    char *str = "Hello, World!\n";
    char *format = "%s";

    // isolation mode
    readonly_list_ptr args = list_memory->init();
    list->push(&args, format);
    list->push(&args, str);
    new_print_list_node(&args);
    list_memory->destroy(&args);

    //no isolation
    list->push(&new_list, format);
    list->push(&new_list, str);
    new_print_list_node(&new_list);

    void* payload = (void*)0xdeadbeef;
    list->push(&new_list, payload);
    list->push(&new_list, ++payload);
    list->push(&new_list, ++payload);
    list->push(&new_list, ++payload);
    list->push(&new_list, ++payload);

    void* q_pop0 = new_list->tail->payload;
    list->pop(&new_list);
    void* q_pop1 = new_list->tail->payload;
    list->pop(&new_list);
    void* q_pop2 = new_list->tail->payload;
    list->pop(&new_list);
    void* q_pop3 = new_list->tail->payload;
    list->pop(&new_list);
    list->push(&new_list, q_pop3);
    q_pop3 = new_list->tail->payload;
    list->pop(&new_list);
    void* q_pop4 = new_list->tail->payload;
    list->pop(&new_list);
    
    list_memory->destroy(&new_list);
}
