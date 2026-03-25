/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: border_input_text_init @ 0x403410 */

00403423        *(arg1 + 0x70c) = arg4
0040342a        sub_44e5b0(arg1 + 0x6cc, arg3)
00403431        char* eax = arg1 + 0x2cc
00403437        *(arg1 + 0x6fc) = 0
0040343d        *(arg1 + 0x710) = 0
0040344a        if (*eax != 0)
0040346b        int32_t edx_4
00403452        eax = &eax[1]
00403454        *(arg1 + 0x710) += 1
00403461        *(arg1 + 0x6fc) += 1
00403467        edx_4.b = *eax
0040346b        do while (edx_4.b != 0)
00403473        *(*(arg1 + 0x6fc) + arg1 + 0x2cc) = 0x7c
00403481        *(*(arg1 + 0x6fc) + arg1 + 0x2cd) = 0
00403488        *(arg1 + 0x704) = 0
00403492        *(arg1 + 0x700) = 1
0040349c        *(arg1 + 0x714) = arg2
004034a4        *(arg1 + 0x708) = 0x3daaaaab
004034ae        float* result = layout_frontend_widget(arg1)
004034b6        if ((arg4.b & 0xc) == 0)
004034c5        return result
004034be        return initialize_input_ok(arg1 + 0x2a8)
