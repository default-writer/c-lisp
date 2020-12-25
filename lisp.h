#ifndef _LISP_H_
#define _LISP_H_

typedef struct str * const str_context;
typedef struct str {
    char* self;
    void (*alloc)(str_context);
    void (*run)(str_context);
    void (*free)(str_context);
} str;

#endif