/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_cameraman @ 0x446160 */

0044616d        cameraman->player = data_4df904 + 0x42fd7c
00446179        struct Game* ecx_1 = data_4df904 + 0x74618
0044617f        cameraman->unresolved_cc = 0
00446186        cameraman->game = ecx_1
00446192        set_matrix_identity(&cameraman->previous_desired_matrix)
0044619a        set_matrix_identity(&cameraman->desired_matrix)
004461a1        set_matrix_identity(cameraman)
004461a6        cameraman->attachment_lift_envelope = 0f
004461b0        cameraman->smoothed_attachment_lift_envelope = 0f
004461ba        cameraman->fov_degrees = 110f
004461c5        return 0
