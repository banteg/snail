/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: play_registered_sound_sample_scaled @ 0x4499a0 */

004499a0        long double x87_r7 = fconvert.t(arg2)
004499a4        long double temp1 = fconvert.t(0f)
004499a4        x87_r7 - temp1
004499aa        int16_t result = (x87_r7 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1) ? 1 : 0) << 0xa | (x87_r7 == temp1 ? 1 : 0) << 0xe
004499af        if ((result:1.b & 1) == 0)
004499b1        long double x87_r7_1 = fconvert.t(arg2)
004499b5        long double temp2_1 = fconvert.t(1f)
004499b5        x87_r7_1 - temp2_1
004499c0        int32_t eax
004499c0        int16_t x87control
004499c0        if ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
004499eb        eax = __ftol(x87control, fconvert.t(1f) * fconvert.t(100f))
00449a01        return data_7527b4(*((arg1 << 2) + &data_7537e0), 0, 0xffffffff, eax, 0, 0xffffffff)
004499cc        long double x87_r7_2 = fconvert.t(arg2)
004499d0        long double temp3_1 = fconvert.t(0f)
004499d0        x87_r7_2 - temp3_1
004499d6        result = (x87_r7_2 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp3_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp3_1 ? 1 : 0) << 0xe
004499db        if ((result:1.b & 0x40) == 0)
004499eb        eax = __ftol(x87control, fconvert.t(arg2) * fconvert.t(100f))
00449a01        return data_7527b4(*((arg1 << 2) + &data_7537e0), 0, 0xffffffff, eax, 0, 0xffffffff)
00449a07        return result
