/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: border_input_text @ 0x4035b0 */

004035b5        char eax = read_repeating_text_input_key_code()
004035bc        uint32_t input_flags = widget->input_flags
004035c4        if ((input_flags.b & 0xc) == 0)
004035e4        label_4035e4:
004035f7        if (eax != 5 && (widget->widget_flags & 0x8000000) == 0)
00403601        if (eax == 6)
00403603        uint8_t input_flags_1 = (widget->input_flags).b
0040360b        char* eax_2
0040360b        char i_16
0040360b        if ((input_flags_1 & 1) != 0)
00403a04        label_403a04:
00403a14        if (widget->input_length s< widget->input_capacity && (eax != 0x20 || (widget->input_flags.b & 1) == 0))
00403a1d        if ((widget->input_flags.b & 2) == 0)
00403a2f        label_403a2f:
00403a2f        widget->text_buffer.raw[widget->input_cursor] = eax
00403a3c        int32_t ebx_4 = widget->input_cursor + 1
00403a3f        widget->input_cursor = ebx_4
00403a45        char i_18 = 0x20
00403a47        char i = widget->text_buffer.raw[ebx_4]
00403a4e        eax_2 = &widget->text_buffer.raw[ebx_4]
00403a57        i_16 = 0x20
00403a59        while (i != 0)
00403a5b        *eax_2 = i_18
00403a5d        eax_2 = &eax_2[1]
00403a5e        i_16 = i
00403a60        i = *eax_2
00403a62        i_18 = i_16
00403a59        goto label_403a68
00403a27        if (eax != 0x2c && eax != 0x2e)
00403a27        goto label_403a2f
00403613        if ((input_flags_1 & 2) == 0)
0040361f        widget->text_buffer.raw[widget->input_cursor] = 0x3e
0040362d        int32_t ebx_2 = widget->input_cursor + 1
00403630        widget->input_cursor = ebx_2
00403636        char i_17 = 0x20
00403638        char i_1 = widget->text_buffer.raw[ebx_2]
0040363f        eax_2 = &widget->text_buffer.raw[ebx_2]
00403648        i_16 = 0x20
0040364a        while (i_1 != 0)
00403650        *eax_2 = i_17
00403652        eax_2 = &eax_2[1]
00403653        i_16 = i_1
00403655        i_1 = *eax_2
00403657        i_17 = i_16
00403a68        label_403a68:
00403a68        *eax_2 = i_16
00403a6a        eax_2[1] = 0
00403a75        widget->input_length += 1
00403665        if (eax == 3)
00403667        int32_t input_cursor = widget->input_cursor
0040366f        if (input_cursor s> 0)
00403675        char edx_1 = widget->text_buffer.raw[input_cursor]
0040368a        widget->text_buffer.raw[input_cursor] = widget->tooltip._pad_3c[3 + input_cursor]
00403691        widget->tooltip._pad_3c[3 + input_cursor] = edx_1
0040369a        widget->input_cursor -= 1
004036a8        if (eax == 4)
004036aa        int32_t input_cursor_1 = widget->input_cursor
004036b8        if (input_cursor_1 s< widget->input_length)
004036be        char edx_2 = widget->text_buffer.raw[input_cursor_1]
004036d3        widget->text_buffer.raw[input_cursor_1] = widget->text_buffer.raw[1 + input_cursor_1]
004036da        widget->text_buffer.raw[1 + input_cursor_1] = edx_2
004036e3        widget->input_cursor += 1
004036f1        if (eax == 7)
004036f7        int32_t input_cursor_2 = widget->input_cursor
004036fd        int32_t edi_1 = 0xffffffff
00403704        if (input_cursor_2 s> 0)
0040370d        while (widget->text_buffer.raw[input_cursor_2] != 0x3e)
0040370f        edi_1 += 1
00403710        input_cursor_2 -= 1
00403713        if (input_cursor_2 s<= 0)
00403713        break
0040371c        if (widget->text_buffer.raw[input_cursor_2] == 0x3e)
0040371e        input_cursor_2 -= 1
00403721        if (input_cursor_2 != 0)
00403727        int32_t ecx_6 = 0
0040372b        if (input_cursor_2 s> 0)
00403734        while (widget->text_buffer.raw[input_cursor_2] != 0x3e)
00403736        ecx_6 += 1
00403737        input_cursor_2 -= 1
0040373a        if (input_cursor_2 s<= 0)
0040373a        break
00403743        if (widget->text_buffer.raw[input_cursor_2] == 0x3e)
00403745        input_cursor_2 += 1
00403748        if (edi_1 s> ecx_6)
0040374a        edi_1 = ecx_6
0040374c        int32_t input_cursor_12 = widget->input_cursor
00403752        char* ecx_7 = &widget->text_buffer.raw[input_cursor_12]
00403762        char i_2
00403762        if (widget->text_buffer.raw[input_cursor_12] != 0)
00403767        *ecx_7 = ecx_7[1]
00403769        i_2 = ecx_7[1]
0040376c        ecx_7 = &ecx_7[1]
0040376f        do while (i_2 != 0)
00403771        int32_t eax_7 = input_cursor_2 + edi_1
00403773        widget->input_cursor = eax_7
00403779        char i_13 = widget->text_buffer.raw[eax_7]
00403780        char* eax_8 = &widget->text_buffer.raw[eax_7]
00403787        i_2 = eax_8[1]
0040378a        eax_8[1] = i_13
0040378d        eax_8 = &eax_8[1]
0040378e        i_13 = i_2
00403793        do while (*eax_8 != 0)
0040379d        if (eax == 8)
004037a3        int32_t input_cursor_3 = widget->input_cursor
004037a9        int32_t ebp_1 = 0
004037af        if (input_cursor_3 s> 0)
004037b8        while (widget->text_buffer.raw[input_cursor_3] != 0x3e)
004037ba        ebp_1 += 1
004037bb        input_cursor_3 -= 1
004037be        if (input_cursor_3 s<= 0)
004037be        break
004037c7        if (widget->text_buffer.raw[input_cursor_3] == 0x3e)
004037c9        input_cursor_3 += 1
004037ca        ebp_1 -= 1
004037d2        int32_t input_cursor_14 = input_cursor_3
004037d6        if (widget->text_buffer.raw[input_cursor_3] != 0)
004037d8        char i_3 = widget->text_buffer.raw[input_cursor_3]
004037e1        while (i_3 != 0x3e)
004037e3        i_3 = widget->text_buffer.raw[1 + input_cursor_14]
004037ea        input_cursor_14 += 1
004037ed        if (i_3 == 0)
004037ed        break
004037f6        if (widget->text_buffer.raw[input_cursor_14] == 0x3e)
004037fd        int32_t eax_9 = 0
004037ff        char i_4 = widget->text_buffer.raw[1 + input_cursor_14]
0040380f        if (i_4 != 0)
00403813        while (i_4 != 0x3e)
00403815        i_4 = widget->text_buffer.raw[1 + input_cursor_14 + eax_9 + 1]
00403819        eax_9 += 1
0040381c        if (i_4 == 0)
0040381c        break
00403820        if (ebp_1 s> eax_9)
00403822        ebp_1 = eax_9
00403824        int32_t input_cursor_4 = widget->input_cursor
0040382a        char* ecx_8 = &widget->text_buffer.raw[input_cursor_4]
0040383a        if (widget->text_buffer.raw[input_cursor_4] != 0)
00403847        char i_5
0040383f        *ecx_8 = ecx_8[1]
00403841        i_5 = ecx_8[1]
00403844        ecx_8 = &ecx_8[1]
00403847        do while (i_5 != 0)
0040384d        widget->input_cursor = input_cursor_14 + 1 + ebp_1 - 1
00403853        char ecx_9 = widget->text_buffer.raw[input_cursor_14 + 1 + ebp_1 - 1]
0040385a        char* eax_11 = &widget->text_buffer.raw[input_cursor_14 + 1 + ebp_1 - 1]
00403861        char edx_4 = eax_11[1]
00403864        eax_11[1] = ecx_9
00403867        eax_11 = &eax_11[1]
00403868        ecx_9 = edx_4
0040386d        do while (*eax_11 != 0)
00403877        if (eax == 9)
00403879        int32_t input_cursor_10 = widget->input_cursor
00403888        if (widget->text_buffer.raw[input_cursor_10] != 0)
0040388a        char i_6 = widget->text_buffer.raw[input_cursor_10]
00403895        while (i_6 != 0x3e)
00403897        i_6 = widget->text_buffer.raw[1 + input_cursor_10]
0040389e        input_cursor_10 += 1
004038a1        if (i_6 == 0)
004038a1        break
004038a3        int32_t input_cursor_13 = widget->input_cursor
004038a9        char* eax_12 = &widget->text_buffer.raw[input_cursor_13]
004038b9        char i_7
004038b9        if (widget->text_buffer.raw[input_cursor_13] != 0)
004038be        *eax_12 = eax_12[1]
004038c0        i_7 = eax_12[1]
004038c3        eax_12 = &eax_12[1]
004038c6        do while (i_7 != 0)
004038cb        widget->input_cursor = input_cursor_10 - 1
004038d1        char i_14 = widget->text_buffer.raw[input_cursor_10 - 1]
004038d8        char* eax_14 = &widget->text_buffer.raw[input_cursor_10 - 1]
004038df        i_7 = eax_14[1]
004038e2        eax_14[1] = i_14
004038e5        eax_14 = &eax_14[1]
004038e6        i_14 = i_7
004038eb        do while (*eax_14 != 0)
004038f5        if (eax == 0xa)
004038f7        int32_t input_cursor_5 = widget->input_cursor
00403901        if (input_cursor_5 s> 0)
0040390a        while (widget->text_buffer.raw[input_cursor_5] != 0x3e)
0040390c        input_cursor_5 -= 1
0040390f        if (input_cursor_5 s<= 0)
0040390f        break
00403918        if (widget->text_buffer.raw[input_cursor_5] == 0x3e)
0040391a        input_cursor_5 += 1
0040391b        int32_t input_cursor_11 = widget->input_cursor
00403928        char* ecx_10 = &widget->text_buffer.raw[input_cursor_11]
00403931        char i_8
00403931        if (widget->text_buffer.raw[input_cursor_11] != 0)
00403936        *ecx_10 = ecx_10[1]
00403938        i_8 = ecx_10[1]
0040393b        ecx_10 = &ecx_10[1]
0040393e        do while (i_8 != 0)
00403940        widget->input_cursor = input_cursor_5
00403946        char i_15 = widget->text_buffer.raw[input_cursor_5]
0040394d        char* eax_15 = &widget->text_buffer.raw[input_cursor_5]
00403954        i_8 = eax_15[1]
00403957        eax_15[1] = i_15
0040395a        eax_15 = &eax_15[1]
0040395b        i_15 = i_8
00403960        do while (*eax_15 != 0)
0040396a        if (eax == 1)
0040396c        int32_t input_cursor_6 = widget->input_cursor
00403974        if (input_cursor_6 s> 0)
0040397b        widget->input_cursor = input_cursor_6 - 1
00403988        char* eax_17 = &widget->text_buffer.raw[input_cursor_6 - 1]
00403991        if (widget->text_buffer.raw[input_cursor_6 - 1] != 0)
0040399e        char i_9
00403996        *eax_17 = eax_17[1]
00403998        i_9 = eax_17[1]
0040399b        eax_17 = &eax_17[1]
0040399e        do while (i_9 != 0)
00403a75        widget->input_length -= 1
004039af        if (eax == 2)
004039b1        int32_t input_cursor_7 = widget->input_cursor
004039bf        if (input_cursor_7 s< widget->input_length)
004039cc        char* eax_20 = &widget->text_buffer.raw[input_cursor_7]
004039d5        if (widget->text_buffer.raw[input_cursor_7] != 0)
004039e2        char i_10
004039da        *eax_20 = eax_20[1]
004039dc        i_10 = eax_20[1]
004039df        eax_20 = &eax_20[1]
004039e2        do while (i_10 != 0)
00403a75        widget->input_length -= 1
004039f2        if (eax != 0)
004039f2        goto label_403a04
00403a84        if ((widget->input_flags.b & 2) != 0)
00403a8c        int32_t ecx_14 = 0
00403a90        if (widget->text_buffer.raw[0] != 0)
00403ae7        char i_11
00403a92        char j = widget->text_buffer.raw[ecx_14]
00403a99        char* input_cursor_8 = &widget->text_buffer.raw[ecx_14]
00403aab        if (j != 0x20 && ecx_14 != widget->input_cursor)
00403aab        break
00403ab3        if (ecx_14 != widget->input_cursor)
00403ab7        while (j != 0)
00403abc        *input_cursor_8 = input_cursor_8[1]
00403abe        j = input_cursor_8[1]
00403ac1        input_cursor_8 = &input_cursor_8[1]
00403ac6        input_cursor_8 = widget->input_cursor
00403ace        if (ecx_14 s<= input_cursor_8)
00403ad1        widget->input_cursor = input_cursor_8 - 1
00403ad7        widget->input_length -= 1
00403add        i_11 = widget->text_buffer.raw[1 + ecx_14]
00403ae4        ecx_14 += 1
00403ae7        do while (i_11 != 0)
00403aef        long double x87_r7_1 = fconvert.t(widget->input_cursor_blink_step) + fconvert.t(widget->input_cursor_blink_progress)
00403af5        widget->input_cursor_blink_progress = fconvert.s(x87_r7_1)
00403afb        long double temp0 = fconvert.t(1f)
00403afb        x87_r7_1 - temp0
00403b06        if ((((x87_r7_1 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0) ? 1 : 0) << 0xa | (x87_r7_1 == temp0 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00403b0e        int32_t eax_27 = 0
00403b12        eax_27.b = widget->input_cursor_visible == 0
00403b15        widget->input_cursor_blink_progress = 0f
00403b1f        widget->input_cursor_visible = eax_27
00403b2c        if (widget->input_cursor_visible != 1)
00403b4f        widget->text_buffer.raw[widget->input_cursor] = 0x20
00403b57        layout_frontend_widget(widget)
00403b5f        return
00403b34        widget->text_buffer.raw[widget->input_cursor] = 0x7c
00403b3e        layout_frontend_widget(widget)
00403b46        return
004035cc        update_input_ok(&widget->tooltip._pad_1c)
004035d1        input_flags.b = widget->tooltip._pad_3c[0]
004035d1        input_flags:1.b = widget->tooltip._pad_3c[1]
004035d1        input_flags:2.b = widget->tooltip._pad_3c[2]
004035d1        input_flags:3.b = widget->tooltip._pad_3c[3]
004035de        if ((*(input_flags + 0x1a0) & 0x20) == 0)
004035de        goto label_4035e4
00403b60        int32_t input_cursor_9 = widget->input_cursor
00403b6d        char* eax_28 = &widget->text_buffer.raw[input_cursor_9]
00403b76        if (widget->text_buffer.raw[input_cursor_9] != 0)
00403b83        char i_12
00403b7b        *eax_28 = eax_28[1]
00403b7d        i_12 = eax_28[1]
00403b80        eax_28 = &eax_28[1]
00403b83        do while (i_12 != 0)
00403b85        enum FrontendWidgetFlag widget_flags = widget->widget_flags
00403b97        widget_flags:1.b &= 0xdf
00403b9a        enum FrontendWidgetFlag widget_flags_1 = widget_flags
00403b9c        int32_t edi_4 = widget->input_length - 1
00403b9d        widget_flags_1:1.b |= 0x40
00403ba0        widget->widget_flags = widget_flags
00403ba8        widget->input_length = edi_4
00403bae        widget->widget_flags = widget_flags_1
00403bb4        layout_frontend_widget(widget)
00403bc0        if ((widget->input_flags.b & 0xc) == 0)
00403bc0        return
00403bc2        g_game_base
00403bc7        uint8_t edx_7[0x4]
00403bc7        edx_7[0] = widget->tooltip._pad_3c[0]
00403bc7        edx_7[1] = widget->tooltip._pad_3c[1]
00403bc7        edx_7[2] = widget->tooltip._pad_3c[2]
00403bc7        edx_7[3] = widget->tooltip._pad_3c[3]
00403bd4        kill_border(edx_7)
00403bdc        return
