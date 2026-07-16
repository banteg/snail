/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_input_controller_pointer_region @ 0x4321c0 */

004321cd        int32_t y = arg7
004321d7        int32_t x = arg6
004321e2        *((arg1 << 2) + &g_input_region_left) = arg2
004321e9        *((arg1 << 2) + &g_input_region_top) = arg3
004321f0        *((arg1 << 2) + &g_input_region_right) = arg4
004321f7        *((arg1 << 2) + &g_input_region_bottom) = arg5
0043220a        if (x s>= arg2 && x s< arg4 && y s>= arg3 && y s< arg5)
0043220e        set_hide_system_cursor_flag(1)
00432224        if (arg12 == 0 || arg13 != 0)
00432234        if (x s< arg2)
00432236        x = arg2
0043223a        if (x s>= arg4)
0043223c        x = arg4 - 1
00432241        if (y s< arg3)
00432243        y = arg3
00432247        if (y s>= arg5)
00432249        y = arg5 - 1
0043224f        click_mouse_screen(arg1, x, y)
00432256        set_hide_system_cursor_flag(1)
00432228        set_hide_system_cursor_flag(0)
00432277        arg12.d = (x - arg2) * 0x280
0043227f        long double x87_r7 = float.t(arg12.d)
00432283        arg12.d = arg4 - arg2
0043228c        long double x87_r7_1 = x87_r7 / float.t(arg12.d)
0043229b        arg12.d = (y - arg3) * 0x1e0
004322a3        int32_t result = arg5 - arg3
004322a5        (&g_input_controller_slot0.authored_x)[arg1 * 0xe] = fconvert.s(x87_r7_1)
004322ab        long double x87_r7_2 = float.t(arg12.d)
004322af        arg12.d = result
004322b3        result.b = arg9
004322bd        (&g_input_controller_slot0.authored_y)[arg1 * 0xe] = fconvert.s(x87_r7_2 / float.t(arg12.d))
004322c7        (&g_input_controller_slot0.pointer_value)[arg1 * 0xe] = fconvert.s(float.t(arg8))
004322cd        if (result.b != 0)
004322cf        result = (&g_input_controller_slot0.buttons)[arg1 * 0xe]
004322d5        result:1.b |= 0x40
004322d8        (&g_input_controller_slot0.buttons)[arg1 * 0xe] = result
004322de        result.b = arg10
004322e4        if (result.b != 0)
004322e6        result = (&g_input_controller_slot0.buttons)[arg1 * 0xe]
004322ec        result:1.b |= 0x80
004322ef        (&g_input_controller_slot0.buttons)[arg1 * 0xe] = result
004322f5        result.b = arg11
004322fb        if (result.b != 0)
004322fd        (&g_input_controller_slot0.buttons)[arg1 * 0xe] |= 0x100000
00432307        long double x87_r7_5 = fconvert.t((&g_input_controller_slot0.authored_x)[arg1 * 0xe])
0043230d        long double temp0 = fconvert.t(1f)
0043230d        x87_r7_5 - temp0
00432313        result.w = (x87_r7_5 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp0) ? 1 : 0) << 0xa | (x87_r7_5 == temp0 ? 1 : 0) << 0xe
00432318        long double x87_r7_6
00432318        if ((result:1.b & 1) == 0)
00432322        long double x87_r7_7 = fconvert.t((&g_input_controller_slot0.authored_x)[arg1 * 0xe])
00432328        long double temp1_1 = fconvert.t(632f)
00432328        x87_r7_7 - temp1_1
0043232e        result.w = (x87_r7_7 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp1_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp1_1 ? 1 : 0) << 0xe
00432333        if ((result:1.b & 0x41) != 0)
0043233d        x87_r7_6 = fconvert.t((&g_input_controller_slot0.authored_x)[arg1 * 0xe])
00432335        x87_r7_6 = fconvert.t(632f)
0043231a        x87_r7_6 = fconvert.t(1f)
00432343        (&g_input_controller_slot0.authored_x)[arg1 * 0xe] = fconvert.s(x87_r7_6)
00432349        long double x87_r7_8 = fconvert.t((&g_input_controller_slot0.authored_y)[arg1 * 0xe])
0043234f        long double temp2 = fconvert.t(1f)
0043234f        x87_r7_8 - temp2
00432355        result.w = (x87_r7_8 < temp2 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp2) ? 1 : 0) << 0xa | (x87_r7_8 == temp2 ? 1 : 0) << 0xe
0043235a        if ((result:1.b & 1) != 0)
0043235c        (&g_input_controller_slot0.authored_y)[arg1 * 0xe] = 0x3f800000
00432366        return result
00432367        long double x87_r7_9 = fconvert.t((&g_input_controller_slot0.authored_y)[arg1 * 0xe])
0043236d        long double temp3 = fconvert.t(472f)
0043236d        x87_r7_9 - temp3
00432373        result.w = (x87_r7_9 < temp3 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp3) ? 1 : 0) << 0xa | (x87_r7_9 == temp3 ? 1 : 0) << 0xe
00432378        if ((result:1.b & 0x41) != 0)
0043238b        (&g_input_controller_slot0.authored_y)[arg1 * 0xe] = fconvert.s(fconvert.t((&g_input_controller_slot0.authored_y)[arg1 * 0xe]))
00432391        return result
0043237a        (&g_input_controller_slot0.authored_y)[arg1 * 0xe] = 0x43ec0000
00432384        return result
