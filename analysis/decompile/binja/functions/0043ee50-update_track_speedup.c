/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_track_speedup @ 0x43ee50 */

0043ee5f        if (speedup->owner_game->subgame_pause_gate != 0)
0043ee5f        return
0043ee65        enum TrackPickupState state = speedup->state
0043ee6d        if (state == TRACK_PICKUP_STATE_INACTIVE)
0043ee6d        return
0043ee74        struct BodList* ecx_1
0043ee74        if (state == 1)
0043eefa        long double x87_r7_1 = fconvert.t(speedup->body.transform.position.z)
0043eefd        long double temp2_1 = fconvert.t(speedup->owner->interaction_max_z)
0043eefd        x87_r7_1 - temp2_1
0043ef08        if ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0043ef0e        uint16_t list_flags_1 = (speedup->body.bod.bod.list_flags).w
0043ef11        speedup->state = TRACK_PICKUP_STATE_INACTIVE
0043ef1d        ecx_1 = &g_game_base->active_bod_list
0043ef26        if ((list_flags_1:1.b & 2) == 0)
0043ef2d        report_errorf("List remove")
0043ef3b        kill_sprite(speedup->sprite)
0043ef42        return
0043ef45        if ((list_flags_1.b & 0x40) != 0)
0043ef4c        report_errorf("List remove NEXTBOD")
0043ef5a        kill_sprite(speedup->sprite)
0043ef61        return
0043ef62        struct BodNode* list_next_1 = speedup->body.bod.bod.list_next
0043ef67        if (list_next_1 != 0)
0043ef6c        list_next_1->list_prev = speedup->body.bod.bod.list_prev
0043ef6f        struct BodNode* list_prev_1 = speedup->body.bod.bod.list_prev
0043ef74        if (list_prev_1 == 0)
0043ef81        label_43ef81:
0043ef81        ecx_1->first = speedup->body.bod.bod.list_next
0043ef81        goto label_43ef87
0043ef79        list_prev_1->list_next = speedup->body.bod.bod.list_next
0043ef87        label_43ef87:
0043ef87        speedup->body.bod.bod.list_next = ecx_1->free_top
0043ef8a        ecx_1->free_top = speedup
0043ef8d        uint32_t list_flags_2 = speedup->body.bod.bod.list_flags
0043ef96        list_flags_2:1.b &= 0xfd
0043ef99        speedup->body.bod.bod.list_flags = list_flags_2
0043ef9c        kill_sprite(speedup->sprite)
0043ee77        if (state == 2)
0043ee7d        uint16_t list_flags = (speedup->body.bod.bod.list_flags).w
0043ee80        speedup->state = TRACK_PICKUP_STATE_INACTIVE
0043ee8c        ecx_1 = &g_game_base->active_bod_list
0043ee95        if ((list_flags:1.b & 2) == 0)
0043ee9c        report_errorf("List remove")
0043eeaa        kill_sprite(speedup->sprite)
0043eeb1        return
0043eeb4        if ((list_flags.b & 0x40) != 0)
0043eebb        report_errorf("List remove NEXTBOD")
0043eec9        kill_sprite(speedup->sprite)
0043eed0        return
0043eed1        struct BodNode* list_next = speedup->body.bod.bod.list_next
0043eed6        if (list_next != 0)
0043eedb        list_next->list_prev = speedup->body.bod.bod.list_prev
0043eede        struct BodNode* list_prev = speedup->body.bod.bod.list_prev
0043eee3        if (list_prev == 0)
0043eee3        goto label_43ef81
0043eeec        list_prev->list_next = speedup->body.bod.bod.list_next
0043eeef        goto label_43ef87
0043efa3        return
