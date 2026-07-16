/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: copy_active_input_controller_state @ 0x4320f0 */

004320fa        if (controller_slot != 0)
00432163        *out_buttons = g_input_controller_slot1.buttons
00432173        *out_axis_x = fconvert.s(fconvert.t(g_input_controller_slot1.axis_x))
0043217f        *out_axis_y = fconvert.s(fconvert.t(g_input_controller_slot1.axis_y))
0043218b        *out_authored_x = fconvert.s(fconvert.t(g_input_controller_slot1.authored_x))
00432197        *out_authored_y = fconvert.s(fconvert.t(g_input_controller_slot1.authored_y))
004321a3        *out_pointer_value = fconvert.s(fconvert.t(g_input_controller_slot1.pointer_value))
004321ab        *out_pointer_x = fconvert.s(fconvert.t(g_input_controller_slot1.pointer_x))
004321b3        *out_pointer_y = fconvert.s(fconvert.t(g_input_controller_slot1.pointer_y))
004321b5        return out_pointer_value
00432106        *out_buttons = g_input_controller_slot0.buttons
00432116        *out_axis_x = fconvert.s(fconvert.t(g_input_controller_slot0.axis_x))
00432122        *out_axis_y = fconvert.s(fconvert.t(g_input_controller_slot0.axis_y))
0043212e        *out_authored_x = fconvert.s(fconvert.t(g_input_controller_slot0.authored_x))
0043213a        *out_authored_y = fconvert.s(fconvert.t(g_input_controller_slot0.authored_y))
00432146        *out_pointer_value = fconvert.s(fconvert.t(g_input_controller_slot0.pointer_value))
0043214e        *out_pointer_x = fconvert.s(fconvert.t(g_input_controller_slot0.pointer_x))
00432156        *out_pointer_y = fconvert.s(fconvert.t(g_input_controller_slot0.pointer_y))
00432158        return out_pointer_value
