/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_challenge_setup_screen @ 0x4161f0 */

004161f5        int32_t eax_1 = *(*arg1 + 0x40)
004161fb        if (eax_1 == 0)
004162f9        data_4df904
00416308        kill_border(arg1[1])
00416310        data_4df904
0041631d        kill_border(arg1[2])
00416325        data_4df904
00416332        kill_border(arg1[3])
00416337        data_4df904
00416346        kill_border(arg1[4])
0041634e        data_4df904
0041635b        return kill_border(arg1[6])
00416202        if (eax_1 == 1)
00416292        data_4df904
0041629f        kill_border(arg1[4])
004162a7        data_4df904
004162b4        kill_border(arg1[6])
004162b9        data_4df904
004162c8        kill_border(arg1[7])
004162d0        data_4df904
004162dd        kill_border(arg1[8])
004162e5        data_4df904
004162f8        return kill_border(arg1[9])
0041620b        if (eax_1 != 4)
00416361        return eax_1 - 4
00416214        data_4df904
00416221        kill_border(arg1[1])
00416229        data_4df904
00416236        kill_border(arg1[2])
0041623b        data_4df904
0041624a        kill_border(arg1[3])
00416252        data_4df904
0041625f        kill_border(arg1[4])
00416267        data_4df904
00416274        kill_border(arg1[6])
00416279        data_4df904
0041628e        return kill_border(arg1[9])
