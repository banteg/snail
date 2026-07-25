/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: search_path_for_golb @ 0x415e30 */

00415e39        int32_t i = 0
00415e3f        int32_t count = manager->count
00415e41        float var_20_1
00415e41        __builtin_strncpy(&var_20_1, "(knN", 8)
00415e4b        if (count s<= 0)
00415eed        return nullptr
00415e57        float* position_z_cursor = &manager->entries[0].position.z
00415edc        struct ContactTargetEntry* nearest_entry
00415e6e        struct Vec3 vector
00415e6e        vector.x = fconvert.s(fconvert.t(position_z_cursor[-2]) - fconvert.t(position->x))
00415e7f        vector.y = fconvert.s(fconvert.t(position_z_cursor[-1]) - fconvert.t(position->y))
00415e83        float var_10_1 = fconvert.s(fconvert.t(*position_z_cursor) - fconvert.t(position->z))
00415e87        long double x87_r7_7 = fconvert.t(var_10_1)
00415e8b        long double temp1_1 = fconvert.t(0f)
00415e8b        x87_r7_7 - temp1_1
00415e95        vector.z = var_10_1
00415e9e        if ((((x87_r7_7 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp1_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00415ea0        long double x87_r7_8 = fconvert.t(var_10_1)
00415ea4        long double temp2_1 = fconvert.t(30f)
00415ea4        x87_r7_8 - temp2_1
00415eaf        if ((((x87_r7_8 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp2_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp2_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00415eb5        long double st0_1 = vector_magnitude(&vector)
00415eba        long double temp3_1 = fconvert.t(var_20_1)
00415eba        st0_1 - temp3_1
00415ec3        if ((((st0_1 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(st0_1, temp3_1) ? 1 : 0) << 0xa | (st0_1 == temp3_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
00415ec5        var_20_1 = fconvert.s(st0_1)
00415ecc        nearest_entry = &position_z_cursor[-3]
00415ed6        i += 1
00415ed7        position_z_cursor = &position_z_cursor[6]
00415edc        do while (i s< manager->count)
00415ee2        return nearest_entry
