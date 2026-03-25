/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_frontend_transition_overlay @ 0x40abf0 */

0040abf0        int32_t result = *arg1
0040abf8        if (result u> 4)
0040abf8        goto label_40ac87
0040abfe        switch (result)
0040ac64        case 1
0040ac64        long double x87_r7_6 = fconvert.t(arg1[1]) - fconvert.t(0.0555555522f)
0040ac6a        arg1[1] = fconvert.s(x87_r7_6)
0040ac6d        long double temp3_1 = fconvert.t(0f)
0040ac6d        x87_r7_6 - temp3_1
0040ac73        result.w = (x87_r7_6 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp3_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp3_1 ? 1 : 0) << 0xe
0040ac78        if ((result:1.b & 0x41) != 0)
0040ac7a        arg1[1] = 0
0040ac81        *arg1 = 0
0040ac78        goto label_40ac87
0040ac08        case 2
0040ac08        long double x87_r7_2 = fconvert.t(arg1[1]) + fconvert.t(0.0555555522f)
0040ac0e        arg1[1] = fconvert.s(x87_r7_2)
0040ac11        long double temp1_1 = fconvert.t(1f)
0040ac11        x87_r7_2 - temp1_1
0040ac17        result.w = (x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe
0040ac1c        if ((result:1.b & 0x41) == 0)
0040ac1e        arg1[1] = 0x3f800000
0040ac25        *arg1 = 3
0040ac2b        arg1[2] = 0
0040ac32        arg1[3] = 0x3eaaaaab
0040ac1c        goto label_40ac87
0040ac3e        case 3
0040ac3e        long double x87_r7_4 = fconvert.t(arg1[3]) + fconvert.t(arg1[2])
0040ac41        arg1[2] = fconvert.s(x87_r7_4)
0040ac44        long double temp2_1 = fconvert.t(1f)
0040ac44        x87_r7_4 - temp2_1
0040ac4a        result.w = (x87_r7_4 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp2_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp2_1 ? 1 : 0) << 0xe
0040ac4f        if ((result:1.b & 0x41) == 0)
0040ac51        *arg1 = 4
0040ac4f        goto label_40ac87
0040ac59        case 4
0040ac59        *arg1 = 1
0040ac87        label_40ac87:
0040ac87        long double x87_r7_7 = fconvert.t(arg1[1])
0040ac8e        long double temp0_1 = fconvert.t(0.00999999978f)
0040ac8e        x87_r7_7 - temp0_1
0040ac94        result.w = (x87_r7_7 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp0_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp0_1 ? 1 : 0) << 0xe
0040ac99        void var_10
0040ac99        if ((result:1.b & 0x41) == 0)
0040acc7        return queue_axis_aligned_textured_quad(2, 0, 0, 640f, 480f, 0x1000000, set_color_rgba(&var_10, 0, 0, 0, fconvert.s(x87_r7_7)), 0xe)
0040acd2        return result
