/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_mouse @ 0x44bc50 */

0044bc50        int32_t* eax_43 = data_777d9c
0044bc5d        int32_t var_14
0044bc5d        if (eax_43 != 0)
0044bc61        __builtin_memset(&var_14, 0, 0x14)
0044bc84        if ((*(*eax_43 + 0x24))(eax_43, 0x14, &var_14) s< 0)
0044bc86        int32_t* eax_1 = data_777d9c
0044bc96        if ((*(*eax_1 + 0x1c))(eax_1) == 0x8007001e)
0044bca8        int32_t i
0044bc98        int32_t* eax_3 = data_777d9c
0044bca0        i = (*(*eax_3 + 0x1c))(eax_3)
0044bca8        do while (i == 0x8007001e)
0044bcb6        RECT rect
0044bcb6        BOOL eax_4 = GetWindowRect(arg1, &rect)
0044bcbe        RECT rect_1
0044bcbe        if (eax_4 == 0)
0044bcd4        __builtin_memset(&rect, 0, 0x10)
0044bcc6        eax_4 = GetClientRect(arg1, &rect_1)
0044bcce        if (eax_4 == 0)
0044bcd4        __builtin_memset(&rect, 0, 0x10)
0044bce6        if (data_4dfaf4 == 0)
0044bcf4        eax_4 = is_mouse_captured(data_4df904 + 0x290)
0044bcfb        int16_t x87control
0044bcfb        if (data_4dfaf4 != 0 || eax_4.b == 0)
0044bd1f        data_777d58 = fconvert.s(float.t(var_14) + fconvert.t(data_777d58))
0044bd2f        int32_t var_10
0044bd2f        data_777d60 = fconvert.s(float.t(var_10) + fconvert.t(data_777d60))
0044bd35        long double x87_r7_5 = fconvert.t(data_777d58)
0044bd3b        long double temp0_1 = fconvert.t(0f)
0044bd3b        x87_r7_5 - temp0_1
0044bd41        eax_4.w = (x87_r7_5 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp0_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp0_1 ? 1 : 0) << 0xe
0044bd46        if ((eax_4:1.b & 1) == 0)
0044bd54        long double x87_r7_6 = fconvert.t(data_777d58)
0044bd5a        long double temp1_1 = fconvert.t(639f)
0044bd5a        x87_r7_6 - temp1_1
0044bd60        eax_4.w = (x87_r7_6 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp1_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp1_1 ? 1 : 0) << 0xe
0044bd65        if ((eax_4:1.b & 0x41) == 0)
0044bd67        data_777d58 = 0x441fc000
0044bd48        data_777d58 = 0
0044bd71        long double x87_r7_7 = fconvert.t(data_777d60)
0044bd77        long double temp2_1 = fconvert.t(0f)
0044bd77        x87_r7_7 - temp2_1
0044bd7d        eax_4.w = (x87_r7_7 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp2_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp2_1 ? 1 : 0) << 0xe
0044bd82        if ((eax_4:1.b & 1) == 0)
0044bd90        long double x87_r7_8 = fconvert.t(data_777d60)
0044bd96        long double temp3_1 = fconvert.t(479f)
0044bd96        x87_r7_8 - temp3_1
0044bd9c        eax_4.w = (x87_r7_8 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp3_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp3_1 ? 1 : 0) << 0xe
0044bda1        if ((eax_4:1.b & 0x41) == 0)
0044bda3        data_777d60 = 0x43ef8000
0044bd84        data_777d60 = 0
0044bd08        x87control = convert_mouse_screen_xy(0, &data_777d58, &data_777d60)
0044bdb3        char eax_5
0044bdb3        if (data_4dfaf4 == 0)
0044bdc5        eax_5 = is_mouse_captured(data_4df904 + 0x290)
0044bdcc        int32_t var_74
0044bdcc        int32_t var_70
0044bdcc        int32_t var_6c
0044bdcc        int32_t var_68
0044bdcc        char var_64
0044bdcc        char var_60
0044bdcc        char var_58_2
0044bdcc        char var_54_4
0044bdcc        RECT rect_2
0044bdcc        int32_t eax_19
0044bdcc        int32_t top
0044bdcc        int32_t edx_12
0044bdcc        int32_t right
0044bdcc        if (data_4dfaf4 == 0 && eax_5 != 0)
0044bde4        RECT* lpRect
0044bde4        if (is_mouse_captured(data_4df904 + 0x290) != 0)
0044be45        lpRect = nullptr
0044be0a        rect_2.left = rect_1.left - data_4b7780 + rect.left
0044be28        rect_2.right = rect_1.right - data_4b7788 + rect.right
0044be3a        rect_2.top = rect_1.top - data_4b7784 + rect.top
0044be3e        rect_2.bottom = rect_1.bottom - data_4b778c + rect.bottom
0044be42        lpRect = &rect_2
0044be46        ClipCursor(lpRect)
0044be57        var_54_4 = data_4dfaf4
0044be63        var_58_2 = is_mouse_captured(data_4df904 + 0x290)
0044be64        int32_t var_5c = 0
0044be6e        var_60 = read_right_mouse_button_state(0)
0044be78        var_64 = read_left_mouse_button_state(0)
0044be88        var_68 = consume_mouse_wheel_delta(0)
0044be89        int32_t eax_17
0044be89        int16_t x87control_1
0044be89        eax_17, x87control_1 = __ftol(x87control, fconvert.t(data_777d60))
0044be94        var_6c = eax_17
0044be95        int32_t eax_18 = __ftol(x87control_1, fconvert.t(data_777d58))
0044be9e        top = rect.top
0044bea2        var_70 = eax_18
0044bea3        eax_19 = data_4b7784
0044bea8        right = rect_1.right
0044beb0        var_74 = rect_1.bottom - eax_19 + top
0044beb1        edx_12 = data_4b7780
0044beb7        goto label_44c007
0044bec3        ClipCursor(nullptr)
0044bed8        int32_t var_80
0044bed8        int32_t var_7c
0044bed8        int32_t var_78
0044bed8        if (is_mouse_captured(data_4df904 + 0x290) != 0)
0044bfa7        var_54_4 = data_4dfaf4
0044bfb3        var_58_2 = is_mouse_captured(data_4df904 + 0x290)
0044bfb4        int32_t var_5c_2 = 0
0044bfbe        var_60 = read_right_mouse_button_state(0)
0044bfc8        var_64 = read_left_mouse_button_state(0)
0044bfd8        var_68 = consume_mouse_wheel_delta(0)
0044bfd9        int32_t eax_36
0044bfd9        int16_t x87control_3
0044bfd9        eax_36, x87control_3 = __ftol(x87control, fconvert.t(data_777d60))
0044bfe4        var_6c = eax_36
0044bfe5        int32_t eax_37 = __ftol(x87control_3, fconvert.t(data_777d58))
0044bfee        top = rect.top
0044bff2        var_70 = eax_37
0044bff3        eax_19 = data_4b7774
0044bff8        right = rect_1.right
0044c000        var_74 = rect_1.bottom - eax_19 + top
0044c001        edx_12 = data_4b7770
0044c007        label_44c007:
0044c007        int32_t left = rect.left
0044c00f        var_78 = right - edx_12 + left
0044c020        var_7c = rect_1.top - eax_19 + top
0044c021        var_80 = rect_1.left - edx_12 + left
0044befd        rect_2.left = rect_1.left - data_4b7780 + rect.left
0044bf19        rect_2.right = rect_1.right - data_4b7788 + rect.right
0044bf31        rect_2.top = rect_1.top - data_4b7784 + rect.top
0044bf35        rect_2.bottom = rect_1.bottom - data_4b778c + rect.bottom
0044bf39        ClipCursor(&rect_2)
0044bf47        var_54_4 = data_4dfaf4
0044bf53        var_58_2 = is_mouse_captured(data_4df904 + 0x290)
0044bf54        int32_t var_5c_1 = 0
0044bf5e        var_60 = read_right_mouse_button_state(0)
0044bf68        var_64 = read_left_mouse_button_state(0)
0044bf78        var_68 = consume_mouse_wheel_delta(0)
0044bf79        int32_t eax_30
0044bf79        int16_t x87control_2
0044bf79        eax_30, x87control_2 = __ftol(x87control, fconvert.t(data_777d60))
0044bf84        var_6c = eax_30
0044bf8a        var_70 = __ftol(x87control_2, fconvert.t(data_777d58))
0044bf8b        var_74 = 0x1e0
0044bf90        var_78 = 0x280
0044bf95        var_7c = 0
0044bf96        var_80 = 0
0044c023        update_input_controller_pointer_region(0, var_80, var_7c, var_78, var_74, var_70, var_6c, var_68, var_64, var_60, 0, var_58_2, var_54_4)
0044c034        if (data_777d70 != 0)
0044c037        SetCursor(nullptr)
0044c043        return 0
