/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_current_directory_with_drive_fallback @ 0x430f30 */

00430f37        char* esi = arg1
00430f44        if (esi != &data_4dfb08)
00430f4d        if (esi[1] != 0x3a)
00430f4d        goto label_430f82
00430f56        char var_104 = *esi
00430f5a        char var_103_1 = 0x3a
00430f5e        char var_102_1 = 0x5c
00430f63        char var_101_1 = 0
00430f68        sub_48c18b(&var_104)
00430f7c        if (esi[2] != 0 && esi[3] != 0)
00430f7e        esi = &esi[3]
00430f82        label_430f82:
00430f8c        if (sub_48c18b(esi) != 0)
00430f98        char var_100[0x100]
00430f98        sub_496946(&var_100, 0x100)
00430fa1        char (* var_114)[0x100] = &var_100
00430fa2        char* var_118 = esi
00430fa8        report_messagef("ERROR: cannot find directory %s (from %s)\n")
00430fbc        return 1
00430fc6        return 0
