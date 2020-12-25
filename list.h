#ifndef _LIST_H_
#define _LIST_H_

#include "lisp.h"

void list_demo();

typedef void * const readonly_ptr;
typedef struct list * const readonly_list_ptr;
typedef struct list {
    /* points to previous node */
    readonly_list_ptr prev;
    /* payload */
    readonly_ptr payload;
} list;

struct list_vtable {
    /* initialize context */
    readonly_list_ptr (*init)();
    /* push item on current context (stack) */
    readonly_list_ptr (*push)(readonly_list_ptr const current, void* item);
    /* pop item on current context (stack) */
    readonly_list_ptr (*pop)(readonly_list_ptr const current);
    /* destroy context */
    void (*destroy)(readonly_list_ptr const current);
};

const struct list_vtable list_vt;

#endif