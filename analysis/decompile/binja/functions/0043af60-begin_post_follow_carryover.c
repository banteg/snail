/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: begin_post_follow_carryover @ 0x43af60 */

0043af6a        if (player->follow_state.active == 0)
0043af8c        player->post_follow_value_b = 0f
0043af92        player->post_follow_value_a = 0f
0043af78        player->post_follow_value_b = player->follow_state.template_record->__offset(0x98).d
0043af84        player->post_follow_value_a = player->follow_state.orientation_b
0043af98        float z = player->live_matrix.position.z
0043af9b        player->follow_state.active = 0
0043afa1        player->attachment_exit_pending = 1
0043afa8        player->_pad_424[0] = z.b
0043afa8        player->_pad_424[1] = z:1.b
0043afa8        player->_pad_424[2] = z:2.b
0043afa8        player->_pad_424[3] = z:3.b
0043afae        player->attachment_exit_progress = 0f
0043afb4        player->attachment_exit_gate_a = 0
0043afba        player->attachment_exit_gate_b = 0
0043afc0        return 0
