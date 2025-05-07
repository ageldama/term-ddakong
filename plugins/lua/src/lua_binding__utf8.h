#ifndef lua_binding__utf8_h
#define lua_binding__utf8_h 1

#include "extern_.h"
#include "lua.h"


EXTERN_ void *luab__utf8_unicode_to_utf8_pfn;

EXTERN_ int luab__utf8_unicode_to_utf8(lua_State *L);


#endif /* ! lua_binding__utf8_h */
