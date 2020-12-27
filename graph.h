#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef void * const readonly_ptr;
typedef struct graph * const readonly_graph_ptr;
typedef struct graph {
    /* points to previous node */
    readonly_graph_ptr prev;
    /* child nodes */
    readonly_graph_ptr child;
    /* payload */
    readonly_ptr payload;
} graph;

struct graph_vtable {
    /* initialize context */
    readonly_graph_ptr (*init)();
    /* push item on current context (stack) */
    void (*push)(readonly_graph_ptr* const current, void* item);
    /* pop item on current context (stack) */
    void (*pop)(readonly_graph_ptr* const current);
    /* push child item */
    void (*push_child)(readonly_graph_ptr* const current, void* item);
    /* pop child item */
    void (*pop_child)(readonly_graph_ptr* const current);
    /* destroy context */
    void (*destroy)(readonly_graph_ptr* const current);
};

const struct graph_vtable graph_vt;

#endif