#ifndef _LISP_H_
#define _LISP_H_

typedef struct list * const context;
typedef struct list {
    void* self;
    void (*alloc)(context);
    void (*run)(context);
    void (*free)(context);
} list;

#endif