/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_slug_hazard_ai @ 0x43f930 */

0043f943        if (slot->game->_pad_00[9] != 0)
0043f943        return 
0043f949        uint32_t state = slot->state
0043f952        void* ecx_15
0043f952        if (state u> 4)
0043fccd        label_43fccd:
0043fccd        unimplemented  {fld st0, dword [eax+0x370]}
0043fcd3        unimplemented  {fadd dword [esi+0x98]}
0043fcd9        *(slot->sprite + 0x7c) = fconvert.s(unimplemented  {fstp dword [ecx+0x7c], st0})
0043fcd9        unimplemented  {fstp dword [ecx+0x7c], st0}
0043fce9        if (slot->player->follow_state.active == 1)
0043fcf1        unimplemented  {fld st0, dword [ecx+0x3a0]}
0043fcf7        unimplemented  {fadd dword [eax+0x7c]}
0043fcfa        *(slot->sprite + 0x7c) = fconvert.s(unimplemented  {fstp dword [eax+0x7c], st0})
0043fcfa        unimplemented  {fstp dword [eax+0x7c], st0}
0043fcff        update_slug_voice_ai(slot)
0043f958        switch (state)
0043f96d        case 1
0043f96d        if (slot->hit_flash_pending != 0 && data_4b7236 != 0)
0043f96f        float hit_flash_progress_step = slot->hit_flash_progress_step
0043f975        slot->hit_flash_pending = 0
0043f97b        slot->hit_flash_progress = hit_flash_progress_step
0043f981        long double x87_r7_1 = fconvert.t(slot->hit_flash_progress)
0043f987        long double temp1_1 = fconvert.t(0f)
0043f987        x87_r7_1 - temp1_1
0043f98d        state.w = (x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe
0043f992        void* eax_1
0043f992        if ((state:1.b & 0x40) != 0)
0043fa56        slot->blink_progress = fconvert.s(fconvert.t(slot->blink_step) + fconvert.t(slot->blink_progress))
0043fa5c        long double x87_r7_6 = fconvert.t(slot->blink_step)
0043fa62        long double temp3_1 = fconvert.t(0f)
0043fa62        x87_r7_6 - temp3_1
0043fa68        state.w = (x87_r7_6 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp3_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp3_1 ? 1 : 0) << 0xe
0043fa6d        if ((state:1.b & 0x41) != 0)
0043fa8f        set_sprite_texture_ref(slot->sprite, 0x77, 0)
0043fa9a        *(slot->sprite + 0x28) = 0
0043fa77        set_sprite_texture_ref(slot->sprite, 0x76, 0)
0043fa7c        void* sprite = slot->sprite
0043fa82        *(sprite + 0x28) = 0
0043fa82        *(sprite + 0x29) = 0
0043fa82        *(sprite + 0x2a) = 0
0043fa82        *(sprite + 0x2b) = 0
0043faba        int32_t edx_4
0043faba        eax_1, edx_4 = store_color4f(slot->sprite + 0x2c, 1f, 1f, 1f, 1f)
0043fabf        long double x87_r6_1 = fconvert.t(slot->blink_progress)
0043fac5        long double temp10_1 = fconvert.t(0f)
0043fac5        x87_r6_1 - temp10_1
0043facb        eax_1.w = (x87_r6_1 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_1, temp10_1) ? 1 : 0) << 0xa | (x87_r6_1 == temp10_1 ? 1 : 0) << 0xe | 0x3800
0043fad0        if ((eax_1:1.b & 1) == 0)
0043faf0        long double x87_r6_3 = fconvert.t(slot->blink_progress)
0043faf6        long double temp13_1 = fconvert.t(1f)
0043faf6        x87_r6_3 - temp13_1
0043fafc        eax_1.w = (x87_r6_3 < temp13_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_3, temp13_1) ? 1 : 0) << 0xa | (x87_r6_3 == temp13_1 ? 1 : 0) << 0xe | 0x3800
0043fb01        if ((eax_1:1.b & 0x41) == 0)
0043fb03        slot->blink_progress = 1f
0043fb0d        slot->blink_step = -0.166666672f
0043fad2        slot->blink_progress = 0f
0043fae3        int32_t edx_5
0043fae3        long double st0_1
0043fae3        st0_1, eax_1, edx_5 = advance_blink_random(data_4df904 + 0x74618)
0043fae8        slot->blink_step = fconvert.s(st0_1)
0043f99e        long double x87_r7_3 = fconvert.t(slot->hit_flash_progress_step) + fconvert.t(slot->hit_flash_progress)
0043f9a4        slot->hit_flash_progress = fconvert.s(x87_r7_3)
0043f9aa        long double temp4_1 = fconvert.t(1f)
0043f9aa        x87_r7_3 - temp4_1
0043f9b0        state.w = (x87_r7_3 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp4_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp4_1 ? 1 : 0) << 0xe
0043f9b5        if ((state:1.b & 0x41) != 0)
0043fa18        *(slot->sprite + 0x28) = 5
0043fa25        set_sprite_texture_ref(slot->sprite, 0x78, 0)
0043fa3f        int32_t edx_2
0043fa3f        eax_1, edx_2 = store_color4f(slot->sprite + 0x2c, 1f, 0f, 0f, 0.99000001f)
0043f9b7        void* sprite_2 = slot->sprite
0043f9bd        slot->hit_flash_progress = 0f
0043f9c3        slot->blink_progress = 1f
0043f9cd        slot->blink_step = -0.166666672f
0043f9d7        *(sprite_2 + 0x28) = 0
0043f9f7        store_color4f(slot->sprite + 0x2c, 1f, 1f, 1f, 1f)
0043fa05        int32_t edx_1
0043fa05        eax_1, edx_1 = set_sprite_texture_ref(slot->sprite, 0x77, 0)
0043fb20        long double x87_r6_5 = fconvert.t(slot->player->live_matrix.position.z) + fconvert.t(1f)
0043fb26        long double temp11_1 = fconvert.t(slot->world_position.z)
0043fb26        x87_r6_5 - temp11_1
0043fb29        eax_1.w = (x87_r6_5 < temp11_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_5, temp11_1) ? 1 : 0) << 0xa | (x87_r6_5 == temp11_1 ? 1 : 0) << 0xe | 0x3800
0043fb36        if ((eax_1:1.b & 0x41) == 0 && slot->ambient_alert_checked == 0)
0043fb38        slot->ambient_alert_checked = 1
0043fb3f        int32_t edx_6
0043fb3f        eax_1, edx_6 = next_math_random_value()
0043fb4c        long double x87_r6_7 = float.t(eax_1) * fconvert.t(3.05175781e-05f)
0043fb52        long double temp15_1 = fconvert.t(0.600000024f)
0043fb52        x87_r6_7 - temp15_1
0043fb58        eax_1.w = (x87_r6_7 < temp15_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_7, temp15_1) ? 1 : 0) << 0xa | (x87_r6_7 == temp15_1 ? 1 : 0) << 0xe | 0x3800
0043fb5d        int32_t edx_8
0043fb5d        int16_t x87control
0043fb5d        if ((eax_1:1.b & 0x41) == 0)
0043fb81        eax_1, edx_8 = play_slug_voice(slot, 0x1e - __ftol(x87control, float.t(next_math_random_value()) * fconvert.t(-0.000122070312f)))
0043fb86        struct Player* player = slot->player
0043fb8c        long double x87_r6_10 = fconvert.t(slot->world_position.z)
0043fb8f        long double temp14_1 = fconvert.t(player->live_matrix.position.z)
0043fb8f        x87_r6_10 - temp14_1
0043fb92        eax_1.w = (x87_r6_10 < temp14_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_10, temp14_1) ? 1 : 0) << 0xa | (x87_r6_10 == temp14_1 ? 1 : 0) << 0xe | 0x3800
0043fb9f        if ((eax_1:1.b & 1) != 0 && slot->passed_player == 0)
0043fba1        slot->passed_player = 1
0043fbaf        if (slot->engagement_voice_gate == 1)
0043fbb4        long double x87_r6_12 = fconvert.t(player->live_matrix.position.z) + fconvert.t(16f)
0043fbba        long double temp17_1 = fconvert.t(slot->world_position.z)
0043fbba        x87_r6_12 - temp17_1
0043fbbd        eax_1.w = (x87_r6_12 < temp17_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_12, temp17_1) ? 1 : 0) << 0xa | (x87_r6_12 == temp17_1 ? 1 : 0) << 0xe | 0x3800
0043fbc2        if ((eax_1:1.b & 0x41) == 0)
0043fbcf        slot->engagement_voice_gate = 0
0043fbd5        play_voice_manager(0x751498, 2, 1, 0xffffffff)
0043fbe5        int32_t* eax_7 = slot->sprite + 0x48
0043fbe8        int32_t edx_10
0043fbe8        edx_10.b = slot->world_position.x.b
0043fbe8        edx_10:1.b = *(&slot->world_position.x + 1)
0043fbe8        edx_10:2.b = *(&slot->world_position.x + 2)
0043fbe8        edx_10:3.b = *(&slot->world_position.x + 3)
0043fbea        *eax_7 = edx_10
0043fbec        int32_t edx_11
0043fbec        edx_11.b = slot->world_position.y.b
0043fbec        edx_11:1.b = *(&slot->world_position.y + 1)
0043fbec        edx_11:2.b = *(&slot->world_position.y + 2)
0043fbec        edx_11:3.b = *(&slot->world_position.y + 3)
0043fbef        eax_7[1] = edx_11
0043fbf2        int32_t ecx_14
0043fbf2        ecx_14.b = slot->world_position.z.b
0043fbf2        ecx_14:1.b = *(&slot->world_position.z + 1)
0043fbf2        ecx_14:2.b = *(&slot->world_position.z + 2)
0043fbf2        ecx_14:3.b = *(&slot->world_position.z + 3)
0043fbf5        eax_7[2] = ecx_14
0043fbf8        struct Player* player_1 = slot->player
0043fbfe        long double x87_r6_13 = fconvert.t(slot->world_position.z)
0043fc01        long double temp16_1 = fconvert.t(player_1->interaction_max_z)
0043fc01        x87_r6_13 - temp16_1
0043fc07        eax_7.w = (x87_r6_13 < temp16_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_13, temp16_1) ? 1 : 0) << 0xa | (x87_r6_13 == temp16_1 ? 1 : 0) << 0xe | 0x3800
0043fc0c        if ((eax_7:1.b & 1) == 0)
0043fc8d        long double x87_r6_14 = fconvert.t(player_1->nuke_effect_progress)
0043fc93        long double temp18_1 = fconvert.t(0f)
0043fc93        x87_r6_14 - temp18_1
0043fc99        eax_7.w = (x87_r6_14 < temp18_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_14, temp18_1) ? 1 : 0) << 0xa | (x87_r6_14 == temp18_1 ? 1 : 0) << 0xe | 0x3800
0043fc9e        if ((eax_7:1.b & 0x41) == 0)
0043fca2        kill_slug_hazard(slot)
0043fcbc        sub_415ef0(&slot->game->__offset(0x1270fd4).d, &slot->world_position.x, 2f, 1, slot)
0043fcbc        goto label_43fccd
0043fc0e        int16_t eax_8 = (slot->_pad_00[4].d).w
0043fc11        slot->state = 0
0043fc20        ecx_15 = data_4df904 + 0x5a8
0043fc26        if ((eax_8:1.b & 2) == 0)
0043fc2d        report_errorf("List remove")
0043fc3b        kill_sprite(slot->sprite)
0043fc46        return 
0043fc49        if ((eax_8.b & 0x40) != 0)
0043fc50        report_errorf("List remove NEXTBOD")
0043fc5e        kill_sprite(slot->sprite)
0043fc69        return 
0043fc6a        void* eax_9
0043fc6a        eax_9.b = slot->_pad_00[0xc]
0043fc6a        eax_9:1.b = slot->_pad_00[0xd]
0043fc6a        eax_9:2.b = slot->_pad_00[0xe]
0043fc6a        eax_9:3.b = slot->_pad_00[0xf]
0043fc6f        if (eax_9 != 0)
0043fc71        int32_t edx_13
0043fc71        edx_13.b = slot->_pad_00[8]
0043fc71        edx_13:1.b = slot->_pad_00[9]
0043fc71        edx_13:2.b = slot->_pad_00[0xa]
0043fc71        edx_13:3.b = slot->_pad_00[0xb]
0043fc74        *(eax_9 + 8) = edx_13
0043fc77        void* eax_10
0043fc77        eax_10.b = slot->_pad_00[8]
0043fc77        eax_10:1.b = slot->_pad_00[9]
0043fc77        eax_10:2.b = slot->_pad_00[0xa]
0043fc77        eax_10:3.b = slot->_pad_00[0xb]
0043fc7c        if (eax_10 == 0)
0043fc7c        goto label_43ffdc
0043fc82        int32_t edx_14
0043fc82        edx_14.b = slot->_pad_00[0xc]
0043fc82        edx_14:1.b = slot->_pad_00[0xd]
0043fc82        edx_14:2.b = slot->_pad_00[0xe]
0043fc82        edx_14:3.b = slot->_pad_00[0xf]
0043fc85        *(eax_10 + 0xc) = edx_14
0043fc88        goto label_43ffe2
0043fe46        case 2
0043fe46        int32_t var_24_4 = 0
0043fe4c        slot->state = 3
0043fe5b        float var_10_1 = fconvert.s(random_float_below(0.300000012f))
0043fe5f        int32_t var_2c_1 = 0
0043fe70        void* var_34_1 = &data_4a4e70
0043fe7a        float var_14_3 = fconvert.s(random_float_below(0.200000003f) + fconvert.t(0.100000001f))
0043fea6        slot->velocity.x = fconvert.s(random_signed_float_below(0.100000001f))
0043feac        slot->velocity.y = var_14_3
0043feb3        slot->velocity.z = var_10_1
0043feb6        uint32_t death_toss_direction = slot->death_toss_direction
0043febf        if (death_toss_direction == 1)
0043fec1        long double x87_r7_20 = fconvert.t(slot->velocity.x)
0043fec3        long double temp2_1 = fconvert.t(0f)
0043fec3        x87_r7_20 - temp2_1
0043fec9        long double x87_r7_21 = fconvert.t(slot->velocity.x)
0043fecb        death_toss_direction.w = (x87_r7_20 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp2_1) ? 1 : 0) << 0xa | (x87_r7_20 == temp2_1 ? 1 : 0) << 0xe | 0x3800
0043fed0        if ((death_toss_direction:1.b & 1) != 0)
0043fed2        x87_r7_21 = fneg(x87_r7_21)
0043fef0        slot->velocity.x = fconvert.s(x87_r7_21)
0043fed9        if (death_toss_direction == 2)
0043fedb        long double x87_r7_22 = fconvert.t(slot->velocity.x)
0043fedd        long double temp7_1 = fconvert.t(0f)
0043fedd        x87_r7_22 - temp7_1
0043fee3        long double x87_r7_23 = fconvert.t(slot->velocity.x)
0043fee5        death_toss_direction.w = (x87_r7_22 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_22, temp7_1) ? 1 : 0) << 0xa | (x87_r7_22 == temp7_1 ? 1 : 0) << 0xe | 0x3800
0043feea        if ((death_toss_direction:1.b & 1) != 0)
0043feec        x87_r7_23 = fneg(x87_r7_23)
0043fef0        slot->velocity.x = fconvert.s(fneg(x87_r7_23))
0043fef2        long double x87_r7_24 = fconvert.t(slot->velocity.x)
0043fef4        long double temp6_1 = fconvert.t(0f)
0043fef4        x87_r7_24 - temp6_1
0043fefa        death_toss_direction.w = (x87_r7_24 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_24, temp6_1) ? 1 : 0) << 0xa | (x87_r7_24 == temp6_1 ? 1 : 0) << 0xe
0043feff        int32_t var_14_4
0043feff        if ((death_toss_direction:1.b & 1) == 0)
0043ff0b        long double x87_r7_25 = fconvert.t(slot->velocity.x)
0043ff0d        long double temp9_1 = fconvert.t(0f)
0043ff0d        x87_r7_25 - temp9_1
0043ff13        var_14_4 = 0
0043ff17        death_toss_direction.w = (x87_r7_25 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_25, temp9_1) ? 1 : 0) << 0xa | (x87_r7_25 == temp9_1 ? 1 : 0) << 0xe
0043ff1c        if ((death_toss_direction:1.b & 0x40) == 0)
0043ff1e        var_14_4 = 1
0043ff01        var_14_4 = 0xffffffff
0043ff2a        struct Game* game = slot->game
0043ff30        slot->_pad_98[4] = 0
0043ff30        slot->_pad_98[5] = 0
0043ff30        slot->_pad_98[6] = 0
0043ff30        slot->_pad_98[7] = 0
0043ff3e        slot->velocity.x = fconvert.s(float.t(var_14_4) * fconvert.t(0.200000003f) + fconvert.t(slot->velocity.x))
0043ff43        long double x87_r7_30 = fconvert.t(game->subgame_rate) * fconvert.t(0.00833333377f)
0043ff49        slot->_pad_98[0xc] = 0
0043ff49        slot->_pad_98[0xd] = 0
0043ff49        slot->_pad_98[0xe] = 0
0043ff49        slot->_pad_98[0xf] = 0
0043ff4f        slot->_pad_98[8].d = fconvert.s(x87_r7_30)
0043ff5e        slot->_pad_98[0x10].d = fconvert.s(fconvert.t(game->subgame_rate) * fconvert.t(0.166666672f))
0043feff        goto label_43ff64
0043ff64        case 3
0043ff64        label_43ff64:
0043ff64        int16_t eax_23 = (slot->_pad_00[4].d).w
0043ff67        slot->state = 0
0043ff73        ecx_15 = data_4df904 + 0x5a8
0043ff7c        if ((eax_23:1.b & 2) == 0)
0043ff83        report_errorf("List remove")
0043ff91        kill_sprite(slot->sprite)
0043ff9c        return 
0043ff9f        if ((eax_23.b & 0x40) != 0)
0043ffa6        report_errorf("List remove NEXTBOD")
0043ffb4        kill_sprite(slot->sprite)
0043ffbf        return 
0043ffc0        void* eax_24
0043ffc0        eax_24.b = slot->_pad_00[0xc]
0043ffc0        eax_24:1.b = slot->_pad_00[0xd]
0043ffc0        eax_24:2.b = slot->_pad_00[0xe]
0043ffc0        eax_24:3.b = slot->_pad_00[0xf]
0043ffc5        if (eax_24 != 0)
0043ffc7        int32_t edx_20
0043ffc7        edx_20.b = slot->_pad_00[8]
0043ffc7        edx_20:1.b = slot->_pad_00[9]
0043ffc7        edx_20:2.b = slot->_pad_00[0xa]
0043ffc7        edx_20:3.b = slot->_pad_00[0xb]
0043ffca        *(eax_24 + 8) = edx_20
0043ffcd        void* eax_25
0043ffcd        eax_25.b = slot->_pad_00[8]
0043ffcd        eax_25:1.b = slot->_pad_00[9]
0043ffcd        eax_25:2.b = slot->_pad_00[0xa]
0043ffcd        eax_25:3.b = slot->_pad_00[0xb]
0043ffd2        if (eax_25 == 0)
0043ffdc        label_43ffdc:
0043ffdc        int32_t eax_26
0043ffdc        eax_26.b = slot->_pad_00[0xc]
0043ffdc        eax_26:1.b = slot->_pad_00[0xd]
0043ffdc        eax_26:2.b = slot->_pad_00[0xe]
0043ffdc        eax_26:3.b = slot->_pad_00[0xf]
0043ffdf        *(ecx_15 + 4) = eax_26.b
0043ffdf        *(ecx_15 + 5) = eax_26:1.b
0043ffdf        *(ecx_15 + 6) = eax_26:2.b
0043ffdf        *(ecx_15 + 7) = eax_26:3.b
0043ffdf        goto label_43ffe2
0043ffd4        int32_t edx_21
0043ffd4        edx_21.b = slot->_pad_00[0xc]
0043ffd4        edx_21:1.b = slot->_pad_00[0xd]
0043ffd4        edx_21:2.b = slot->_pad_00[0xe]
0043ffd4        edx_21:3.b = slot->_pad_00[0xf]
0043ffd7        *(eax_25 + 0xc) = edx_21
0043ffe2        label_43ffe2:
0043ffe2        int32_t edx_22
0043ffe2        edx_22.b = *(ecx_15 + 8)
0043ffe2        edx_22:1.b = *(ecx_15 + 9)
0043ffe2        edx_22:2.b = *(ecx_15 + 0xa)
0043ffe2        edx_22:3.b = *(ecx_15 + 0xb)
0043ffe5        slot->_pad_00[0xc] = edx_22.b
0043ffe5        slot->_pad_00[0xd] = edx_22:1.b
0043ffe5        slot->_pad_00[0xe] = edx_22:2.b
0043ffe5        slot->_pad_00[0xf] = edx_22:3.b
0043ffe8        *(ecx_15 + 8) = slot.b
0043ffe8        *(ecx_15 + 9) = slot:1.b
0043ffe8        *(ecx_15 + 0xa) = slot:2.b
0043ffe8        *(ecx_15 + 0xb) = slot:3.b
0043ffeb        int32_t eax_27
0043ffeb        eax_27.b = slot->_pad_00[4]
0043ffeb        eax_27:1.b = slot->_pad_00[5]
0043ffeb        eax_27:2.b = slot->_pad_00[6]
0043ffeb        eax_27:3.b = slot->_pad_00[7]
0043ffee        void* sprite_1 = slot->sprite
0043fff4        eax_27:1.b &= 0xfd
0043fff7        slot->_pad_00[4] = eax_27.b
0043fff7        slot->_pad_00[5] = eax_27:1.b
0043fff7        slot->_pad_00[6] = eax_27:2.b
0043fff7        slot->_pad_00[7] = eax_27:3.b
0043fffa        kill_sprite(sprite_1)
0043fd11        case 4
0043fd11        long double x87_r7_8 = fconvert.t(slot->lateral_phase_step) + fconvert.t(slot->lateral_phase)
0043fd17        long double temp0_1 = fconvert.t(6.28318548f)
0043fd17        x87_r7_8 - temp0_1
0043fd1d        slot->lateral_phase = fconvert.s(x87_r7_8)
0043fd1d        bool c1_1 = unimplemented  {fst dword [esi+0xb8], st0}
0043fd23        state.w = (x87_r7_8 < temp0_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_8, temp0_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp0_1 ? 1 : 0) << 0xe | 0x3800
0043fd28        if ((state:1.b & 0x41) == 0)
0043fd30        slot->lateral_phase = fconvert.s(x87_r7_8 - fconvert.t(6.28318548f))
0043fd55        slot->world_position.x = fconvert.s(sine(slot->lateral_phase) * fconvert.t(3f))
0043fd58        long double x87_r7_13 = fconvert.t(slot->world_position.z)
0043fd5b        long double temp5_1 = fconvert.t(slot->player->live_matrix.position.z)
0043fd5b        x87_r7_13 - temp5_1
0043fd6b        if ((((x87_r7_13 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_13, temp5_1) ? 1 : 0) << 0xa | (x87_r7_13 == temp5_1 ? 1 : 0) << 0xe):1.b & 1) != 0 && slot->passed_player == 0)
0043fd6d        slot->passed_player = 1
0043fd7d        float* edx_16 = slot->sprite + 0x48
0043fd80        *edx_16 = slot->world_position.x
0043fd85        edx_16[1] = slot->world_position.y
0043fd8b        edx_16[2] = slot->world_position.z
0043fd8e        struct Player* player_2 = slot->player
0043fd94        long double x87_r7_14 = fconvert.t(slot->world_position.z)
0043fd97        long double temp8_1 = fconvert.t(player_2->interaction_max_z)
0043fd97        x87_r7_14 - temp8_1
0043fd9d        float eax_15
0043fd9d        eax_15.w = (x87_r7_14 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp8_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp8_1 ? 1 : 0) << 0xe
0043fda2        if ((eax_15:1.b & 1) == 0)
0043fe23        long double x87_r7_15 = fconvert.t(player_2->nuke_effect_progress)
0043fe29        long double temp12_1 = fconvert.t(0f)
0043fe29        x87_r7_15 - temp12_1
0043fe2f        eax_15.w = (x87_r7_15 < temp12_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_15, temp12_1) ? 1 : 0) << 0xa | (x87_r7_15 == temp12_1 ? 1 : 0) << 0xe
0043fe34        if ((eax_15:1.b & 0x41) == 0)
0043fe3c        kill_slug_hazard(slot)
0043fe34        goto label_43fccd
0043fda4        int16_t eax_16 = (slot->_pad_00[4].d).w
0043fda7        slot->state = 0
0043fdb3        ecx_15 = data_4df904 + 0x5a8
0043fdbc        if ((eax_16:1.b & 2) == 0)
0043fdc3        report_errorf("List remove")
0043fdd1        kill_sprite(slot->sprite)
0043fddc        return 
0043fddf        if ((eax_16.b & 0x40) != 0)
0043fde6        report_errorf("List remove NEXTBOD")
0043fdf4        kill_sprite(slot->sprite)
0043fdff        return 
0043fe00        void* eax_17
0043fe00        eax_17.b = slot->_pad_00[0xc]
0043fe00        eax_17:1.b = slot->_pad_00[0xd]
0043fe00        eax_17:2.b = slot->_pad_00[0xe]
0043fe00        eax_17:3.b = slot->_pad_00[0xf]
0043fe05        if (eax_17 != 0)
0043fe07        int32_t edx_17
0043fe07        edx_17.b = slot->_pad_00[8]
0043fe07        edx_17:1.b = slot->_pad_00[9]
0043fe07        edx_17:2.b = slot->_pad_00[0xa]
0043fe07        edx_17:3.b = slot->_pad_00[0xb]
0043fe0a        *(eax_17 + 8) = edx_17
0043fe0d        void* eax_18
0043fe0d        eax_18.b = slot->_pad_00[8]
0043fe0d        eax_18:1.b = slot->_pad_00[9]
0043fe0d        eax_18:2.b = slot->_pad_00[0xa]
0043fe0d        eax_18:3.b = slot->_pad_00[0xb]
0043fe12        if (eax_18 == 0)
0043fe12        goto label_43ffdc
0043fe18        int32_t edx_18
0043fe18        edx_18.b = slot->_pad_00[0xc]
0043fe18        edx_18:1.b = slot->_pad_00[0xd]
0043fe18        edx_18:2.b = slot->_pad_00[0xe]
0043fe18        edx_18:3.b = slot->_pad_00[0xf]
0043fe1b        *(eax_18 + 0xc) = edx_18
0043fe1e        goto label_43ffe2
0043fd0a        return
