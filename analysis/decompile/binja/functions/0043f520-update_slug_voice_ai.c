/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_slug_voice_ai @ 0x43f520 */

0043f520        int16_t eax
0043f520        eax.b = slug->voice_active
0043f52a        if (eax.b == 0)
0043f52a        return
0043f532        long double x87_r7_2 = fconvert.t(slug->voice_progress_step) + fconvert.t(slug->voice_progress)
0043f538        slug->voice_progress = fconvert.s(x87_r7_2)
0043f53e        long double temp0_1 = fconvert.t(1f)
0043f53e        x87_r7_2 - temp0_1
0043f549        if ((((x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043f54b        slug->voice_progress = 0f
0043f551        slug->voice_active = 0
0043f557        return
