/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_invincible_shell @ 0x444b50 */

00444b66        switch (invincible->state)
00444b6d        case INVINCIBLE_STATE_INACTIVE
00444b6d        struct GameRoot* game_base_1 = g_game_base
00444b79        if ((game_base_1->subgame.player.movement_flags.b & 0x80) == 0)
00444b8e        game_base_1->subgame.player.presentation.invincible_shell.body.bod.bod.list_flags &= 0xffffffdf
00444b94        return
00444b7d        start_invincible_shell(invincible)
00444b83        return
00444b9b        case INVINCIBLE_STATE_FADING_IN
00444b9b        long double x87_r7_2 = fconvert.t(invincible->fade_step) + fconvert.t(invincible->fade_progress)
00444ba1        invincible->fade_progress = fconvert.s(x87_r7_2)
00444ba7        long double temp1_1 = fconvert.t(1f)
00444ba7        x87_r7_2 - temp1_1
00444bb2        if ((((x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00444bb4        invincible->fade_progress = 1f
00444bbe        invincible->state = INVINCIBLE_STATE_ACTIVE
00444bd4        if ((g_game_base->subgame.player.movement_flags.b & 0x80) == 0)
00444bd6        invincible->state = INVINCIBLE_STATE_FADING_OUT
00444beb        case INVINCIBLE_STATE_ACTIVE
00444beb        if ((g_game_base->subgame.player.movement_flags.b & 0x80) == 0)
00444bed        invincible->state = INVINCIBLE_STATE_FADING_OUT
00444bfb        case INVINCIBLE_STATE_FADING_OUT
00444bfb        long double x87_r7_4 = fconvert.t(invincible->fade_progress) - fconvert.t(invincible->fade_step)
00444c01        invincible->fade_progress = fconvert.s(x87_r7_4)
00444c07        long double temp2_1 = fconvert.t(0f)
00444c07        x87_r7_4 - temp2_1
00444c12        if ((((x87_r7_4 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp2_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp2_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00444c17        invincible->fade_progress = 0f
00444c1d        invincible->state = INVINCIBLE_STATE_INACTIVE
00444c2f        change_snail_skin(&g_game_base->subgame.player.presentation.snail_skin, 0, 0f)
00444c35        return
00444c43        if ((g_game_base->subgame.player.movement_flags.b & 0x80) != 0)
00444c45        invincible->state = INVINCIBLE_STATE_FADING_IN
00444c55        long double x87_r7_6 = fconvert.t(invincible->spin_phase_step) + fconvert.t(invincible->spin_phase)
00444c5b        long double temp0 = fconvert.t(1f)
00444c5b        x87_r7_6 - temp0
00444c61        invincible->spin_phase = fconvert.s(x87_r7_6)
00444c61        bool c1 = unknown  {fst dword [ebx+0x84], st0}
00444c6c        if ((((x87_r7_6 < temp0 ? 1 : 0) << 8 | (c1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_6, temp0) ? 1 : 0) << 0xa | (x87_r7_6 == temp0 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
00444c74        invincible->spin_phase = fconvert.s(x87_r7_6 - fconvert.t(1f))
00444c90        change_snail_skin(&g_game_base->subgame.player.presentation.snail_skin, 2, 0f)
00444c98        set_color_white(&invincible->body.bod.color)
00444cae        invincible->body.bod.color.a = fconvert.s(fconvert.t(invincible->fade_progress) * fconvert.t(0.800000012f))
00444cb7        long double x87_r7_11 = fconvert.t(invincible->spin_phase)
00444cd0        int32_t var_10 = __builtin_memcpy(&invincible->body.transform, &g_game_base->subgame.player.presentation.body.transform, 0x40)
00444cd6        rotate_matrix_local_y(&invincible->body.transform, fconvert.s(x87_r7_11 * fconvert.t(6.28318548f)))
00444cde        return
