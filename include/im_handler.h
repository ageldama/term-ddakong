
#ifndef im_handler_h
#define im_handler_h 1

#include "extern_.h"
#include "typedef_.h"
#include <stdlib.h>
#include <unistd.h>

#ifndef IM_HANDLER_TOGGLE_STATE

#define IM_HANDLER_TOGGLE_STATE BYTE

#define IM_HANDLER_TOGGLE__OFF ((IM_HANDLER_TOGGLE_STATE)0)
#define IM_HANDLER_TOGGLE__ONCE ((IM_HANDLER_TOGGLE_STATE)1)

#endif /* ! IM_HANDLER_TOGGLE_STATE */

typedef void handle_write_to_child_cb_t (const ssize_t n_written,
                                         const BYTE *buf, void *cb_aux);

typedef struct
{
  BOOL im_mode;
  IM_HANDLER_TOGGLE_STATE toggle;
} im_handler_status;

EXTERN_
void im_handler_status__empty (im_handler_status *p_status);

EXTERN_
void handle_stdin (im_handler_status *p_status, const int fd_keyin,
                   const int fd_child, BYTE *buf, const ssize_t buf_max,
                   handle_write_to_child_cb_t write_cb, void *write_cb_aux);

#endif /* ! im_handler_h */
