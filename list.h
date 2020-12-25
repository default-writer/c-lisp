#ifndef _LIST_H_
#define _LIST_H_

#include "lisp.h"

typedef void * assignable_ptr;
typedef struct list * assignable_list_ptr;

#define MUTATE_PTR(a, b) *((assignable_ptr*)&a) = b
#define MUTATE_LIST_PTR(a, b) *((assignable_list_ptr*)&a) = b

const struct list_vtable list_vt;

#endif