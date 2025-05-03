#include "plugin.h"

#include "im_handler.h"
#include "err.h"
#include "fd_io.h"
#include "global_flags.h"
#include "winsz.h"
#include "utf8_.h"
#include "termios_.h"
#include "sig.h"
#include "pty_.h"
#include "im_handler_hangeul.h"


/* SUPPORT: global_flags.h */

int __get_verbose_flag(void) { return verbose_flag; }
void __set_verbose_flag(const int verbose)
{ verbose_flag = verbose; }

char *__get_keylog_filename(void) { return keylog_filename; }
void __set_keylog_filename(char *sz_filename)
{ keylog_filename = sz_filename; }

char *__get_default_keylog_filename(void)
{ return default_keylog_filename; }


/* SUPPORT: im_handler_hangeul.h */

hangeul_automata_status *get_current_hangeul_automata_status(void)
{ return &_hangeul_avtomat; }


/* SUPPORT: $_ */

plugin_func_t *get_plugin_funcs(void)
{ return (plugin_func_t *) plugin_funcs; }

ssize_t get_plugin_funcs_len(void)
{ return plugin_funcs_len; }


/* function regitry */

const plugin_func_t plugin_funcs[] = {
  { .p_func = get_plugin_funcs,
    .sz_func_name = "get_plugin_funcs",
    .sz_func_doc = "", },
  { .p_func = get_plugin_funcs_len,
    .sz_func_name = "get_plugin_funcs_len",
    .sz_func_doc = "", },

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

  /* im_handler_hangeul.h */
  { .p_func = get_current_hangeul_automata_status,
    .sz_func_name = "get_current_hangeul_automata_status",
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

  /* fd_io.h */
  { .p_func = cp_fd,
    .sz_func_name = "cp_fd",
    .sz_func_doc = "", },
  { .p_func = fcntl_nb,
    .sz_func_name = "fcntl_nb",
    .sz_func_doc = "", },

  /* global_flags.h */
  { .p_func = print_banner,
    .sz_func_name = "print_banner",
    .sz_func_doc = "", },
  { .p_func = __get_verbose_flag,
    .sz_func_name = "get_verbose_flag",
    .sz_func_doc = "", },
  { .p_func = __set_verbose_flag,
    .sz_func_name = "set_verbose_flag",
    .sz_func_doc = "", },
  { .p_func = __get_keylog_filename,
    .sz_func_name = "get_keylog_filename",
    .sz_func_doc = "", },
  { .p_func = __set_keylog_filename,
    .sz_func_name = "set_keylog_filename",
    .sz_func_doc = "", },
  { .p_func = __get_default_keylog_filename,
    .sz_func_name = "get_default_keylog_filename",
    .sz_func_doc = "", },

  /* winsz.h */
  { .p_func = winsz_update,
    .sz_func_name = "winsz_update",
    .sz_func_doc = "", },

  /* utf8_.h */
  { .p_func = unicode_to_utf8,
    .sz_func_name = "unicode_to_utf8",
    .sz_func_doc = "", },

  /* termios_.h */
  { .p_func = termios__init,
    .sz_func_name = "termios__init",
    .sz_func_doc = "", },

  { .p_func = termios__reset,
    .sz_func_name = "termios__reset",
    .sz_func_doc = "", },

  /* sig_.h */
  { .p_func = signal_trap_norecover,
    .sz_func_name = "signal_trap_norecover",
    .sz_func_doc = "", },

  /* pty_.h */
  { .p_func = forkpty_with_exec,
    .sz_func_name = "forkpty_with_exec",
    .sz_func_doc = "", },
  { .p_func = kill_forkpty,
    .sz_func_name = "kill_forkpty",
    .sz_func_doc = "", },

};

const ssize_t plugin_funcs_len = sizeof(plugin_funcs) / sizeof(plugin_func_t);
