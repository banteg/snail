/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: submit_sprite_draw_batches @ 0x4126c0 */

004126cb        int32_t result = *(arg1 i+ 0x10)
004126de        if ((result & 0x80000) != 0 && (result & 0x40000) == 0)
004126e4        result = *(arg1 i+ 0x2c)
004126e9        if (result != 0)
004126f0        sub_412250(arg1)
004126f9        int32_t* eax = data_502fec
0041270e        void var_40
0041270e        __builtin_memcpy(&var_40, arg2, 0x40)
00412719        (*(*eax + 0x94))(eax, 0x100, &var_40)
00412726        char var_54_3
00412726        if ((*(arg1 i+ 0x10) & 0x100000) == 0)
0041272c        var_54_3 = 1
00412728        var_54_3 = 0
0041272e        sub_4129f0(var_54_3)
00412739        int32_t i = 0
0041273d        if (*(arg1 i+ 0x64) s> 0)
00412743        int32_t ebx
00412743        ebx.b = arg6
0041274b        int32_t ecx_2
0041274b        ecx_2.b = data_503260
00412753        if (ecx_2.b != 0)
00412789        if (ecx_2.b != 1 || ebx.b != ecx_2.b || (**(*(arg1 i+ 0xd0) + (i << 2)) & 0x10000) != 0)
00412795        label_412795:
00412795        int32_t* eax_5 = *(*(arg1 i+ 0xd0) + (i << 2))
0041279a        if (eax_5 != 0)
004127a4        int32_t* var_54_4
004127a4        if ((*(arg1 i+ 0x10) & 8) == 0)
004127ac        var_54_4 = eax_5
004127a9        var_54_4 = *(arg1 i+ 0x18)
004127ad        sub_414500(var_54_4)
004127ba        if ((*(arg1 i+ 0x10) & 0x80) == 0)
00412801        int32_t* eax_9 = data_502fec
0041280f        (*(*eax_9 + 0xfc))(eax_9, 0, 0x18, 0)
004127ca        int32_t* eax_7 = data_502fec
004127cf        data_5031f8 = arg3
004127d5        int32_t var_54_5 = 0x5031d8
004127da        int32_t var_58_2 = 0x10
004127dd        data_5031fc = fconvert.s(fconvert.t(1f) - fconvert.t(arg4))
004127e5        (*(*eax_7 + 0x94))(eax_7, var_58_2, var_54_5)
004127eb        int32_t* eax_8 = data_502fec
004127f9        (*(*eax_8 + 0xfc))(eax_8, 0, 0x18, 2)
0041282d        if (arg5[3] == 0x3f800000 || (**(*(arg1 i+ 0xd0) + (i << 2)) & 0x10000) == 0)
0041286f        int32_t* eax_12 = data_502fec
0041287b        (*(*eax_12 + 0xc8))(eax_12, 0x1b, 0)
00412833        sub_412d00(*(arg1 i+ 0x14))
00412838        int32_t eax_11 = *(arg1 i+ 0x10)
00412840        if ((eax_11.b & 0x50) != 0)
00412842        eax_11.b &= 0xbf
00412849        *(arg1 i+ 0x10) = eax_11
00412851        int32_t var_60_3 = *arg5
00412856        int32_t var_5c_5 = arg5[1]
0041285c        int32_t var_58_5 = arg5[2]
00412862        int32_t var_54_9 = arg5[3]
00412865        sub_4141d0(arg1)
00412887        int32_t* eax_13 = data_502fec
00412897        (*(*eax_13 + 0x14c))(eax_13, 0, *(*(arg1 i+ 0xc0) + 8), 0x18)
0041289d        int32_t* eax_14 = data_502fec
004128aa        (*(*eax_14 + 0x130))(eax_14, 0x142)
004128b6        int32_t* eax_15 = data_502fec
004128c3        (*(*eax_15 + 0x154))(eax_15, **(arg1 i+ 0xc8), 0)
004128cf        int32_t* eax_16 = data_502fec
004128f0        (*(*eax_16 + 0x11c))(eax_16, 4, 0, *(arg1 i+ 0xc4), *(*(arg1 i+ 0xcc) + (i << 2)), *(*(arg1 i+ 0xd4) + (i << 2)))
0041290c        ecx_2.b = data_503260
00412912        int32_t eax_19 = data_503170 + 1
00412913        data_4f7450 += *(*(arg1 i+ 0xd4) + (i << 2))
00412919        data_503170 = eax_19
00412769        if (ebx.b != 1 || (**(*(arg1 i+ 0xd0) + (i << 2)) & 0x10000) == 0)
00412758        goto label_412795
00412921        i += 1
00412924        do while (i s< *(arg1 i+ 0x64))
00412930        return sub_4123e0(arg1, arg2)
0041293f        return result
