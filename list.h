#ifndef _LIST_H_
#define _LIST_H_

#include "lisp.h"

void list_alloc(readonly_list_ptr ctx);
void list_parse(readonly_list_ptr ctx);
void list_free(readonly_list_ptr ctx);

readonly_list_ptr list_init();
void list_push(readonly_list_ptr* const current, void* payload);
void* list_pop(readonly_list_ptr* const current);
void list_destroy(readonly_list_ptr* const current);
void list_print_head(readonly_list_ptr* const current);
void list_print(readonly_list_ptr* const current);

const struct list_vtable list_vt;

#endif