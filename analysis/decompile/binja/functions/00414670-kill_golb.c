/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: kill_golb @ 0x414670 */

00414676        struct BodNode* shot_1 = shot
00414678        struct BodList* ecx = &g_game_base->active_bod_list
0041467e        uint16_t list_flags = (shot_1->list_flags).w
00414684        if ((list_flags:1.b & 2) == 0)
0041468b        report_errorf("List remove")
00414697        if ((list_flags.b & 0x40) == 0)
004146a8        struct BodNode* list_next = shot_1->list_next
004146ad        if (list_next != 0)
004146b2        list_next->list_prev = shot_1->list_prev
004146b5        struct BodNode* list_prev = shot_1->list_prev
004146ba        if (list_prev == 0)
004146c7        ecx->first = shot_1->list_next
004146bf        list_prev->list_next = shot_1->list_next
004146cd        shot_1->list_next = ecx->free_top
004146d0        ecx->free_top = shot_1
004146d3        uint32_t list_flags_1 = shot_1->list_flags
004146d6        list_flags_1:1.b &= 0xfd
004146d9        shot_1->list_flags = list_flags_1
0041469e        report_errorf("List remove NEXTBOD")
004146dc        int32_t eax_1 = shot_1->__offset(0x1c0).d
004146e2        shot_1->__offset(0x244).d = 0
004146ef        if (eax_1 == 0)
0041480b        kill_sprite(shot_1->__offset(0x248).d)
0041480b        return
004146f6        if (eax_1 == 1)
00414795        int16_t ecx_8 = (shot_1->__offset(0x84).d).w
004147a1        struct BodList* edx_6 = &g_game_base->active_bod_list
004147aa        if ((ecx_8:1.b & 2) == 0)
004147b1        report_errorf("List remove")
004147ba        return
004147be        if ((ecx_8.b & 0x40) != 0)
004147c5        report_errorf("List remove NEXTBOD")
004147ce        return
004147cf        void* ecx_9 = shot_1->__offset(0x8c).d
004147d4        if (ecx_9 != 0)
004147d9        *(ecx_9 + 8) = shot_1->__offset(0x88).d
004147dc        void* ecx_10 = shot_1->__offset(0x88).d
004147e1        if (ecx_10 == 0)
004147ee        edx_6->first = shot_1->__offset(0x8c).d
004147e6        *(ecx_10 + 0xc) = shot_1->__offset(0x8c).d
004147f5        shot_1->__offset(0x8c).d = edx_6->free_top
004147f8        edx_6->free_top = &shot_1[8]
004147fb        int32_t ecx_13 = shot_1->__offset(0x84).d
004147fe        ecx_13:1.b &= 0xfd
00414801        shot_1->__offset(0x84).d = ecx_13
00414804        return
004146fd        if (eax_1 != 2)
004146fd        return
0041470f        struct BodList* edx_4 = &g_game_base->active_bod_list
00414715        int16_t ecx_2 = (shot_1->__offset(0x11c).d).w
0041471b        if ((ecx_2:1.b & 2) == 0)
00414722        report_errorf("List remove")
0041472f        if ((ecx_2.b & 0x40) == 0)
00414740        void* ecx_3 = shot_1->__offset(0x124).d
00414746        if (ecx_3 != 0)
0041474b        *(ecx_3 + 8) = shot_1->__offset(0x120).d
0041474e        void* ecx_4 = shot_1->__offset(0x120).d
00414753        if (ecx_4 == 0)
00414760        edx_4->first = shot_1->__offset(0x124).d
00414758        *(ecx_4 + 0xc) = shot_1->__offset(0x124).d
00414767        shot_1->__offset(0x124).d = edx_4->free_top
0041476a        edx_4->free_top = shot_1 + 0x118
0041476d        int32_t ecx_7 = shot_1->__offset(0x11c).d
00414770        ecx_7:1.b &= 0xfd
00414773        shot_1->__offset(0x11c).d = ecx_7
00414736        report_errorf("List remove NEXTBOD")
00414776        void* esi = shot_1->__offset(0x198).d
0041477e        if (esi == 0)
00414784        return
00414784        int32_t eax_6 = *(esi + 4)
00414787        eax_6:1.b &= 0xef
0041478a        *(esi + 4) = eax_6
00414811        return
