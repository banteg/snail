/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_ring_or_special_effect_parent @ 0x43e830 */

0043e839        struct SubgameRuntime* rate_source = ring->rate_source
0043e844        if (rate_source->subgame_pause_gate != 0)
0043e844        return
0043e850        int32_t edi_2 = ring->star_shower_counter + 1
0043e853        ring->star_shower_counter = edi_2
0043e85c        if (edi_2 == 3)
0043e860        ring->star_shower_counter = 0
0043e879        switch (ring->state)
0043e880        case 1
0043e880        int16_t eax
0043e880        eax.b = ring->oscillate_x
0043e888        if (eax.b != 0)
0043e890        long double x87_r7_2 = fconvert.t(ring->active_phase_step) + fconvert.t(ring->active_phase)
0043e896        long double temp0_1 = fconvert.t(6.28318548f)
0043e896        x87_r7_2 - temp0_1
0043e89c        ring->active_phase = fconvert.s(x87_r7_2)
0043e89c        bool c1_1 = unknown  {fst dword [esi+0x1e0], st0}
0043e8a7        if ((((x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) != 0)
0043e8b7        long double temp4_1 = fconvert.t(0f)
0043e8b7        x87_r7_2 - temp4_1
0043e8c2        if ((((x87_r7_2 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp4_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp4_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
0043e8ca        ring->active_phase = fconvert.s(x87_r7_2 + fconvert.t(6.28318548f))
0043e8af        ring->active_phase = fconvert.s(x87_r7_2 - fconvert.t(6.28318548f))
0043e8e9        ring->world_position.x = fconvert.s(sine(ring->active_phase) * fconvert.t(3f))
0043e8f2        int32_t i_10 = 0xa
0043e8f7        struct SubRingStar (* particle)[0xa] = &ring->particles
0043e904        int32_t i
0043e8fb        update_ring_or_special_effect_particle(particle)
0043e900        particle = &(*particle)[1]
0043e903        i = i_10
0043e903        i_10 -= 1
0043e904        do while (i != 1)
0043e906        struct Player* owner_player = ring->owner_player
0043e90c        long double x87_r7_8 = fconvert.t(ring->world_position.z)
0043e90f        long double temp7_1 = fconvert.t(owner_player->interaction_max_z)
0043e90f        x87_r7_8 - temp7_1
0043e91a        if ((((x87_r7_8 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp7_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp7_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0043e920        uint16_t list_flags = (ring->bod.list_flags).w
0043e923        ring->state = 0
0043e933        void* ecx_5 = &g_game_base[0x5a8]
0043e93c        if ((list_flags:1.b & 2) == 0)
0043e943        report_errorf("List remove")
0043e94f        if ((list_flags.b & 0x40) == 0)
0043e960        struct BodNode* list_next = ring->bod.list_next
0043e965        if (list_next != 0)
0043e96a        list_next->list_prev = ring->bod.list_prev
0043e96d        struct BodNode* list_prev = ring->bod.list_prev
0043e972        if (list_prev == 0)
0043e97f        *(ecx_5 + 4) = ring->bod.list_next
0043e977        list_prev->list_next = ring->bod.list_next
0043e985        ring->bod.list_next = *(ecx_5 + 8)
0043e988        *(ecx_5 + 8) = ring
0043e98b        uint32_t list_flags_1 = ring->bod.list_flags
0043e98e        list_flags_1:1.b &= 0xfd
0043e991        ring->bod.list_flags = list_flags_1
0043e956        report_errorf("List remove NEXTBOD")
0043e994        struct SubRingStar (* esi_1)[0xa] = &ring->particles
0043e996        int32_t i_13 = 0xa
0043e9a6        int32_t i_1
0043e99d        kill_sprite((esi_1 - 0x90)->particles[0].sprite)
0043e9a2        esi_1 = &(*esi_1)[1]
0043e9a5        i_1 = i_13
0043e9a5        i_13 -= 1
0043e9a6        do while (i_1 != 1)
0043e9af        return
0043e9be        if (owner_player->lives s< ring->owner_lives_snapshot)
0043e9c4        ring->state = 4
0043e9d6        case 2
0043e9d6        ring->state = 3
0043e9e0        ring->transition_progress = 0f
0043e9ef        ring->transition_step = fconvert.s(fconvert.t(rate_source->subgame_rate) * fconvert.t(0.0694444478f))
0043e9fb        label_43e9fb:
0043e9fb        int32_t i_11 = 0xa
0043ea00        struct SubRingStar (* particle_1)[0xa] = &ring->particles
0043ea0d        int32_t i_2
0043ea04        update_ring_or_special_effect_particle(particle_1)
0043ea09        particle_1 = &(*particle_1)[1]
0043ea0c        i_2 = i_11
0043ea0c        i_11 -= 1
0043ea0d        do while (i_2 != 1)
0043ea15        long double x87_r7_12 = fconvert.t(ring->transition_step) + fconvert.t(ring->transition_progress)
0043ea1b        ring->transition_progress = fconvert.s(x87_r7_12)
0043ea21        long double temp5 = fconvert.t(1f)
0043ea21        x87_r7_12 - temp5
0043ea2c        if ((((x87_r7_12 < temp5 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp5) ? 1 : 0) << 0xa | (x87_r7_12 == temp5 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0043eac8        int32_t i_9 = 0xa
0043eacd        struct Vec3* eax_10 = &ring->owner_player->cached_camera_target_world
0043eae7        float* ecx_13 = &ring->particles[0].radius
0043eb2d        ring->world_position.x = fconvert.s((fconvert.t(eax_10->x) - fconvert.t(ring->world_position.x)) * fconvert.t(0.939999998f) + fconvert.t(ring->world_position.x))
0043eb36        ring->world_position.y = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(eax_10->y) - fconvert.t(ring->world_position.y))) * fconvert.t(0.939999998f))) + fconvert.t(ring->world_position.y))
0043eb40        ring->world_position.z = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(eax_10->z) + fconvert.t(0.200000003f))) - fconvert.t(ring->world_position.z))) * fconvert.t(0.939999998f))) + fconvert.t(ring->world_position.z))
0043eb67        int32_t i_3
0043eb45        long double x87_r7_22 = fconvert.t((ecx_13 - 0xac)->particles[0].radius) * fconvert.t(0.939999998f)
0043eb4d        struct Vec3* esi_3 = &ecx_13[-5]
0043eb50        ecx_13 = &ecx_13[8]
0043eb53        i_3 = i_9
0043eb53        i_9 -= 1
0043eb54        (ecx_13 - 0xac)->owner_lives_snapshot = fconvert.s(x87_r7_22)
0043eb59        esi_3->x = ring->world_position.x
0043eb5e        esi_3->y = ring->world_position.y
0043eb64        esi_3->z = ring->world_position.z
0043eb67        do while (i_3 != 1)
0043eb70        return
0043ea32        uint16_t list_flags_2 = (ring->bod.list_flags).w
0043ea35        ring->state = 0
0043ea45        void* ecx_10 = &g_game_base[0x5a8]
0043ea4e        if ((list_flags_2:1.b & 2) == 0)
0043ea55        report_errorf("List remove")
0043ea61        if ((list_flags_2.b & 0x40) == 0)
0043ea72        struct BodNode* list_next_1 = ring->bod.list_next
0043ea77        if (list_next_1 != 0)
0043ea7c        list_next_1->list_prev = ring->bod.list_prev
0043ea7f        struct BodNode* list_prev_1 = ring->bod.list_prev
0043ea84        if (list_prev_1 == 0)
0043ea91        *(ecx_10 + 4) = ring->bod.list_next
0043ea89        list_prev_1->list_next = ring->bod.list_next
0043ea97        ring->bod.list_next = *(ecx_10 + 8)
0043ea9a        *(ecx_10 + 8) = ring
0043ea9d        uint32_t list_flags_3 = ring->bod.list_flags
0043eaa0        list_flags_3:1.b &= 0xfd
0043eaa3        ring->bod.list_flags = list_flags_3
0043ea68        report_errorf("List remove NEXTBOD")
0043eaa6        struct SubRingStar (* esi_2)[0xa] = &ring->particles
0043eaa8        int32_t i_14 = 0xa
0043eab8        int32_t i_4
0043eaaf        kill_sprite((esi_2 - 0x90)->particles[0].sprite)
0043eab4        esi_2 = &(*esi_2)[1]
0043eab7        i_4 = i_14
0043eab7        i_14 -= 1
0043eab8        do while (i_4 != 1)
0043e879        case 3
0043e879        goto label_43e9fb
0043eb71        case 4
0043eb71        ring->state = 5
0043eb7b        ring->transition_progress = 0f
0043eb8a        ring->transition_step = fconvert.s(fconvert.t(rate_source->subgame_rate) * fconvert.t(0.0694444478f))
0043eb96        label_43eb96:
0043eb96        int32_t i_12 = 0xa
0043eb9b        struct SubRingStar (* particle_2)[0xa] = &ring->particles
0043eba8        int32_t i_5
0043eb9f        update_ring_or_special_effect_particle(particle_2)
0043eba4        particle_2 = &(*particle_2)[1]
0043eba7        i_5 = i_12
0043eba7        i_12 -= 1
0043eba8        do while (i_5 != 1)
0043ebb0        long double x87_r7_26 = fconvert.t(ring->transition_step) + fconvert.t(ring->transition_progress)
0043ebb6        ring->transition_progress = fconvert.s(x87_r7_26)
0043ebbc        long double temp6_1 = fconvert.t(1f)
0043ebbc        x87_r7_26 - temp6_1
0043ebc7        if ((((x87_r7_26 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_26, temp6_1) ? 1 : 0) << 0xa | (x87_r7_26 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043ebcd        uint16_t list_flags_4 = (ring->bod.list_flags).w
0043ebd0        ring->state = 0
0043ebe3        void* ecx_15 = &g_game_base[0x5a8]
0043ebe9        if ((list_flags_4:1.b & 2) == 0)
0043ebf0        report_errorf("List remove")
0043ebfc        if ((list_flags_4.b & 0x40) == 0)
0043ec0d        struct BodNode* list_next_2 = ring->bod.list_next
0043ec12        if (list_next_2 != 0)
0043ec17        list_next_2->list_prev = ring->bod.list_prev
0043ec1a        struct BodNode* list_prev_2 = ring->bod.list_prev
0043ec1f        if (list_prev_2 == 0)
0043ec2c        *(ecx_15 + 4) = ring->bod.list_next
0043ec24        list_prev_2->list_next = ring->bod.list_next
0043ec32        ring->bod.list_next = *(ecx_15 + 8)
0043ec35        *(ecx_15 + 8) = ring
0043ec38        uint32_t list_flags_5 = ring->bod.list_flags
0043ec3b        list_flags_5:1.b &= 0xfd
0043ec3e        ring->bod.list_flags = list_flags_5
0043ec03        report_errorf("List remove NEXTBOD")
0043ec41        struct SubRingStar (* esi_4)[0xa] = &ring->particles
0043ec43        int32_t i_15 = 0xa
0043ec53        int32_t i_6
0043ec4a        kill_sprite((esi_4 - 0x90)->particles[0].sprite)
0043ec4f        esi_4 = &(*esi_4)[1]
0043ec52        i_6 = i_15
0043ec52        i_15 -= 1
0043ec53        do while (i_6 != 1)
0043ec5c        return
0043ec60        float* eax_15 = &ring->particles[0].radius
0043ec66        int32_t i_8 = 0xa
0043ec8f        int32_t i_7
0043ec6d        long double x87_r7_28 = fconvert.t((eax_15 - 0xac)->particles[0].radius) * fconvert.t(1.10000002f)
0043ec75        struct Vec3* esi_5 = &eax_15[-5]
0043ec78        eax_15 = &eax_15[8]
0043ec7b        i_7 = i_8
0043ec7b        i_8 -= 1
0043ec7c        (eax_15 - 0xac)->owner_lives_snapshot = fconvert.s(x87_r7_28)
0043ec81        esi_5->x = ring->world_position.x
0043ec86        esi_5->y = ring->world_position.y
0043ec8c        esi_5->z = ring->world_position.z
0043ec8f        do while (i_7 != 1)
0043e879        case 5
0043e879        goto label_43eb96
0043ec98        return
