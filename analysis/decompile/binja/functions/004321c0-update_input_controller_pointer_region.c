/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_input_controller_pointer_region @ 0x4321c0 */

004321cd        int32_t y_1 = y
004321d7        int32_t x_1 = x
004321e2        g_input_region_left[slot] = left
004321e9        g_input_region_top[slot] = top
004321f0        g_input_region_right[slot] = right
004321f7        g_input_region_bottom[slot] = bottom
0043220a        if (x_1 s>= left && x_1 s< right && y_1 s>= top && y_1 s< bottom)
0043220e        set_hide_system_cursor_flag(1)
00432224        if (capture_when_outside == 0 || force_clamp != 0)
00432234        if (x_1 s< left)
00432236        x_1 = left
0043223a        if (x_1 s>= right)
0043223c        x_1 = right - 1
00432241        if (y_1 s< top)
00432243        y_1 = top
00432247        if (y_1 s>= bottom)
00432249        y_1 = bottom - 1
0043224f        click_mouse_screen(slot, x_1, y_1)
00432256        set_hide_system_cursor_flag(1)
00432228        set_hide_system_cursor_flag(0)
00432277        capture_when_outside.d = (x_1 - left) * 0x280
0043227f        long double x87_r7 = float.t(capture_when_outside.d)
00432283        capture_when_outside.d = right - left
0043228c        long double x87_r7_1 = x87_r7 / float.t(capture_when_outside.d)
0043229b        capture_when_outside.d = (y_1 - top) * 0x1e0
004322a5        (&g_input_controller_slot0.authored_x)[slot * 0xe] = fconvert.s(x87_r7_1)
004322ab        long double x87_r7_2 = float.t(capture_when_outside.d)
004322af        capture_when_outside.d = bottom - top
004322b3        int16_t eax_6
004322b3        eax_6.b = button_a
004322bd        (&g_input_controller_slot0.authored_y)[slot * 0xe] = fconvert.s(x87_r7_2 / float.t(capture_when_outside.d))
004322c7        (&g_input_controller_slot0.pointer_value)[slot * 0xe] = fconvert.s(float.t(pointer_value))
004322cd        if (eax_6.b != 0)
004322cf        int32_t eax_7 = (&g_input_controller_slot0.buttons)[slot * 0xe]
004322d5        eax_7:1.b |= 0x40
004322d8        (&g_input_controller_slot0.buttons)[slot * 0xe] = eax_7
004322de        eax_6.b = button_b
004322e4        if (eax_6.b != 0)
004322e6        int32_t eax_8 = (&g_input_controller_slot0.buttons)[slot * 0xe]
004322ec        eax_8:1.b |= 0x80
004322ef        (&g_input_controller_slot0.buttons)[slot * 0xe] = eax_8
004322f5        eax_6.b = button_c
004322fb        if (eax_6.b != 0)
004322fd        (&g_input_controller_slot0.buttons)[slot * 0xe] |= 0x100000
00432307        long double x87_r7_5 = fconvert.t((&g_input_controller_slot0.authored_x)[slot * 0xe])
0043230d        long double temp0 = fconvert.t(1f)
0043230d        x87_r7_5 - temp0
00432318        long double x87_r7_6
00432318        if ((((x87_r7_5 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp0) ? 1 : 0) << 0xa | (x87_r7_5 == temp0 ? 1 : 0) << 0xe):1.b & 1) == 0)
00432322        long double x87_r7_7 = fconvert.t((&g_input_controller_slot0.authored_x)[slot * 0xe])
00432328        long double temp1_1 = fconvert.t(632f)
00432328        x87_r7_7 - temp1_1
00432333        if ((((x87_r7_7 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp1_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0043233d        x87_r7_6 = fconvert.t((&g_input_controller_slot0.authored_x)[slot * 0xe])
00432335        x87_r7_6 = fconvert.t(632f)
0043231a        x87_r7_6 = fconvert.t(1f)
00432343        (&g_input_controller_slot0.authored_x)[slot * 0xe] = fconvert.s(x87_r7_6)
00432349        long double x87_r7_8 = fconvert.t((&g_input_controller_slot0.authored_y)[slot * 0xe])
0043234f        long double temp2 = fconvert.t(1f)
0043234f        x87_r7_8 - temp2
0043235a        if ((((x87_r7_8 < temp2 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp2) ? 1 : 0) << 0xa | (x87_r7_8 == temp2 ? 1 : 0) << 0xe):1.b & 1) != 0)
0043235c        (&g_input_controller_slot0.authored_y)[slot * 0xe] = 0x3f800000
00432366        return
00432367        long double x87_r7_9 = fconvert.t((&g_input_controller_slot0.authored_y)[slot * 0xe])
0043236d        long double temp3 = fconvert.t(472f)
0043236d        x87_r7_9 - temp3
00432378        if ((((x87_r7_9 < temp3 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp3) ? 1 : 0) << 0xa | (x87_r7_9 == temp3 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0043238b        (&g_input_controller_slot0.authored_y)[slot * 0xe] = fconvert.s(fconvert.t((&g_input_controller_slot0.authored_y)[slot * 0xe]))
00432391        return
0043237a        (&g_input_controller_slot0.authored_y)[slot * 0xe] = 0x43ec0000
00432384        return
