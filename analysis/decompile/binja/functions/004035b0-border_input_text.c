/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: border_input_text @ 0x4035b0 */

004035b5        char eax
004035b5        char* edx
004035b5        eax, edx = read_repeating_text_input_key_code()
004035ba        int32_t ebx
004035ba        ebx.b = eax
004035bc        char* eax_1 = arg1->_pad_6fc[0x10].d
004035c4        if ((eax_1.b & 0xc) != 0)
004035cc        update_input_ok(&arg1->tooltip._pad_1c)
004035f7        char i
004035f7        if (((eax_1.b & 0xc) != 0 && (arg1->tooltip._pad_3c[0x1a0] & 0x20) != 0) || ebx.b == 5 || (arg1->widget_flags & 0x8000000) != 0)
00403b60        int32_t eax_23 = arg1->_pad_6fc[0].d
00403b6d        char* eax_24 = &arg1->text_buffer.raw[eax_23]
00403b76        if (arg1->text_buffer.raw[eax_23] != 0)
00403b7b        *eax_24 = eax_24[1]
00403b7d        i = eax_24[1]
00403b80        eax_24 = &eax_24[1]
00403b83        do while (i != 0)
00403b97        uint32_t edx_2
00403b97        edx_2:1.b = arg1->widget_flags:1.b & 0xdf
00403b9c        int32_t edi_4 = arg1->_pad_6fc[0x14].d - 1
00403b9d        uint32_t eax_25
00403b9d        eax_25:1.b = edx_2:1.b | 0x40
00403ba0        arg1->widget_flags = edx_2
00403ba8        arg1->_pad_6fc[0x14] = edi_4.b
00403ba8        arg1->_pad_6fc[0x15] = edi_4:1.b
00403ba8        arg1->_pad_6fc[0x16] = edi_4:2.b
00403ba8        arg1->_pad_6fc[0x17] = edi_4:3.b
00403bae        arg1->widget_flags = eax_25
00403bb4        int32_t result = layout_frontend_widget(arg1)
00403bc0        if ((arg1->_pad_6fc[0x10] & 0xc) == 0)
00403bdc        return result
00403bc2        data_4df904
00403bd4        return kill_border(arg1->tooltip._pad_3c)
00403601        if (ebx.b == 6)
00403603        eax_1 = arg1->_pad_6fc[0x10].d
0040360b        char* eax_3
0040360b        if ((eax_1.b & 1) != 0)
00403a04        label_403a04:
00403a14        if (arg1->_pad_6fc[0x14].d s< arg1->_pad_6fc[0x18].d && (ebx.b != 0x20 || (arg1->_pad_6fc[0x10] & 1) == 0))
00403a1d        if ((arg1->_pad_6fc[0x10] & 2) == 0)
00403a2f        label_403a2f:
00403a2f        arg1->text_buffer.raw[arg1->_pad_6fc[0].d] = ebx.b
00403a3c        int32_t ebx_4 = arg1->_pad_6fc[0].d + 1
00403a3d        int32_t eax_18 = ebx_4
00403a3f        arg1->_pad_6fc[0] = ebx_4.b
00403a3f        arg1->_pad_6fc[1] = ebx_4:1.b
00403a3f        arg1->_pad_6fc[2] = ebx_4:2.b
00403a3f        arg1->_pad_6fc[3] = ebx_4:3.b
00403a45        ebx_4.b = 0x20
00403a47        int32_t ecx_13
00403a47        ecx_13.b = arg1->text_buffer.raw[eax_18]
00403a4e        eax_3 = &arg1->text_buffer.raw[eax_18]
00403a57        edx.b = 0x20
00403a59        while (ecx_13.b != 0)
00403a5b        *eax_3 = ebx_4.b
00403a5d        eax_3 = &eax_3[1]
00403a5e        edx.b = ecx_13.b
00403a60        ecx_13.b = *eax_3
00403a62        ebx_4.b = edx.b
00403a59        goto label_403a68
00403a27        if (ebx.b != 0x2c && ebx.b != 0x2e)
00403a27        goto label_403a2f
00403613        if ((eax_1.b & 2) == 0)
0040361f        arg1->text_buffer.raw[arg1->_pad_6fc[0].d] = 0x3e
0040362d        int32_t ebx_2 = arg1->_pad_6fc[0].d + 1
0040362e        int32_t eax_2 = ebx_2
00403630        arg1->_pad_6fc[0] = ebx_2.b
00403630        arg1->_pad_6fc[1] = ebx_2:1.b
00403630        arg1->_pad_6fc[2] = ebx_2:2.b
00403630        arg1->_pad_6fc[3] = ebx_2:3.b
00403636        ebx_2.b = 0x20
00403638        int32_t ecx_1
00403638        ecx_1.b = arg1->text_buffer.raw[eax_2]
0040363f        eax_3 = &arg1->text_buffer.raw[eax_2]
00403648        edx.b = 0x20
0040364a        while (ecx_1.b != 0)
00403650        *eax_3 = ebx_2.b
00403652        eax_3 = &eax_3[1]
00403653        edx.b = ecx_1.b
00403655        ecx_1.b = *eax_3
00403657        ebx_2.b = edx.b
00403a68        label_403a68:
00403a68        *eax_3 = edx.b
00403a6a        eax_3[1] = 0
00403a74        eax_1 = arg1->_pad_6fc[0x14].d + 1
00403a75        label_403a75:
00403a75        arg1->_pad_6fc[0x14] = eax_1.b
00403a75        arg1->_pad_6fc[0x15] = eax_1:1.b
00403a75        arg1->_pad_6fc[0x16] = eax_1:2.b
00403a75        arg1->_pad_6fc[0x17] = eax_1:3.b
00403665        if (ebx.b == 3)
00403667        eax_1 = arg1->_pad_6fc[0].d
0040366f        if (eax_1 s> 0)
00403675        edx.b = *(&arg1->text_buffer + eax_1)
0040367c        ebx.b = *(&arg1->tooltip._pad_3c[3] + eax_1)
0040368a        *(&arg1->text_buffer + eax_1) = ebx.b
00403691        *(&arg1->tooltip._pad_3c[3] + eax_1) = edx.b
00403699        eax_1 = arg1->_pad_6fc[0].d - 1
0040369a        arg1->_pad_6fc[0] = eax_1.b
0040369a        arg1->_pad_6fc[1] = eax_1:1.b
0040369a        arg1->_pad_6fc[2] = eax_1:2.b
0040369a        arg1->_pad_6fc[3] = eax_1:3.b
004036a8        if (ebx.b == 4)
004036aa        eax_1 = arg1->_pad_6fc[0].d
004036b8        if (eax_1 s< arg1->_pad_6fc[0x14].d)
004036be        edx.b = *(&arg1->text_buffer + eax_1)
004036c5        ebx.b = *(&arg1->text_buffer.raw[1] + eax_1)
004036d3        *(&arg1->text_buffer + eax_1) = ebx.b
004036da        *(&arg1->text_buffer.raw[1] + eax_1) = edx.b
004036e2        eax_1 = arg1->_pad_6fc[0].d + 1
004036e3        arg1->_pad_6fc[0] = eax_1.b
004036e3        arg1->_pad_6fc[1] = eax_1:1.b
004036e3        arg1->_pad_6fc[2] = eax_1:2.b
004036e3        arg1->_pad_6fc[3] = eax_1:3.b
004036f1        if (ebx.b == 7)
004036f7        eax_1 = arg1->_pad_6fc[0].d
004036fd        int32_t edi_1 = 0xffffffff
00403704        if (eax_1 s> 0)
0040370d        while (*(&arg1->text_buffer + eax_1) != 0x3e)
0040370f        edi_1 += 1
00403710        eax_1 -= 1
00403713        if (eax_1 s<= 0)
00403713        break
0040371c        if (*(&arg1->text_buffer + eax_1) == 0x3e)
0040371e        eax_1 -= 1
00403721        if (eax_1 != 0)
00403727        int32_t ecx_5 = 0
0040372b        if (eax_1 s> 0)
00403734        while (*(&arg1->text_buffer + eax_1) != 0x3e)
00403736        ecx_5 += 1
00403737        eax_1 -= 1
0040373a        if (eax_1 s<= 0)
0040373a        break
00403743        if (*(&arg1->text_buffer + eax_1) == 0x3e)
00403745        eax_1 = &eax_1[1]
00403748        if (edi_1 s> ecx_5)
0040374a        edi_1 = ecx_5
0040374c        edx = arg1->_pad_6fc[0].d
00403752        char* ecx_6 = &arg1->text_buffer + edx
00403759        edx.b = *(&arg1->text_buffer + edx)
00403762        while (edx.b != 0)
00403764        edx.b = ecx_6[1]
00403767        *ecx_6 = edx.b
00403769        edx.b = ecx_6[1]
0040376c        ecx_6 = &ecx_6[1]
00403771        void* eax_6 = &eax_1[edi_1]
00403773        arg1->_pad_6fc[0] = eax_6.b
00403773        arg1->_pad_6fc[1] = eax_6:1.b
00403773        arg1->_pad_6fc[2] = eax_6:2.b
00403773        arg1->_pad_6fc[3] = eax_6:3.b
00403779        ecx_6.b = *(&arg1->text_buffer + eax_6)
00403780        eax_1 = &arg1->text_buffer + eax_6
00403787        edx.b = eax_1[1]
0040378a        eax_1[1] = ecx_6.b
0040378d        eax_1 = &eax_1[1]
0040378e        ecx_6.b = edx.b
00403793        do while (*eax_1 != 0)
0040379d        if (ebx.b == 8)
004037a3        eax_1 = arg1->_pad_6fc[0].d
004037a9        int32_t ebp_1 = 0
004037af        if (eax_1 s> 0)
004037b8        while (*(&arg1->text_buffer + eax_1) != 0x3e)
004037ba        ebp_1 += 1
004037bb        eax_1 -= 1
004037be        if (eax_1 s<= 0)
004037be        break
004037c7        if (*(&arg1->text_buffer + eax_1) == 0x3e)
004037c9        eax_1 = &eax_1[1]
004037ca        ebp_1 -= 1
004037d2        edx = eax_1
004037d6        if (*(&arg1->text_buffer + eax_1) != 0)
004037d8        eax_1.b = *(&arg1->text_buffer + eax_1)
004037e1        while (eax_1.b != 0x3e)
004037e3        eax_1.b = *(&arg1->text_buffer.raw[1] + edx)
004037ea        edx = &edx[1]
004037ed        if (eax_1.b == 0)
004037ed        break
004037f6        if (*(&arg1->text_buffer + edx) == 0x3e)
004037fd        int32_t eax_7 = 0
004037ff        i = *(&arg1->text_buffer.raw[1] + edx)
0040380f        if (i != 0)
00403813        while (i != 0x3e)
00403815        i = *(&arg1->text_buffer.raw[1] + edx + eax_7 + 1)
00403819        eax_7 += 1
0040381c        if (i == 0)
0040381c        break
00403820        if (ebp_1 s> eax_7)
00403822        ebp_1 = eax_7
00403824        int32_t eax_8 = arg1->_pad_6fc[0].d
0040382a        char* ecx_7 = &arg1->text_buffer.raw[eax_8]
00403831        eax_8.b = arg1->text_buffer.raw[eax_8]
0040383a        while (eax_8.b != 0)
0040383c        eax_8.b = ecx_7[1]
0040383f        *ecx_7 = eax_8.b
00403841        eax_8.b = ecx_7[1]
00403844        ecx_7 = &ecx_7[1]
00403849        void* eax_9 = &edx[ebp_1]
0040384d        arg1->_pad_6fc[0] = eax_9.b
0040384d        arg1->_pad_6fc[1] = eax_9:1.b
0040384d        arg1->_pad_6fc[2] = eax_9:2.b
0040384d        arg1->_pad_6fc[3] = eax_9:3.b
00403853        ecx_7.b = *(&arg1->text_buffer + eax_9)
0040385a        eax_1 = &arg1->text_buffer + eax_9
00403861        edx.b = eax_1[1]
00403864        eax_1[1] = ecx_7.b
00403867        eax_1 = &eax_1[1]
00403868        ecx_7.b = edx.b
0040386d        do while (*eax_1 != 0)
00403877        if (ebx.b == 9)
00403879        int32_t ecx_8 = arg1->_pad_6fc[0].d
0040387f        eax_1.b = arg1->text_buffer.raw[ecx_8]
00403888        if (eax_1.b != 0)
0040388a        eax_1.b = arg1->text_buffer.raw[ecx_8]
00403895        while (eax_1.b != 0x3e)
00403897        eax_1.b = arg1->text_buffer.raw[1 + ecx_8]
0040389e        ecx_8 += 1
004038a1        if (eax_1.b == 0)
004038a1        break
004038a3        edx = arg1->_pad_6fc[0].d
004038a9        char* eax_10 = &arg1->text_buffer + edx
004038b0        edx.b = *(&arg1->text_buffer + edx)
004038b9        while (edx.b != 0)
004038bb        edx.b = eax_10[1]
004038be        *eax_10 = edx.b
004038c0        edx.b = eax_10[1]
004038c3        eax_10 = &eax_10[1]
004038c8        int32_t eax_11 = ecx_8 - 1
004038cb        arg1->_pad_6fc[0] = eax_11.b
004038cb        arg1->_pad_6fc[1] = eax_11:1.b
004038cb        arg1->_pad_6fc[2] = eax_11:2.b
004038cb        arg1->_pad_6fc[3] = eax_11:3.b
004038d1        ecx_8.b = arg1->text_buffer.raw[eax_11]
004038d8        eax_1 = &arg1->text_buffer.raw[eax_11]
004038df        edx.b = eax_1[1]
004038e2        eax_1[1] = ecx_8.b
004038e5        eax_1 = &eax_1[1]
004038e6        ecx_8.b = edx.b
004038eb        do while (*eax_1 != 0)
004038f5        if (ebx.b == 0xa)
004038f7        int32_t eax_12 = arg1->_pad_6fc[0].d
00403901        if (eax_12 s> 0)
0040390a        while (arg1->text_buffer.raw[eax_12] != 0x3e)
0040390c        eax_12 -= 1
0040390f        if (eax_12 s<= 0)
0040390f        break
00403918        if (arg1->text_buffer.raw[eax_12] == 0x3e)
0040391a        eax_12 += 1
0040391b        int32_t ecx_9 = arg1->_pad_6fc[0].d
00403921        edx.b = arg1->text_buffer.raw[ecx_9]
00403928        char* ecx_10 = &arg1->text_buffer.raw[ecx_9]
00403931        while (edx.b != 0)
00403933        edx.b = ecx_10[1]
00403936        *ecx_10 = edx.b
00403938        edx.b = ecx_10[1]
0040393b        ecx_10 = &ecx_10[1]
00403940        arg1->_pad_6fc[0] = eax_12.b
00403940        arg1->_pad_6fc[1] = eax_12:1.b
00403940        arg1->_pad_6fc[2] = eax_12:2.b
00403940        arg1->_pad_6fc[3] = eax_12:3.b
00403946        ecx_10.b = arg1->text_buffer.raw[eax_12]
0040394d        eax_1 = &arg1->text_buffer.raw[eax_12]
00403954        edx.b = eax_1[1]
00403957        eax_1[1] = ecx_10.b
0040395a        eax_1 = &eax_1[1]
0040395b        ecx_10.b = edx.b
00403960        do while (*eax_1 != 0)
0040396a        if (ebx.b == 1)
0040396c        eax_1 = arg1->_pad_6fc[0].d
00403974        if (eax_1 s> 0)
0040397b        arg1->_pad_6fc[0] = (eax_1 - 1).b
0040397b        arg1->_pad_6fc[1] = (eax_1 - 1):1.b
0040397b        arg1->_pad_6fc[2] = (eax_1 - 1):2.b
0040397b        arg1->_pad_6fc[3] = (eax_1 - 1):3.b
00403988        char* eax_14 = &arg1->text_buffer + eax_1 - 1
00403991        if (*(&arg1->text_buffer + eax_1 - 1) != 0)
00403996        *eax_14 = eax_14[1]
00403998        i = eax_14[1]
0040399b        eax_14 = &eax_14[1]
0040399e        do while (i != 0)
004039a6        eax_1 = arg1->_pad_6fc[0x14].d - 1
004039a7        goto label_403a75
004039af        if (ebx.b == 2)
004039b1        eax_1 = arg1->_pad_6fc[0].d
004039bf        if (eax_1 s< arg1->_pad_6fc[0x14].d)
004039c5        int32_t ecx_11
004039c5        ecx_11.b = *(&arg1->text_buffer + eax_1)
004039cc        char* eax_16 = &arg1->text_buffer + eax_1
004039d5        while (ecx_11.b != 0)
004039d7        edx.b = eax_16[1]
004039da        *eax_16 = edx.b
004039dc        ecx_11.b = eax_16[1]
004039df        eax_16 = &eax_16[1]
004039ea        eax_1 = arg1->_pad_6fc[0x14].d - 1
004039eb        goto label_403a75
004039f2        if (ebx.b != 0)
004039f2        goto label_403a04
00403a7b        eax_1.b = arg1->_pad_6fc[0x10]
00403a84        if ((eax_1.b & 2) != 0)
00403a86        eax_1.b = arg1->text_buffer.raw[0]
00403a8c        int32_t ecx_14 = 0
00403a90        while (eax_1.b != 0)
00403a92        edx.b = arg1->text_buffer.raw[ecx_14]
00403a99        eax_1 = &arg1->text_buffer.raw[ecx_14]
00403aab        if (edx.b != 0x20 && ecx_14 != arg1->_pad_6fc[0].d)
00403aab        break
00403ab3        if (ecx_14 != arg1->_pad_6fc[0].d)
00403ab7        while (edx.b != 0)
00403ab9        edx.b = eax_1[1]
00403abc        *eax_1 = edx.b
00403abe        edx.b = eax_1[1]
00403ac1        eax_1 = &eax_1[1]
00403ac6        eax_1 = arg1->_pad_6fc[0].d
00403ace        if (ecx_14 s<= eax_1)
00403ad1        arg1->_pad_6fc[0] = (eax_1 - 1).b
00403ad1        arg1->_pad_6fc[1] = (eax_1 - 1):1.b
00403ad1        arg1->_pad_6fc[2] = (eax_1 - 1):2.b
00403ad1        arg1->_pad_6fc[3] = (eax_1 - 1):3.b
00403ad7        arg1->_pad_6fc[0x14].d -= 1
00403add        eax_1.b = arg1->text_buffer.raw[1 + ecx_14]
00403ae4        ecx_14 += 1
00403aef        long double x87_r7_1 = fconvert.t(arg1->_pad_6fc[0xc].d) + fconvert.t(arg1->_pad_6fc[8].d)
00403af5        arg1->_pad_6fc[8].d = fconvert.s(x87_r7_1)
00403afb        long double temp0 = fconvert.t(1f)
00403afb        x87_r7_1 - temp0
00403b01        eax_1.w = (x87_r7_1 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0) ? 1 : 0) << 0xa | (x87_r7_1 == temp0 ? 1 : 0) << 0xe
00403b06        if ((eax_1:1.b & 0x41) == 0)
00403b12        int32_t eax_20
00403b12        eax_20.b = arg1->_pad_6fc[4].d == 0
00403b15        arg1->_pad_6fc[8] = 0
00403b15        arg1->_pad_6fc[9] = 0
00403b15        arg1->_pad_6fc[0xa] = 0
00403b15        arg1->_pad_6fc[0xb] = 0
00403b1f        arg1->_pad_6fc[4] = eax_20.b
00403b1f        arg1->_pad_6fc[5] = eax_20:1.b
00403b1f        arg1->_pad_6fc[6] = eax_20:2.b
00403b1f        arg1->_pad_6fc[7] = eax_20:3.b
00403b2c        if (arg1->_pad_6fc[4].d != 1)
00403b4f        arg1->text_buffer.raw[arg1->_pad_6fc[0].d] = 0x20
00403b5f        return layout_frontend_widget(arg1)
00403b34        arg1->text_buffer.raw[arg1->_pad_6fc[0].d] = 0x7c
00403b46        return layout_frontend_widget(arg1)
