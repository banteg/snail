/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_high_score_tables @ 0x417540 */

00417545        int32_t i = 0
00417547        int32_t* edi = arg1 + 8
0041755a        initialize_high_score_entry(edi, 0, 0, 0x3f800000, 0, 0, i)
0041755f        i += 1
00417560        edi = &edi[0x7eb0]
00417569        do while (i s< 0xb)
0041756b        int32_t i_1 = 0
0041756d        int32_t* edi_1 = arg1 + 0x15c648
00417583        initialize_high_score_entry(edi_1, 0, 0, 0x3f800000, 0, 1, i_1)
00417588        i_1 += 1
00417589        edi_1 = &edi_1[0x7eb0]
00417592        do while (i_1 s< 0xb)
00417594        int32_t i_2 = 0
00417596        int32_t* edi_2 = arg1 + 0x2b8c88
004175ac        initialize_high_score_entry(edi_2, 0, 0, 0x3f800000, 0, 2, i_2)
004175b1        i_2 += 1
004175b2        edi_2 = &edi_2[0x7eb0]
004175bb        do while (i_2 s< 0x33)
004175da        return initialize_high_score_entry(arg1 + 0x9080c8, 0, 0, 0x3f800000, 0, 0, 0)
