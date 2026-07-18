/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: play_movement_state_sound @ 0x43afd0 */

0043afd7        uint8_t movement_flags = (player->movement_flags).b
0043afdf        int32_t eax_1
0043afdf        int32_t sound_id
0043afdf        int16_t x87control
0043afdf        if ((movement_flags & 7) == 0)
0043b006        if ((movement_flags & 0x18) != 0)
0043b01b        eax_1 = ftol(x87control, float.t(next_math_random_value()) * fconvert.t(9.15527344e-05f))
0043b020        player->movement_sound_variant_sample = eax_1
0043b026        sound_id = eax_1 + 0x13
0043b029        goto label_43b054
0043b02d        if ((movement_flags & 0x60) != 0)
0043b046        eax_1 = ftol(x87control, float.t(next_math_random_value()) * fconvert.t(9.15527344e-05f))
0043b04b        player->movement_sound_variant_sample = eax_1
0043b051        sound_id = eax_1 + 0x16
0043b051        goto label_43b054
0043b02d        return
0043aff4        eax_1 = ftol(x87control, float.t(next_math_random_value()) * fconvert.t(6.10351562e-05f))
0043aff9        player->movement_sound_variant_sample = eax_1
0043afff        sound_id = eax_1 + 0x11
0043b054        label_43b054:
0043b057        if (sound_id == 0xffffffff)
0043b057        return
0043b065        if (player->attachment_exit_pending != 0)
0043b06b        struct GameRoot* game_base_1 = g_game_base
0043b09b        struct Vec3 vector
0043b09b        vector.y = fconvert.s(fconvert.t(game_base_1->players[0].body.transform.position.y) - fconvert.t(player->body.transform.position.y))
0043b0a3        vector.x = fconvert.s(fconvert.t(game_base_1->players[0].body.transform.position.x) - fconvert.t(player->body.transform.position.x))
0043b0af        vector.z = fconvert.s(fconvert.t(game_base_1->players[0].body.transform.position.z) - fconvert.t(player->body.transform.position.z))
0043b0be        long double x87_r7_15 = fconvert.t(1f) - normalize_vector(&vector) * fconvert.t(0.0166666675f)
0043b0c4        float gain = fconvert.s(x87_r7_15)
0043b0c8        long double temp0 = fconvert.t(0f)
0043b0c8        x87_r7_15 - temp0
0043b0d3        if ((((x87_r7_15 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_15, temp0) ? 1 : 0) << 0xa | (x87_r7_15 == temp0 ? 1 : 0) << 0xe):1.b & 1) == 0)
0043b0df        long double x87_r7_16 = fconvert.t(gain)
0043b0e3        long double temp1_1 = fconvert.t(1f)
0043b0e3        x87_r7_16 - temp1_1
0043b0ee        if ((((x87_r7_16 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_16, temp1_1) ? 1 : 0) << 0xa | (x87_r7_16 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043b0f0        gain = 1f
0043b0d5        gain = 0f
0043b103        play_sound_effect_scaled(&g_sound_effect_manager, sound_id, gain)
0043b10d        return
0043b114        play_sound_effect(&g_sound_effect_manager, sound_id)
0043b11e        return
