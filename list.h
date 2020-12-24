#ifndef _LIST_H_
#define _LIST_H_

#include "lisp.h"

void list_alloc(list_ptr ctx);
void list_parse(list_ptr ctx);
void list_free(list_ptr ctx);

void list_init(list_ptr* const current);
void list_push(list_ptr* const current, void* payload);
void* list_pop(list_ptr* const current);
void list_destroy(list_ptr* const current);

const struct list_vtable list_vt;

#endif