/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_nuke @ 0x447110 */

00447118        if (*arg1 == 0)
00447123        int32_t* esi_1 = &arg1[6]
0044712f        int32_t i_1 = 0x19
00447134        arg1[3] = fconvert.s(fconvert.t(*(arg1[1] + 0x70)) - fconvert.t(5f))
0044713d        long double x87_r7_3 = fconvert.t(*(data_4df904 + 0x74650))
00447145        arg1[4] = 0
00447148        arg1[5] = 0x3dd67750
0044714f        *arg1 = 1
00447155        arg1[2] = fconvert.s(x87_r7_3 + x87_r7_3)
004471c3        int32_t i
00447170        int32_t* eax_3 = allocate_sprite(&data_790f30, *(arg1[1] + 0x380), 0x83, 0xffffffff, 0xffffffff)
00447175        *esi_1 = eax_3
0044717a        int32_t edx_2
0044717a        edx_2:1.b = eax_3[1]:1.b | 8
0044717d        esi_1 = &esi_1[1]
00447180        eax_3[1] = edx_2
0044718b        *(esi_1[-1] + 0x68) = 0
00447191        *(esi_1[-1] + 0x6c) = 0
00447197        *(esi_1[-1] + 0x60) = 0x40400000
0044719d        *(esi_1[-1] + 0x64) = 0x40400000
004471a3        int32_t* eax_5 = esi_1[-1] + 0x54
004471a6        eax_5[2] = 0
004471a9        eax_5[1] = 0
004471ac        *eax_5 = 0
004471b1        int32_t* eax_7 = esi_1[-1] + 0x48
004471b4        i = i_1
004471b4        i_1 -= 1
004471b5        eax_7[2] = 0
004471b8        eax_7[1] = 0
004471bb        *eax_7 = 0
004471c0        *(esi_1[-1] + 0x78) = 0
004471c3        do while (i != 1)
004471d0        return update_nuke(arg1)
