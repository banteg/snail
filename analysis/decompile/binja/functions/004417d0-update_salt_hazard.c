/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_salt_hazard @ 0x4417d0 */

004417d6        struct SaltHazardSlot* slot_1 = slot
004417df        slot.b = slot_1->owner_template->__offset(0x9).b
004417e4        if (slot.b != 0)
004417e4        return 
004417ea        uint32_t active = slot_1->active
004417f1        if (active == 1)
004418a0        long double x87_r7_2 = fconvert.t(slot_1->__offset(0x9c).d) + fconvert.t(slot_1->__offset(0x98).d)
004418a6        slot_1->__offset(0x98).d = fconvert.s(x87_r7_2)
004418ac        long double temp1_1 = fconvert.t(1f)
004418ac        x87_r7_2 - temp1_1
004418b2        int32_t eax_1
004418b2        eax_1.w = (x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe
004418b7        if ((eax_1:1.b & 0x41) == 0)
004418b9        slot_1->active = 2
004418ca        return 
004418d7        slot_1->world_position.x = fconvert.s(fconvert.t(slot_1->velocity_x) + fconvert.t(slot_1->world_position.x))
004418e2        slot_1->world_position.y = fconvert.s(fconvert.t(slot_1->velocity_y) + fconvert.t(slot_1->world_position.y))
004418ee        slot_1->world_position.z = fconvert.s(fconvert.t(slot_1->armed_substate) + fconvert.t(slot_1->world_position.z))
004418f1        long double x87_r7_9 = fconvert.t(slot_1->world_position.y)
004418f4        long double temp3_1 = fconvert.t(0f)
004418f4        x87_r7_9 - temp3_1
004418fa        eax_1.w = (x87_r7_9 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp3_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp3_1 ? 1 : 0) << 0xe
004418ff        if ((eax_1:1.b & 1) != 0)
00441ac3        deactivate_salt_hazard(slot_1)
0044190b        long double x87_r7_10 = fconvert.t(slot_1->world_position.z)
0044190e        long double temp4_1 = fconvert.t(slot_1->owner_template->__offset(0x3be0e4).d)
0044190e        x87_r7_10 - temp4_1
00441914        struct PathTemplate* eax_8
00441914        eax_8.w = (x87_r7_10 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp4_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp4_1 ? 1 : 0) << 0xe
00441919        if ((eax_8:1.b & 1) != 0)
00441ac3        deactivate_salt_hazard(slot_1)
0044192c        struct TrackRowCell* eax_9 = get_track_grid_cell_at_world_position(data_4df904 + 0x74618, &slot_1->world_position)
00441945        char* ebx_1 = get_track_runtime_cell_at_world_z(data_4df904 + 0x74618, &slot_1->world_position.x)
00441947        char* eax_10
00441947        eax_10.b = eax_9->tile_id
0044194c        if (eax_10.b != 0xe)
00441965        label_441965:
00441965        char eax_12
00441965        if ((*ebx_1 & 0x40) != 0)
00441977        int32_t eax_11 = *(ebx_1 + 0xa4)
0044199a        float var_38_1 = fconvert.s(fconvert.t(slot_1->velocity_x) * fconvert.t(1.04999995f))
004419b0        float var_34_1 = fconvert.s(fconvert.t(slot_1->velocity_y) * fconvert.t(1.04999995f))
004419c3        float var_30_1 = fconvert.s(fconvert.t(slot_1->armed_substate) * fconvert.t(1.04999995f))
004419fd        eax_12 = is_point_inside_track_attachment(*(eax_11 + 0x38), fconvert.s(fconvert.t(slot_1->velocity_x) + fconvert.t(slot_1->world_position.x)), fconvert.s(fconvert.t(slot_1->velocity_y) + fconvert.t(slot_1->world_position.y)), fconvert.s(fconvert.t(slot_1->armed_substate) + fconvert.t(slot_1->world_position.z)), eax_11)
00441a04        if ((*ebx_1 & 0x40) != 0 && eax_12 != 0)
00441a06        char* var_2c_4 = "lazer path kill\n"
00441ac3        deactivate_salt_hazard(slot_1)
00441a13        if ((*ebx_1 & 0x80) != 0)
00441a25        int32_t ebx_2 = *(ebx_1 + 0xa8)
00441a48        float var_38_2 = fconvert.s(fconvert.t(slot_1->velocity_x) * fconvert.t(1.04999995f))
00441a5e        float var_34_2 = fconvert.s(fconvert.t(slot_1->velocity_y) * fconvert.t(1.04999995f))
00441a73        float var_30_2 = fconvert.s(fconvert.t(slot_1->armed_substate) * fconvert.t(1.04999995f))
00441aab        char eax_15 = is_point_inside_track_attachment(*(ebx_2 + 0x38), fconvert.s(fconvert.t(slot_1->velocity_x) + fconvert.t(slot_1->world_position.x)), fconvert.s(fconvert.t(slot_1->velocity_y) + fconvert.t(slot_1->world_position.y)), fconvert.s(fconvert.t(slot_1->armed_substate) + fconvert.t(slot_1->world_position.z)), ebx_2)
00441ab2        if (eax_15 != 0)
00441ab4        char* var_2c_6 = "lazer path2 kill\n"
00441ac3        deactivate_salt_hazard(slot_1)
0044194e        long double x87_r7_11 = fconvert.t(slot_1->world_position.y)
00441951        long double temp5_1 = fconvert.t(7f)
00441951        x87_r7_11 - temp5_1
00441957        eax_10.w = (x87_r7_11 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_11, temp5_1) ? 1 : 0) << 0xa | (x87_r7_11 == temp5_1 ? 1 : 0) << 0xe
0044195c        if ((eax_10:1.b & 1) == 0)
0044195c        goto label_441965
00441ac3        deactivate_salt_hazard(slot_1)
004417f8        if (active == 2)
00441804        int16_t eax_3 = (slot_1->_pad_00[4].d).w
00441807        void* ecx_1 = data_4df904 + 0x5a8
00441810        if ((eax_3:1.b & 2) == 0)
00441817        report_errorf("List remove")
0044181f        slot_1->active = 0
00441830        return 
00441833        if ((eax_3.b & 0x40) != 0)
0044183a        report_errorf("List remove NEXTBOD")
00441842        slot_1->active = 0
00441853        return 
00441854        void* eax_4
00441854        eax_4.b = slot_1->_pad_00[0xc]
00441854        eax_4:1.b = slot_1->_pad_00[0xd]
00441854        eax_4:2.b = slot_1->_pad_00[0xe]
00441854        eax_4:3.b = slot_1->_pad_00[0xf]
00441859        if (eax_4 != 0)
0044185b        int32_t edx
0044185b        edx.b = slot_1->_pad_00[8]
0044185b        edx:1.b = slot_1->_pad_00[9]
0044185b        edx:2.b = slot_1->_pad_00[0xa]
0044185b        edx:3.b = slot_1->_pad_00[0xb]
0044185e        *(eax_4 + 8) = edx
00441861        void* eax_5
00441861        eax_5.b = slot_1->_pad_00[8]
00441861        eax_5:1.b = slot_1->_pad_00[9]
00441861        eax_5:2.b = slot_1->_pad_00[0xa]
00441861        eax_5:3.b = slot_1->_pad_00[0xb]
00441866        if (eax_5 == 0)
00441870        int32_t eax_6
00441870        eax_6.b = slot_1->_pad_00[0xc]
00441870        eax_6:1.b = slot_1->_pad_00[0xd]
00441870        eax_6:2.b = slot_1->_pad_00[0xe]
00441870        eax_6:3.b = slot_1->_pad_00[0xf]
00441873        *(ecx_1 + 4) = eax_6.b
00441873        *(ecx_1 + 5) = eax_6:1.b
00441873        *(ecx_1 + 6) = eax_6:2.b
00441873        *(ecx_1 + 7) = eax_6:3.b
00441868        int32_t edx_1
00441868        edx_1.b = slot_1->_pad_00[0xc]
00441868        edx_1:1.b = slot_1->_pad_00[0xd]
00441868        edx_1:2.b = slot_1->_pad_00[0xe]
00441868        edx_1:3.b = slot_1->_pad_00[0xf]
0044186b        *(eax_5 + 0xc) = edx_1
00441876        int32_t edx_2
00441876        edx_2.b = *(ecx_1 + 8)
00441876        edx_2:1.b = *(ecx_1 + 9)
00441876        edx_2:2.b = *(ecx_1 + 0xa)
00441876        edx_2:3.b = *(ecx_1 + 0xb)
00441879        slot_1->_pad_00[0xc] = edx_2.b
00441879        slot_1->_pad_00[0xd] = edx_2:1.b
00441879        slot_1->_pad_00[0xe] = edx_2:2.b
00441879        slot_1->_pad_00[0xf] = edx_2:3.b
0044187c        *(ecx_1 + 8) = slot_1.b
0044187c        *(ecx_1 + 9) = slot_1:1.b
0044187c        *(ecx_1 + 0xa) = slot_1:2.b
0044187c        *(ecx_1 + 0xb) = slot_1:3.b
0044187f        int32_t eax_7
0044187f        eax_7.b = slot_1->_pad_00[4]
0044187f        eax_7:1.b = slot_1->_pad_00[5]
0044187f        eax_7:2.b = slot_1->_pad_00[6]
0044187f        eax_7:3.b = slot_1->_pad_00[7]
00441882        slot_1->active = 0
0044188c        eax_7:1.b &= 0xfd
0044188f        slot_1->_pad_00[4] = eax_7.b
0044188f        slot_1->_pad_00[5] = eax_7:1.b
0044188f        slot_1->_pad_00[6] = eax_7:2.b
0044188f        slot_1->_pad_00[7] = eax_7:3.b
00441acf        return
