/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_mouse @ 0x44bc50 */

0044bc50        void* mouse_device_3 = g_mouse_device
0044bc5d        int32_t var_14
0044bc5d        if (mouse_device_3 != 0)
0044bc61        __builtin_memset(&var_14, 0, 0x14)
0044bc84        if ((*(*mouse_device_3 + 0x24))(mouse_device_3, 0x14, &var_14) s< 0)
0044bc86        void* mouse_device_1 = g_mouse_device
0044bc96        if ((*(*mouse_device_1 + 0x1c))(mouse_device_1) == 0x8007001e)
0044bca8        int32_t i
0044bc98        void* mouse_device_2 = g_mouse_device
0044bca0        i = (*(*mouse_device_2 + 0x1c))(mouse_device_2)
0044bca8        do while (i == 0x8007001e)
0044bcb6        RECT rect
0044bcb6        BOOL eax_2 = GetWindowRect(window_handle, &rect)
0044bcbe        RECT rect_1
0044bcbe        if (eax_2 == 0)
0044bcd4        __builtin_memset(&rect, 0, 0x10)
0044bcc6        eax_2 = GetClientRect(window_handle, &rect_1)
0044bcce        if (eax_2 == 0)
0044bcd4        __builtin_memset(&rect, 0, 0x10)
0044bce6        if (g_fullscreen_active == 0)
0044bcf4        eax_2 = is_mouse_captured(&g_game_base->players[0].mouse_cursor)
0044bcfb        int16_t x87control
0044bcfb        if (g_fullscreen_active != 0 || eax_2.b == 0)
0044bd1f        g_mouse_live_x[0] = fconvert.s(float.t(var_14) + fconvert.t(g_mouse_live_x[0]))
0044bd2f        int32_t var_10
0044bd2f        g_mouse_live_y[0] = fconvert.s(float.t(var_10) + fconvert.t(g_mouse_live_y[0]))
0044bd35        long double x87_r7_5 = fconvert.t(g_mouse_live_x[0])
0044bd3b        long double temp0_1 = fconvert.t(0f)
0044bd3b        x87_r7_5 - temp0_1
0044bd46        if ((((x87_r7_5 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp0_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp0_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0044bd54        long double x87_r7_6 = fconvert.t(g_mouse_live_x[0])
0044bd5a        long double temp1_1 = fconvert.t(639f)
0044bd5a        x87_r7_6 - temp1_1
0044bd65        if ((((x87_r7_6 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp1_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044bd67        g_mouse_live_x[0] = 639f
0044bd48        g_mouse_live_x[0] = 0f
0044bd71        long double x87_r7_7 = fconvert.t(g_mouse_live_y[0])
0044bd77        long double temp2_1 = fconvert.t(0f)
0044bd77        x87_r7_7 - temp2_1
0044bd82        if ((((x87_r7_7 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp2_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp2_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0044bd90        long double x87_r7_8 = fconvert.t(g_mouse_live_y[0])
0044bd96        long double temp3_1 = fconvert.t(479f)
0044bd96        x87_r7_8 - temp3_1
0044bda1        if ((((x87_r7_8 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp3_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044bda3        g_mouse_live_y[0] = 479f
0044bd84        g_mouse_live_y[0] = 0f
0044bd08        x87control = convert_mouse_screen_xy(0, &g_mouse_live_x, &g_mouse_live_y)
0044bdb3        uint8_t eax_4
0044bdb3        if (g_fullscreen_active == 0)
0044bdc5        eax_4 = is_mouse_captured(&g_game_base->players[0].mouse_cursor)
0044bdcc        int32_t bottom
0044bdcc        int32_t x
0044bdcc        int32_t y
0044bdcc        int32_t pointer_value
0044bdcc        char button_a
0044bdcc        char button_b
0044bdcc        uint8_t capture_when_outside
0044bdcc        char fullscreen_active_1
0044bdcc        RECT rect_2
0044bdcc        int32_t eax_16
0044bdcc        int32_t top
0044bdcc        int32_t edx_12
0044bdcc        int32_t right
0044bdcc        if (g_fullscreen_active == 0 && eax_4 != 0)
0044bde4        RECT* lpRect
0044bde4        if (is_mouse_captured(&g_game_base->players[0].mouse_cursor) != 0)
0044be45        lpRect = nullptr
0044be0a        rect_2.left = rect_1.left - data_4b7780 + rect.left
0044be28        rect_2.right = rect_1.right - data_4b7788 + rect.right
0044be3a        rect_2.top = rect_1.top - data_4b7784 + rect.top
0044be3e        rect_2.bottom = rect_1.bottom - data_4b778c + rect.bottom
0044be42        lpRect = &rect_2
0044be46        ClipCursor(lpRect)
0044be57        fullscreen_active_1 = g_fullscreen_active
0044be63        capture_when_outside = is_mouse_captured(&g_game_base->players[0].mouse_cursor)
0044be64        int32_t var_5c = 0
0044be6e        button_b = read_right_mouse_button_state(0)
0044be78        button_a = read_left_mouse_button_state(0)
0044be88        pointer_value = consume_mouse_wheel_delta(0)
0044be89        int32_t y_1
0044be89        int16_t x87control_1
0044be89        y_1, x87control_1 = ftol(x87control, fconvert.t(g_mouse_live_y[0]))
0044be94        y = y_1
0044be95        int32_t x_1 = ftol(x87control_1, fconvert.t(g_mouse_live_x[0]))
0044be9e        top = rect.top
0044bea2        x = x_1
0044bea3        eax_16 = data_4b7784
0044bea8        right = rect_1.right
0044beb0        bottom = rect_1.bottom - eax_16 + top
0044beb1        edx_12 = data_4b7780
0044beb7        goto label_44c007
0044bec3        ClipCursor(nullptr)
0044bed8        int32_t left_1
0044bed8        int32_t top_1
0044bed8        int32_t right_1
0044bed8        if (is_mouse_captured(&g_game_base->players[0].mouse_cursor) != 0)
0044bfa7        fullscreen_active_1 = g_fullscreen_active
0044bfb3        capture_when_outside = is_mouse_captured(&g_game_base->players[0].mouse_cursor)
0044bfb4        int32_t var_5c_2 = 0
0044bfbe        button_b = read_right_mouse_button_state(0)
0044bfc8        button_a = read_left_mouse_button_state(0)
0044bfd8        pointer_value = consume_mouse_wheel_delta(0)
0044bfd9        int32_t y_3
0044bfd9        int16_t x87control_3
0044bfd9        y_3, x87control_3 = ftol(x87control, fconvert.t(g_mouse_live_y[0]))
0044bfe4        y = y_3
0044bfe5        int32_t x_2 = ftol(x87control_3, fconvert.t(g_mouse_live_x[0]))
0044bfee        top = rect.top
0044bff2        x = x_2
0044bff3        eax_16 = data_4b7774
0044bff8        right = rect_1.right
0044c000        bottom = rect_1.bottom - eax_16 + top
0044c001        edx_12 = data_4b7770
0044c007        label_44c007:
0044c007        int32_t left = rect.left
0044c00f        right_1 = right - edx_12 + left
0044c020        top_1 = rect_1.top - eax_16 + top
0044c021        left_1 = rect_1.left - edx_12 + left
0044befd        rect_2.left = rect_1.left - data_4b7780 + rect.left
0044bf19        rect_2.right = rect_1.right - data_4b7788 + rect.right
0044bf31        rect_2.top = rect_1.top - data_4b7784 + rect.top
0044bf35        rect_2.bottom = rect_1.bottom - data_4b778c + rect.bottom
0044bf39        ClipCursor(&rect_2)
0044bf47        fullscreen_active_1 = g_fullscreen_active
0044bf53        capture_when_outside = is_mouse_captured(&g_game_base->players[0].mouse_cursor)
0044bf54        int32_t var_5c_1 = 0
0044bf5e        button_b = read_right_mouse_button_state(0)
0044bf68        button_a = read_left_mouse_button_state(0)
0044bf78        pointer_value = consume_mouse_wheel_delta(0)
0044bf79        int32_t y_2
0044bf79        int16_t x87control_2
0044bf79        y_2, x87control_2 = ftol(x87control, fconvert.t(g_mouse_live_y[0]))
0044bf84        y = y_2
0044bf8a        x = ftol(x87control_2, fconvert.t(g_mouse_live_x[0]))
0044bf8b        bottom = 0x1e0
0044bf90        right_1 = 0x280
0044bf95        top_1 = 0
0044bf96        left_1 = 0
0044c023        update_input_controller_pointer_region(0, left_1, top_1, right_1, bottom, x, y, pointer_value, button_a, button_b, 0, capture_when_outside, fullscreen_active_1)
0044c034        if (g_hide_system_cursor_flag != 0)
0044c037        SetCursor(nullptr)
0044c043        return 0
