/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: ensure_music_stream_from_path @ 0x449720 */

0044972b        if (*arg1 != 0)
00449733        int32_t eax_1 = sub_44e6c0(arg2, &data_7516a0)
0044973d        if (eax_1 != 0)
004497dd        return eax_1
00449745        stop_music_stream(arg1)
0044974b        char* edi_1 = arg2
0044974d        int32_t i = 0xffffffff
00449752        while (i != 0)
00449752        bool cond:0_1 = 0 != *edi_1
00449752        edi_1 = &edi_1[1]
00449752        i -= 1
00449752        if (not(cond:0_1))
00449752        break
0044975f        sub_44e5b0(&data_7516a0, arg2)
0044976e        if (data_753c20 != 0)
00449772        stop_music_stream(arg1)
0044977a        data_753c20 = 0
00449785        if (not.d(i) - 1 s> 4)
00449790        int32_t eax_3 = data_753bf8(0, arg2, 0, 0, 0)
00449798        data_753c20 = eax_3
0044979d        if (eax_3 != 0)
004497a5        if (arg3 == 0)
004497bf        int32_t eax_5 = data_7517a0(eax_3, 0, 0)
004497c5        *arg1 = 1
004497ca        return eax_5
004497ac        int32_t eax_4 = data_7517a0(eax_3, 0, 4)
004497b2        *arg1 = 1
004497b7        return eax_4
004497cd        char* __saved_edi_1 = arg2
004497d3        return report_errorf("Music Play Memory Failed %s")
