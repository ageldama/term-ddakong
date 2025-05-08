/**
 * wordexp(3) helper
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#ifndef wordexp__h
#define wordexp__h 1

#include "extern_.h"

#include <stdlib.h>
#include <unistd.h>
#include <wordexp.h>

EXTERN_ char *wordexp__errmsg (const int n_wordexp);

EXTERN_ int wordexp_1st (const char *sz_input, char *sz_output,
                         const ssize_t sz_output_len);

#endif /* ! wordexp__h */
