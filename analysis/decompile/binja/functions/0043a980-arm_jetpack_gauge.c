/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: arm_jetpack_gauge @ 0x43a980 */

0043a988        if (sub_hover->state != SUB_HOVER_STATE_INACTIVE)
0043a988        return
0043a98a        sub_hover->state = SUB_HOVER_STATE_ACTIVE
0043a991        sub_hover->progress = 0
0043a993        sub_hover->wobble_alpha = 0f
0043a996        sub_hover->wobble_y = 0f
0043a999        sub_hover->wobble_x = 0f
0043a9a9        set_snail_jetpack(&g_game_base->subgame.player.presentation, 1)
0043a9b0        initialize_jet_particles(sub_hover)
0043a9b6        return
