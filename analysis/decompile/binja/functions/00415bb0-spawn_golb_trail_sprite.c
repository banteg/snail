/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_golb_trail_sprite @ 0x415bb0 */

00415bcc        void** result = allocate_sprite(&g_sprite_manager, shot->owner_player->player_slot, 0x21, 0xffffffff, 0xffffffff)
00415bd1        int32_t ecx_1 = result[1]
00415bd6        ecx_1:1.b |= 8
00415bd9        result[0x1a] = 0
00415bdc        result[1] = ecx_1
00415be5        uint8_t movement_flags = (shot->owner_player->movement_flags).b
00415bee        if ((movement_flags & 1) != 0)
00415bf0        result[0x1b] = 0x3e73cf3d
00415bfc        if ((movement_flags & 2) != 0)
00415bfe        result[0x1b] = 0x3eaaaaab
00415c09        result[0x1b] = 0x3f0e38e4
00415c10        result[0x1c] = 0
00415c13        result[0x1d] = 0
00415c16        result[0x18] = 0x3e4ccccd
00415c1d        result[0x19] = 0x3cf5c28f
00415c24        result[0x17] = 0
00415c27        result[0x16] = 0
00415c2a        result[0x15] = 0
00415c2d        result[0x1e] = 0
00415c35        result[0x12] = position->x
00415c3b        result[0x13] = position->y
00415c42        result[0x14] = position->z
00415c4b        *result = shot->object_ref
00415c4e        return result
