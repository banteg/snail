/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_frontend_transition_overlay @ 0x40abf0 */

0040abf0        int32_t state = fade->state
0040abf8        if (state u> 4)
0040abf8        goto label_40ac87
0040abfe        switch (state)
0040ac64        case 1
0040ac64        long double x87_r7_6 = fconvert.t(fade->alpha) - fconvert.t(0.0555555522f)
0040ac6a        fade->alpha = fconvert.s(x87_r7_6)
0040ac6d        long double temp3_1 = fconvert.t(0f)
0040ac6d        x87_r7_6 - temp3_1
0040ac78        if ((((x87_r7_6 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp3_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0040ac7a        fade->alpha = 0f
0040ac81        fade->state = 0
0040ac78        goto label_40ac87
0040ac08        case 2
0040ac08        long double x87_r7_2 = fconvert.t(fade->alpha) + fconvert.t(0.0555555522f)
0040ac0e        fade->alpha = fconvert.s(x87_r7_2)
0040ac11        long double temp1_1 = fconvert.t(1f)
0040ac11        x87_r7_2 - temp1_1
0040ac1c        if ((((x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0040ac1e        fade->alpha = 1f
0040ac25        fade->state = 3
0040ac2b        fade->hold_progress = 0f
0040ac32        fade->hold_progress_step = 0.333333343f
0040ac1c        goto label_40ac87
0040ac3e        case 3
0040ac3e        long double x87_r7_4 = fconvert.t(fade->hold_progress_step) + fconvert.t(fade->hold_progress)
0040ac41        fade->hold_progress = fconvert.s(x87_r7_4)
0040ac44        long double temp2_1 = fconvert.t(1f)
0040ac44        x87_r7_4 - temp2_1
0040ac4f        if ((((x87_r7_4 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp2_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0040ac51        fade->state = 4
0040ac4f        goto label_40ac87
0040ac59        case 4
0040ac59        fade->state = 1
0040ac87        label_40ac87:
0040ac87        long double x87_r7_7 = fconvert.t(fade->alpha)
0040ac8e        long double temp0_1 = fconvert.t(0.00999999978f)
0040ac8e        x87_r7_7 - temp0_1
0040ac99        struct tColour color
0040ac99        if ((((x87_r7_7 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp0_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0040acc7        queue_axis_aligned_textured_quad(2, 0f, 0f, 640f, 480f, 0x1000000, set_color_rgba(&color, 0f, 0f, 0f, fconvert.s(x87_r7_7)), 0xe)
0040acd2        return
