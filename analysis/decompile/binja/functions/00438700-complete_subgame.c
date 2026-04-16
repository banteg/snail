/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: complete_subgame @ 0x438700 */

0043870a        display_score_stats(arg1 + 0x3bb764)
00438715        int32_t eax_1 = *(arg1 + 0xff25dc) * 3
00438718        *(arg1 + (eax_1 << 1) + 0xfd2b84) |= 8
00438734        int32_t ecx_2 = *(arg1 + 0xff25dc) + 1
00438735        *(arg1 + 0xfd2b7c) += 1
0043873b        *(arg1 + 0xff25dc) = ecx_2
00438741        void* result
00438741        result.b = data_4b2f40
0043874d        if ((1 & result.b) == 0)
00438759        int32_t eax_2 = *(arg1 + 0x3bba64)
00438761        *(arg1 + 0xfd2b14) = *(arg1 + 0x3bba48)
00438778        __builtin_memcpy(arg1 + 0xfd2b18, arg1 + 0x3bba4c, 0x18)
0043877a        int32_t esi_2 = *(arg1 + 0x34)
0043877d        int32_t ecx_4 = *(arg1 + 0x28)
00438780        *(arg1 + 0xfd2b30) = eax_2
00438789        *(arg1 + 0xfd2b60) = *(arg1 + 0x2c)
0043878f        int32_t eax_4 = *(arg1 + 0x30)
00438792        *(arg1 + 0xfd2b44) = esi_2
00438798        int32_t esi_3 = *(arg1 + 0x125ffd8)
0043879e        *(arg1 + 0xfd2b58) = eax_4
004387a4        result = *(arg1 + 0x40)
004387a7        *(arg1 + 0xff25c0) = esi_3
004387ad        int32_t esi_4 = *(arg1 + 0x125ffdc)
004387b9        *(arg1 + 0xfd2b5c) = ecx_4
004387bf        int32_t ecx_5 = *(arg1 + 0x3bba68)
004387c5        *(arg1 + 0xff25c4) = esi_4
004387ce        *(arg1 + 0xfd2b10) = 1
004387d1        *(arg1 + 0xfd2b34) = ecx_5
004387d7        *(arg1 + 0xfd2b3c) = result
004387e2        if (result != 1 || ecx_5 != 0)
004387e4        ecx_5.b = *(arg1 + 0xff25d0)
004387f2        if (ecx_5.b == 0 && arg2 == 1)
004387f7        if (result == 0)
00438839        return add_arcade_high_score(arg1 + 0x68b4c8, arg1 + 0xfd2b10, *(arg1 + 0x44))
004387f9        void* eax_6 = result - 1
004387fa        if (result == 1)
0043882b        return add_survival_high_score(arg1 + 0x68b4c8, arg1 + 0xfd2b10)
004387fc        result = eax_6 - 3
004387ff        if (eax_6 == 3)
00438801        ecx_5.b = *(arg1 + 0x3bbba4)
0043881a        return add_time_trial_high_score(arg1 + 0x68b4c8, arg1 + 0xfd2b10, *(arg1 + 0x44), ecx_5.b)
00438840        return result
