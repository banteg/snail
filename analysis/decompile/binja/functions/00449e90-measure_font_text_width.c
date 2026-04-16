/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: measure_font_text_width @ 0x449e90 */

00449e91        char* ebp = arg1
00449e9a        int32_t eax
00449e9a        eax.b = *ebp
00449e9d        arg1 = nullptr
00449ea7        if (eax.b != 0)
00449ec1        int32_t edi_2 = arg2 * 0x828
00449ed2        ebp = &ebp[1]
00449eda        long double x87_r7_2 = fconvert.t(*(((sx.d(font_slot_index_for_char(eax.b)) + arg2 * 0x20a) << 2) + &data_777704)) * fconvert.t(*(edi_2 + 0x777b10))
00449ee0        eax.b = *ebp
00449ef3        arg1 = fconvert.s(x87_r7_2 * fconvert.t(*(edi_2 + 0x777b14)) * fconvert.t(arg3) + fconvert.t(arg1))
00449ef7        do while (eax.b != 0)
00449f1c        int32_t ecx_8 = arg2 * 0x828
00449f1f        int32_t eax_4 = sx.d(font_slot_index_for_char(0x20))
00449f45        return (fconvert.t(1f) - fconvert.t(*(ecx_8 + 0x777b14))) * fconvert.t(*(((eax_4 + arg2 * 0x20a) << 2) + &data_777704)) * fconvert.t(*(ecx_8 + 0x777b10)) * fconvert.t(arg3) + fconvert.t(arg1)
