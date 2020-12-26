#define DEBUG

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "lisp.h"

#include "list.h"
#include "graph.h"

#include "str.h"

extern void list_demo();
extern void graph_demo();

int main(int argc, char* argv) {

    str_context ctx = (str_context)calloc(1, sizeof(struct str));
    ctx->alloc = str_alloc;
    ctx->run = str_run;
    ctx->free = str_free;

    ctx->self = "Hello, World!\n";

    ctx->alloc(ctx);
    ctx->run(ctx);
    ctx->free(ctx);

    free(ctx);

    list_demo();
    graph_demo();

    return 0;
}