/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_golb_trail_sprite @ 0x415bb0 */

00415bcc        struct Sprite* trail_sprite = allocate_sprite(&g_sprite_manager, shot->owner_player->player_slot, 0x21, 0xffffffff, 0xffffffff)
00415bd1        enum SpriteFlag flags = trail_sprite->flags
00415bd6        flags:1.b |= 8
00415bd9        trail_sprite->progress = 0f
00415bdc        trail_sprite->flags = flags
00415be5        uint8_t shoot_flags = (shot->owner_player->shoot_flags).b
00415bee        if ((shoot_flags & 1) != 0)
00415bf0        trail_sprite->progress_step = 0.238095239f
00415bfc        if ((shoot_flags & 2) != 0)
00415bfe        trail_sprite->progress_step = 0.333333343f
00415c09        trail_sprite->progress_step = 0.555555582f
00415c10        trail_sprite->lifetime = 0f
00415c13        trail_sprite->lifetime_step = 0f
00415c16        trail_sprite->size_start = 0.200000003f
00415c1d        trail_sprite->size_end = 0.0299999993f
00415c2a        __builtin_memset(&trail_sprite->velocity, 0, 0xc)
00415c2d        trail_sprite->gravity_step = 0f
00415c35        trail_sprite->position.x = position->x
00415c3b        trail_sprite->position.y = position->y
00415c42        trail_sprite->position.z = position->z
00415c4b        trail_sprite->object_ref = shot->object_ref
00415c4e        return trail_sprite
