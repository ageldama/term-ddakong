#include "config.h"

#include "lua_binding.h"
#include "lua_binding__err.h"
#include "plugin-api.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lua.h"

void *luab__ERR_err_p_pfn = NULL;
void *luab__ERR_clear_pfn = NULL;
void *luab__ERR_set_pfn = NULL;
void *luab__ERR_dieif_pfn = NULL;
void *luab__ERR_warn_and_clear_if_pfn = NULL;

int
luab__ERR_err_p (lua_State *L)
{
  /* (p_err) => (b) */
  void *p_err = lua_touserdata (L, -1);
  assert (p_err != NULL);
  lua_remove (L, 1);

  typedef char (*pfn_t) (void *);
  assert (luab__ERR_err_p_pfn != NULL);
  char b_ret = ((pfn_t)luab__ERR_err_p_pfn) (p_err);

  lua_pushboolean (L, (int)b_ret);

  return 1;
}

int
luab__ERR_clear (lua_State *L)
{
  /* (p_err) => () */
  void *p_err = lua_touserdata (L, -1);
  assert (p_err != NULL);
  lua_remove (L, 1);

  typedef void (*pfn_t) (void *);
  assert (luab__ERR_clear_pfn != NULL);

  ((pfn_t)luab__ERR_clear_pfn) (p_err);

  return 0;
}

int
luab__ERR_set (lua_State *L)
{
  /* (p_err, sz_errmsg) => () */
  const char *sz_errmsg = lua_tostring (L, -2);
  assert (sz_errmsg != NULL);
  void *p_err = lua_touserdata (L, -1);
  assert (p_err != NULL);
  lua_remove (L, 2);

  typedef void (*pfn_t) (void * /*p_err*/, const char * /*errmsg*/,
                         void * /*errmsg_free*/);
  assert (luab__ERR_set_pfn != NULL);

  const ssize_t sz_len = strlen (sz_errmsg);
  char *sz2 = (char *)malloc (sz_len);
  strncpy (sz2, sz_errmsg, sz_len);

  ((pfn_t)luab__ERR_set_pfn) (p_err, sz2, free);

  return 0;
}

int
luab__ERR_dieif (lua_State *L)
{
  /* (p_err) => () */
  void *p_err = lua_touserdata (L, -1);
  assert (p_err != NULL);
  lua_remove (L, 1);

  typedef void (*pfn_t) (void *);
  assert (luab__ERR_dieif_pfn != NULL);

  ((pfn_t)luab__ERR_dieif_pfn) (p_err);

  return 0;
}

int
luab__ERR_warn_and_clear_if (lua_State *L)
{
  /* (p_err) => () */
  void *p_err = lua_touserdata (L, -1);
  assert (p_err != NULL);
  lua_remove (L, 1);

  typedef void (*pfn_t) (void *, void *);
  assert (luab__ERR_warn_and_clear_if_pfn != NULL);

  ((pfn_t)luab__ERR_warn_and_clear_if_pfn) (p_err, stderr);

  return 0;
}

int
luab__ERR_get_errmsg (lua_State *L)
{
  /* (p_err) => (errmsg) */
  void *p_err = lua_touserdata (L, -1);
  assert (p_err != NULL);
  lua_remove (L, 1);

  typedef struct
  {
    char *errmsg;
    void *errmsg_free;
  } ERR_t;

  lua_pushstring (L, ((ERR_t *)p_err)->errmsg);

  return 1;
}
