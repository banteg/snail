/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_golb_trail_sprite @ 0x415bb0 */

00415bcc        struct Sprite* result = allocate_sprite(&g_sprite_manager, *(*(arg1 + 0x278) + 0x380), 0x21, 0xffffffff, 0xffffffff)
00415bd1        uint32_t flags = result->flags
00415bd6        flags:1.b |= 8
00415bd9        result->progress = 0f
00415bdc        result->flags = flags
00415be5        char ecx_2 = (*(*(arg1 + 0x278) + 0x338)).b
00415bee        if ((ecx_2 & 1) != 0)
00415bf0        result->progress_step = 0.238095239f
00415bfc        if ((ecx_2 & 2) != 0)
00415bfe        result->progress_step = 0.333333343f
00415c09        result->progress_step = 0.555555582f
00415c10        result->lifetime = 0f
00415c13        result->lifetime_step = 0f
00415c16        result->size_start = 0.200000003f
00415c1d        result->size_end = 0.0299999993f
00415c24        result->velocity.z = 0f
00415c27        result->velocity.y = 0f
00415c2a        result->velocity.x = 0
00415c2d        result->gravity_step = 0f
00415c35        result->position.x = *arg2
00415c3b        result->position.y = arg2[1]
00415c42        result->position.z = arg2[2]
00415c4b        result->object_ref = *(arg1 + 0x274)
00415c4e        return result
