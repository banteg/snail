/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: apply_damage_gauge_delta @ 0x4413f0 */

004413f0        struct GameRoot* game_base_2 = g_game_base
00441400        int16_t eax
00441400        if ((game_base_2->subgame.player.movement_flags.b & 0x80) != 0)
00441402        eax.b = force
00441408        if ((game_base_2->subgame.player.movement_flags.b & 0x80) != 0 && eax.b == 0)
00441408        return
0044140e        enum DamageGuageState state = damage_guage->state
00441413        if (state == DAMAGE_GUAGE_STATE_DRAINING)
00441415        long double x87_r7_1 = fconvert.t(delta)
00441419        long double temp2_1 = fconvert.t(0f)
00441419        x87_r7_1 - temp2_1
00441424        if ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0044142c        if (state != state)
0044142c        goto label_44144c
0044142e        long double x87_r7_2 = fconvert.t(delta)
00441432        long double temp6_1 = fconvert.t(0f)
00441432        x87_r7_2 - temp6_1
00441446        if ((((x87_r7_2 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp6_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp6_1 ? 1 : 0) << 0xe):1.b & 1) == 0 || game_base_2->subgame.player.trampoline_bounce_active != 1)
0044143d        goto label_44144c
00441424        return
0044144c        label_44144c:
0044144c        long double x87_r7_3 = fconvert.t(damage_guage->hit_flash_progress)
0044144f        long double temp1_1 = fconvert.t(0f)
0044144f        x87_r7_3 - temp1_1
0044145a        if ((((x87_r7_3 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp1_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00441460        long double x87_r7_4 = fconvert.t(delta)
00441464        long double temp4_1 = fconvert.t(0f)
00441464        x87_r7_4 - temp4_1
0044146f        if ((((x87_r7_4 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp4_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp4_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044147e        change_snail_skin(&game_base_2->subgame.player.presentation.snail_skin, 1, 0.200000003f)
00441495        if (play_voice_manager(&g_voice_manager, 0, 1, 0xffffffff) != 0)
004414ed        damage_guage->hit_flash_progress = damage_guage->hit_flash_step
004414a9        if (play_voice_manager(&g_voice_manager, 9, 0, 0xffffffff) != 0)
004414ae        damage_guage->hit_flash_progress = damage_guage->hit_flash_step
004414b1        struct GameRoot* game_base_1 = g_game_base
004414be        if (game_base_1->subgame.player.control_override_active == 0)
004414cc        dispatch_cutscene_animation(&game_base_1->subgame.player.presentation, 6, 1, 0xffffffff)
004414e3        dispatch_cutscene_animation(&g_game_base->subgame.player.presentation, 1, 0, 0xffffffff)
004414f4        long double x87_r7_6 = fconvert.t(delta) + fconvert.t(damage_guage->fill)
004414f7        long double temp3_1 = fconvert.t(0f)
004414f7        x87_r7_6 - temp3_1
004414fd        damage_guage->fill = fconvert.s(x87_r7_6)
004414fd        bool c1_1 = unknown  {fst dword [esi+0x1c], st0}
00441505        if ((((x87_r7_6 < temp3_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_6, temp3_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp3_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
0044150f        damage_guage->fill = fconvert.s(fconvert.t(0f))
00441513        return
00441516        long double temp5_1 = fconvert.t(1f)
00441516        x87_r7_6 - temp5_1
00441521        if ((((x87_r7_6 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp5_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp5_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
00441525        x87_r7_6 = fconvert.t(1f)
0044152b        damage_guage->fill = fconvert.s(x87_r7_6)
0044152f        return
