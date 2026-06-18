/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_sprite_manager @ 0x44e160 */

0044e169        manager->paused = 0
0044e16b        __builtin_memset(&manager->active_heads, 0, 0x14)
0044e187        int32_t i = 0
0044e18f        manager->free_head = &manager->sprites
0044e19b        void* ebp_1 = manager + i * 0xb4
0044e1a1        initialize_sprite(ebp_1 + 4)
0044e1a8        if (i == 0)
0044e1b0        manager->sprites[0].prev = nullptr
0044e1b3        manager->sprites[0].next = &manager->sprites[1]
0044e1be        if (i != 0xbb7)
0044e1e0        *(ebp_1 + 0x14) = ebp_1 - 0xb0
0044e1e3        *(ebp_1 + 0x10) = ebp_1 + 0xb8
0044e1c6        manager->sprites[0xbb7].prev = &manager->sprites[0xbb6]
0044e1cc        manager->sprites[0xbb7].next = nullptr
0044e1e6        i += 1
0044e1ed        do while (i s< 0xbb8)
0044e1f3        return
