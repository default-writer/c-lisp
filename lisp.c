#include <stdlib.h>
#include "lisp.h"
#include "list.h"

#include "str.h"

#define DEBUG

#ifdef DEBUG

#include <stddef.h>
#include <stdio.h>

typedef long long unsigned int ADDR;
#endif

void print_head(list_ptr* const current);
void list_print(list_ptr* const current);
void list_demo();

int main(int argc, char* argv) {

    str_context ctx = (str_context)calloc(1, sizeof(struct str));
    ctx->alloc = str_alloc;
    ctx->run = str_run;
    ctx->free = str_free;

    ctx->self = "Hello, World!";

    ctx->alloc(ctx);
    ctx->run(ctx);
    ctx->free(ctx);

    free(ctx);

    list_demo();

    return 0;
}

void list_demo() {
    // initialize current context (stack)
    struct list_context* ctx = (struct list_context*)calloc(1, sizeof(struct list_context));
    // create list
    const struct list_vtable* list = &list_vt;

    list_ptr ptr = ctx->head;

    // initialize list
    list->init(&ptr);

    list_ptr* const current = &ptr;

    void* payload = (void*)0xdeadbeef;
    void* is_null[] = {
        list->pop(current)
    };
    if (0 != is_null[0]) {
        return;
    }
    list->push(current, payload);
    print_head(current);
    list->push(current, ++payload);
    print_head(current);
    list->push(current, ++payload);
    print_head(current);
    list->push(current, ++payload);
    print_head(current);
    list->push(current, ++payload);
    print_head(current);
#ifdef DEBUG
    printf("\n");
#endif
#ifdef DEBUG
    list_print(current);
#endif
    void* q_pop0 = list->pop(current); 
#ifdef DEBUG
    list_print(current);
#endif
    void* q_pop1 = list->pop(current); 
#ifdef DEBUG
    list_print(current);
#endif
    void* q_pop2 = list->pop(current); 
#ifdef DEBUG
    list_print(current);
#endif
    void* q_pop3 = list->pop(current); 
    list->push(current, q_pop3);
    q_pop3 = list->pop(current); 
#ifdef DEBUG
    list_print(current);
#endif
    void* q_pop4 = list->pop(current); 
#ifdef DEBUG
    list_print(current);
#endif

    // destroy list
    list->destroy(&ptr);
    // free curent context (stack)
    free(ctx);
}

// print head on current context (stack)
void print_head(list_ptr* const current) {
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