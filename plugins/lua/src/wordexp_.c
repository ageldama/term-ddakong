#include "wordexp_.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

char *
wordexp__errmsg (const int n_wordexp)
{
  if (n_wordexp == 0)
    return NULL;
  else
    switch (n_wordexp)
      {
      case WRDE_BADCHAR:
        return "Illegal occurrence of newline or one of |, &, ;, <, >, (, ), "
               "{, }.";
      case WRDE_BADVAL:
        return "An undefined shell variable was referenced, and the "
               "WRDE_UNDEF flag told us to consider this an error.";
      case WRDE_CMDSUB:
        return "Command substitution requested, but the WRDE_NOCMD flag told "
               "us to consider this an error.";
      case WRDE_NOSPACE:
        return "Out of memory.";
      case WRDE_SYNTAX:
        return "Shell  syntax  error,  such  as  unbalanced  parentheses  or "
               "unmatched quotes.";
      default:
        return "???";
      }
}

int
wordexp_1st (const char *sz_input, char *sz_output,
             const ssize_t sz_output_len)
{
  wordexp_t wexp;
  char **wexp_w;

  int n_wordexp = wordexp (sz_input, &wexp, WRDE_NOCMD | WRDE_UNDEF);
  if (n_wordexp != 0)
    return n_wordexp; /* FAIL */
  if (wexp.we_wordc < 1)
    return WRDE_UNDEF; /* FAIL */

  strncpy (sz_output, wexp.we_wordv[0], sz_output_len);

  wordfree (&wexp);

  return 0; /* OK */
}
