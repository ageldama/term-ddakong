#ifndef __plugin_api_h__
#define __plugin_api_h__ 1

#if defined(__cplusplus)
#define EXTERN_ extern "c"
#else
#define EXTERN_ extern
#endif


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * 1-바이트
 *
 * C23-등에서 정의해주기 전에는 이렇게 적당히 쓰려고.
 */
#ifndef BYTE
#define BYTE char
#endif /* ! BYTE */

/**
 * "true" (BOOL)
 */
#ifndef TRUE
#define TRUE 1
#endif /* ! TRUE */

/**
 * "false" (BOOL)
 */
#ifndef FALSE
#define FALSE 0
#endif /* ! FALSE */

/**
 * BOOL-타입 (1바이트)
 */
#ifndef BOOL
#define BOOL char
#endif /* ! BOOL */


#ifndef IM_HANDLER_TOGGLE_STATE

/** "toggle-key" 눌린 횟수 카운터 타입 */
#define IM_HANDLER_TOGGLE_STATE BYTE

/** "toggle-key" 눌리지 않음 */
#define IM_HANDLER_TOGGLE__OFF ((IM_HANDLER_TOGGLE_STATE)0)

/** "toggle-key" 한 번 눌림 */
#define IM_HANDLER_TOGGLE__ONCE ((IM_HANDLER_TOGGLE_STATE)1)

#endif /* ! IM_HANDLER_TOGGLE_STATE */


typedef struct {
  void *p_func;
  char *sz_func_name;
  char *sz_func_doc;
} plugin_func_t;


EXTERN_ void ddakong_plugin_entry
(const plugin_func_t *, const ssize_t);

EXTERN_ void ddakong_plugin_deinit();


typedef struct
{
  BOOL im_mode;
  IM_HANDLER_TOGGLE_STATE toggle;
} im_handler_status;

typedef void handle_write_to_child_cb_t (const ssize_t n_written,
                                         const BYTE *buf, void *cb_aux);

typedef void (*handle_input_fn_t)
(void *p_status,
 const int fd_keyin,
 const int fd_child,
 BYTE *buf,
 const ssize_t buf_max,
 handle_write_to_child_cb_t write_cb,
 void *write_cb_aux);

typedef void (*set_current_handle_input_fn_t) (handle_input_fn_t fn);

EXTERN_ void
handle_input (im_handler_status *p_status, const int fd_keyin,
              const int fd_child, BYTE *buf, const ssize_t buf_max,
              handle_write_to_child_cb_t write_cb, void *write_cb_aux);

#endif /* ! __plugin_api_h__ */
