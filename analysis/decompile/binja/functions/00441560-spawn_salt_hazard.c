/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_salt_hazard @ 0x441560 */

00441561        int32_t eax = 0
00441563        enum SaltState* edx = &manager->slots[0].state
0044156c        while ((edx - 0x80)->slots[0].state != SALT_STATE_INACTIVE)
0044156e        eax += 1
0044156f        edx = &edx[0x26]
00441578        if (eax s>= 0x28)
0044157b        return eax
00441585        struct Salt* salt = &manager->slots[eax]
0044158c        salt->state = SALT_STATE_ACTIVE
00441596        salt->fade_alpha = 0f
004415b8        salt->spawn_velocity_y = fconvert.s(fconvert.t(g_game_base->subgame.subgame_rate) * fconvert.t(0.0333333351f))
004415c0        salt->body.transform.position.x = position->x
004415c5        salt->body.transform.position.y = position->y
004415cd        salt->body.transform.position.z = position->z
004415d0        set_matrix_rotation_identity(&salt->body.transform)
004415de        int32_t var_c = 0x1fff
004415f4        rotate_matrix_local_y(&salt->body.transform, fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(0.000191747604f)))
004415f9        salt->collision_armed = 1
0044160a        struct BodBase* eax_5 = &g_game_base->subgame.salt_hazard_list_head
00441617        if ((0x200 & salt->body.bod.bod.list_flags) != 0)
0044161e        report_errorf("List ADDafter")
00441627        return 0
0044162a        salt->body.bod.bod.list_prev = eax_5
00441630        salt->body.bod.bod.list_next = eax_5->bod.list_next
00441633        eax_5->bod.list_next = salt
00441636        struct BodNode* list_next = salt->body.bod.bod.list_next
0044163b        if (list_next != 0)
0044163d        list_next->list_prev = salt
00441643        uint32_t eax_7 = salt->body.bod.bod.list_flags | 0x200
00441645        salt->body.bod.bod.list_flags = eax_7
00441649        return eax_7
