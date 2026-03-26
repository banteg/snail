/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: play_movement_state_sound @ 0x43afd0 */

0043afd7        uint32_t movement_flags = player->movement_flags
0043afdf        int32_t edi_1
0043afdf        int16_t x87control
0043afdf        if ((movement_flags.b & 7) == 0)
0043b006        if ((movement_flags.b & 0x18) != 0)
0043b01b        movement_flags = __ftol(x87control, float.t(next_math_random_value()) * fconvert.t(9.15527344e-05f))
0043b020        player->_pad_124[0xa8] = movement_flags.b
0043b020        player->_pad_124[0xa9] = movement_flags:1.b
0043b020        player->_pad_124[0xaa] = movement_flags:2.b
0043b020        player->_pad_124[0xab] = movement_flags:3.b
0043b026        edi_1 = movement_flags + 0x13
0043b029        goto label_43b054
0043b02d        if ((movement_flags.b & 0x60) != 0)
0043b046        movement_flags = __ftol(x87control, float.t(next_math_random_value()) * fconvert.t(9.15527344e-05f))
0043b04b        player->_pad_124[0xa8] = movement_flags.b
0043b04b        player->_pad_124[0xa9] = movement_flags:1.b
0043b04b        player->_pad_124[0xaa] = movement_flags:2.b
0043b04b        player->_pad_124[0xab] = movement_flags:3.b
0043b051        edi_1 = movement_flags + 0x16
0043b051        goto label_43b054
0043aff4        movement_flags = __ftol(x87control, float.t(next_math_random_value()) * fconvert.t(6.10351562e-05f))
0043aff9        player->_pad_124[0xa8] = movement_flags.b
0043aff9        player->_pad_124[0xa9] = movement_flags:1.b
0043aff9        player->_pad_124[0xaa] = movement_flags:2.b
0043aff9        player->_pad_124[0xab] = movement_flags:3.b
0043afff        edi_1 = movement_flags + 0x11
0043b054        label_43b054:
0043b057        if (edi_1 != 0xffffffff)
0043b05d        movement_flags.b = player->attachment_exit_pending
0043b065        if (movement_flags.b == 0)
0043b114        return play_sound_effect(edi_1)
0043b06b        void* eax_3 = data_4df904
0043b09b        struct Vec3 vector
0043b09b        vector.y = fconvert.s(fconvert.t(*(eax_3 + 0x190)) - fconvert.t(player->position.y))
0043b0a3        vector.x = fconvert.s(fconvert.t(*(eax_3 + 0x18c)) - fconvert.t(player->position.x))
0043b0af        vector.z = fconvert.s(fconvert.t(*(eax_3 + 0x194)) - fconvert.t(player->position.z))
0043b0be        long double x87_r7_15 = fconvert.t(1f) - normalize_vector(&vector) * fconvert.t(0.0166666675f)
0043b0c4        float var_1c_4 = fconvert.s(x87_r7_15)
0043b0c8        long double temp0 = fconvert.t(0f)
0043b0c8        x87_r7_15 - temp0
0043b0d3        if ((((x87_r7_15 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_15, temp0) ? 1 : 0) << 0xa | (x87_r7_15 == temp0 ? 1 : 0) << 0xe):1.b & 1) == 0)
0043b0df        long double x87_r7_16 = fconvert.t(var_1c_4)
0043b0e3        long double temp1_1 = fconvert.t(1f)
0043b0e3        x87_r7_16 - temp1_1
0043b0ee        if ((((x87_r7_16 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_16, temp1_1) ? 1 : 0) << 0xa | (x87_r7_16 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043b0f0        var_1c_4 = 1f
0043b0d5        var_1c_4 = 0f
0043b10d        return play_sound_effect_scaled(edi_1, var_1c_4)
0043b11e        return movement_flags
