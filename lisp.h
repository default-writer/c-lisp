#ifndef _LISP_H_
#define _LISP_H_

typedef struct str * const str_context;
typedef struct str {
    char* self;
    void (*alloc)(str_context);
    void (*run)(str_context);
    void (*free)(str_context);
} str;

typedef struct list * const list_ptr;
typedef struct list {
    /* points to previous node */
    list_ptr prev;
    /* payload */
    void*  payload;
} list;

typedef struct mutable_list * mutable_list_ptr;
typedef struct mutable_list {
    /* points to previous node */
    mutable_list_ptr prev;
    /* payload */
    void*  payload;
} mutation_list;

struct list_context { 
    // head element
    list_ptr head;
};

struct list_vtable {
    /* initialize context */
    void (*init)(list_ptr* const current);
    /* push item on current context (stack) */
    void (*push)(list_ptr* const current, void* item);
    /* pop item on current context (stack) */
    void* (*pop)(list_ptr* const current);
    /* destroy context */
    void (*destroy)(list_ptr* const current);
};

const struct list_vtable list_vt;

#endif