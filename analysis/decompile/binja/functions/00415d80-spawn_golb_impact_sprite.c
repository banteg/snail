/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_golb_impact_sprite @ 0x415d80 */

00415d8a        if ((g_runtime_config.render_flags.b & 0x10) == 0)
00415d8a        return
00415da9        struct Sprite* eax_1 = allocate_sprite(&g_sprite_manager, shot->owner_player->player_slot, 0x21, 0xffffffff, 0xffffffff)
00415dae        enum SpriteFlag flags = eax_1->flags
00415db4        flags:1.b |= 8
00415dbf        eax_1->flags = flags
00415dc6        eax_1->progress = 0f
00415dc9        eax_1->velocity.x = 0
00415dcf        eax_1->lifetime = 0f
00415dd2        int32_t var_c_1 = 0
00415dd6        eax_1->velocity.y = 0.0500000007f
00415dd9        int32_t var_4_1 = 0
00415de2        int32_t* position_1 = position
00415de6        eax_1->progress_step = 0.0555555522f
00415ded        __builtin_strncpy(&eax_1->lifetime_step, "VUU?", 8)
00415df4        eax_1->size_start = 0.5f
00415dfb        eax_1->size_end = 1f
00415e02        eax_1->velocity.z = 0f
00415e0b        eax_1->position.x = *position_1
00415e10        eax_1->position.y = position_1[1]
00415e16        eax_1->position.z = position_1[2]
00415e1c        return
