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
  #if 0
"get_plugin_funcs",
"get_plugin_funcs_len",
 
"get_current_handle_input_fn",
"set_current_handle_input_fn",
"get_current_handle_input_status",
"set_current_handle_input_status",
"hangeul2_im_handler_status_empty",
"hangeul2_handle_stdin",

"get_current_hangeul_automata_status",

"ERR_err_p",
"ERR_clear",
"ERR_set",
"ERR_set_nofree",
"ERR_dieif",
"ERR_warn_and_clear_if",

"cp_fd",
"fcntl_nb",

"print_banner",
"get_verbose_flag",
"set_verbose_flag",
"get_keylog_filename",
"set_keylog_filename",
"get_default_keylog_filename",
"get_plugin_dll_filename",
"get_child_pid",
"get_child_fd",

"winsz_update",

"unicode_to_utf8",

"termios__init",
"termios__reset",

"signal_trap_norecover",

"forkpty_with_exec",
"kill_forkpty",

"hangeul_const_chojungjong_nul",
"hangeul_const_choseong",
"hangeul_const_jungseong",
"hangeul_const_jongseong",
"hangeul_const_moeum",
"hangeul_const_jaeum",

"hangeul_automata_status__new",
"hangeul_automata_status__delete",
"hangeul_automata_status__get_stage",
"hangeul_automata_status__set_stage",
"hangeul_automata_status__get_prev_ch",
"hangeul_automata_status__set_prev_ch",
"hangeul_automata_status__get_cho",
"hangeul_automata_status__set_cho",
"hangeul_automata_status__get_jung",
"hangeul_automata_status__set_jung",
"hangeul_automata_status__get_jong",
"hangeul_automata_status__set_jong",
"hangeul_clear_automata_status",
"hangeul_flush_automata_status",
"hangeul_auto_compose_to_unicode",
"hangeul_full_compose_to_unicode",
"hangeul_jamo_compose_to_unicode",
"hangeul_jamo_jaeum_to_unicode",
"hangeul_partial_jamo_p",
"hangeul_empty_automata_status_p",
"hangeul_2beol_alpha_as_jamoeum",
"hangeul_2beol_fill",
"hangeul_2beol_find_code",
"hangeul_double_jaeum",
"hangeul_put_unicode",
"hangeul_decompose_jongseong",
"hangeul_2beol_commit_1_and_flush",
"hangeul_put_jamo_unicode",
"hangeul_remap_code",
#endif
};


const ssize_t __lua_bindings_len =
  sizeof(__lua_bindings) / sizeof(lua_binding_row_t);
