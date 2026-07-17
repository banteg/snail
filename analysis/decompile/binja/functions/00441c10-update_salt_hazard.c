/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_salt_hazard @ 0x441c10 */

00441c13        struct SubgameRuntime* owner_game = salt->owner_game
00441c1e        if (owner_game->subgame_pause_gate != 0)
00441c1e        return
00441c24        int32_t state = salt->state
00441c2b        if (state == 1)
00441cd0        long double x87_r7_4 = fconvert.t(1f) - (fconvert.t(salt->body.transform.position.z) - fconvert.t(owner_game->player.body.transform.position.z)) * fconvert.t(0.0217391308f)
00441cd6        long double temp1_1 = fconvert.t(0f)
00441cd6        x87_r7_4 - temp1_1
00441cdc        salt->fade_alpha = fconvert.s(x87_r7_4)
00441cdc        bool c1_1 = unknown  {fst dword [esi+0x8c], st0}
00441ce7        if ((((x87_r7_4 < temp1_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_4, temp1_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp1_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) == 0)
00441cf3        long double temp3_1 = fconvert.t(1f)
00441cf3        x87_r7_4 - temp3_1
00441cfe        if ((((x87_r7_4 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp3_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp3_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
00441d02        x87_r7_4 = fconvert.t(1f)
00441ceb        x87_r7_4 = fconvert.t(0f)
00441d08        salt->fade_alpha = fconvert.s(x87_r7_4)
00441d16        set_color_alpha(&salt->body.bod.color, 0.899999976f)
00441d21        long double x87_r7_7 = fconvert.t(salt->body.transform.position.z)
00441d24        long double temp4_1 = fconvert.t(salt->owner_game->player.interaction_max_z)
00441d24        x87_r7_7 - temp4_1
00441d2f        if ((((x87_r7_7 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp4_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp4_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00441d31        salt->state = 2
00441c32        if (state == 2)
00441c3d        struct BodList* ecx_3 = &g_game_base->active_bod_list
00441c43        uint16_t list_flags = (salt->body.bod.bod.list_flags).w
00441c49        if ((list_flags:1.b & 2) == 0)
00441c50        report_errorf("List remove")
00441c58        salt->state = 0
00441c63        return
00441c66        if ((list_flags.b & 0x40) != 0)
00441c6d        report_errorf("List remove NEXTBOD")
00441c75        salt->state = 0
00441c80        return
00441c81        struct BodNode* list_next = salt->body.bod.bod.list_next
00441c86        if (list_next != 0)
00441c8b        list_next->list_prev = salt->body.bod.bod.list_prev
00441c8e        struct BodNode* list_prev = salt->body.bod.bod.list_prev
00441c93        if (list_prev == 0)
00441ca0        ecx_3->first = salt->body.bod.bod.list_next
00441c98        list_prev->list_next = salt->body.bod.bod.list_next
00441ca6        salt->body.bod.bod.list_next = ecx_3->free_top
00441ca9        ecx_3->free_top = salt
00441cac        uint32_t list_flags_1 = salt->body.bod.bod.list_flags
00441caf        salt->state = 0
00441cb9        list_flags_1:1.b &= 0xfd
00441cbc        salt->body.bod.bod.list_flags = list_flags_1
00441d3c        return
