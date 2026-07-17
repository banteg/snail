/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_active_landscape_entry @ 0x418ac0 */

00418acd        if (g_game_base->subgame.subgame_pause_gate != 0)
00418acd        return
00418acf        int32_t state = active_entry->state
00418adb        if (state == 0 || state != 1)
00418adb        return
00418add        struct Object* object = active_entry->bod.bod.object
00418ae1        struct RenderableBod* reference_bod = active_entry->reference_bod
00418aed        long double x87_r7_2 = fconvert.t(object->bounds_max.z) + fconvert.t(active_entry->bod.transform.position.z)
00418af3        long double x87_r6_2 = fconvert.t(reference_bod->transform.position.z) - fconvert.t(10f)
00418af9        x87_r6_2 - x87_r7_2
00418b00        if ((((x87_r6_2 < x87_r7_2 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_2, x87_r7_2) ? 1 : 0) << 0xa | (x87_r6_2 == x87_r7_2 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00418b11        active_entry->bod.transform.position.z = fconvert.s(fconvert.t(active_entry->repeat_z_span) * fconvert.t(3f) + fconvert.t(active_entry->bod.transform.position.z))
00418b20        long double x87_r7_7 = fconvert.t(object->bounds_min.z) + fconvert.t(active_entry->bod.transform.position.z)
00418b26        long double x87_r6_4 = fconvert.t(g_game_base->fog_end) + fconvert.t(reference_bod->transform.position.z)
00418b2a        x87_r6_4 - x87_r7_7
00418b31        uint32_t list_flags = active_entry->bod.bod.bod.list_flags
00418b34        if ((((x87_r6_4 < x87_r7_7 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_4, x87_r7_7) ? 1 : 0) << 0xa | (x87_r6_4 == x87_r7_7 ? 1 : 0) << 0xe):1.b & 1) != 0)
00418b36        list_flags.b &= 0xdf
00418b38        active_entry->bod.bod.bod.list_flags = list_flags
00418b3b        return
00418b3c        list_flags.b |= 0x20
00418b3e        active_entry->bod.bod.bod.list_flags = list_flags
00418b41        return
