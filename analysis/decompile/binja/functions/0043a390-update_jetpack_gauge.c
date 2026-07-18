/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_jetpack_gauge @ 0x43a390 */

0043a399        enum SubHoverState state = sub_hover->state
0043a3a5        if (state == SUB_HOVER_STATE_INACTIVE || state != 1)
0043a3a5        return
0043a3b0        float var_8_1 = fconvert.s(fconvert.t(sub_hover->progress_step) + fconvert.t(sub_hover->progress))
0043a3b4        long double x87_r7_3 = fconvert.t(var_8_1)
0043a3b8        long double temp2_1 = fconvert.t(1f)
0043a3b8        x87_r7_3 - temp2_1
0043a3c2        sub_hover->progress = var_8_1
0043a3c9        if ((((x87_r7_3 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp2_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0043a3d5        struct Player* player = sub_hover->player
0043a3e2        long double x87_r7_4 = float.t(sub_hover->game->completion_row_start - 5)
0043a3e6        long double temp4_1 = fconvert.t(player->body.transform.position.z)
0043a3e6        x87_r7_4 - temp4_1
0043a3ee        if ((((x87_r7_4 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp4_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp4_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0043a3f4        long double x87_r7_5 = fconvert.t(var_8_1)
0043a3f8        long double temp5 = fconvert.t(0.100000001f)
0043a3f8        x87_r7_5 - temp5
0043a3fe        long double x87_r7_6 = fconvert.t(var_8_1)
0043a407        if ((((x87_r7_5 < temp5 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp5) ? 1 : 0) << 0xa | (x87_r7_5 == temp5 ? 1 : 0) << 0xe | 0x3800):1.b & 1) == 0)
0043a41a        long double temp6_1 = fconvert.t(0.939999998f)
0043a41a        x87_r7_6 - temp6_1
0043a425        if ((((x87_r7_6 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp6_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0043a46c        sub_hover->warning_intensity = 1f
0043a476        struct GameRoot* game_base_1 = g_game_base
0043a48d        player = *get_track_runtime_cell_at_world_z(&game_base_1->subgame, &game_base_1->subgame.player.body.transform.position)
0043a492        if ((player:1.b & 0x80) != 0)
0043a499        sub_hover->progress = 0x3f70a3d7
0043a437        sub_hover->warning_intensity = fconvert.s((fconvert.t(1f) - fconvert.t(var_8_1)) * fconvert.t(16.6666679f))
0043a441        long double x87_r7_12 = fconvert.t(var_8_1) - fconvert.t(sub_hover->progress_step)
0043a444        long double temp7_1 = fconvert.t(0.939999998f)
0043a444        x87_r7_12 - temp7_1
0043a44f        if ((((x87_r7_12 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp7_1) ? 1 : 0) << 0xa | (x87_r7_12 == temp7_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0043a45e        set_snail_jetpack(&g_game_base->subgame.player.presentation, 0)
0043a465        player = uninit_jet_particles(sub_hover)
0043a40f        sub_hover->warning_intensity = fconvert.s(x87_r7_6 * fconvert.t(10f))
0043a4b3        struct Player* player_1 = player
0043a4ce        sub_hover->warning_intensity = fconvert.s(fconvert.t(1f) - (cosine(fconvert.s(fconvert.t(sub_hover->warning_intensity) * fconvert.t(3.14159274f))) + fconvert.t(1f)) * fconvert.t(0.5f))
0043a4f0        sub_hover->wobble_x = fconvert.s(sine(fconvert.s(fconvert.t(sub_hover->progress) * fconvert.t(25.1327419f))) * fconvert.t(sub_hover->warning_intensity) * fconvert.t(0.25f))
0043a503        long double x87_r7_27 = sine(fconvert.s(fconvert.t(sub_hover->progress) * fconvert.t(37.6991119f))) * fconvert.t(0.25f)
0043a50e        float warning_intensity = sub_hover->warning_intensity
0043a520        float progress = sub_hover->progress
0043a521        struct Vec3* var_18 = &sub_hover->player->body.transform.position
0043a524        long double x87_r7_29 = (x87_r7_27 + fconvert.t(1f)) * fconvert.t(sub_hover->warning_intensity)
0043a52a        sub_hover->wobble_alpha = 0f
0043a52d        sub_hover->warning_intensity_latch = warning_intensity
0043a533        sub_hover->wobble_y = fconvert.s(x87_r7_29)
0043a540        return
0043a543        end_jetpack_hover(sub_hover)
0043a548        long double x87_r7_30 = fconvert.t(sub_hover->progress)
0043a54a        long double temp3_1 = fconvert.t(0.939999998f)
0043a54a        x87_r7_30 - temp3_1
0043a555        if ((((x87_r7_30 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_30, temp3_1) ? 1 : 0) << 0xa | (x87_r7_30 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0043a563        set_snail_jetpack(&g_game_base->subgame.player.presentation, 0)
0043a568        sub_hover->state = SUB_HOVER_STATE_INACTIVE
0043a56b        sub_hover->wobble_alpha = 0f
0043a56e        sub_hover->wobble_y = 0f
0043a571        sub_hover->wobble_x = 0f
0043a579        return
