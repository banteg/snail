/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_sub_lazer_projectile @ 0x441670 */

00441678        sub_lazer->state = SUB_LAZER_STATE_ACTIVE
00441684        set_matrix_identity(&sub_lazer->body.transform)
00441698        sub_lazer->body.transform.position.x = origin->x
0044169d        sub_lazer->body.transform.position.y = origin->y
004416a7        sub_lazer->body.transform.position.z = origin->z
004416ae        sub_lazer->velocity.x = direction->x
004416b3        sub_lazer->velocity.y = direction->y
004416b6        float z = direction->z
004416b9        sub_lazer->sprite_bob_phase = 0f
004416c8        sub_lazer->velocity.z = z
004416cb        struct SubgameRuntime* owner_game = sub_lazer->owner_game
004416e2        bool cond:0 = (0x200 & sub_lazer->body.bod.bod.list_flags) == 0
004416e4        sub_lazer->sprite_bob_phase_step = fconvert.s(fconvert.t(owner_game->subgame_rate) * fconvert.t(0.00555555569f))
004416ea        if (not(cond:0))
004416f1        report_errorf("List ADDafter")
004416fc        set_matrix_z_direction(&sub_lazer->body.transform, &sub_lazer->velocity)
00441704        return
00441707        sub_lazer->body.bod.bod.list_prev = &owner_game->barrier_sub_lazer_list_head
0044170d        sub_lazer->body.bod.bod.list_next = owner_game->barrier_sub_lazer_list_head.bod.list_next
00441710        owner_game->barrier_sub_lazer_list_head.bod.list_next = sub_lazer
00441713        struct BodNode* list_next = sub_lazer->body.bod.bod.list_next
00441718        if (list_next != 0)
0044171a        list_next->list_prev = sub_lazer
00441725        sub_lazer->body.bod.bod.list_flags |= 0x200
00441728        set_matrix_z_direction(&sub_lazer->body.transform, &sub_lazer->velocity)
00441730        return
