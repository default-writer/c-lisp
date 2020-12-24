#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "lisp.h"

void str_alloc(context ctx) {
    char * str = "Hello, World!";
    char len = strlen(str) + 1;
    ctx->self = calloc(len, sizeof(char));
    memcpy(ctx->self, str, len);
}

void str_run(context ctx) {
    printf("%s", ctx->self);
}

void str_free(context ctx) {
    free(ctx->self);
    ctx->self = NULL;
}
