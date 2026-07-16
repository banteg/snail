/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_damage_gauge @ 0x440fd0 */

00440fd6        struct GameRoot* game_base_1 = g_game_base
00440fdc        int16_t eax
00440fdc        eax.b = game_base_1->subgame.subgame_pause_gate
00440fe4        if (eax.b == 0)
00440ff9        damage_guage->display_fill = fconvert.s((fconvert.t(damage_guage->fill) - fconvert.t(damage_guage->display_fill)) * fconvert.t(0.200000003f) + fconvert.t(damage_guage->display_fill))
00440ffc        long double x87_r7_5 = fconvert.t(damage_guage->hit_flash_progress)
00440fff        long double temp1_1 = fconvert.t(0f)
00440fff        x87_r7_5 - temp1_1
0044100a        if ((((x87_r7_5 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp1_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044100f        long double x87_r7_7 = fconvert.t(damage_guage->hit_flash_step) + fconvert.t(damage_guage->hit_flash_progress)
00441012        damage_guage->hit_flash_progress = fconvert.s(x87_r7_7)
00441015        long double temp4_1 = fconvert.t(1f)
00441015        x87_r7_7 - temp4_1
00441020        if ((((x87_r7_7 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp4_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp4_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00441022        damage_guage->hit_flash_progress = 0f
00441029        enum DamageGuageState state = damage_guage->state
0044102e        if (state == DAMAGE_GUAGE_STATE_MONITORING)
0044116c        if (damage_guage->fill != 0x3f800000)
004411ad        game_base_1 = g_game_base
0044116e        game_base_1 = g_game_base
00441186        if (game_base_1->subgame.player.attachment_exit_pending == 0 && game_base_1->subgame.player.completion_handoff_active == 0)
00441188        damage_guage->state = 1
0044118e        damage_guage->warning_transition_progress = 0f
00441195        damage_guage->warning_transition_step = 0.166666672f
004411a8        start_warning(&g_game_base->subgame.player.warning)
004411ad        game_base_1 = g_game_base
00441035        if (state == 1)
0044111c        if (g_game_base->subgame.player.completion_handoff_active != 0)
0044111e        damage_guage->warning_transition_progress = 1f
00441128        long double x87_r7_12 = fconvert.t(damage_guage->warning_transition_step) + fconvert.t(damage_guage->warning_transition_progress)
0044112b        damage_guage->warning_transition_progress = fconvert.s(x87_r7_12)
0044112e        long double temp9_1 = fconvert.t(1f)
0044112e        x87_r7_12 - temp9_1
00441139        if ((((x87_r7_12 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp9_1) ? 1 : 0) << 0xa | (x87_r7_12 == temp9_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004411ad        game_base_1 = g_game_base
0044113b        game_base_1 = g_game_base
0044114b        if (game_base_1->subgame.player.body.transform.position.y == 0x3efae148)
00441158        damage_guage->state = 2
0044115e        play_voice_manager(0x751498, 0xe, 0, 0xffffffff)
004411ad        game_base_1 = g_game_base
0044103c        if (state != 2)
004411ad        game_base_1 = g_game_base
00441054        change_snail_skin(&g_game_base->subgame.player.presentation.snail_skin, 1, 0.200000003f)
00441062        apply_damage_gauge_delta(damage_guage, -0.00166666671f, true)
00441067        damage_guage->skin_hold_ticks = 5
0044106e        game_base_1 = g_game_base
00441074        int16_t eax_6
00441074        eax_6.b = game_base_1->subgame.player.completion_handoff_active
0044107c        if (eax_6.b != 0)
00441087        apply_damage_gauge_delta(damage_guage, -0.00666666683f, false)
0044108c        game_base_1 = g_game_base
00441092        long double x87_r7_8 = fconvert.t(damage_guage->fill)
00441095        long double temp11_1 = fconvert.t(0f)
00441095        x87_r7_8 - temp11_1
004410ac        if ((((x87_r7_8 < temp11_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp11_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp11_1 ? 1 : 0) << 0xe):1.b & 0x40) == 0 || game_base_1->subgame.player.body.transform.position.y != 0x3efae148)
004410ae        long double x87_r7_9 = fconvert.t(game_base_1->subgame.player.completion_handoff_timer)
004410b4        long double temp13_1 = fconvert.t(0f)
004410b4        x87_r7_9 - temp13_1
004410bf        if ((((x87_r7_9 < temp13_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp13_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp13_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
004410bf        goto label_4410e2
004410c1        long double x87_r7_10 = fconvert.t(game_base_1->subgame.player.resurrect_progress)
004410c7        long double temp14_1 = fconvert.t(0f)
004410c7        x87_r7_10 - temp14_1
004410dc        if ((((x87_r7_10 < temp14_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp14_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp14_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0 || game_base_1->subgame.player.presentation.cutscene.state != CUT_SCENE_STATE_INACTIVE)
004410d2        goto label_4410e2
004410e2        label_4410e2:
004410e2        damage_guage->state = 0
004410f4        stop_warning(&g_game_base->subgame.player.warning)
00441105        stop_warning_sample(&g_game_base->subgame.player.warning)
004411ad        game_base_1 = g_game_base
004411b3        long double x87_r7_13 = fconvert.t(damage_guage->display_fill)
004411b6        long double temp0 = fconvert.t(0.999000013f)
004411b6        x87_r7_13 - temp0
004411bc        int16_t eax_11 = (x87_r7_13 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_13, temp0) ? 1 : 0) << 0xa | (x87_r7_13 == temp0 ? 1 : 0) << 0xe
004411c1        float height
004411c1        if ((eax_11:1.b & 0x41) != 0)
004411cd        long double x87_r7_14 = fconvert.t(damage_guage->display_fill)
004411d0        long double temp2_1 = fconvert.t(0.00999999978f)
004411d0        x87_r7_14 - temp2_1
004411d6        eax_11 = (x87_r7_14 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp2_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp2_1 ? 1 : 0) << 0xe
004411db        if ((eax_11:1.b & 1) == 0)
004411f6        height = fconvert.s(fconvert.t(351f) - fconvert.t(damage_guage->display_fill) * fconvert.t(308f))
004411dd        height = 396f
004411c3        height = 0f
004411fa        eax_11.b = game_base_1->subgame.subgame_pause_gate
00441202        if (eax_11.b == 0)
0044120a        damage_guage->pulse_progress = fconvert.s(fconvert.t(damage_guage->pulse_step) + fconvert.t(damage_guage->pulse_progress))
0044120d        long double x87_r7_20 = fconvert.t(damage_guage->pulse_progress)
00441210        long double temp6 = fconvert.t(1f)
00441210        x87_r7_20 - temp6
0044121b        if ((((x87_r7_20 < temp6 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp6) ? 1 : 0) << 0xa | (x87_r7_20 == temp6 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00441226        damage_guage->pulse_progress = fconvert.s(fconvert.t(damage_guage->pulse_progress) - fconvert.t(1f))
00441229        long double x87_r7_23 = fconvert.t(damage_guage->display_fill)
0044122c        long double temp8 = fconvert.t(0.899999976f)
0044122c        x87_r7_23 - temp8
0044123c        struct tColour color
0044123c        if ((((x87_r7_23 < temp8 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp8) ? 1 : 0) << 0xa | (x87_r7_23 == temp8 ? 1 : 0) << 0xe):1.b & 0x41) == 0 || damage_guage->state != DAMAGE_GUAGE_STATE_MONITORING)
00441242        long double x87_r7_24 = fconvert.t(damage_guage->display_fill)
00441245        long double temp10_1 = fconvert.t(0.899999976f)
00441245        x87_r7_24 - temp10_1
00441250        float var_18_1
00441250        if ((((x87_r7_24 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_24, temp10_1) ? 1 : 0) << 0xa | (x87_r7_24 == temp10_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0044126c        long double x87_r7_28 = fconvert.t(damage_guage->display_fill)
0044126f        long double temp12_1 = fconvert.t(0.100000001f)
0044126f        x87_r7_28 - temp12_1
0044127a        if ((((x87_r7_28 < temp12_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_28, temp12_1) ? 1 : 0) << 0xa | (x87_r7_28 == temp12_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0044128b        var_18_1 = 1f
00441285        var_18_1 = fconvert.s(fconvert.t(damage_guage->display_fill) * fconvert.t(10f))
00441255        if (damage_guage->state != DAMAGE_GUAGE_STATE_MONITORING)
0044128b        var_18_1 = 1f
00441266        var_18_1 = fconvert.s((fconvert.t(damage_guage->display_fill) - fconvert.t(0.899999976f)) * fconvert.t(10f))
0044129c        struct GameRoot* game_base_2 = game_base_1
00441311        queue_axis_aligned_textured_quad_uv(0x5b, 560f, 70f, 64f, 396f, 0x1000000, set_color_rgba(&color, 1f, 1f, 1f, fconvert.s(fconvert.t(var_18_1) - (sine(fconvert.s(fconvert.t(damage_guage->pulse_progress) * fconvert.t(6.28318548f))) + fconvert.t(1f)) * fconvert.t(0.5f) * fconvert.t(var_18_1) * fconvert.t(0.5f))), 0f, 0f, 1f, 0.7734375f, 3, 0f)
0044132b        float var_18_3 = fconvert.s(fconvert.t(height) * fconvert.t(0.001953125f))
00441372        queue_axis_aligned_textured_quad_uv(0x59, 560f, 70f, 64f, height, 0x1000000, set_color_rgba(&color, 1f, 1f, 1f, 1f), 0f, 0f, 1f, var_18_3, 3, 0f)
004413a3        struct tColour* color_1
004413a3        int32_t ecx_12
004413a3        color_1, ecx_12 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
004413b8        int32_t var_40_1 = ecx_12
004413cb        int32_t var_48 = ecx_12
004413d6        queue_axis_aligned_textured_quad_uv(0x5a, 560f, fconvert.s(fconvert.t(height) + fconvert.t(70f)), 64f, fconvert.s(fconvert.t(396f) - fconvert.t(height)), 0x1000000, color_1, 0f, var_18_3, 1f, 0.7734375f, 3, 0f)
004413e2        return
