/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_row_model @ 0x443070 */

00443079        row_model->body.transform.position.x = fconvert.s(fconvert.t(row_model->velocity.x) + fconvert.t(row_model->body.transform.position.x))
00443085        row_model->body.transform.position.y = fconvert.s(fconvert.t(row_model->velocity.y) + fconvert.t(row_model->body.transform.position.y))
00443091        row_model->body.transform.position.z = fconvert.s(fconvert.t(row_model->velocity.z) + fconvert.t(row_model->body.transform.position.z))
00443097        struct GameRoot* game_base_1 = g_game_base
004430a3        long double x87_r7_6 = fconvert.t(row_model->body.bod.object->bounds_max.z) + fconvert.t(game_base_1->subgame.player.interaction_max_z)
004430a9        long double temp0 = fconvert.t(row_model->body.transform.position.z)
004430a9        x87_r7_6 - temp0
004430b1        if ((((x87_r7_6 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp0) ? 1 : 0) << 0xa | (x87_r7_6 == temp0 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
004430b1        return
004430b3        uint16_t list_flags = (row_model->body.bod.bod.list_flags).w
004430bf        if ((list_flags:1.b & 2) == 0)
004430c6        report_errorf("List remove")
004430ce        return
004430d1        if ((list_flags.b & 0x40) != 0)
004430d8        report_errorf("List remove NEXTBOD")
004430e0        return
004430e1        struct BodNode* list_next = row_model->body.bod.bod.list_next
004430e7        if (list_next != 0)
004430ec        list_next->list_prev = row_model->body.bod.bod.list_prev
004430ef        struct BodNode* list_prev = row_model->body.bod.bod.list_prev
004430f4        if (list_prev != 0)
004430f9        list_prev->list_next = row_model->body.bod.bod.list_next
004430ff        row_model->body.bod.bod.list_next = game_base_1->active_bod_list.free_top
00443102        game_base_1->active_bod_list.free_top = row_model
00443105        uint32_t list_flags_1 = row_model->body.bod.bod.list_flags
00443109        list_flags_1:1.b &= 0xfd
0044310c        row_model->body.bod.bod.list_flags = list_flags_1
0044310f        return
00443114        game_base_1->active_bod_list.first = row_model->body.bod.bod.list_next
0044311a        row_model->body.bod.bod.list_next = game_base_1->active_bod_list.free_top
0044311d        game_base_1->active_bod_list.free_top = row_model
00443120        uint32_t list_flags_2 = row_model->body.bod.bod.list_flags
00443123        list_flags_2:1.b &= 0xfd
00443126        row_model->body.bod.bod.list_flags = list_flags_2
00443129        return
