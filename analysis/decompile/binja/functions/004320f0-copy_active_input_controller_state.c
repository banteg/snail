/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: copy_active_input_controller_state @ 0x4320f0 */

004320fa        if (arg1 != 0)
00432163        *arg2 = data_50337c
00432173        *arg3 = fconvert.s(fconvert.t(data_503374))
0043217f        *arg4 = fconvert.s(fconvert.t(data_503378))
0043218b        *arg5 = fconvert.s(fconvert.t(data_503388))
00432197        *arg6 = fconvert.s(fconvert.t(data_50338c))
004321a3        *arg7 = fconvert.s(fconvert.t(data_503390))
004321ab        *arg8 = fconvert.s(fconvert.t(data_503380))
004321b3        *arg9 = fconvert.s(fconvert.t(data_503384))
004321b5        return arg7
00432106        *arg2 = g_input_slot0_buttons
00432116        *arg3 = fconvert.s(fconvert.t(g_input_slot0_axis_x))
00432122        *arg4 = fconvert.s(fconvert.t(g_input_slot0_axis_y))
0043212e        *arg5 = fconvert.s(fconvert.t(g_input_slot0_authored_x))
0043213a        *arg6 = fconvert.s(fconvert.t(g_input_slot0_authored_y))
00432146        *arg7 = fconvert.s(fconvert.t(g_input_slot0_pointer_value))
0043214e        *arg8 = fconvert.s(fconvert.t(g_input_slot0_pointer_x))
00432156        *arg9 = fconvert.s(fconvert.t(g_input_slot0_pointer_y))
00432158        return arg7
