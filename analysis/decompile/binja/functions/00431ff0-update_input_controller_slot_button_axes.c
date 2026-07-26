/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_input_controller_slot_button_axes @ 0x431ff0 */

00431ff6        if (slot != 0)
0043205d        (&g_input_controller_slot0.buttons)[slot * 0xe] = buttons
00432063        *(slot * 0x38 + &g_input_controller_slot0) = axis_x
0043206d        (&g_input_controller_slot0.axis_y)[slot * 0xe] = axis_y
00432073        long double x87_r7_2 = fconvert.t(g_input_controller_slot0.axis_x)
00432079        long double temp0_1 = fconvert.t(0.150000006f)
00432079        x87_r7_2 - temp0_1
00432084        long double x87_r7_4
00432084        if ((((x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) != 0)
00432094        long double temp2_1 = fconvert.t(-0.150000006f)
00432094        x87_r7_2 - temp2_1
0043209f        if ((((x87_r7_2 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp2_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp2_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) != 0)
004320b3        x87_r7_4 = (fneg(x87_r7_2) - fconvert.t(0.150000006f)) * fconvert.t(-1.17647064f)
004320a3        x87_r7_4 = fconvert.t(0f)
0043208c        x87_r7_4 = (x87_r7_2 - fconvert.t(0.150000006f)) * fconvert.t(1.17647064f)
004320bf        enum InputButtonFlag buttons_1 = g_input_controller_slot1.buttons
004320cd        g_input_controller_slot1.authored_x = fconvert.s((x87_r7_4 + fconvert.t(1f)) * fconvert.t(320f))
004320d3        if ((buttons.b & 0xf0) != 0)
004320d5        buttons_1:1.b |= 0x40
004320d8        g_input_controller_slot1.buttons = buttons_1
004320dd        return
004320de        buttons_1:1.b &= 0xbf
004320e1        g_input_controller_slot1.buttons = buttons_1
00431ff8        long double x87_r7 = fconvert.t(g_input_controller_slot0.axis_x)
00431ffe        long double temp1_1 = fconvert.t(0f)
00431ffe        x87_r7 - temp1_1
00432010        g_input_controller_slot0.buttons |= buttons
0043201b        if ((((x87_r7 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1_1) ? 1 : 0) << 0xa | (x87_r7 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00432021        g_input_controller_slot0.axis_x = axis_x
00432027        long double x87_r7_1 = fconvert.t(g_input_controller_slot0.axis_y)
0043202d        long double temp3_1 = fconvert.t(0f)
0043202d        x87_r7_1 - temp3_1
00432038        if ((((x87_r7_1 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp3_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00432042        g_input_controller_slot0.axis_y = axis_y
004320e6        return
