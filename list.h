#ifndef _LIST_H_
#define _LIST_H_

#include "lisp.h"

typedef void * assignable_ptr;
typedef struct list * assignable_list_ptr;

#define MUTATE_PTR(a, b) *((assignable_ptr*)&a) = b
#define MUTATE_LIST_PTR(a, b) *((assignable_list_ptr*)&a) = b

void list_alloc(readonly_list_ptr ctx);
void list_parse(readonly_list_ptr ctx);
void list_free(readonly_list_ptr ctx);

const struct list_vtable list_vt;

#endif