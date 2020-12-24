#ifndef _STR_H_
#define _STR_H_

#include "lisp.h"

void str_alloc(str_context);
void str_run(str_context);
void str_free(str_context);

#endif