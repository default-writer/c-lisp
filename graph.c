#define DEBUG

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"

typedef long long unsigned int ADDR;
typedef void * assignable_ptr;
typedef struct graph * assignable_graph_ptr;

#define MUTATE_PTR(a, b) *((assignable_ptr*)&a) = b
#define MUTATE_GRAPH_PTR(a, b) *((assignable_graph_ptr*)&a) = b

readonly_graph_ptr graph_init();
void graph_push(readonly_graph_ptr* const current, void* payload);
void graph_pop(readonly_graph_ptr* const current);
void graph_push_child(readonly_graph_ptr* const current, void* payload);
void graph_pop_child(readonly_graph_ptr* const current);
void graph_destroy(readonly_graph_ptr* const current);

void graph_print_head(readonly_graph_ptr const current);
void graph_print(readonly_graph_ptr const current);

/* graph vtable */
const struct graph_vtable graph_vt = {
    .init = graph_init,
    .push = graph_push,
    .pop = graph_pop,
    .push_child = graph_push_child,
    .pop_child = graph_pop_child,
    .destroy = graph_destroy
};

/* free memory block */
void graph_free(readonly_graph_ptr ptr) {
#ifdef DEBUG
    printf("free: 0x%llx\n", (ADDR)ptr);
#endif
#ifndef DIRTY
    /* zero all pointers */
    MUTATE_GRAPH_PTR(ptr->prev, 0);
    MUTATE_PTR(ptr->payload, 0);
#endif
    /* free pointer */
    free(ptr);
}

/* initializes the new context's head element */
/* as a result, new memory block will be allocated */
/* current context pointer set to zero */
readonly_graph_ptr graph_init() {
    /* sets current context's head element */
    /* stores into pre-allocated value newly allocated memory buffer pointer */
    readonly_graph_ptr ptr = (readonly_graph_ptr)calloc(1, sizeof(struct graph));
#ifdef DEBUG
    printf("alloc: 0x%llx\n", (ADDR)ptr);
#endif
    /* returns current head pointer */
    return ptr;
}

/* allocates a memory for provided payload  */
/* at current context, data payload stored at allocated memory buffer */
/* as a result, items counter will increase */
void graph_push(readonly_graph_ptr* const current, void* payload) {
    /* stores into pre-allocated value newly allocated memory buffer pointer */
    readonly_graph_ptr ptr = graph_init();
    /* sets the new data into allocated memory buffer */
    MUTATE_PTR(ptr->payload, payload);
    /* pushes new item on top of the stack in current context */
    /* assigns item's prev pointer to head pointer */
    MUTATE_GRAPH_PTR(ptr->prev, *current);
    /* advances position of head pointer to the new head */
    MUTATE_GRAPH_PTR(*current, ptr);
#ifdef DEBUG
    graph_print(ptr);
#endif
}

/* pop existing element at the top of the stack/queue/graph */
/* at current context, existing head will be removed out of stack */
/* for the new stack header, correcponding values will be fixed */
/* as a result, header will be set to previous position, represented as head's reference to previos head */
void graph_pop(readonly_graph_ptr* const current) {
    /* get current context's head */
    readonly_graph_ptr head = *current;
    /* if we call method on empty stack, do not return head element, return null element by convention */
    if (head != 0) {
        /* gets previos pointer */
        readonly_graph_ptr prev = head->prev;
        /* free current pointer */
        graph_free(head);    
        /* rewinds head pointer to previous pointer value */
        MUTATE_GRAPH_PTR(*current, prev);
    }
}

/* allocates a memory for provided payload  */
/* at current context, data payload stored at allocated memory buffer */
/* as a result, items counter will increase */
void graph_push_child(readonly_graph_ptr* const current, void* payload) {
    /* stores into pre-allocated value newly allocated memory buffer pointer */
    readonly_graph_ptr ptr = graph_init();
    /* sets the new data into allocated memory buffer */
    MUTATE_PTR(ptr->payload, payload);
    /* pushes new item on top of the stack in current context */
    /* assigns item's prev pointer to head pointer */
    MUTATE_GRAPH_PTR(ptr->prev, *current);
    /* advances position of head pointer to the new head */
    MUTATE_GRAPH_PTR(*current, ptr);
#ifdef DEBUG
    graph_print(ptr);
#endif
}

/* pop existing element at the top of the stack/queue/graph */
/* at current context, existing head will be removed out of stack */
/* for the new stack header, correcponding values will be fixed */
/* as a result, header will be set to previous position, represented as head's reference to previos head */
void graph_pop_child(readonly_graph_ptr* const current) {
    /* get current context's head */
    readonly_graph_ptr head = *current;
    /* if we call method on empty stack, do not return head element, return null element by convention */
    if (head != 0) {
        /* charts */
        readonly_graph_ptr* child = &head->child;
        if (*child != 0) {
            /* gets previos pointer */
            readonly_graph_ptr prev = head->prev;
            /* free current pointer */
            graph_free(head);    
            /* rewinds head pointer to previous pointer value */
            MUTATE_GRAPH_PTR(*current, prev);
        }
    }
}

/* destroys the memory stack */
/* frees all memory elements */
/* as a result, memory will be freed */
void graph_destroy(readonly_graph_ptr* const current) {
    /* get current context's head */
    /* assigns currently selected item pointer to temporary */
    readonly_graph_ptr head = *current;
    /* if not already freed */
    if (head != 0) {
        /* until we found element with no parent (previous) node */
        do {
            /* gets previos pointer */           
            readonly_graph_ptr prev = head->prev;
            /* free current pointer */
            graph_free(head);
            /* rewinds head pointer to previous pointer value */
            MUTATE_GRAPH_PTR(head, prev);
        } while (head != 0);
        /* all stack items are processed */
        MUTATE_GRAPH_PTR(*current, 0);
    }
}


// print head on current context (stack)
void graph_print_head(readonly_graph_ptr const current) {
    // visualise item
    printf("[0x%llx]: 0x%llx\n", (ADDR)current, (ADDR)current->payload);
}

// print all stack trace to output
// in a single loop, print out all elements except root element (which does not have a payload)
// as a result, all stack will be printed in last-to-first order (reverse)
void graph_print(readonly_graph_ptr const current) {
    // get current context's head
    // get root element
    // struct graph *root = ctx->root;
    // sets the counter
    int i = 0; 
    // assigns current's head pointer to the temporary
    readonly_graph_ptr tmp = current;
    if (tmp != 0)
    {
        // until we found root element (element with no previous element reference)
        do {
#ifdef DEBUG
            // debug output of memory dump
            printf("%d: 0x%llx 0x%llx\n", ++i, (ADDR)tmp, (ADDR)tmp->payload);
#endif
            // remember temprary's prior pointer value to temporary
            MUTATE_GRAPH_PTR(tmp, tmp->prev);
        } while (tmp != 0);
    }
    // stop on root element
}

void print_graph_node(readonly_graph_ptr* args) {
    const struct graph_vtable* graph = &graph_vt;
    /* get current context's head */
    char *str = (*args)->payload;
    graph->pop(args);
    char *format = (*args)->payload;
    graph->pop(args);
    printf(format, str);
}

void graph_demo() {
    // create graph
    const struct graph_vtable* graph = &graph_vt;

    // initialize graph
    readonly_graph_ptr gr = graph->init();

    char *str = "Hello, World!\n";
    char *format = "%s";

    // isolation mode
    readonly_graph_ptr args = graph->init();
    graph->push(&args, format);
    graph->push(&args, str);
    graph->push(&gr, args);
    print_graph_node(&args);

    graph->destroy(&args);
    graph->destroy(&gr);
}
