/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: copy_active_input_controller_state @ 0x4320f0 */

004320fa        if (controller_slot != 0)
00432163        *out_buttons = data_50337c
00432173        *out_axis_x = fconvert.s(fconvert.t(data_503374))
0043217f        *out_axis_y = fconvert.s(fconvert.t(data_503378))
0043218b        *out_authored_x = fconvert.s(fconvert.t(data_503388))
00432197        *out_authored_y = fconvert.s(fconvert.t(data_50338c))
004321a3        *out_pointer_value = fconvert.s(fconvert.t(data_503390))
004321ab        *out_pointer_x = fconvert.s(fconvert.t(data_503380))
004321b3        *out_pointer_y = fconvert.s(fconvert.t(data_503384))
004321b5        return out_pointer_value
00432106        *out_buttons = g_input_slot0_buttons
00432116        *out_axis_x = fconvert.s(fconvert.t(g_input_slot0_axis_x))
00432122        *out_axis_y = fconvert.s(fconvert.t(g_input_slot0_axis_y))
0043212e        *out_authored_x = fconvert.s(fconvert.t(g_input_slot0_authored_x))
0043213a        *out_authored_y = fconvert.s(fconvert.t(g_input_slot0_authored_y))
00432146        *out_pointer_value = fconvert.s(fconvert.t(g_input_slot0_pointer_value))
0043214e        *out_pointer_x = fconvert.s(fconvert.t(g_input_slot0_pointer_x))
00432156        *out_pointer_y = fconvert.s(fconvert.t(g_input_slot0_pointer_y))
00432158        return out_pointer_value
