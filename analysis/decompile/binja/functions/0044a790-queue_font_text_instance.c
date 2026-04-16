/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: queue_font_text_instance @ 0x44a790 */

0044a790        int32_t eax
0044a790        eax.b = data_4b7236
0044a797        if (eax.b != 0)
0044a79d        int32_t ecx_1 = data_777b24
0044a7a9        if (ecx_1 != 0x400)
0044a7be        int32_t eax_4 = ecx_1 * 0x84
0044a7c5        *(eax_4 + &data_7544e8) = arg8 | 1
0044a7cf        *(eax_4 + 0x754524) = arg2
0044a7dd        *(eax_4 + 0x754528) = arg3
0044a7e7        *(eax_4 + 0x7544ec) = arg4
0044a7f1        *(eax_4 + 0x7544f0) = arg5
0044a7fb        *(eax_4 + 0x754530) = arg6
0044a801        *(eax_4 + 0x754534) = arg7
0044a807        char* ecx_7 = data_7772f0
0044a80e        *(eax_4 + 0x75452c) = ecx_7
0044a81c        *(eax_4 + 0x754554) = *arg9
0044a825        *(eax_4 + 0x754558) = arg9[1]
0044a82b        *(eax_4 + 0x75455c) = arg9[2]
0044a832        *(eax_4 + 0x754560) = arg9[3]
0044a839        *(eax_4 + 0x75451c) = arg10
0044a83f        int32_t edx_5
0044a83f        edx_5.b = arg11
0044a843        *(eax_4 + 0x754520) = edx_5.b
0044a849        char* eax_5 = arg1
0044a851        while (*eax_5 != 0)
0044a861        if (ecx_7 - 0x753ce8 s> 0x7fe)
0044a896        *ecx_7 = 0
0044a89e        int32_t eax_8 = data_7772f0 + 1
0044a89f        data_7772f0 = eax_8
0044a8a4        return eax_8
0044a863        void* edx_7
0044a863        edx_7.b = *eax_5
0044a865        *ecx_7 = edx_7.b
0044a86d        ecx_7 = data_7772f0 + 1
0044a86e        eax_5 = &eax_5[1]
0044a86f        data_7772f0 = ecx_7
0044a87a        *ecx_7 = 0
0044a889        eax = data_777b24 + 1
0044a88a        data_7772f0 += 1
0044a890        data_777b24 = eax
0044a895        return eax
