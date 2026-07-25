/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_main_loop_display_state @ 0x406d70 */

00406d75        clear_display_mode_state(&g_display_mode_state)
00406d81        g_window_deactivated = 0
00406d86        g_pending_window_deactivate = 0
00406d8b        set_matrix_identity(&g_object_texture_transform_matrix)
00406d90        return initialize_main_loop_timing_state() __tailcall
