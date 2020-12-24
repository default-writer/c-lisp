#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lisp.h"

#include "str.h"

void str_alloc(str_context ctx) {
    // char str[100];
    // sscanf(ctx->self, "%[^\n]",str);
    // char len = strlen(str) + 1;
    // ctx->self = calloc(len, sizeof(char));
    // memcpy(ctx->self, str, len);
}

void str_run(str_context ctx) {
    printf("%s", ctx->self);
}

void str_free(str_context ctx) {
    // free(ctx->self);
    // ctx->self = NULL;
}