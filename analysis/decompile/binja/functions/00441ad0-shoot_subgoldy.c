/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: shoot_subgoldy @ 0x441ad0 */

00441ad5        int32_t i = 0
00441ad8        int32_t var_1c = 0
00441adc        enum SubLazerState* ecx = &manager->slots[0].state
00441ae5        if ((ecx - 0x80)->slots[0].state == SUB_LAZER_STATE_INACTIVE)
00441b21        struct Vec3 origin_1
00441b21        origin_1.x = origin->x
00441b30        origin_1.y = fconvert.s(float.t(i) * fconvert.t(-0.00999999978f) + fconvert.t(origin->y))
00441b38        origin_1.z = origin->z
00441b51        spawn_sub_lazer_projectile(&manager->slots[i], &origin_1, direction)
00441b5e        play_sound_effect_at_position(&g_sound_effect_manager, 0xf, origin)
00441b67        return
00441ae7        i += 1
00441ae8        ecx = &ecx[0x2c]
00441af1        do while (i s< 0x14)
00441af3        int32_t i_1 = i
00441afb        return
