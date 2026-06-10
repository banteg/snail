/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_garbage_hazard @ 0x43f130 */

0043f133        slot->state = 0
0043f142        void* ecx = data_4df904 + 0x5a8
0043f148        int16_t eax_1 = (slot->_pad_00[4].d).w
0043f14e        if ((eax_1:1.b & 2) == 0)
0043f155        report_errorf("List remove")
0043f161        if ((eax_1.b & 0x40) == 0)
0043f172        void* eax_2
0043f172        eax_2.b = slot->_pad_00[0xc]
0043f172        eax_2:1.b = slot->_pad_00[0xd]
0043f172        eax_2:2.b = slot->_pad_00[0xe]
0043f172        eax_2:3.b = slot->_pad_00[0xf]
0043f177        if (eax_2 != 0)
0043f179        int32_t edx
0043f179        edx.b = slot->_pad_00[8]
0043f179        edx:1.b = slot->_pad_00[9]
0043f179        edx:2.b = slot->_pad_00[0xa]
0043f179        edx:3.b = slot->_pad_00[0xb]
0043f17c        *(eax_2 + 8) = edx
0043f17f        void* eax_3
0043f17f        eax_3.b = slot->_pad_00[8]
0043f17f        eax_3:1.b = slot->_pad_00[9]
0043f17f        eax_3:2.b = slot->_pad_00[0xa]
0043f17f        eax_3:3.b = slot->_pad_00[0xb]
0043f184        if (eax_3 == 0)
0043f18e        int32_t eax_4
0043f18e        eax_4.b = slot->_pad_00[0xc]
0043f18e        eax_4:1.b = slot->_pad_00[0xd]
0043f18e        eax_4:2.b = slot->_pad_00[0xe]
0043f18e        eax_4:3.b = slot->_pad_00[0xf]
0043f191        *(ecx + 4) = eax_4.b
0043f191        *(ecx + 5) = eax_4:1.b
0043f191        *(ecx + 6) = eax_4:2.b
0043f191        *(ecx + 7) = eax_4:3.b
0043f186        int32_t edx_1
0043f186        edx_1.b = slot->_pad_00[0xc]
0043f186        edx_1:1.b = slot->_pad_00[0xd]
0043f186        edx_1:2.b = slot->_pad_00[0xe]
0043f186        edx_1:3.b = slot->_pad_00[0xf]
0043f189        *(eax_3 + 0xc) = edx_1
0043f194        int32_t edx_2
0043f194        edx_2.b = *(ecx + 8)
0043f194        edx_2:1.b = *(ecx + 9)
0043f194        edx_2:2.b = *(ecx + 0xa)
0043f194        edx_2:3.b = *(ecx + 0xb)
0043f197        slot->_pad_00[0xc] = edx_2.b
0043f197        slot->_pad_00[0xd] = edx_2:1.b
0043f197        slot->_pad_00[0xe] = edx_2:2.b
0043f197        slot->_pad_00[0xf] = edx_2:3.b
0043f19a        *(ecx + 8) = slot.b
0043f19a        *(ecx + 9) = slot:1.b
0043f19a        *(ecx + 0xa) = slot:2.b
0043f19a        *(ecx + 0xb) = slot:3.b
0043f19d        int32_t eax_5
0043f19d        eax_5.b = slot->_pad_00[4]
0043f19d        eax_5:1.b = slot->_pad_00[5]
0043f19d        eax_5:2.b = slot->_pad_00[6]
0043f19d        eax_5:3.b = slot->_pad_00[7]
0043f1a0        eax_5:1.b &= 0xfd
0043f1a3        slot->_pad_00[4] = eax_5.b
0043f1a3        slot->_pad_00[5] = eax_5:1.b
0043f1a3        slot->_pad_00[6] = eax_5:2.b
0043f1a3        slot->_pad_00[7] = eax_5:3.b
0043f168        report_errorf("List remove NEXTBOD")
0043f1ac        kill_sprite(slot->sprite)
0043f1b1        struct Game* game = slot->game
0043f1b7        void* eax_6 = game->__offset(0x359140).d
0043f1bf        if (eax_6 == slot)
0043f1c8        game->__offset(0x359140).d = slot->next_active
0043f1ce        return 
0043f1d1        if (eax_6 == 0)
0043f1d1        return 
0043f1d3        while (true)
0043f1d3        void* ecx_2 = *(eax_6 + 0x80)
0043f1db        if (ecx_2 == slot)
0043f1eb        *(eax_6 + 0x80) = slot->next_active
0043f1f1        slot->next_active = nullptr
0043f1f1        break
0043f1dd        eax_6 = ecx_2
0043f1e1        if (eax_6 == 0)
0043f1e4        return 
0043f1fc        return
