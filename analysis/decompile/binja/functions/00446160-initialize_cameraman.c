/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_cameraman @ 0x446160 */

0044616d        cameraman->player = &g_game_base->subgame.__offset(0x3bb764).d
0044617f        cameraman->unresolved_cc = 0
00446186        cameraman->game = &g_game_base->subgame
00446192        set_matrix_identity(&cameraman->previous_desired_matrix)
0044619a        set_matrix_identity(&cameraman->desired_matrix)
004461a1        set_matrix_identity(cameraman)
004461a6        cameraman->attachment_lift_envelope = 0f
004461b0        cameraman->smoothed_attachment_lift_envelope = 0f
004461ba        cameraman->fov_degrees = 110f
004461c5        return
