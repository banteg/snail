/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_sub_lazer_projectile @ 0x4417d0 */

004417e4        if (slot->owner_game->subgame_pause_gate != 0)
004417e4        return
004417ea        int32_t state = slot->state
004417f1        if (state == 1)
004418a0        long double x87_r7_2 = fconvert.t(slot->sprite_bob_phase_step) + fconvert.t(slot->sprite_bob_phase)
004418a6        slot->sprite_bob_phase = fconvert.s(x87_r7_2)
004418ac        long double temp1_1 = fconvert.t(1f)
004418ac        x87_r7_2 - temp1_1
004418b7        if ((((x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
004418b9        slot->state = 2
004418ca        return
004418d7        slot->position.x = fconvert.s(fconvert.t(slot->velocity.x) + fconvert.t(slot->position.x))
004418e2        slot->position.y = fconvert.s(fconvert.t(slot->velocity.y) + fconvert.t(slot->position.y))
004418ee        slot->position.z = fconvert.s(fconvert.t(slot->velocity.z) + fconvert.t(slot->position.z))
004418f1        long double x87_r7_9 = fconvert.t(slot->position.y)
004418f4        long double temp3_1 = fconvert.t(0f)
004418f4        x87_r7_9 - temp3_1
004418ff        if ((((x87_r7_9 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp3_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp3_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00441ac3        deactivate_sub_lazer_projectile(slot)
0044190b        long double x87_r7_10 = fconvert.t(slot->position.z)
0044190e        long double temp4_1 = fconvert.t(slot->owner_game->player.interaction_max_z)
0044190e        x87_r7_10 - temp4_1
00441919        if ((((x87_r7_10 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp4_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp4_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00441ac3        deactivate_sub_lazer_projectile(slot)
0044192c        struct TrackRowCell* eax_7 = get_track_grid_cell_at_world_position(&g_game_base->subgame, &slot->position.x)
00441940        struct SubRow* eax_8 = get_track_runtime_cell_at_world_z(&g_game_base->subgame, &slot->position.x)
00441947        int16_t eax_9
00441947        eax_9.b = eax_7->tile_id
0044194c        long double x87_r7_11
0044194c        long double temp5_1
0044194c        if (eax_9.b == 0xe)
0044194e        x87_r7_11 = fconvert.t(slot->position.y)
00441951        temp5_1 = fconvert.t(7f)
00441951        x87_r7_11 - temp5_1
0044195c        if (eax_9.b == 0xe && (((x87_r7_11 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_11, temp5_1) ? 1 : 0) << 0xa | (x87_r7_11 == temp5_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00441ac3        deactivate_sub_lazer_projectile(slot)
00441965        bool eax_10
00441965        if ((eax_8->flags.b & 0x40) != 0)
00441977        struct TrackRowCell* primary_attachment_cell = eax_8->primary_attachment_cell
004419b0        float var_34_1 = fconvert.s(fconvert.t(slot->velocity.y) * fconvert.t(1.04999995f))
004419c3        float var_30_1 = fconvert.s(fconvert.t(slot->velocity.z) * fconvert.t(1.04999995f))
004419ec        float var_40_1 = fconvert.s(fconvert.t(slot->velocity.y) + fconvert.t(slot->position.y))
004419f7        float var_3c_1 = fconvert.s(fconvert.t(slot->velocity.z) + fconvert.t(slot->position.z))
004419fd        eax_10 = is_point_inside_track_attachment(primary_attachment_cell->attachment_template_record, fconvert.s(fconvert.t(slot->velocity.x) + fconvert.t(slot->position.x)), fconvert.s(fconvert.t(slot->velocity.x) * fconvert.t(1.04999995f)), primary_attachment_cell)
00441a04        char* var_2c_4
00441a04        if ((eax_8->flags.b & 0x40) != 0 && eax_10 != 0)
00441a06        var_2c_4 = "lazer path kill\n"
00441ac3        deactivate_sub_lazer_projectile(slot)
00441a13        if ((eax_8->flags.b & 0x80) != 0)
00441a25        struct TrackRowCell* secondary_attachment_cell = eax_8->secondary_attachment_cell
00441a5e        float var_34_2 = fconvert.s(fconvert.t(slot->velocity.y) * fconvert.t(1.04999995f))
00441a73        float var_30_2 = fconvert.s(fconvert.t(slot->velocity.z) * fconvert.t(1.04999995f))
00441a9a        float var_40_2 = fconvert.s(fconvert.t(slot->velocity.y) + fconvert.t(slot->position.y))
00441aa8        float var_3c_2 = fconvert.s(fconvert.t(slot->velocity.z) + fconvert.t(slot->position.z))
00441ab2        if (is_point_inside_track_attachment(secondary_attachment_cell->attachment_template_record, fconvert.s(fconvert.t(slot->velocity.x) + fconvert.t(slot->position.x)), fconvert.s(fconvert.t(slot->velocity.x) * fconvert.t(1.04999995f)), secondary_attachment_cell) != 0)
00441ab4        var_2c_4 = "lazer path2 kill\n"
00441ac3        deactivate_sub_lazer_projectile(slot)
004417f8        if (state == 2)
00441804        uint16_t list_flags = (slot->bod.list_flags).w
00441807        struct FrameBodList* ecx_2 = &g_game_base->active_bod_list
00441810        if ((list_flags:1.b & 2) == 0)
00441817        report_errorf("List remove")
0044181f        slot->state = 0
00441830        return
00441833        if ((list_flags.b & 0x40) != 0)
0044183a        report_errorf("List remove NEXTBOD")
00441842        slot->state = 0
00441853        return
00441854        struct BodNode* list_next = slot->bod.list_next
00441859        if (list_next != 0)
0044185e        list_next->list_prev = slot->bod.list_prev
00441861        struct BodNode* list_prev = slot->bod.list_prev
00441866        if (list_prev == 0)
00441873        ecx_2->first = slot->bod.list_next
0044186b        list_prev->list_next = slot->bod.list_next
00441879        slot->bod.list_next = ecx_2->free_top
0044187c        ecx_2->free_top = slot
0044187f        uint32_t list_flags_1 = slot->bod.list_flags
00441882        slot->state = 0
0044188c        list_flags_1:1.b &= 0xfd
0044188f        slot->bod.list_flags = list_flags_1
00441acf        return
