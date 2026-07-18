/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_nuke @ 0x4471e0 */

004471e0        int32_t loop_index_float_source = nuke
004471e4        enum NukeState state = nuke->state
004471f0        if (state == NUKE_STATE_INACTIVE || state != 1)
004471f0        return
004471fc        nuke->orbit_center_z = fconvert.s(fconvert.t(nuke->orbit_center_z_step) + fconvert.t(nuke->orbit_center_z))
00447202        long double x87_r7_4 = fconvert.t(nuke->orbit_phase_step) + fconvert.t(nuke->orbit_phase)
00447205        long double temp2_1 = fconvert.t(6.28318548f)
00447205        x87_r7_4 - temp2_1
0044720b        nuke->orbit_phase = fconvert.s(x87_r7_4)
0044720b        bool c1_1 = unknown  {fst dword [edi+0x10], st0}
00447213        if ((((x87_r7_4 < temp2_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_4, temp2_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp2_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
0044721b        nuke->orbit_phase = fconvert.s(x87_r7_4 - fconvert.t(6.28318548f))
00447224        int32_t i = 0
00447227        loop_index_float_source = 0
0044722b        struct Sprite** sprite_slots = &nuke->sprite_slots
00447246        (*sprite_slots)->position.z = nuke->orbit_center_z
00447249        float var_4 = fconvert.s(float.t(loop_index_float_source) * fconvert.t(0.0399999991f) * fconvert.t(6.28318548f) + fconvert.t(nuke->orbit_phase))
00447260        (*sprite_slots)->position.x = fconvert.s(sine(var_4) * fconvert.t(7f))
00447268        long double x87_r7_14 = cosine(var_4) * fconvert.t(7f)
0044726e        struct Sprite* eax_4 = *sprite_slots
00447273        i += 1
00447274        sprite_slots = &sprite_slots[1]
0044727a        loop_index_float_source = i
0044727e        eax_4->position.y = fconvert.s(x87_r7_14)
00447281        do while (i s< 0x19)
00447288        return
