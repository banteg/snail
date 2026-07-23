/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: format_time_trial_string @ 0x448960 */

00448965        long double x87_r7 = fconvert.t(timer->total_seconds)
00448967        long double temp1 = fconvert.t(0f)
00448967        x87_r7 - temp1
00448972        if ((((x87_r7 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1) ? 1 : 0) << 0xa | (x87_r7 == temp1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
0044897e        sprintf(0x751478, "-:--:--")
0044898c        return 0x751478
004489a5        sprintf(0x751478, "%1i:%02i:%03i", timer->minutes, timer->seconds, timer->display_thousandths)
004489c0        sprintf(0x751478, "%1i:%02i:%02i", timer->minutes, timer->seconds, timer->display_hundredths)
004489ce        return 0x751478
