/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_loading_screen @ 0x418e80 */

00418e89        int32_t result = *arg1
00418e8e        if (result != 0)
00418e98        arg1[2] += 1
00418e9b        int32_t ecx_2 = data_4df9c4
00418ea3        if (ecx_2 == 0)
00418ea5        ecx_2 = 1
00418eaa        data_4df9c4 = 1
00418ebf        int32_t edi_1 = divs.dp.d(sx.q(arg1[2] * 0x64), ecx_2)
00418ec3        int32_t var_8 = edi_1
00418ec7        if (edi_1 s< 0)
00418ec9        edi_1 = 0
00418ed7        var_8 = edi_1
00418ed0        if (edi_1 s> 0x64)
00418ed2        edi_1 = 0x64
00418ed7        var_8 = edi_1
00418ee0        result = edi_1 - arg1[1]
00418ee5        if (result s>= 1)
00418ef8        float var_4_1 = fconvert.s(float.t(var_8) * fconvert.t(0.920000017f))
00418efc        if (edi_1 s> 0x62)
00418efe        var_4_1 = 100f
00418f06        int32_t* eax_7 = data_502fec
00418f1d        (*(*eax_7 + 0x90))(eax_7, 0, 0, 2, 0xff000000, 0x3f800000, 0)
00418f23        int32_t* eax_8 = data_502fec
00418f2b        (*(*eax_8 + 0x88))(eax_8)
00418f31        int32_t* eax_9 = data_502fec
00418f41        (*(*eax_9 + 0xf4))(eax_9, 0, data_503288)
00418f47        int32_t* eax_10 = data_502fec
00418f54        (*(*eax_10 + 0xfc))(eax_10, 0, 0xd, 3)
00418f5a        int32_t* eax_11 = data_502fec
00418f67        (*(*eax_11 + 0xfc))(eax_11, 0, 0xe, 3)
00418f73        int32_t* eax_12 = data_502fec
00418f82        (*(*eax_12 + 0x14c))(eax_12, 0, *(data_503284 + 8), 0x14)
00418f88        int32_t* eax_13 = data_502fec
00418f95        (*(*eax_13 + 0x130))(eax_13, 0x102)
00418f9b        int32_t* eax_14 = data_502fec
00418fa8        (*(*eax_14 + 0x118))(eax_14, 6, 0, 2)
00418fb9        int32_t* eax_16 = *(data_5032a4 + 8)
00418fc2        (*(*eax_16 + 0x2c))(eax_16, 0, 0x50, &var_8, 0)
00418fcd        *var_8 = 0x43400000
00418fe2        *(var_8 + 4) = 0x43908000
00418fe9        long double x87_r7_5 = fconvert.t(var_4_1) * fconvert.t(2.55999994f) + fconvert.t(192f)
00418fef        *(var_8 + 8) = 0
00418ff6        *(var_8 + 0xc) = 0
00418fff        *(var_8 + 0x10) = 0
00419006        *(var_8 + 0x14) = fconvert.s(x87_r7_5)
00419011        long double x87_r6_3 = fconvert.t(var_4_1) * fconvert.t(0.00999999978f)
00419017        *(var_8 + 0x18) = 0x43908000
0041901e        *(var_8 + 0x1c) = 0
00419025        float var_4_2 = fconvert.s(x87_r6_3)
00419029        *(var_8 + 0x20) = fconvert.s(x87_r6_3)
00419030        *(var_8 + 0x24) = 0
00419037        *(var_8 + 0x28) = fconvert.s(x87_r7_5)
00419047        *(var_8 + 0x2c) = 0x43a08000
0041904e        *(var_8 + 0x30) = 0
00419055        *(var_8 + 0x34) = fconvert.s(fconvert.t(var_4_2))
0041905c        *(var_8 + 0x38) = 0x3f800000
00419067        *(var_8 + 0x3c) = 0x43400000
00419072        *(var_8 + 0x40) = 0x43a08000
00419079        *(var_8 + 0x44) = 0
00419080        *(var_8 + 0x48) = 0
00419087        *(var_8 + 0x4c) = 0x3f800000
00419093        int32_t* eax_22 = *(data_5032a4 + 8)
00419099        (*(*eax_22 + 0x30))(eax_22)
0041909c        int32_t* eax_23 = data_502fec
004190ac        (*(*eax_23 + 0xf4))(eax_23, 0, data_503280)
004190b8        int32_t* eax_24 = data_502fec
004190c7        (*(*eax_24 + 0x14c))(eax_24, 0, *(data_5032a4 + 8), 0x14)
004190cd        int32_t* eax_25 = data_502fec
004190da        (*(*eax_25 + 0x130))(eax_25, 0x102)
004190e0        int32_t* eax_26 = data_502fec
004190ed        (*(*eax_26 + 0x118))(eax_26, 6, 0, 2)
004190f3        int32_t* eax_27 = data_502fec
004190fb        (*(*eax_27 + 0x8c))(eax_27)
00419101        result = sub_413520()
00419106        arg1[1] = edi_1
0041910f        return result
