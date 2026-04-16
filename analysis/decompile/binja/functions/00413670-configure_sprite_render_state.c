/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: configure_sprite_render_state @ 0x413670 */

00413674        int32_t result = *(arg1 + 0x28)
0041367a        if (result u<= 0xd)
00413682        int32_t ecx_1
00413682        ecx_1.b = lookup_table_4137d4[result]
00413688        switch (ecx_1)
004136a2        case 0
004136a2        int32_t* eax_2 = data_502fec
004136ae        (*(*eax_2 + 0xc8))(eax_2, 0x1b, 1)
004136b4        int32_t* eax_3 = data_502fec
004136c0        (*(*eax_3 + 0xc8))(eax_3, 0x13, 5)
004136c6        int32_t* eax_4 = data_502fec
004136d8        return (*(*eax_4 + 0xc8))(eax_4, 0x14, 6)
004136d9        case 1
004136d9        int32_t* eax_6 = data_502fec
004136e5        (*(*eax_6 + 0xc8))(eax_6, 0x1b, 1)
004136eb        int32_t* eax_7 = data_502fec
004136f7        (*(*eax_7 + 0xc8))(eax_7, 0x13, 1)
004136fd        int32_t* eax_8 = data_502fec
0041370f        return (*(*eax_8 + 0xc8))(eax_8, 0x14, 6)
0041368f        case 2
0041368f        int32_t* eax = data_502fec
004136a1        return (*(*eax + 0xc8))(eax, 0x1b, 0)
00413710        case 3
00413710        int32_t* eax_10 = data_502fec
0041371c        (*(*eax_10 + 0xc8))(eax_10, 0x1b, 1)
00413722        int32_t* eax_11 = data_502fec
0041372e        (*(*eax_11 + 0xc8))(eax_11, 0x13, 5)
00413734        int32_t* eax_12 = data_502fec
00413746        return (*(*eax_12 + 0xc8))(eax_12, 0x14, 2)
00413747        case 4
00413747        int32_t* eax_14 = data_502fec
00413753        (*(*eax_14 + 0xc8))(eax_14, 0x1b, 1)
00413759        int32_t* eax_15 = data_502fec
00413765        (*(*eax_15 + 0xc8))(eax_15, 0x13, 5)
0041376b        int32_t* eax_16 = data_502fec
0041377d        return (*(*eax_16 + 0xc8))(eax_16, 0x14, 2)
0041377e        case 5
0041377e        int32_t* eax_18 = data_502fec
0041378a        (*(*eax_18 + 0xc8))(eax_18, 0x1b, 1)
00413790        int32_t* eax_19 = data_502fec
0041379c        (*(*eax_19 + 0xc8))(eax_19, 0x13, 5)
004137a2        int32_t* eax_20 = data_502fec
004137ae        return (*(*eax_20 + 0xc8))(eax_20, 0x14, 3)
004137b4        return result
