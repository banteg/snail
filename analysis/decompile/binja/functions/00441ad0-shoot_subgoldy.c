/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: shoot_subgoldy @ 0x441ad0 */

00441ad5        int32_t i = 0
00441ad8        int32_t var_1c = 0
00441adc        int32_t* ecx = arg1 + 0x80
00441ae5        if (*ecx == 0)
00441b21        struct Vec3 origin
00441b21        origin.x = *arg2
00441b30        origin.y = fconvert.s(float.t(i) * fconvert.t(-0.00999999978f) + fconvert.t(arg2[1]))
00441b38        origin.z = arg2[2]
00441b51        spawn_sub_lazer_projectile(i * 0xb0 + arg1, &origin, arg3)
00441b67        return play_sound_effect_at_position(0xf, arg2)
00441ae7        i += 1
00441ae8        ecx = &ecx[0x2c]
00441af1        do while (i s< 0x14)
00441af3        int32_t i_1 = i
00441afb        return i
