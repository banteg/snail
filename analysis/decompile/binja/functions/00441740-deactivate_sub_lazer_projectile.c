/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: deactivate_sub_lazer_projectile @ 0x441740 */

00441748        void* ecx = data_4df904 + 0x5a8
0044174e        int16_t eax = (slot->_pad_00[4].d).w
00441754        if ((eax:1.b & 2) == 0)
0044175b        report_errorf("List remove")
00441763        slot->state = 0
0044176e        return 0
00441771        if ((eax.b & 0x40) != 0)
00441778        report_errorf("List remove NEXTBOD")
00441780        slot->state = 0
0044178b        return 0
0044178c        void* eax_1
0044178c        eax_1.b = slot->_pad_00[0xc]
0044178c        eax_1:1.b = slot->_pad_00[0xd]
0044178c        eax_1:2.b = slot->_pad_00[0xe]
0044178c        eax_1:3.b = slot->_pad_00[0xf]
00441791        if (eax_1 != 0)
00441793        int32_t edx
00441793        edx.b = slot->_pad_00[8]
00441793        edx:1.b = slot->_pad_00[9]
00441793        edx:2.b = slot->_pad_00[0xa]
00441793        edx:3.b = slot->_pad_00[0xb]
00441796        *(eax_1 + 8) = edx
00441799        void* eax_2
00441799        eax_2.b = slot->_pad_00[8]
00441799        eax_2:1.b = slot->_pad_00[9]
00441799        eax_2:2.b = slot->_pad_00[0xa]
00441799        eax_2:3.b = slot->_pad_00[0xb]
0044179e        if (eax_2 == 0)
004417a8        int32_t eax_3
004417a8        eax_3.b = slot->_pad_00[0xc]
004417a8        eax_3:1.b = slot->_pad_00[0xd]
004417a8        eax_3:2.b = slot->_pad_00[0xe]
004417a8        eax_3:3.b = slot->_pad_00[0xf]
004417ab        *(ecx + 4) = eax_3.b
004417ab        *(ecx + 5) = eax_3:1.b
004417ab        *(ecx + 6) = eax_3:2.b
004417ab        *(ecx + 7) = eax_3:3.b
004417a0        int32_t edx_1
004417a0        edx_1.b = slot->_pad_00[0xc]
004417a0        edx_1:1.b = slot->_pad_00[0xd]
004417a0        edx_1:2.b = slot->_pad_00[0xe]
004417a0        edx_1:3.b = slot->_pad_00[0xf]
004417a3        *(eax_2 + 0xc) = edx_1
004417ae        int32_t edx_2
004417ae        edx_2.b = *(ecx + 8)
004417ae        edx_2:1.b = *(ecx + 9)
004417ae        edx_2:2.b = *(ecx + 0xa)
004417ae        edx_2:3.b = *(ecx + 0xb)
004417b1        slot->_pad_00[0xc] = edx_2.b
004417b1        slot->_pad_00[0xd] = edx_2:1.b
004417b1        slot->_pad_00[0xe] = edx_2:2.b
004417b1        slot->_pad_00[0xf] = edx_2:3.b
004417b4        *(ecx + 8) = slot.b
004417b4        *(ecx + 9) = slot:1.b
004417b4        *(ecx + 0xa) = slot:2.b
004417b4        *(ecx + 0xb) = slot:3.b
004417b7        int32_t result
004417b7        result.b = slot->_pad_00[4]
004417b7        result:1.b = slot->_pad_00[5]
004417b7        result:2.b = slot->_pad_00[6]
004417b7        result:3.b = slot->_pad_00[7]
004417ba        slot->state = 0
004417c4        result:1.b &= 0xfd
004417c7        slot->_pad_00[4] = result.b
004417c7        slot->_pad_00[5] = result:1.b
004417c7        slot->_pad_00[6] = result:2.b
004417c7        slot->_pad_00[7] = result:3.b
004417cb        return result
