#ifndef _NEW_LIST_H_
#define _NEW_LIST_H_

typedef void * const readonly_ptr;
typedef struct new_list * const readonly_list_ptr;
typedef struct new_list_item * const readonly_list_item_ptr;

typedef struct new_list_item {
    /* points to previous node */
    readonly_list_item_ptr prev;
    /* payload */
    readonly_ptr payload;
} new_list_item;

typedef struct new_list {
    /* points to previous node */
    readonly_list_item_ptr head;
    /* points to previous node */
    readonly_list_item_ptr tail;
} new_list;

struct new_list_vtable {
    /* initialize context */
    readonly_list_ptr (*init)();
    /* push item on current context (stack) */
    void (*push)(readonly_list_ptr* const current, void* item);
    /* pop item on current context (stack) */
    void (*pop)(readonly_list_ptr* const current);
    /* destroy context */
    void (*destroy)(readonly_list_ptr* const current);
};

const struct new_list_vtable new_list_vt;

#endif