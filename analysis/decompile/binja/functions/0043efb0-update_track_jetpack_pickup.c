/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_track_jetpack_pickup @ 0x43efb0 */

0043efbc        if (jetpack->owner_game->subgame_pause_gate != 0)
0043efbc        return
0043efc2        enum TrackPickupState state = jetpack->state
0043efc7        if (state == TRACK_PICKUP_STATE_INACTIVE)
0043efc7        return
0043efce        struct BodList* ecx_1
0043efce        if (state == 1)
0043f048        long double x87_r7_1 = fconvert.t(jetpack->bod.position.z)
0043f04b        long double temp2_1 = fconvert.t(jetpack->owner->interaction_max_z)
0043f04b        x87_r7_1 - temp2_1
0043f056        if ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0043f05c        uint16_t list_flags_1 = (jetpack->bod.bod.list_flags).w
0043f05f        jetpack->state = TRACK_PICKUP_STATE_INACTIVE
0043f068        ecx_1 = &g_game_base->active_bod_list
0043f071        if ((list_flags_1:1.b & 2) == 0)
0043f078        report_errorf("List remove")
0043f083        kill_sprite(jetpack->sprite)
0043f08a        return
0043f08d        if ((list_flags_1.b & 0x40) != 0)
0043f094        report_errorf("List remove NEXTBOD")
0043f09f        kill_sprite(jetpack->sprite)
0043f0a6        return
0043f0a7        struct BodNode* list_next_1 = jetpack->bod.bod.list_next
0043f0ac        if (list_next_1 != 0)
0043f0b1        list_next_1->list_prev = jetpack->bod.bod.list_prev
0043f0b4        struct BodNode* list_prev_1 = jetpack->bod.bod.list_prev
0043f0b9        if (list_prev_1 == 0)
0043f0c6        label_43f0c6:
0043f0c6        ecx_1->first = jetpack->bod.bod.list_next
0043f0c6        goto label_43f0cc
0043f0be        list_prev_1->list_next = jetpack->bod.bod.list_next
0043f0cc        label_43f0cc:
0043f0cc        jetpack->bod.bod.list_next = ecx_1->free_top
0043f0cf        ecx_1->free_top = jetpack
0043f0d2        uint32_t list_flags_2 = jetpack->bod.bod.list_flags
0043f0d8        list_flags_2:1.b &= 0xfd
0043f0db        jetpack->bod.bod.list_flags = list_flags_2
0043f0de        kill_sprite(jetpack->sprite)
0043f0e5        return
0043efd1        if (state == 2)
0043efd7        uint16_t list_flags = (jetpack->bod.bod.list_flags).w
0043efda        jetpack->state = TRACK_PICKUP_STATE_INACTIVE
0043efe3        ecx_1 = &g_game_base->active_bod_list
0043efec        if ((list_flags:1.b & 2) == 0)
0043eff3        report_errorf("List remove")
0043effe        kill_sprite(jetpack->sprite)
0043f005        return
0043f008        if ((list_flags.b & 0x40) != 0)
0043f00f        report_errorf("List remove NEXTBOD")
0043f01a        kill_sprite(jetpack->sprite)
0043f021        return
0043f022        struct BodNode* list_next = jetpack->bod.bod.list_next
0043f027        if (list_next != 0)
0043f02c        list_next->list_prev = jetpack->bod.bod.list_prev
0043f02f        struct BodNode* list_prev = jetpack->bod.bod.list_prev
0043f034        if (list_prev == 0)
0043f034        goto label_43f0c6
0043f03d        list_prev->list_next = jetpack->bod.bod.list_next
0043f040        goto label_43f0cc
0043f0e9        long double x87_r7_3 = fconvert.t(jetpack->bob_phase_step) + fconvert.t(jetpack->bob_phase)
0043f0ec        long double temp4_1 = fconvert.t(1f)
0043f0ec        x87_r7_3 - temp4_1
0043f0f2        jetpack->bob_phase = fconvert.s(x87_r7_3)
0043f0f2        bool c1_1 = unknown  {fst dword [esi+0x6c], st0}
0043f0fa        if ((((x87_r7_3 < temp4_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_3, temp4_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp4_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
0043f102        jetpack->bob_phase = fconvert.s(x87_r7_3 - fconvert.t(1f))
0043f112        struct JetPack* jetpack_1 = jetpack
0043f12a        jetpack->sprite->position.y = fconvert.s(sine(fconvert.s(fconvert.t(jetpack->bob_phase) * fconvert.t(6.28318548f))) * fconvert.t(0.300000012f) + fconvert.t(jetpack->bod.position.y))
0043f12f        return
