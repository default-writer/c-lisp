#define DEBUG

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "lisp.h"
#include "list.h"

#include "str.h"

void list_demo();

int main(int argc, char* argv) {

    str_context ctx = (str_context)calloc(1, sizeof(struct str));
    ctx->alloc = str_alloc;
    ctx->run = str_run;
    ctx->free = str_free;

    ctx->self = "Hello, World!\n";

    ctx->alloc(ctx);
    ctx->run(ctx);
    ctx->free(ctx);

    free(ctx);

    list_demo();

    return 0;
}

struct list_context {
    // head element
    readonly_list_ptr head;
};

void list_demo() {
    // initialize current context (stack)
    struct list_context* ctx = (struct list_context*)calloc(1, sizeof(struct list_context));
    // create list
    const struct list_vtable* list = &list_vt;

    readonly_list_ptr ptr = ctx->head;

    // initialize list
    list->init(&ptr);

    readonly_list_ptr* const current = &ptr;

    void* payload = (void*)0xdeadbeef;
    void* is_null[] = {
        list->pop(current)
    };
    if (0 != is_null[0]) {
        return;
    }
    list->push(current, payload);
    list->print_head(current);
    list->push(current, ++payload);
    list->print_head(current);
    list->push(current, ++payload);
    list->print_head(current);
    list->push(current, ++payload);
    list->print_head(current);
    list->push(current, ++payload);
    list->print_head(current);
#ifdef DEBUG
    printf("\n");
#endif
#ifdef DEBUG
    list->print(current);
#endif
    void* q_pop0 = list->pop(current); 
#ifdef DEBUG
    list->print(current);
#endif
    void* q_pop1 = list->pop(current); 
#ifdef DEBUG
    list->print(current);
#endif
    void* q_pop2 = list->pop(current); 
#ifdef DEBUG
    list->print(current);
#endif
    void* q_pop3 = list->pop(current); 
    list->push(current, q_pop3);
    q_pop3 = list->pop(current); 
#ifdef DEBUG
    list->print(current);
#endif
    void* q_pop4 = list->pop(current); 
#ifdef DEBUG
    list->print(current);
#endif

    // destroy list
    list->destroy(&ptr);
    // free curent context (stack)
    free(ctx);
}
