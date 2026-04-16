/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: stop_music_stream @ 0x4498d0 */

004498d6        if (*arg1 == 0)
004498d6        return 
004498d8        int32_t eax_1 = data_751680
004498df        if (eax_1 != 0)
004498e8        data_75165c(data_753c20, eax_1)
004498ee        data_751680 = 0
004498ff        data_753be4(data_753c20)
0044990c        data_753cb0(data_753c20)
00449912        *arg1 = 0
00449916        return
