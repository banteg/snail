/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: format_time_trial_string @ 0x448960 */

00448965        long double x87_r7 = fconvert.t(*arg1)
00448967        long double temp1 = fconvert.t(0f)
00448967        x87_r7 - temp1
00448972        if ((((x87_r7 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1) ? 1 : 0) << 0xa | (x87_r7 == temp1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
0044897e        sub_48b32c(0x751478, "-:--:--")
0044898c        return 0x751478
00448998        int32_t var_8 = arg1[4]
00448999        int32_t var_c = arg1[2]
0044899a        int32_t var_10 = arg1[1]
004489a5        sub_48b32c(0x751478, "%1i:%02i:%03i")
004489b3        int32_t var_1c = arg1[3]
004489b4        int32_t var_20 = arg1[2]
004489b5        int32_t var_24 = arg1[1]
004489c0        sub_48b32c(0x751478, "%1i:%02i:%02i")
004489ce        return 0x751478
