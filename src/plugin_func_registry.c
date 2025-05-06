/**
 * "DLL"-Plugin system of Ddakong
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

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


#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>



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


hangeul_automata_status *__hangeul_automata_status__new(void)
{
  hangeul_automata_status *p_status = NULL;
  p_status = (hangeul_automata_status *) malloc(sizeof(hangeul_automata_status));
  return p_status;
}

void __hangeul_automata_status__delete
(hangeul_automata_status *p_status) {
  if (p_status != NULL) {
    free(p_status);
  }
}

CHOJUNGJONG __hangeul_automata_status__get_stage
(hangeul_automata_status *p_status)
{
  assert(p_status != NULL);
  return p_status->stage;
}

void __hangeul_automata_status__set_stage
(hangeul_automata_status *p_status,
 const CHOJUNGJONG cjj)
{
  assert(p_status != NULL);
  p_status->stage = cjj;
}

BYTE __hangeul_automata_status__get_prev_ch
(hangeul_automata_status *p_status)
{
  assert(p_status != NULL);
  return p_status->prev_ch;
}

void __hangeul_automata_status__set_prev_ch
(hangeul_automata_status *p_status, const BYTE ch)
{
  assert(p_status != NULL);
  p_status->prev_ch = ch;
}

BYTE __hangeul_automata_status__get_cho
(hangeul_automata_status *p_status)
{
  assert(p_status != NULL);
  return p_status->cho;
}

void __hangeul_automata_status__set_cho
(hangeul_automata_status *p_status, const BYTE cho)
{
  assert(p_status != NULL);
  p_status->cho = cho;
}

BYTE __hangeul_automata_status__get_jung
(hangeul_automata_status *p_status)
{
  assert(p_status != NULL);
  return p_status->jung;
}

void __hangeul_automata_status__set_jung
(hangeul_automata_status *p_status, const BYTE jung)
{
  assert(p_status != NULL);
  p_status->jung = jung;
}

BYTE __hangeul_automata_status__get_jong
(hangeul_automata_status *p_status)
{
  assert(p_status != NULL);
  return p_status->jong;
}

void __hangeul_automata_status__set_jong
(hangeul_automata_status *p_status, const BYTE jong)
{
  assert(p_status != NULL);
  p_status->jong = jong;
}




/* SUPPORT: $_ */

plugin_func_t *get_plugin_funcs(void)
{ return (plugin_func_t *) plugin_funcs; }

ssize_t get_plugin_funcs_len(void)
{ return plugin_funcs_len; }


/* SUPPORT: global_flags.h */

int __get_verbose_flag(void) { return verbose_flag; }

void __set_verbose_flag(const int verbose)
{ verbose_flag = verbose; }

char *__get_keylog_filename(void) { return keylog_filename; }
void __set_keylog_filename(char *sz_filename)
{ keylog_filename = sz_filename; }

char *__get_default_keylog_filename(void)
{ return default_keylog_filename; }

pid_t __get_child_pid(void)
{ return child_pid; }

int __get_child_fd(void)
{ return child_fd; }

char *__get_plugin_dll_filename(void)
{ return plugin_dll_filename; }


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
  { .p_func = __get_plugin_dll_filename,
    .sz_func_name = "get_plugin_dll_filename",
    .sz_func_doc = "", },
  { .p_func = __get_child_pid,
    .sz_func_name = "get_child_pid",
    .sz_func_doc = "", },
  { .p_func = __get_child_fd,
    .sz_func_name = "get_child_fd",
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

  { .p_func = __hangeul_automata_status__new,
    .sz_func_name = "hangeul_automata_status__new",
    .sz_func_doc = "", },
  { .p_func = __hangeul_automata_status__delete,
    .sz_func_name = "hangeul_automata_status__delete",
    .sz_func_doc = "", },
  { .p_func = __hangeul_automata_status__get_stage,
    .sz_func_name = "hangeul_automata_status__get_stage",
    .sz_func_doc = "", },
  { .p_func = __hangeul_automata_status__set_stage,
    .sz_func_name = "hangeul_automata_status__set_stage",
    .sz_func_doc = "", },
  { .p_func = __hangeul_automata_status__get_prev_ch,
    .sz_func_name = "hangeul_automata_status__get_prev_ch",
    .sz_func_doc = "", },
  { .p_func = __hangeul_automata_status__set_prev_ch,
    .sz_func_name = "hangeul_automata_status__set_prev_ch",
    .sz_func_doc = "", },
  { .p_func = __hangeul_automata_status__get_cho,
    .sz_func_name = "hangeul_automata_status__get_cho",
    .sz_func_doc = "", },
  { .p_func = __hangeul_automata_status__set_cho,
    .sz_func_name = "hangeul_automata_status__set_cho",
    .sz_func_doc = "", },
  { .p_func = __hangeul_automata_status__get_jung,
    .sz_func_name = "hangeul_automata_status__get_jung",
    .sz_func_doc = "", },
  { .p_func = __hangeul_automata_status__set_jung,
    .sz_func_name = "hangeul_automata_status__set_jung",
    .sz_func_doc = "", },
  { .p_func = __hangeul_automata_status__get_jong,
    .sz_func_name = "hangeul_automata_status__get_jong",
    .sz_func_doc = "", },
  { .p_func = __hangeul_automata_status__set_jong,
    .sz_func_name = "hangeul_automata_status__set_jong",
    .sz_func_doc = "", },

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
