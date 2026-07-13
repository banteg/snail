/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_sub_lazer_projectile @ 0x441670 */

00441678        slot->state = 1
00441684        set_matrix_identity(&slot->basis_right)
00441698        slot->position.x = origin->x
0044169d        slot->position.y = origin->y
004416a7        slot->position.z = origin->z
004416ae        slot->velocity.x = direction->x
004416b3        slot->velocity.y = direction->y
004416b6        float z = direction->z
004416b9        slot->sprite_bob_phase = 0f
004416c8        slot->velocity.z = z
004416cb        struct SubgameRuntime* owner_game = slot->owner_game
004416e2        bool cond:0 = (0x200 & slot->bod.list_flags) == 0
004416e4        slot->sprite_bob_phase_step = fconvert.s(fconvert.t(owner_game->subgame_rate) * fconvert.t(0.00555555569f))
004416ea        if (not(cond:0))
004416f1        report_errorf("List ADDafter")
004416fc        set_matrix_z_direction(&slot->basis_right, &slot->velocity)
00441704        return
00441707        slot->bod.list_prev = &owner_game->unknown_1b014c[0x1a5a88]
0044170a        struct BodNode* edx_4
0044170a        edx_4.b = owner_game->unknown_1b014c[0x1a5a94]
0044170a        edx_4:1.b = owner_game->unknown_1b014c[0x1a5a95]
0044170a        edx_4:2.b = owner_game->unknown_1b014c[0x1a5a96]
0044170a        edx_4:3.b = owner_game->unknown_1b014c[0x1a5a97]
0044170d        slot->bod.list_next = edx_4
00441710        owner_game->unknown_1b014c[0x1a5a94] = slot.b
00441710        owner_game->unknown_1b014c[0x1a5a95] = slot:1.b
00441710        owner_game->unknown_1b014c[0x1a5a96] = slot:2.b
00441710        owner_game->unknown_1b014c[0x1a5a97] = slot:3.b
00441713        struct BodNode* list_next = slot->bod.list_next
00441718        if (list_next != 0)
0044171a        list_next->list_prev = slot
00441725        slot->bod.list_flags |= 0x200
00441728        set_matrix_z_direction(&slot->basis_right, &slot->velocity)
00441730        return
