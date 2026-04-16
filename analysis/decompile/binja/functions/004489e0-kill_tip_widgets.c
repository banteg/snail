/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: kill_tip_widgets @ 0x4489e0 */

004489e3        data_4df904
004489f3        kill_border(arg1[3])
004489f8        void* eax_1 = arg1[4]
004489fd        if (eax_1 != 0)
004489ff        data_4df904
00448a0c        kill_border(eax_1)
00448a11        void* result = arg1[5]
00448a16        if (result != 0)
00448a19        data_4df904
00448a24        result = kill_border(result)
00448a29        *arg1 = 0
00448a30        return result
