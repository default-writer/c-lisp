#include <stdlib.h>
#include "lisp.h"
#include "list.h"

void main_alloc(context ctx) {
    ctx->alloc(ctx);
}

void main_run(context ctx) {
    ctx->run(ctx);
}

void main_free(context ctx) {
    ctx->free(ctx);
}

int main(int argc, char* argv) {

    context ctx = (context)calloc(1, sizeof(struct list));
    ctx->alloc = str_alloc;
    ctx->run = str_run;
    ctx->free = str_free;

    main_alloc(ctx);
    main_run(ctx);
    main_free(ctx);

    free(ctx);

    return 0;
}