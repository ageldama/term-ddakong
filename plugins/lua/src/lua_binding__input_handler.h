#ifndef lua_binding__input_handler_h
#define lua_binding__input_handler_h 1

#include "extern_.h"
#include "lua.h"

#include <stdint.h>


typedef void handle_write_to_child_cb_t (const ssize_t n_written,
                                         const char *buf, void *cb_aux);


typedef void (*handle_input_fn_t)
(void *p_status,
 const int fd_keyin,
 const int fd_child,
 char *buf,
 const ssize_t buf_max,
 handle_write_to_child_cb_t write_cb,
 void *write_cb_aux);


EXTERN_ void *luab__input_handler_get_current_handle_input_fn_pfn;
EXTERN_ void *luab__input_handler_set_current_handle_input_fn_pfn;


EXTERN_ int luab__input_handler_get_current_handle_input_fn (lua_State *L);

EXTERN_ int luab__input_handler_set_current_handle_input_fn (lua_State *L);

EXTERN_ void luab__input_handler_handle_input
(void *p_status,
 const int fd_keyin,
 const int fd_child,
 char *buf,
 const ssize_t buf_max,
 handle_write_to_child_cb_t write_cb,
 void *write_cb_aux);



#endif /* ! lua_binding__input_handler_h */
