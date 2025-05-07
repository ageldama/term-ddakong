#ifndef wordexp__h
#define wordexp__h 1

#include "extern_.h"

#include <stdlib.h>
#include <wordexp.h>

EXTERN_ char *wordexp__errmsg (const int n_wordexp);

EXTERN_ int wordexp_1st (const char *sz_input, char *sz_output,
                         const ssize_t sz_output_len);

#endif /* ! wordexp__h */
