/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_voice_set @ 0x449360 */

00449360        long double x87_r7 = fconvert.t(set->cooldown)
00449363        long double temp0 = fconvert.t(0f)
00449363        x87_r7 - temp0
0044936e        if ((((x87_r7 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp0) ? 1 : 0) << 0xa | (x87_r7 == temp0 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0044936e        return
00449373        long double x87_r7_2 = fconvert.t(set->cooldown_step) + fconvert.t(set->cooldown)
00449376        set->cooldown = fconvert.s(x87_r7_2)
00449379        long double temp1_1 = fconvert.t(1f)
00449379        x87_r7_2 - temp1_1
00449384        if ((((x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00449386        set->cooldown = 0f
0044938d        return
