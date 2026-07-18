/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: begin_post_follow_carryover @ 0x43af60 */

0043af6a        if (player->follow_state.active == 0)
0043af8c        player->post_follow_heading_carryover = 0
0043af92        player->post_follow_exit_roll = 0f
0043af78        player->post_follow_heading_carryover = player->follow_state.template_record->installed_heading_delta
0043af84        player->post_follow_exit_roll = player->follow_state.orientation_b
0043af98        float z = player->body.transform.position.z
0043af9b        player->follow_state.active = 0
0043afa1        player->attachment_exit_pending = 1
0043afa8        player->attachment_exit_anchor_z = z
0043afae        player->attachment_exit_progress = 0f
0043afb4        player->attachment_exit_gate_a = 0
0043afba        player->attachment_exit_gate_b = 0
0043afc0        return
