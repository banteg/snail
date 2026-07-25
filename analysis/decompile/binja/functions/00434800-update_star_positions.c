/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_star_positions @ 0x434800 */

00434807        int32_t i = 0
0043480b        if (manager->count s<= 0)
0043480b        return
00434813        int32_t edx_1 = 0
00434818        struct StarManagerEntry* distance_entry = manager->entries + edx_1
00434820        distance_entry->travel_distance = fconvert.s(fconvert.t(distance_entry->speed) + fconvert.t(distance_entry->travel_distance))
00434823        struct StarManagerEntry* entries = manager->entries
00434826        long double x87_r7_3 = fconvert.t(*(&entries->travel_distance + edx_1))
0043482a        long double temp1_1 = fconvert.t(35f)
0043482a        x87_r7_3 - temp1_1
00434839        if ((((x87_r7_3 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp1_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043483f        *(&entries->travel_distance + edx_1) = 0f
0043484c        (*(&manager->entries->sprite + edx_1))->facing_refresh_progress = 0f
00434856        struct GameRoot* game_base_1 = g_game_base
004348c8        *(*(&manager->entries->sprite + edx_1) + 0x48) = struct Vec3 {
    .x = fconvert.s(fconvert.t(game_base_1->overlay_0.bod.transform.basis_forward.x) * fconvert.t(50f) + fconvert.t(game_base_1->overlay_0.bod.transform.position.x))
    .y = fconvert.s(fconvert.t(fconvert.s(fconvert.t(game_base_1->overlay_0.bod.transform.basis_forward.y) * fconvert.t(50f))) + fconvert.t(game_base_1->overlay_0.bod.transform.position.y))
    .z = fconvert.s(fconvert.t(fconvert.s(fconvert.t(game_base_1->overlay_0.bod.transform.basis_forward.z) * fconvert.t(50f))) + fconvert.t(game_base_1->overlay_0.bod.transform.position.z))
}
004348ce        struct StarManagerEntry* velocity_entry = manager->entries + edx_1
004348d6        struct Vec3* sprite_velocity = &velocity_entry->sprite->velocity
004348db        sprite_velocity->x = velocity_entry->velocity.x
004348e0        sprite_velocity->y = velocity_entry->velocity.y
004348e6        sprite_velocity->z = velocity_entry->velocity.z
004348ec        struct StarManagerEntry* motion_entry = manager->entries + edx_1
00434900        float var_8_1 = fconvert.s(fconvert.t(motion_entry->velocity.y) * fconvert.t(10f))
00434910        struct Vec3* motion_position = &motion_entry->sprite->position
00434913        float var_4_1 = fconvert.s(fconvert.t(motion_entry->velocity.z) * fconvert.t(10f))
00434919        motion_position->x = fconvert.s(fconvert.t(motion_entry->velocity.x) * fconvert.t(10f) + fconvert.t(motion_position->x))
00434922        motion_position->y = fconvert.s(fconvert.t(var_8_1) + fconvert.t(motion_position->y))
0043492c        motion_position->z = fconvert.s(fconvert.t(var_4_1) + fconvert.t(motion_position->z))
00434932        struct StarManagerEntry* travel_entry = manager->entries + edx_1
00434940        travel_entry->travel_distance = fconvert.s(fconvert.t(travel_entry->speed) * fconvert.t(10f) + fconvert.t(travel_entry->travel_distance))
00434946        struct StarManagerEntry* alpha_entry = manager->entries + edx_1
00434948        i += 1
00434949        edx_1 += 0x2c
00434965        alpha_entry->sprite->color.a = fconvert.s((fconvert.t(alpha_entry->travel_distance) - fconvert.t(2f)) * fconvert.t(alpha_entry->alpha_scale) * fconvert.t(0.0114285713f) * fconvert.t(fade_alpha))
0043496b        do while (i s< manager->count)
00434977        return
