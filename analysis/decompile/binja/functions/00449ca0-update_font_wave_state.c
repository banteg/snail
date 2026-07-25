/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_font_wave_state @ 0x449ca0 */

00449ca6        long double x87_r7 = fconvert.t(g_font_wave_step_a) + fconvert.t(g_font_wave_phase_a)
00449cae        g_font_text_cursor = &g_font_text_buffer
00449cb8        g_registered_font_count = 0
00449cbd        g_font_queue_count = 0
00449cc2        g_font_wave_phase_a = fconvert.s(x87_r7)
00449cc8        long double temp0 = fconvert.t(6.28318548f)
00449cc8        x87_r7 - temp0
00449cd3        if ((((x87_r7 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp0) ? 1 : 0) << 0xa | (x87_r7 == temp0 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00449ce1        g_font_wave_phase_a = fconvert.s(fconvert.t(g_font_wave_phase_a) - fconvert.t(6.28318548f))
00449ced        long double x87_r7_4 = fconvert.t(g_font_wave_step_b) + fconvert.t(g_font_wave_phase_b)
00449cf3        g_font_wave_phase_b = fconvert.s(x87_r7_4)
00449cf9        long double temp1 = fconvert.t(6.28318548f)
00449cf9        x87_r7_4 - temp1
00449d04        if ((((x87_r7_4 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp1) ? 1 : 0) << 0xa | (x87_r7_4 == temp1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00449d12        g_font_wave_phase_b = fconvert.s(fconvert.t(g_font_wave_phase_b) - fconvert.t(6.28318548f))
00449d18        return
