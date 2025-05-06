#include "config.h"

#include "lua_binding.h"

#include <stdlib.h>

#include "lua.h"




void lua_binding_build
(lua_State *L,
 const plugin_func_t *funcs,
 const ssize_t funcs_len)
{
  for (int i = 0 ; i < funcs_len ; i ++)
    {
      plugin_func_t *p_func_row = (plugin_func_t *) &funcs[i];
    }
}




lua_binding_row_t __lua_bindings[] = {
  { .sz_lua_func_name = "get_current_handle_input_fn",
    .pfn_wrap = NULL, .ppfn = NULL, },
  { .sz_lua_func_name = "set_current_handle_input_fn",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "get_current_handle_input_status",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "set_current_handle_input_status",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul2_im_handler_status_empty",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul2_handle_stdin",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "get_current_hangeul_automata_status",
    .pfn_wrap = NULL, },

  { .sz_lua_func_name = "ERR_err_p",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "ERR_clear",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "ERR_set",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "ERR_set_nofree",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "ERR_dieif",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "ERR_warn_and_clear_if",
    .pfn_wrap = NULL, },

  { .sz_lua_func_name = "cp_fd",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "fcntl_nb",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "print_banner",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "get_verbose_flag",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "set_verbose_flag",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "get_keylog_filename",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "set_keylog_filename",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "get_default_keylog_filename",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "get_plugin_dll_filename",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "get_child_pid",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "get_child_fd",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "winsz_update",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "unicode_to_utf8",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "termios__init",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "termios__reset",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "signal_trap_norecover",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "forkpty_with_exec",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "kill_forkpty",
    .pfn_wrap = NULL, },

  { .sz_lua_func_name = "hangeul_const_chojungjong_nul",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_const_choseong",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_const_jungseong",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_const_jongseong",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_const_moeum",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_const_jaeum",
    .pfn_wrap = NULL, },

  { .sz_lua_func_name = "hangeul_automata_status__new",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_automata_status__delete",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_automata_status__get_stage",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_automata_status__set_stage",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_automata_status__get_prev_ch",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_automata_status__set_prev_ch",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_automata_status__get_cho",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_automata_status__set_cho",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_automata_status__get_jung",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_automata_status__set_jung",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_automata_status__get_jong",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_automata_status__set_jong",
    .pfn_wrap = NULL, },

  { .sz_lua_func_name = "hangeul_clear_automata_status",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_flush_automata_status",
    .pfn_wrap = NULL, },

  { .sz_lua_func_name = "hangeul_auto_compose_to_unicode",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_full_compose_to_unicode",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_jamo_compose_to_unicode",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_jamo_jaeum_to_unicode",
    .pfn_wrap = NULL, },

  { .sz_lua_func_name = "hangeul_partial_jamo_p",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_empty_automata_status_p",
    .pfn_wrap = NULL, },

  { .sz_lua_func_name = "hangeul_2beol_alpha_as_jamoeum",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_2beol_fill",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_2beol_find_code",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_double_jaeum",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_put_unicode",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_decompose_jongseong",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_2beol_commit_1_and_flush",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_put_jamo_unicode",
    .pfn_wrap = NULL, },
  { .sz_lua_func_name = "hangeul_remap_code",
    .pfn_wrap = NULL, },

};


const ssize_t __lua_bindings_len =
  sizeof(__lua_bindings) / sizeof(lua_binding_row_t);
