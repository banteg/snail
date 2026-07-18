/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_sprite_facing_angle @ 0x44e410 */

0044e41c        struct Vec3 vector
0044e41c        if (((sprite->flags).w:1.b & 4) == 0)
0044e4e8        vector.x = fconvert.s(fconvert.t(sprite->position.x) - fconvert.t(sprite->previous_position.x))
0044e4ff        vector.y = fconvert.s(fconvert.t(sprite->position.y) - fconvert.t(sprite->previous_position.y))
0044e50f        vector.z = fconvert.s(fconvert.t(sprite->position.z) - fconvert.t(sprite->previous_position.z))
0044e513        struct Vec3* eax_8 = rotate_vector_by_matrix(&vector, matrix)
0044e524        vector.z = eax_8->z
0044e536        sprite->facing_angle = fconvert.s(atan2_positive(eax_8->x, eax_8->y) + fconvert.t(7.06858349f))
0044e536        return
0044e422        long double x87_r7 = fconvert.t(sprite->facing_refresh_progress)
0044e428        long double temp1_1 = fconvert.t(0f)
0044e428        x87_r7 - temp1_1
0044e433        if ((((x87_r7 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1_1) ? 1 : 0) << 0xa | (x87_r7 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
0044e449        vector.x = fconvert.s(fconvert.t(sprite->position.x) - fconvert.t(sprite->previous_position.x))
0044e460        vector.y = fconvert.s(fconvert.t(sprite->position.y) - fconvert.t(sprite->previous_position.y))
0044e470        vector.z = fconvert.s(fconvert.t(sprite->position.z) - fconvert.t(sprite->previous_position.z))
0044e474        struct Vec3* eax_4 = rotate_vector_by_matrix(&vector, matrix)
0044e485        vector.z = eax_4->z
0044e48e        long double x87_r7_8 = atan2_positive(eax_4->x, eax_4->y) + fconvert.t(7.06858349f)
0044e497        sprite->facing_refresh_progress = 0.00100000005f
0044e4a1        sprite->facing_angle = fconvert.s(x87_r7_8)
0044e4aa        long double x87_r7_10 = fconvert.t(sprite->facing_refresh_step) + fconvert.t(sprite->facing_refresh_progress)
0044e4b0        sprite->facing_refresh_progress = fconvert.s(x87_r7_10)
0044e4b6        long double temp2_1 = fconvert.t(1f)
0044e4b6        x87_r7_10 - temp2_1
0044e4c1        if ((((x87_r7_10 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp2_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044e4c3        sprite->facing_refresh_progress = 0f
0044e53d        return
