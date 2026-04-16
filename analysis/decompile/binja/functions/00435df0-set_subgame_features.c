/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_subgame_features @ 0x435df0 */

00435df8        if (*(arg1 + 0xff25d0) != 0)
00435dfa        void* eax_1 = *(arg1 + 0xff25d4)
00435e03        *(arg1 + 0x4c) = *(eax_1 + 0x38)
00435e06        return eax_1
00435e07        int32_t eax_2 = *(arg1 + 0x40)
00435e0a        *(arg1 + 0x4c) = 0x484
00435e14        *(arg1 + 0x4c) = 0x600484
00435e1d        switch (eax_2)
00435e24        case 0, 1
00435e24        *(arg1 + 0x4c) = 0xf5cfff
00435e2c        case 4
00435e2c        *(arg1 + 0x4c) = 0x75cfff
00435e34        case 7
00435e34        *(arg1 + 0x4c) = 0xe4cfff
00435e3b        return eax_2
