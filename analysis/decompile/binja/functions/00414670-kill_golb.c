/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: kill_golb @ 0x414670 */

00414678        struct BodList* ecx = &g_game_base->active_bod_list
0041467e        uint16_t list_flags = (shot->primary_body.bod.bod.list_flags).w
00414684        if ((list_flags:1.b & 2) == 0)
0041468b        report_errorf("List remove")
00414697        if ((list_flags.b & 0x40) == 0)
004146a8        struct BodNode* list_next = shot->primary_body.bod.bod.list_next
004146ad        if (list_next != 0)
004146b2        list_next->list_prev = shot->primary_body.bod.bod.list_prev
004146b5        struct BodNode* list_prev = shot->primary_body.bod.bod.list_prev
004146ba        if (list_prev == 0)
004146c7        ecx->first = shot->primary_body.bod.bod.list_next
004146bf        list_prev->list_next = shot->primary_body.bod.bod.list_next
004146cd        shot->primary_body.bod.bod.list_next = ecx->free_top
004146d0        ecx->free_top = shot
004146d3        uint32_t list_flags_1 = shot->primary_body.bod.bod.list_flags
004146d6        list_flags_1:1.b &= 0xfd
004146d9        shot->primary_body.bod.bod.list_flags = list_flags_1
0041469e        report_errorf("List remove NEXTBOD")
004146dc        int32_t kind = shot->kind
004146e2        shot->state = 0
004146ef        if (kind == 0)
0041480b        kill_sprite(shot->render_body_owner)
0041480b        return
004146f6        if (kind == 1)
00414795        uint16_t list_flags_5 = (shot->vapour.body.bod.bod.list_flags).w
004147a1        struct BodList* edx_6 = &g_game_base->active_bod_list
004147aa        if ((list_flags_5:1.b & 2) == 0)
004147b1        report_errorf("List remove")
004147ba        return
004147be        if ((list_flags_5.b & 0x40) != 0)
004147c5        report_errorf("List remove NEXTBOD")
004147ce        return
004147cf        struct BodNode* list_next_2 = shot->vapour.body.bod.bod.list_next
004147d4        if (list_next_2 != 0)
004147d9        list_next_2->list_prev = shot->vapour.body.bod.bod.list_prev
004147dc        struct BodNode* list_prev_2 = shot->vapour.body.bod.bod.list_prev
004147e1        if (list_prev_2 == 0)
004147ee        edx_6->first = shot->vapour.body.bod.bod.list_next
004147e6        list_prev_2->list_next = shot->vapour.body.bod.bod.list_next
004147f5        shot->vapour.body.bod.bod.list_next = edx_6->free_top
004147f8        edx_6->free_top = &shot->vapour
004147fb        uint32_t list_flags_6 = shot->vapour.body.bod.bod.list_flags
004147fe        list_flags_6:1.b &= 0xfd
00414801        shot->vapour.body.bod.bod.list_flags = list_flags_6
00414804        return
004146fd        if (kind != 2)
004146fd        return
0041470f        struct BodList* edx_4 = &g_game_base->active_bod_list
00414715        uint16_t list_flags_3 = (shot->tertiary_body.bod.bod.list_flags).w
0041471b        if ((list_flags_3:1.b & 2) == 0)
00414722        report_errorf("List remove")
0041472f        if ((list_flags_3.b & 0x40) == 0)
00414740        struct BodNode* list_next_1 = shot->tertiary_body.bod.bod.list_next
00414746        if (list_next_1 != 0)
0041474b        list_next_1->list_prev = shot->tertiary_body.bod.bod.list_prev
0041474e        struct BodNode* list_prev_1 = shot->tertiary_body.bod.bod.list_prev
00414753        if (list_prev_1 == 0)
00414760        edx_4->first = shot->tertiary_body.bod.bod.list_next
00414758        list_prev_1->list_next = shot->tertiary_body.bod.bod.list_next
00414767        shot->tertiary_body.bod.bod.list_next = edx_4->free_top
0041476a        edx_4->free_top = &shot->tertiary_body
0041476d        uint32_t list_flags_4 = shot->tertiary_body.bod.bod.list_flags
00414770        list_flags_4:1.b &= 0xfd
00414773        shot->tertiary_body.bod.bod.list_flags = list_flags_4
00414736        report_errorf("List remove NEXTBOD")
00414776        struct ContactTargetObject* homing_target_object = shot->homing_target_object
0041477e        if (homing_target_object == 0)
00414784        return
00414784        int32_t list_flags_2 = homing_target_object->list_flags
00414787        list_flags_2:1.b &= 0xef
0041478a        homing_target_object->list_flags = list_flags_2
00414811        return
