/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: emit_ring_star_shower @ 0x43e690 */

0043e690        int32_t result
0043e690        result.b = data_4df934
0043e69d        if ((result.b & 0x10) != 0)
0043e6ca        int32_t* eax_2
0043e6ca        int32_t ecx_1
0043e6ca        eax_2, ecx_1 = allocate_sprite(&data_790f30, *(arg2 + 0x380), *(arg1[1] + 0x1ec), 0xffffffff, 0xffffffff)
0043e6d1        int32_t var_24_1 = ecx_1
0043e6d2        int32_t eax_3 = eax_2[1]
0043e6d5        eax_2[0x1a] = 0
0043e6dc        eax_3:1.b |= 8
0043e6df        eax_2[0x1b] = 0x3de38e38
0043e6e6        eax_2[1] = eax_3
0043e6e9        eax_2[0x18] = 0x3ecccccd
0043e6f0        eax_2[0x19] = 0x3e4ccccd
0043e70b        float var_c_1 = fconvert.s(sine(fconvert.s(fconvert.t(arg1[5]) + fconvert.t(1.04719758f))) * fconvert.t(arg1[7]))
0043e73b        long double x87_r7_9 = cosine(fconvert.s(fconvert.t(arg1[5]) + fconvert.t(1.04719758f))) * fconvert.t(arg1[7]) * fconvert.t(0.300000012f)
0043e741        eax_2[0x15] = fconvert.s(fconvert.t(var_c_1) * fconvert.t(0.300000012f))
0043e74f        eax_2[0x16] = fconvert.s(x87_r7_9)
0043e752        eax_2[0x17] = 0
0043e757        int32_t* eax_6 = *arg1 + 0x48
0043e75f        eax_2[0x12] = *eax_6
0043e764        eax_2[0x13] = eax_6[1]
0043e767        result = eax_6[2]
0043e76a        eax_2[0x1e] = 0
0043e771        eax_2[0x14] = result
0043e779        return result
