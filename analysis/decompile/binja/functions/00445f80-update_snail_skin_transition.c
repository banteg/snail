/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_snail_skin_transition @ 0x445f80 */

00445f83        struct Object* object = snail_skin->owner_snail->body.bod.object
00445f8c        object->flags |= OBJECT_FLAG_USE_OVERRIDE_TEXTURE
00445f9b        snail_skin->owner_snail->body.bod.object->override_texture_ref = snail_skin->material_overrides[snail_skin->selected_slot]
00445fa2        if (snail_skin->active != 1)
00445fa2        return
00445fa7        long double x87_r7_2 = fconvert.t(snail_skin->progress_step) + fconvert.t(snail_skin->progress)
00445faa        snail_skin->progress = fconvert.s(x87_r7_2)
00445fad        long double temp1_1 = fconvert.t(1f)
00445fad        x87_r7_2 - temp1_1
00445fb8        if ((((x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00445fb8        return
00445fbc        snail_skin->progress = 0f
00445fbf        snail_skin->active = 0
00445fc2        snail_skin->selected_slot = 0
00445fc4        return
