#include "plugin.h"

#include "im_handler.h"
#include "err.h"



/* function regitry */

const plugin_func_t plugin_funcs[] = {
  /* im_handler.h */
  { .p_func = get_current_handle_input_fn,
    .sz_func_name = "get_current_handle_input_fn",
    .sz_func_doc = "", },
  { .p_func = set_current_handle_input_fn,
    .sz_func_name = "set_current_handle_input_fn",
    .sz_func_doc = "", },
  { .p_func = get_current_handle_input_status,
    .sz_func_name = "get_current_handle_input_status",
    .sz_func_doc = "", },
  { .p_func = set_current_handle_input_status,
    .sz_func_name = "set_current_handle_input_status",
    .sz_func_doc = "", },
  { .p_func = im_handler_status__empty,
    .sz_func_name = "hangeul2_im_handler_status_empty",
    .sz_func_doc = "", },
  { .p_func = handle_stdin,
    .sz_func_name = "hangeul2_handle_stdin",
    .sz_func_doc = "", },

  /* err.h */
  { .p_func = ERR_err_p,
    .sz_func_name = "ERR_err_p",
    .sz_func_doc = "", },
  { .p_func = ERR_clear,
    .sz_func_name = "ERR_clear",
    .sz_func_doc = "", },
  { .p_func = ERR_set,
    .sz_func_name = "ERR_set",
    .sz_func_doc = "", },
  { .p_func = ERR_set_nofree_fn,
    .sz_func_name = "ERR_set_nofree",
    .sz_func_doc = "", },
  { .p_func = ERR_dieif,
    .sz_func_name = "ERR_dieif",
    .sz_func_doc = "", },
  { .p_func = ERR_warn_and_clear_if,
    .sz_func_name = "ERR_warn_and_clear_if",
    .sz_func_doc = "", },
  
};

const ssize_t plugin_funcs_len = sizeof(plugin_funcs) / sizeof(plugin_func_t);
