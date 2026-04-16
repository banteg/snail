/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: border_input_text_init @ 0x403410 */

00403423        arg1->__offset(0x70c).d = arg4
0040342a        sub_44e5b0(arg1 + 0x6cc, arg3)
00403431        char* eax = arg1 + 0x2cc
00403437        arg1->__offset(0x6fc).d = 0
0040343d        arg1->__offset(0x710).d = 0
0040344a        if (*eax != 0)
0040346b        int32_t edx_4
00403452        eax = &eax[1]
00403454        arg1->__offset(0x710).d += 1
00403461        arg1->__offset(0x6fc).d += 1
00403467        edx_4.b = *eax
0040346b        do while (edx_4.b != 0)
00403473        *(arg1->__offset(0x6fc).d + arg1 + 0x2cc) = 0x7c
00403481        *(arg1->__offset(0x6fc).d + arg1 + 0x2cd) = 0
00403488        arg1->__offset(0x704).d = 0
00403492        arg1->__offset(0x700).d = 1
0040349c        arg1->__offset(0x714).d = arg2
004034a4        arg1->__offset(0x708).d = 0x3daaaaab
004034ae        int32_t result = layout_frontend_widget(arg1)
004034b6        if ((arg4.b & 0xc) == 0)
004034c5        return result
004034be        return initialize_input_ok(arg1 + 0x2a8)
