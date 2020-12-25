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

readonly_list_ptr list_init();
readonly_list_ptr list_push(readonly_list_ptr const current, void* payload);
void* list_pop(readonly_list_ptr* const current);
void list_destroy(readonly_list_ptr* const current);
void list_print_head(readonly_list_ptr* const current);
void list_print(readonly_list_ptr* const current);

const struct list_vtable list_vt;

#endif