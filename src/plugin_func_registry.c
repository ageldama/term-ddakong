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
#include "hangeul.h"


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


/* SUPPORT: hangeul.h */

CHOJUNGJONG __hangeul_const_chojungjong_nul(void)
{ return CHOJUNGJONG_NUL; }

CHOJUNGJONG __hangeul_const_choseong(void)
{ return CHOSEONG;}

CHOJUNGJONG __hangeul_const_jungseong(void)
{ return JUNGSEONG;}

CHOJUNGJONG __hangeul_const_jongseong(void)
{ return JONGSEONG;}

CHOJUNGJONG __hangeul_const_moeum(void)
{ return MOEUM;}

CHOJUNGJONG __hangeul_const_jaeum(void)
{ return JAEUM;}

  /* TODO hangeul_automata_status__new */
  /* TODO hangeul_automata_status__delete */
  /* TODO hangeul_automata_status__get_stage */
  /* TODO hangeul_automata_status__set_stage */
  /* TODO hangeul_automata_status__get_prev_ch */
  /* TODO hangeul_automata_status__set_prev_ch */
  /* TODO hangeul_automata_status__get_cho */
  /* TODO hangeul_automata_status__set_cho */
  /* TODO hangeul_automata_status__get_jung */
  /* TODO hangeul_automata_status__set_jung */
  /* TODO hangeul_automata_status__get_jong */
  /* TODO hangeul_automata_status__set_jong */



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

  /* hangeul.h */
  { .p_func = __hangeul_const_chojungjong_nul,
    .sz_func_name = "hangeul_const_chojungjong_nul",
    .sz_func_doc = "", },
  { .p_func = __hangeul_const_choseong,
    .sz_func_name = "hangeul_const_choseong",
    .sz_func_doc = "", },
  { .p_func = __hangeul_const_jungseong,
    .sz_func_name = "hangeul_const_jungseong",
    .sz_func_doc = "", },
  { .p_func = __hangeul_const_jongseong,
    .sz_func_name = "hangeul_const_jongseong",
    .sz_func_doc = "", },
  { .p_func = __hangeul_const_moeum,
    .sz_func_name = "hangeul_const_moeum",
    .sz_func_doc = "", },
  { .p_func = __hangeul_const_jaeum,
    .sz_func_name = "hangeul_const_jaeum",
    .sz_func_doc = "", },

  /* TODO hangeul_automata_status__new */
  /* TODO hangeul_automata_status__delete */
  /* TODO hangeul_automata_status__get_stage */
  /* TODO hangeul_automata_status__set_stage */
  /* TODO hangeul_automata_status__get_prev_ch */
  /* TODO hangeul_automata_status__set_prev_ch */
  /* TODO hangeul_automata_status__get_cho */
  /* TODO hangeul_automata_status__set_cho */
  /* TODO hangeul_automata_status__get_jung */
  /* TODO hangeul_automata_status__set_jung */
  /* TODO hangeul_automata_status__get_jong */
  /* TODO hangeul_automata_status__set_jong */

  { .p_func = hangeul_clear_automata_status,
    .sz_func_name = "hangeul_clear_automata_status",
    .sz_func_doc = "", },
  { .p_func = hangeul_flush_automata_status,
    .sz_func_name = "hangeul_flush_automata_status",
    .sz_func_doc = "", },
  { .p_func = hangeul_auto_compose_to_unicode,
    .sz_func_name = "hangeul_auto_compose_to_unicode",
    .sz_func_doc = "", },
  { .p_func = hangeul_full_compose_to_unicode,
    .sz_func_name = "hangeul_full_compose_to_unicode",
    .sz_func_doc = "", },
  { .p_func = hangeul_jamo_compose_to_unicode,
    .sz_func_name = "hangeul_jamo_compose_to_unicode",
    .sz_func_doc = "", },
  { .p_func = hangeul_jamo_jaeum_to_unicode,
    .sz_func_name = "hangeul_jamo_jaeum_to_unicode",
    .sz_func_doc = "", },
  { .p_func = hangeul_partial_jamo_p,
    .sz_func_name = "hangeul_partial_jamo_p",
    .sz_func_doc = "", },
  { .p_func = hangeul_empty_automata_status_p,
    .sz_func_name = "hangeul_empty_automata_status_p",
    .sz_func_doc = "", },
  { .p_func = hangeul_2beol_alpha_as_jamoeum,
    .sz_func_name = "hangeul_2beol_alpha_as_jamoeum",
    .sz_func_doc = "", },
  { .p_func = hangeul_2beol_fill,
    .sz_func_name = "hangeul_2beol_fill",
    .sz_func_doc = "", },
  { .p_func = hangeul_2beol_find_code,
    .sz_func_name = "hangeul_2beol_find_code",
    .sz_func_doc = "", },
  { .p_func = hangeul_double_jaeum,
    .sz_func_name = "hangeul_double_jaeum",
    .sz_func_doc = "", },
  { .p_func = hangeul_put_unicode,
    .sz_func_name = "hangeul_put_unicode",
    .sz_func_doc = "", },
  { .p_func = hangeul_decompose_jongseong,
    .sz_func_name = "hangeul_decompose_jongseong",
    .sz_func_doc = "", },
  { .p_func = hangeul_2beol_commit_1_and_flush,
    .sz_func_name = "hangeul_2beol_commit_1_and_flush",
    .sz_func_doc = "", },
  { .p_func = hangeul_put_jamo_unicode,
    .sz_func_name = "hangeul_put_jamo_unicode",
    .sz_func_doc = "", },
  { .p_func = hangeul_remap_code,
    .sz_func_name = "hangeul_remap_code",
    .sz_func_doc = "", },
};

const ssize_t plugin_funcs_len = sizeof(plugin_funcs) / sizeof(plugin_func_t);
