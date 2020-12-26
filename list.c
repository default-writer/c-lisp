#define DEBUG

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "list.h"

typedef long long unsigned int ADDR;
typedef void * assignable_ptr;
typedef struct list * assignable_list_ptr;

#define MUTATE_PTR(a, b) *((assignable_ptr*)&a) = b
#define MUTATE_LIST_PTR(a, b) *((assignable_list_ptr*)&a) = b

readonly_list_ptr list_init();
void list_push(readonly_list_ptr* const current, void* payload);
void list_pop(readonly_list_ptr* const current);
void list_destroy(readonly_list_ptr* const current);

void list_print_head(readonly_list_ptr const current);
void list_print(readonly_list_ptr const current);

/* list vtable */
const struct list_vtable list_vt = {
    .init = list_init,
    .push = list_push,
    .pop = list_pop,
    .destroy = list_destroy
};

/* initializes the new context's head element */
/* as a result, new memory block will be allocated */
/* current context pointer set to zero */
readonly_list_ptr list_init() {
    /* sets current context's head element */
    /* stores into pre-allocated value newly allocated memory buffer pointer */
    readonly_list_ptr ptr = (readonly_list_ptr)calloc(1, sizeof(struct list));
#ifdef DEBUG
    printf("alloc: 0x%llx\n", (ADDR)ptr);
#endif
    /* returns current head pointer */
    return ptr;
}

/* allocates a memory for provided payload  */
/* at current context, data payload stored at allocated memory buffer */
/* as a result, items counter will increase */
void list_push(readonly_list_ptr* const current, void* payload) {
    /* stores into pre-allocated value newly allocated memory buffer pointer */
    readonly_list_ptr ptr = list_init();
    /* sets the new data into allocated memory buffer */
    MUTATE_PTR(ptr->payload, payload);
    /* pushes new item on top of the stack in current context */
    /* assigns item's prev pointer to head pointer */
    MUTATE_LIST_PTR(ptr->prev, *current);
    /* advances position of head pointer to the new head */
    MUTATE_LIST_PTR(*current, ptr);
#ifdef DEBUG
    list_print(ptr);
#endif
}


/* free memory block */
void list_free(readonly_list_ptr ptr) {
#ifdef DEBUG
    printf("free: 0x%llx\n", (ADDR)ptr);
#endif
#ifndef DIRTY
    /* zero all pointers */
    MUTATE_LIST_PTR(ptr->prev, 0);
    MUTATE_PTR(ptr->payload, 0);
#endif
    /* free pointer */
    free(ptr);
}

/* pop existing element at the top of the stack/queue/list */
/* at current context, existing head will be removed out of stack */
/* for the new stack header, correcponding values will be fixed */
/* as a result, header will be set to previous position, represented as head's reference to previos head */
void list_pop(readonly_list_ptr* const current) {
    /* get current context's head */
    readonly_list_ptr head = *current;
    /* if we call method on empty stack, do not return head element, return null element by convention */
    if (head != 0) {
        /* gets previos pointer */
        readonly_list_ptr prev = head->prev;
        /* free current pointer */
        list_free(head);    
        /* rewinds head pointer to previous pointer value */
        MUTATE_LIST_PTR(*current, prev);
    }
}

/* destroys the memory stack */
/* frees all memory elements */
/* as a result, memory will be freed */
void list_destroy(readonly_list_ptr* const current) {
    /* get current context's head */
    /* assigns currently selected item pointer to temporary */
    readonly_list_ptr head = *current;
    /* if not already freed */
    if (head != 0) {
        /* until we found element with no parent (previous) node */
        do {
            /* gets previos pointer */           
            readonly_list_ptr prev = head->prev;
            /* free current pointer */
            list_free(head);
            /* rewinds head pointer to previous pointer value */
            MUTATE_LIST_PTR(head, prev);
        } while (head != 0);
        /* all stack items are processed */
        MUTATE_LIST_PTR(*current, 0);
    }
}


// print head on current context (stack)
void list_print_head(readonly_list_ptr const current) {
    // visualise item
    printf("[0x%llx]: 0x%llx\n", (ADDR)current, (ADDR)current->payload);
}

// print all stack trace to output
// in a single loop, print out all elements except root element (which does not have a payload)
// as a result, all stack will be printed in last-to-first order (reverse)
void list_print(readonly_list_ptr const current) {
    // get current context's head
    // get root element
    // struct list *root = ctx->root;
    // sets the counter
    int i = 0; 
    // assigns current's head pointer to the temporary
    readonly_list_ptr tmp = current;
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
        } while (tmp != 0);
    }
    // stop on root element
}

void print_list_node(readonly_list_ptr* args) {
    const struct list_vtable* list = &list_vt;
    /* get current context's head */
    char *str = (*args)->payload;
    list->pop(args);
    char *format = (*args)->payload;
    list->pop(args);
    printf(format, str);
}

void list_demo() {
    // create list
    const struct list_vtable* list = &list_vt;

    // initialize list
    readonly_list_ptr head = list->init();

    char *str = "Hello, World!\n";
    char *format = "%s";

    // isolation mode
    readonly_list_ptr args = list->init();
    list->push(&args, format);
    list->push(&args, str);
    print_list_node(&args);
    list->destroy(&args);

    // no isolation
    list->push(&head, format);
    list->push(&head, str);
    print_list_node(&head);

    void* payload = (void*)0xdeadbeef;
    list->push(&head, payload);
    list->push(&head, ++payload);
    list->push(&head, ++payload);
    list->push(&head, ++payload);
    list->push(&head, ++payload);

    void* q_pop0 = head->payload;
    list->pop(&head);
    void* q_pop1 = head->payload;
    list->pop(&head);
    void* q_pop2 = head->payload;
    list->pop(&head);
    void* q_pop3 = head->payload;
    list->pop(&head);
    list->push(&head, q_pop3);
    q_pop3 = head->payload;
    list->pop(&head);
    void* q_pop4 = head->payload;
    list->pop(&head);
    list->destroy(&head);
}
