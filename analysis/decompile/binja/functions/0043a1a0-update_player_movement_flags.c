/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_player_movement_flags @ 0x43a1a0 */

0043a1a3        int32_t eax = player->__offset(0x308).d
0043a1a9        player->__offset(0x338).d = 0
0043a1b6        if (eax u> 8)
0043a288        player->__offset(0x338).d = 0x81
0043a292        player->__offset(0x2734).d = 0x3d888889
0043a1bc        switch (eax)
0043a1c3        case 0
0043a1c3        player->__offset(0x338).d = 1
0043a1cd        player->__offset(0x2734).d = 0x3d97b426
0043a1dc        case 1
0043a1dc        player->__offset(0x338).d = 2
0043a1e6        player->__offset(0x2734).d = 0x3d97b426
0043a1f5        case 2
0043a1f5        player->__offset(0x338).d = 4
0043a1ff        player->__offset(0x2734).d = 0x3d97b426
0043a20e        case 3
0043a20e        player->__offset(0x338).d = 8
0043a218        player->__offset(0x2734).d = 0x3de38e38
0043a224        case 4
0043a224        player->__offset(0x338).d = 0x10
0043a22e        player->__offset(0x2734).d = 0x3de38e38
0043a23a        case 5
0043a23a        player->__offset(0x338).d = 0x20
0043a292        player->__offset(0x2734).d = 0x3d888889
0043a246        case 6
0043a246        player->__offset(0x338).d = 0x40
0043a250        player->__offset(0x2734).d = 0x3e088889
0043a25c        case 7
0043a25c        player->__offset(0x338).d = 0xc0
0043a266        player->__offset(0x2734).d = 0x3e088889
0043a272        case 8
0043a272        player->__offset(0x338).d = 0x90
0043a27c        player->__offset(0x2734).d = 0x3de38e38
0043a29c        int32_t eax_1 = player->__offset(0x338).d
0043a2aa        if (eax_1 == player->__offset(0x33c).d)
0043a2cc        player->__offset(0x33c).d = player->__offset(0x338).d
0043a2d3        return eax_1
0043a2b3        set_snail_weapon(player + 0x2984, eax_1)
0043a2b8        int32_t eax_2 = player->__offset(0x338).d
0043a2be        player->__offset(0x33c).d = eax_2
0043a2c5        return eax_2
