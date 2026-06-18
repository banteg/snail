/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_sprite_facing_angle @ 0x44e410 */

0044e41c        float var_c
0044e41c        if (((sprite->flags).w:1.b & 4) == 0)
0044e4e1        long double x87_r7_14 = fconvert.t(sprite->position.y) - fconvert.t(sprite->previous_position.y)
0044e4e8        var_c = fconvert.s(fconvert.t(sprite->position.x) - fconvert.t(sprite->previous_position.x))
0044e4ff        float var_8_2 = fconvert.s(x87_r7_14)
0044e50f        float var_4_3 = fconvert.s(fconvert.t(sprite->position.z) - fconvert.t(sprite->previous_position.z))
0044e513        int32_t* eax_8 = rotate_vector_by_matrix(&var_c, matrix)
0044e524        int32_t var_4_4 = eax_8[2]
0044e536        sprite->facing_angle = fconvert.s(atan2_positive(*eax_8, eax_8[1]) + fconvert.t(7.06858349f))
0044e536        return
0044e422        long double x87_r7 = fconvert.t(sprite->facing_refresh_progress)
0044e428        long double temp1_1 = fconvert.t(0f)
0044e428        x87_r7 - temp1_1
0044e433        if ((((x87_r7 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1_1) ? 1 : 0) << 0xa | (x87_r7 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
0044e442        long double x87_r7_4 = fconvert.t(sprite->position.y) - fconvert.t(sprite->previous_position.y)
0044e449        var_c = fconvert.s(fconvert.t(sprite->position.x) - fconvert.t(sprite->previous_position.x))
0044e460        float var_8_1 = fconvert.s(x87_r7_4)
0044e470        float var_4_1 = fconvert.s(fconvert.t(sprite->position.z) - fconvert.t(sprite->previous_position.z))
0044e474        int32_t* eax_4 = rotate_vector_by_matrix(&var_c, matrix)
0044e485        int32_t var_4_2 = eax_4[2]
0044e48e        long double x87_r7_8 = atan2_positive(*eax_4, eax_4[1]) + fconvert.t(7.06858349f)
0044e497        sprite->facing_refresh_progress = 0.00100000005f
0044e4a1        sprite->facing_angle = fconvert.s(x87_r7_8)
0044e4aa        long double x87_r7_10 = fconvert.t(sprite->facing_refresh_step) + fconvert.t(sprite->facing_refresh_progress)
0044e4b0        sprite->facing_refresh_progress = fconvert.s(x87_r7_10)
0044e4b6        long double temp2_1 = fconvert.t(1f)
0044e4b6        x87_r7_10 - temp2_1
0044e4c1        if ((((x87_r7_10 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp2_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044e4c3        sprite->facing_refresh_progress = 0f
0044e53d        return
