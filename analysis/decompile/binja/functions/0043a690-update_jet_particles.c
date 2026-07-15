/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_jet_particles @ 0x43a690 */

0043a69a        if (sub_hover->state != SUB_HOVER_STATE_ACTIVE)
0043a69a        return
0043a6a0        struct SubgameRuntime* game = sub_hover->game
0043a6b8        if (game->player.presentation.jetpack_channel.anim_manager.active_animation != *(game->player.presentation.jetpack_channel.animation_slots[0].body.bod.object + 0xbc))
0043a6b8        return
0043a6da        float var_3c_1 = fconvert.s(float.t(next_math_random_value()) * fconvert.t(1.52587893e-06f) + fconvert.t(0.400000006f))
0043a6e7        int32_t esi_1 = 0
0043a6ed        int32_t var_50_1 = 0
0043a6fd        float var_40_1 = fconvert.s(float.t(next_math_random_value()) * fconvert.t(1.52587893e-06f) + fconvert.t(0.119999997f))
0043a70b        while (true)
0043a70b        int32_t i = 0
0043a70d        int32_t i_1 = 0
0043a717        float var_48_1 = fconvert.s(float.t(var_50_1) * fconvert.t(0.0714285746f))
0043a72f        float var_44_3 = fconvert.s((fconvert.t(1f) - fconvert.t(var_48_1)) * fconvert.t(var_40_1) * fconvert.t(sub_hover->warning_intensity))
0043a735        float x
0043a735        float y
0043a735        float z
0043a735        if (i != 0)
0043a75e        struct Vec3* edx_5 = &sub_hover->game->player.presentation.snail_hotspots_world[0xe]
0043a766        x = edx_5->x
0043a76d        y = edx_5->y
0043a774        z = edx_5->z
0043a73d        struct Vec3* eax_4 = &sub_hover->game->player.presentation.snail_hotspots_world[0xd]
0043a744        x = eax_4->x
0043a74b        y = eax_4->y
0043a752        z = eax_4->z
0043a787        struct Vec3* eax_9 = &sub_hover->player->presentation.body.transform.basis_forward
0043a792        long double x87_r7_16 = fneg(fconvert.t(var_48_1) * fconvert.t(var_3c_1) * fconvert.t(sub_hover->warning_intensity))
0043a7a5        long double x87_r7_17 = x87_r7_16 * fconvert.t(eax_9->z)
0043a7b7        void** eax_12 = ((i + (esi_1 << 1) + 2) << 4) + sub_hover
0043a7b9        float var_34_1 = fconvert.s(fconvert.t(x) + fconvert.t(fconvert.s(x87_r7_16 * fconvert.t(eax_9->x))))
0043a7c3        long double x87_r6_8 = fconvert.t(y) + fconvert.t(fconvert.s(x87_r7_16 * fconvert.t(eax_9->y)))
0043a7c7        *(*eax_12 + 0x64) = var_44_3
0043a7cc        *(*eax_12 + 0x60) = var_44_3
0043a7d1        float var_30_1 = fconvert.s(x87_r6_8)
0043a7e1        int32_t* eax_14 = *eax_12 + 0x48
0043a7e9        *eax_14 = var_34_1
0043a7eb        eax_14[1] = var_30_1
0043a7ee        float var_2c_1 = fconvert.s(fconvert.t(z) + x87_r7_17)
0043a7f8        eax_14[2] = var_2c_1
0043a7fb        if (esi_1 == 0xe)
0043a80e        long double x87_r7_20 = float.t(next_math_random_value()) * fconvert.t(3.05175781e-05f)
0043a814        long double temp0_1 = fconvert.t(0.899999976f)
0043a814        x87_r7_20 - temp0_1
0043a81f        if ((((x87_r7_20 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp0_1) ? 1 : 0) << 0xa | (x87_r7_20 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043a83d        struct Sprite* eax_18 = allocate_sprite(&g_sprite_manager, sub_hover->game->player.player_slot, 0x21, 0xffffffff, 0xffffffff)
0043a853        enum SpriteFlag flags = eax_18->flags
0043a85b        flags:1.b |= 8
0043a862        eax_18->flags = flags
0043a867        eax_18->progress = 0f
0043a86a        eax_18->progress_step = 0.138888896f
0043a871        eax_18->lifetime = 0f
0043a874        eax_18->lifetime_step = 0f
0043a877        struct tColour color
0043a877        struct tColour* eax_19 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0043a881        eax_18->color.r = eax_19->r
0043a887        eax_18->color.g = eax_19->g
0043a88d        eax_18->color.b = eax_19->b
0043a890        float a = eax_19->a
0043a893        eax_18->size_start = 0.100000001f
0043a89a        eax_18->size_end = 0.300000012f
0043a8a1        eax_18->color.a = a
0043a8aa        struct Vec3* eax_21 = &sub_hover->game->player.velocity
0043a8bd        float var_28_1 = fconvert.s(fconvert.t(eax_21->x) * fconvert.t(0.850000024f))
0043a8ce        float var_24_1 = fconvert.s(fconvert.t(eax_21->y) * fconvert.t(0.850000024f))
0043a8d5        long double x87_r7_26 = fconvert.t(eax_21->z) * fconvert.t(0.850000024f)
0043a8df        eax_18->gravity_step = 0x3a83126f
0043a8e6        eax_18->velocity.x = var_28_1
0043a8e8        eax_18->position.x = var_34_1
0043a8ea        float var_20_1 = fconvert.s(x87_r7_26)
0043a8f2        eax_18->velocity.y = var_24_1
0043a8f9        eax_18->position.y = var_30_1
0043a8fc        eax_18->velocity.z.b = var_20_1.b
0043a8fc        *(&eax_18->velocity.z + 1) = var_20_1:1.b
0043a8fc        *(&eax_18->velocity.z + 2) = var_20_1:2.b
0043a8fc        *(&eax_18->velocity.z + 3) = var_20_1:3.b
0043a8ff        eax_18->position.z = var_2c_1
0043a902        esi_1 = var_50_1
0043a906        i = i_1
0043a90a        i += 1
0043a90e        i_1 = i
0043a912        do while (i s< 2)
0043a91c        var_50_1 = esi_1 + 1
0043a920        if (esi_1 + 1 s>= 0xf)
0043a920        break
0043a703        esi_1 = var_50_1
0043a92d        return
