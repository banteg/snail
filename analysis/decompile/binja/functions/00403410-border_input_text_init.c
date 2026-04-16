/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: border_input_text_init @ 0x403410 */

00403423        arg1->_pad_6f8[0x10] = arg4.b
00403423        arg1->_pad_6f8[0x11] = arg4:1.b
00403423        arg1->_pad_6f8[0x12] = arg4:2.b
00403423        arg1->_pad_6f8[0x13] = arg4:3.b
0040342a        sub_44e5b0(&arg1->text_buffer.raw[0x400], arg3)
00403431        char* eax = &arg1->text_buffer
00403437        arg1->_pad_6f8[0] = 0
00403437        arg1->_pad_6f8[1] = 0
00403437        arg1->_pad_6f8[2] = 0
00403437        arg1->_pad_6f8[3] = 0
0040343d        arg1->_pad_6f8[0x14] = 0
0040343d        arg1->_pad_6f8[0x15] = 0
0040343d        arg1->_pad_6f8[0x16] = 0
0040343d        arg1->_pad_6f8[0x17] = 0
0040344a        if (*eax != 0)
0040346b        int32_t edx_4
00403452        eax = &eax[1]
00403453        int32_t edx_2 = arg1->_pad_6f8[0x14].d + 1
00403454        arg1->_pad_6f8[0x14] = edx_2.b
00403454        arg1->_pad_6f8[0x15] = edx_2:1.b
00403454        arg1->_pad_6f8[0x16] = edx_2:2.b
00403454        arg1->_pad_6f8[0x17] = edx_2:3.b
00403460        edx_4 = arg1->_pad_6f8[0].d + 1
00403461        arg1->_pad_6f8[0] = edx_4.b
00403461        arg1->_pad_6f8[1] = edx_4:1.b
00403461        arg1->_pad_6f8[2] = edx_4:2.b
00403461        arg1->_pad_6f8[3] = edx_4:3.b
00403467        edx_4.b = *eax
0040346b        do while (edx_4.b != 0)
00403473        arg1->text_buffer.raw[arg1->_pad_6f8[0].d] = 0x7c
00403481        arg1->text_buffer.raw[1 + arg1->_pad_6f8[0].d] = 0
00403488        arg1->_pad_6f8[8] = 0
00403488        arg1->_pad_6f8[9] = 0
00403488        arg1->_pad_6f8[0xa] = 0
00403488        arg1->_pad_6f8[0xb] = 0
00403492        arg1->_pad_6f8[4] = 1
00403492        arg1->_pad_6f8[5] = 0
00403492        arg1->_pad_6f8[6] = 0
00403492        arg1->_pad_6f8[7] = 0
0040349c        arg1->_pad_6f8[0x18] = arg2.b
0040349c        arg1->_pad_6f8[0x19] = arg2:1.b
0040349c        arg1->_pad_6f8[0x1a] = arg2:2.b
0040349c        arg1->_pad_6f8[0x1b] = arg2:3.b
004034a4        arg1->_pad_6f8[0xc] = 0xab
004034a4        arg1->_pad_6f8[0xd] = 0xaa
004034a4        arg1->_pad_6f8[0xe] = 0xaa
004034a4        arg1->_pad_6f8[0xf] = 0x3d
004034ae        int32_t result = layout_frontend_widget(arg1)
004034b6        if ((arg4.b & 0xc) == 0)
004034c5        return result
004034be        return initialize_input_ok(&arg1->tooltip._pad_1c)
