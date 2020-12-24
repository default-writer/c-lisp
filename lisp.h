#ifndef _LISP_H_
#define _LISP_H_

typedef struct str * const str_context;
typedef struct str {
    char* self;
    void (*alloc)(str_context);
    void (*run)(str_context);
    void (*free)(str_context);
} str;

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
    void (*init)(readonly_list_ptr* const current);
    /* push item on current context (stack) */
    void (*push)(readonly_list_ptr* const current, void* item);
    /* pop item on current context (stack) */
    void* (*pop)(readonly_list_ptr* const current);
    /* destroy context */
    void (*destroy)(readonly_list_ptr* const current);
    /* print head */
    void (*print_head)(readonly_list_ptr* const current);
    /* print list */
    void (*print)(readonly_list_ptr* const current);
};

const struct list_vtable list_vt;

#endif