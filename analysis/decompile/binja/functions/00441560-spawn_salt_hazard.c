/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_salt_hazard @ 0x441560 */

00441561        int32_t eax = 0
00441563        int32_t* edx = &manager->slots[0].state
0044156c        while ((edx - 0x80)->slots[0].state != 0)
0044156e        eax += 1
0044156f        edx = &edx[0x26]
00441578        if (eax s>= 0x28)
0044157b        return eax
00441585        struct BodNode* esi = &manager->slots[eax]
0044158c        esi->__offset(0x80).d = 1
00441596        esi->__offset(0x8c).d = 0
004415b8        esi->__offset(0x90).d = fconvert.s(fconvert.t(g_game_base->subgame.subgame_rate) * fconvert.t(0.0333333351f))
004415c0        *(esi + 0x68) = position->x
004415c5        *(esi + 0x6c) = position->y
004415cd        esi[7].vtable = position->z
004415d0        set_matrix_rotation_identity(esi + 0x38)
004415de        int32_t var_c = 0x1fff
004415f4        rotate_matrix_local_y(esi + 0x38, fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(0.000191747604f)))
004415f9        esi->__offset(0x94).b = 1
0044160a        struct BodBase* eax_5 = &g_game_base->subgame.salt_hazard_list_head
00441617        if ((0x200 & esi->list_flags) != 0)
0044161e        report_errorf("List ADDafter")
00441627        return 0
0044162a        esi->list_prev = eax_5
00441630        esi->list_next = eax_5->bod.list_next
00441633        eax_5->bod.list_next = esi
00441636        struct BodNode* list_next = esi->list_next
0044163b        if (list_next != 0)
0044163d        list_next->list_prev = esi
00441643        uint32_t eax_7 = esi->list_flags | 0x200
00441645        esi->list_flags = eax_7
00441649        return eax_7
