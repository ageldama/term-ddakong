
#ifndef err_h
#define err_h 1

#include <stdio.h>
#include <stdlib.h>

#include "extern_.h"
#include "typedef_.h"

typedef void (*ERR_errmsg_free) (void *_Nullable);

typedef struct
{
  char *errmsg;
  ERR_errmsg_free errmsg_free;
} ERR;

EXTERN_ BOOL ERR_err_p (const ERR *p_err);

EXTERN_ void ERR_clear (ERR *p_err);

EXTERN_ void ERR_set (ERR *p_err, const char *errmsg,
                      ERR_errmsg_free errmsg_free);

#define ERR_set_nofree(p_err, errmsg) (ERR_set (p_err, errmsg))

EXTERN_ char *ERR_printf (ERR *p_err, const char *errmsg_fmt, ...);

EXTERN_ void ERR_dieif (const ERR *p_err);

EXTERN_ void ERR_warn_and_clear_if (ERR *p_err, FILE *fp_out);

#define ERR_assert(p_err, assertion)                                          \
  ((assertion) ?: ERR_set_nofree (p_err, "Assertion failed: "##assertion))

#endif /* ! err_h */
