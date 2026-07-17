/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_track_health_pickup @ 0x43ecc0 */

0043eccc        if (pickup->owner_game->subgame_pause_gate != 0)
0043eccc        return
0043ecd2        enum TrackPickupState state = pickup->state
0043ecd7        if (state == TRACK_PICKUP_STATE_INACTIVE)
0043ecd7        return
0043ecde        struct BodList* ecx_1
0043ecde        if (state == 1)
0043ed58        long double x87_r7_1 = fconvert.t(pickup->bod.position.z)
0043ed5b        long double temp2_1 = fconvert.t(pickup->owner->interaction_max_z)
0043ed5b        x87_r7_1 - temp2_1
0043ed66        if ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0043ed6c        uint16_t list_flags_1 = (pickup->bod.bod.list_flags).w
0043ed6f        pickup->state = TRACK_PICKUP_STATE_INACTIVE
0043ed78        ecx_1 = &g_game_base->active_bod_list
0043ed81        if ((list_flags_1:1.b & 2) == 0)
0043ed88        report_errorf("List remove")
0043ed93        kill_sprite(pickup->sprite)
0043ed9a        return
0043ed9d        if ((list_flags_1.b & 0x40) != 0)
0043eda4        report_errorf("List remove NEXTBOD")
0043edaf        kill_sprite(pickup->sprite)
0043edb6        return
0043edb7        struct BodNode* list_next_1 = pickup->bod.bod.list_next
0043edbc        if (list_next_1 != 0)
0043edc1        list_next_1->list_prev = pickup->bod.bod.list_prev
0043edc4        struct BodNode* list_prev_1 = pickup->bod.bod.list_prev
0043edc9        if (list_prev_1 == 0)
0043edd6        label_43edd6:
0043edd6        ecx_1->first = pickup->bod.bod.list_next
0043edd6        goto label_43eddc
0043edce        list_prev_1->list_next = pickup->bod.bod.list_next
0043eddc        label_43eddc:
0043eddc        pickup->bod.bod.list_next = ecx_1->free_top
0043eddf        ecx_1->free_top = pickup
0043ede2        uint32_t list_flags_2 = pickup->bod.bod.list_flags
0043ede8        list_flags_2:1.b &= 0xfd
0043edeb        pickup->bod.bod.list_flags = list_flags_2
0043edee        kill_sprite(pickup->sprite)
0043edf5        return
0043ece1        if (state == 2)
0043ece7        uint16_t list_flags = (pickup->bod.bod.list_flags).w
0043ecea        pickup->state = TRACK_PICKUP_STATE_INACTIVE
0043ecf3        ecx_1 = &g_game_base->active_bod_list
0043ecfc        if ((list_flags:1.b & 2) == 0)
0043ed03        report_errorf("List remove")
0043ed0e        kill_sprite(pickup->sprite)
0043ed15        return
0043ed18        if ((list_flags.b & 0x40) != 0)
0043ed1f        report_errorf("List remove NEXTBOD")
0043ed2a        kill_sprite(pickup->sprite)
0043ed31        return
0043ed32        struct BodNode* list_next = pickup->bod.bod.list_next
0043ed37        if (list_next != 0)
0043ed3c        list_next->list_prev = pickup->bod.bod.list_prev
0043ed3f        struct BodNode* list_prev = pickup->bod.bod.list_prev
0043ed44        if (list_prev == 0)
0043ed44        goto label_43edd6
0043ed4d        list_prev->list_next = pickup->bod.bod.list_next
0043ed50        goto label_43eddc
0043edf9        long double x87_r7_3 = fconvert.t(pickup->bob_phase_step) + fconvert.t(pickup->bob_phase)
0043edfc        long double temp4_1 = fconvert.t(1f)
0043edfc        x87_r7_3 - temp4_1
0043ee02        pickup->bob_phase = fconvert.s(x87_r7_3)
0043ee02        bool c1_1 = unknown  {fst dword [esi+0x6c], st0}
0043ee0a        if ((((x87_r7_3 < temp4_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_3, temp4_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp4_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
0043ee12        pickup->bob_phase = fconvert.s(x87_r7_3 - fconvert.t(1f))
0043ee22        struct SubHealth* pickup_1 = pickup
0043ee40        pickup->sprite->position.y = fconvert.s((sine(fconvert.s(fconvert.t(pickup->bob_phase) * fconvert.t(6.28318548f))) + fconvert.t(1f)) * fconvert.t(0.300000012f) + fconvert.t(pickup->bod.position.y))
0043ee45        return
