/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_sprite @ 0x44df30 */

0044df30        uint32_t flags_2 = sprite->flags
0044df37        int16_t eax
0044df37        if ((flags_2:1.b & 8) != 0)
0044df39        eax.b = g_sprite_manager
0044df40        if ((flags_2:1.b & 8) != 0 && eax.b != 0)
0044df40        return
0044df49        if ((flags_2.b & 8) != 0)
0044dfb9        sprite->flags = flags_2 & 0xfffffff7
0044dfbc        label_44dfbc:
0044dfbc        uint32_t flags = sprite->flags
0044dfc0        flags.b &= 0xf7
0044dfc5        sprite->flags = flags
0044dfcf        sprite->previous_position.x = sprite->position.x
0044dfd4        sprite->previous_position.y = sprite->position.y
0044dfdb        sprite->previous_position.z = sprite->position.z
0044dfe3        sprite->position.x = fconvert.s(fconvert.t(sprite->velocity.x) + fconvert.t(sprite->position.x))
0044dfeb        sprite->position.y = fconvert.s(fconvert.t(sprite->velocity.y) + fconvert.t(sprite->position.y))
0044dff4        sprite->position.z = fconvert.s(fconvert.t(sprite->velocity.z) + fconvert.t(sprite->position.z))
0044dffd        sprite->velocity.y = fconvert.s(fconvert.t(sprite->gravity_step) + fconvert.t(sprite->velocity.y))
0044e009        sprite->facing_angle = fconvert.s(fconvert.t(sprite->facing_angle_step) + fconvert.t(sprite->facing_angle))
0044e00c        long double x87_r7_17 = fconvert.t(sprite->lifetime_step)
0044e00f        long double temp1_1 = fconvert.t(0f)
0044e00f        x87_r7_17 - temp1_1
0044e01a        uint32_t flags_1 = sprite->flags
0044e01d        if ((((x87_r7_17 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_17, temp1_1) ? 1 : 0) << 0xa | (x87_r7_17 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0044e024        flags_1:1.b &= 0xfd
0044e01f        flags_1:1.b |= 2
0044e029        sprite->flags = flags_1
0044e032        if ((flags_1 & 0x2000) != 0)
0044e03e        long double x87_r7_19 = fconvert.t(sprite->frame_progress_step) + fconvert.t(sprite->frame_progress)
0044e044        long double temp5_1 = fconvert.t(1f)
0044e044        x87_r7_19 - temp5_1
0044e04a        sprite->frame_progress = fconvert.s(x87_r7_19)
0044e04a        bool c1_2 = unimplemented  {fst dword [ecx+0xac], st0}
0044e055        if ((((x87_r7_19 < temp5_1 ? 1 : 0) << 8 | (c1_2 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_19, temp5_1) ? 1 : 0) << 0xa | (x87_r7_19 == temp5_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
0044e06d        int32_t edx_3 = sprite->frame + sprite->frame_step
0044e06f        int32_t frame_count = sprite->frame_count
0044e07b        sprite->frame_progress = fconvert.s(x87_r7_19 - fconvert.t(1f))
0044e081        sprite->frame = edx_3
0044e087        if ((flags_1 & 0x4000) != 0)
0044e08e        if (edx_3 == frame_count)
0044e091        sprite->frame_step = 0xffffffff
0044e097        sprite->frame = frame_count - 1
0044e0a3        if (sprite->frame == 0xffffffff)
0044e0a5        sprite->frame = 0
0044e0af        sprite->frame_step = 1
0044e0bd        if (edx_3 == frame_count)
0044e0bf        sprite->frame = 0
0044e0d7        set_sprite_texture_ref(sprite, sprite->texture_id, sprite->frame)
0044df4e        long double x87_r7_2 = fconvert.t(sprite->progress_step) + fconvert.t(sprite->progress)
0044df51        long double temp0_1 = fconvert.t(1f)
0044df51        x87_r7_2 - temp0_1
0044df57        sprite->progress = fconvert.s(x87_r7_2)
0044df57        bool c1_1 = unimplemented  {fst dword [ecx+0x68], st0}
0044df5f        long double temp2_1
0044df5f        if ((((x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) != 0)
0044df61        temp2_1 = fconvert.t(0f)
0044df61        x87_r7_2 - temp2_1
0044df6c        if ((((x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) != 0 && (((x87_r7_2 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp2_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp2_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0044df6e        long double x87_r7_3 = fconvert.t(sprite->lifetime_step)
0044df71        long double temp3_1 = fconvert.t(0f)
0044df71        x87_r7_3 - temp3_1
0044df7c        if ((((x87_r7_3 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp3_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
0044df81        long double x87_r7_5 = fconvert.t(sprite->lifetime_step) + fconvert.t(sprite->lifetime)
0044df84        sprite->lifetime = fconvert.s(x87_r7_5)
0044df87        long double temp4_1 = fconvert.t(1f)
0044df87        x87_r7_5 - temp4_1
0044df92        if ((((x87_r7_5 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp4_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp4_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044df94        sprite->lifetime_step = 0f
0044df7c        goto label_44dfbc
0044dfa2        sprite->progress = 1f
0044dfa9        if ((flags_2:1.b & 1) == 0)
0044dfaf        kill_sprite(sprite)
0044e0e1        return
