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

void list_demo() {
    // create list
    const struct list_vtable* list = &list_vt;

    // initialize list
    readonly_list_ptr ptr = list->init();

    readonly_list_ptr* const current = &ptr;

    void* payload = (void*)0xdeadbeef;
    void* is_null[] = {
        list->pop(current)
    };
    if (0 != is_null[0]) {
        return;
    }
    MUTATE_LIST_PTR(ptr, list->push(ptr, payload));
    list->print_head(ptr);
    MUTATE_LIST_PTR(ptr, list->push(ptr, ++payload));
    list->print_head(ptr);
    MUTATE_LIST_PTR(ptr, list->push(ptr, ++payload));
    list->print_head(ptr);
    MUTATE_LIST_PTR(ptr, list->push(ptr, ++payload));
    list->print_head(ptr);
    MUTATE_LIST_PTR(ptr, list->push(ptr, ++payload));
    list->print_head(ptr);
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
    MUTATE_LIST_PTR(ptr, list->push(ptr, q_pop3));
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
}
