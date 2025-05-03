/**
 * Simple error facility for plain-C
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#include "err.h"
#include "cc_nanny.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

BOOL
ERR_err_p (const ERR *p_err)
{
  assert (p_err != NULL);
  if (p_err->errmsg == NULL)
    return FALSE;
  return TRUE;
}

void
ERR_clear (ERR *p_err)
{
  assert (p_err != NULL);
  if (p_err->errmsg_free != NULL)
    {
      p_err->errmsg_free (p_err->errmsg);
    }
  p_err->errmsg = NULL;
}

void
ERR_set (ERR *p_err, const char *errmsg, ERR_errmsg_free errmsg_free)
{
  assert (p_err != NULL);
  assert (FALSE == ERR_err_p (p_err));

  p_err->errmsg = (char *)errmsg;
  p_err->errmsg_free = errmsg_free;
}

char *
ERR_printf (ERR *p_err, const char *errmsg_fmt, ...)
{
  char *outbuf = NULL;

  assert (p_err != NULL);
  assert (FALSE == ERR_err_p (p_err));

  va_list vargs;
  va_start (vargs, errmsg_fmt);
  int n UNUSED = vasprintf (&outbuf, errmsg_fmt, vargs);
  va_end (vargs);

  p_err->errmsg = outbuf;
  p_err->errmsg_free = free;

  return p_err->errmsg;
}

void
ERR_dieif (const ERR *p_err)
{
  assert (p_err != NULL);

  if (ERR_err_p (p_err))
    {
      assert (p_err->errmsg == NULL);
      assert (p_err == NULL); /* fallback */
    }
}

void
ERR_warn_and_clear_if (ERR *p_err, FILE *fp_out)
{
  assert (p_err != NULL);

  if (ERR_err_p (p_err))
    {
      FILE *fp = fp_out;
      if (fp == NULL) fp = stderr;
      fprintf (fp_out, "[WARN] %s\n", p_err->errmsg);
      ERR_clear (p_err);
    }
}

void ERR_set_nofree_fn(ERR *p_err, const char *sz_errmsg)
{
  ERR_set_nofree(p_err, sz_errmsg);
}
