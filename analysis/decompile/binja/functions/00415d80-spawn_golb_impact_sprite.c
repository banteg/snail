/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_golb_impact_sprite @ 0x415d80 */

00415d8a        if ((g_runtime_config.render_flags.b & 0x10) == 0)
00415d8a        return
00415da9        struct Sprite* impact_sprite = allocate_sprite(&g_sprite_manager, shot->owner_player->player_slot, 0x21, 0xffffffff, 0xffffffff)
00415dae        enum SpriteFlag flags = impact_sprite->flags
00415db4        flags:1.b |= 8
00415dbf        impact_sprite->flags = flags
00415dc6        impact_sprite->progress = 0f
00415dc9        impact_sprite->velocity.x = 0
00415dcf        impact_sprite->lifetime = 0f
00415dd2        int32_t var_c_1 = 0
00415dd6        impact_sprite->velocity.y = 0.0500000007f
00415dd9        int32_t var_4_1 = 0
00415ddf        impact_sprite->gravity_step = 0f
00415de6        impact_sprite->progress_step = 0.0555555522f
00415ded        impact_sprite->lifetime_step = 0.833333373f
00415df4        impact_sprite->size_start = 0.5f
00415dfb        impact_sprite->size_end = 1f
00415e02        impact_sprite->velocity.z = 0f
00415e0b        impact_sprite->position.x = position->x
00415e10        impact_sprite->position.y = position->y
00415e16        impact_sprite->position.z = position->z
00415e1c        return
