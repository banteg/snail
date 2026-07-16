/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_input_controller_pointer_authored_xy @ 0x4323a0 */

004323ba        int32_t edi = *((arg1 << 2) + &g_input_region_left)
004323c8        (&g_input_controller_slot0.authored_x)[arg1 * 0xe] = arg2
004323ce        int32_t ecx_1 = *((arg1 << 2) + &g_input_region_bottom)
004323d5        (&g_input_controller_slot0.authored_y)[arg1 * 0xe] = arg3
004323db        int32_t eax_3 = *((arg1 << 2) + &g_input_region_top)
004323fe        int32_t y
004323fe        int16_t x87control
004323fe        int16_t x87control_1
004323fe        y, x87control_1 = ftol(x87control, float.t(ecx_1 - eax_3) * fconvert.t(arg3) * fconvert.t(0.00208333344f) + float.t(eax_3))
00432437        return click_mouse_screen(arg1, ftol(x87control_1, float.t(*((arg1 << 2) + &g_input_region_right) - edi) * fconvert.t(arg2) * fconvert.t(0.00156250002f) + float.t(edi)), y)
