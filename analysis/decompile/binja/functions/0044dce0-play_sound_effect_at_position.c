/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: play_sound_effect_at_position @ 0x44dce0 */

0044dce3        struct GameRoot* game_base_1 = g_game_base
0044dced        float var_1c = 1e+10f
0044dd1f        struct Vec3 vector
0044dd1f        vector.y = fconvert.s(fconvert.t(position->y) - fconvert.t(game_base_1->players[0].camera.body.transform.position.y))
0044dd27        vector.x = fconvert.s(fconvert.t(position->x) - fconvert.t(game_base_1->players[0].camera.body.transform.position.x))
0044dd33        vector.z = fconvert.s(fconvert.t(position->z) - fconvert.t(game_base_1->players[0].camera.body.transform.position.z))
0044dd37        long double st0 = vector_magnitude(&vector)
0044dd3c        long double temp1 = fconvert.t(1e+10f)
0044dd3c        st0 - temp1
0044dd47        if ((((st0 < temp1 ? 1 : 0) << 8 | (is_unordered.t(st0, temp1) ? 1 : 0) << 0xa | (st0 == temp1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
0044dd49        var_1c = fconvert.s(st0)
0044dd51        long double x87_r7_8 = fconvert.t(var_1c)
0044dd55        long double temp2 = fconvert.t(25f)
0044dd55        x87_r7_8 - temp2
0044dd60        if ((((x87_r7_8 < temp2 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp2) ? 1 : 0) << 0xa | (x87_r7_8 == temp2 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044dd60        return
0044dd7e        long double x87_r7_14 = fconvert.t(position->x) * fconvert.t(-0.25f) * fconvert.t(100f)
0044dd84        position = fconvert.s(x87_r7_14)
0044dd88        long double temp3_1 = fconvert.t(-100f)
0044dd88        x87_r7_14 - temp3_1
0044dd93        if ((((x87_r7_14 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp3_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp3_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0044dd9f        long double x87_r7_15 = fconvert.t(position)
0044dda3        long double temp4_1 = fconvert.t(100f)
0044dda3        x87_r7_15 - temp4_1
0044ddae        if ((((x87_r7_15 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_15, temp4_1) ? 1 : 0) << 0xa | (x87_r7_15 == temp4_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044ddb0        position = 0x42c80000
0044dd95        position = 0xc2c80000
0044ddcc        play_sound_effect_backend(sound_id, fconvert.s(fconvert.t(1f) - fconvert.t(var_1c) * fconvert.t(0.0399999991f)), -1f, position)
0044ddd8        return
