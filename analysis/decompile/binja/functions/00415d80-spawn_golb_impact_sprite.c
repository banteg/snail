/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_golb_impact_sprite @ 0x415d80 */

00415d80        struct Vec3* result
00415d80        result.b = data_4df934
00415d8a        if ((result.b & 0x10) != 0)
00415da9        struct Sprite* eax_1 = allocate_sprite(&g_sprite_manager, *(*(arg1 + 0x278) + 0x380), 0x21, 0xffffffff, 0xffffffff)
00415dae        uint32_t flags = eax_1->flags
00415db4        flags:1.b |= 8
00415dbf        eax_1->flags = flags
00415dc6        eax_1->progress = 0f
00415dc9        eax_1->velocity.x = 0
00415dcf        eax_1->lifetime = 0f
00415dd2        int32_t var_c_1 = 0
00415dd6        eax_1->velocity.y = 0.0500000007f
00415dd9        int32_t var_4_1 = 0
00415de6        eax_1->progress_step = 0.0555555522f
00415ded        __builtin_strncpy(&eax_1->lifetime_step, "VUU?", 8)
00415df4        eax_1->size_start = 0.5f
00415dfb        eax_1->size_end = 1f
00415e02        eax_1->velocity.z = 0f
00415e07        result = &eax_1->position
00415e0b        result->x = *arg2
00415e10        result->y = arg2[1]
00415e16        result->z = arg2[2]
00415e1c        return result
