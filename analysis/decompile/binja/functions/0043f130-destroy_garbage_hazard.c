/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_garbage_hazard @ 0x43f130 */

0043f133        self->state = 0
0043f142        void* ecx = data_4df904 + 0x5a8
0043f148        int16_t eax_1 = (self->_pad_00[4].d).w
0043f14e        if ((eax_1:1.b & 2) == 0)
0043f155        report_errorf("List remove")
0043f161        if ((eax_1.b & 0x40) == 0)
0043f172        void* eax_2 = self->_pad_00[0xc].d
0043f177        if (eax_2 != 0)
0043f17c        *(eax_2 + 8) = self->_pad_00[8].d
0043f17f        void* eax_3 = self->_pad_00[8].d
0043f184        if (eax_3 == 0)
0043f191        *(ecx + 4) = self->_pad_00[0xc].d
0043f189        *(eax_3 + 0xc) = self->_pad_00[0xc].d
0043f194        int32_t edx_3 = *(ecx + 8)
0043f197        self->_pad_00[0xc] = edx_3.b
0043f197        self->_pad_00[0xd] = edx_3:1.b
0043f197        self->_pad_00[0xe] = edx_3:2.b
0043f197        self->_pad_00[0xf] = edx_3:3.b
0043f19a        *(ecx + 8) = self
0043f1a0        int32_t eax_5
0043f1a0        eax_5:1.b = self->_pad_00[4].d:1.b & 0xfd
0043f1a3        self->_pad_00[4] = eax_5.b
0043f1a3        self->_pad_00[5] = eax_5:1.b
0043f1a3        self->_pad_00[6] = eax_5:2.b
0043f1a3        self->_pad_00[7] = eax_5:3.b
0043f168        report_errorf("List remove NEXTBOD")
0043f1ac        kill_sprite(self->sprite)
0043f1b1        struct Game* game = self->game
0043f1b7        void* eax_6 = game->__offset(0x359140).d
0043f1bf        if (eax_6 == self)
0043f1c1        struct GarbageHazardRuntime* next_active = self->next_active
0043f1c8        game->__offset(0x359140).d = next_active
0043f1ce        return next_active
0043f1d1        if (eax_6 != 0)
0043f1d3        while (true)
0043f1d3        void* ecx_2 = *(eax_6 + 0x80)
0043f1db        if (ecx_2 == self)
0043f1eb        *(eax_6 + 0x80) = self->next_active
0043f1f1        self->next_active = nullptr
0043f1f1        break
0043f1dd        eax_6 = ecx_2
0043f1e1        if (eax_6 == 0)
0043f1e4        return eax_6
0043f1fc        return eax_6
