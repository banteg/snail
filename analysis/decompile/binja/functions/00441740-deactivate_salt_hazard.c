/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: deactivate_salt_hazard @ 0x441740 */

00441748        void* ecx = data_4df904 + 0x5a8
0044174e        int16_t eax = (slot->_pad_00[4].d).w
00441754        if ((eax:1.b & 2) == 0)
0044175b        report_errorf("List remove")
00441763        slot->active = 0
0044176e        return 
00441771        if ((eax.b & 0x40) != 0)
00441778        report_errorf("List remove NEXTBOD")
00441780        slot->active = 0
0044178b        return 
0044178c        void* eax_1 = slot->_pad_00[0xc].d
00441791        if (eax_1 != 0)
00441796        *(eax_1 + 8) = slot->_pad_00[8].d
00441799        void* eax_2 = slot->_pad_00[8].d
0044179e        if (eax_2 == 0)
004417ab        *(ecx + 4) = slot->_pad_00[0xc].d
004417a3        *(eax_2 + 0xc) = slot->_pad_00[0xc].d
004417ae        int32_t edx_3 = *(ecx + 8)
004417b1        slot->_pad_00[0xc] = edx_3.b
004417b1        slot->_pad_00[0xd] = edx_3:1.b
004417b1        slot->_pad_00[0xe] = edx_3:2.b
004417b1        slot->_pad_00[0xf] = edx_3:3.b
004417b4        *(ecx + 8) = slot
004417b7        int32_t eax_4 = slot->_pad_00[4].d
004417ba        slot->active = 0
004417c4        eax_4:1.b &= 0xfd
004417c7        slot->_pad_00[4] = eax_4.b
004417c7        slot->_pad_00[5] = eax_4:1.b
004417c7        slot->_pad_00[6] = eax_4:2.b
004417c7        slot->_pad_00[7] = eax_4:3.b
004417cb        return
