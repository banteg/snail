/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_font_wave_state @ 0x449ca0 */

00449ca6        long double x87_r7 = fconvert.t(data_777b28) + fconvert.t(data_7772e8)
00449cae        data_7772f0 = 0x753ce8
00449cb8        data_777b20 = 0
00449cbd        data_777b24 = 0
00449cc2        data_7772e8 = fconvert.s(x87_r7)
00449cc8        long double temp0 = fconvert.t(6.28318548f)
00449cc8        x87_r7 - temp0
00449cd3        if ((((x87_r7 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp0) ? 1 : 0) << 0xa | (x87_r7 == temp0 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00449ce1        data_7772e8 = fconvert.s(fconvert.t(data_7772e8) - fconvert.t(6.28318548f))
00449ced        long double x87_r7_4 = fconvert.t(data_7772f4) + fconvert.t(data_7772ec)
00449cf3        data_7772ec = fconvert.s(x87_r7_4)
00449cf9        long double temp1 = fconvert.t(6.28318548f)
00449cf9        x87_r7_4 - temp1
00449cff        int16_t result = (x87_r7_4 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp1) ? 1 : 0) << 0xa | (x87_r7_4 == temp1 ? 1 : 0) << 0xe
00449d04        if ((result:1.b & 0x41) == 0)
00449d12        data_7772ec = fconvert.s(fconvert.t(data_7772ec) - fconvert.t(6.28318548f))
00449d18        return result
