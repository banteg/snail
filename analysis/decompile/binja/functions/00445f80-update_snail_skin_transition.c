/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_snail_skin_transition @ 0x445f80 */

00445f83        void* eax = *(state->owner_render_state + 0x24)
00445f8c        *(eax + 0x10) |= 8
00445f9b        *(*(state->owner_render_state + 0x24) + 0x18) = state->slot_ids[state->selected_slot]
00445fa2        if (state->active != 1)
00445fa2        return 
00445fa7        long double x87_r7_2 = fconvert.t(state->progress_step) + fconvert.t(state->progress)
00445faa        state->progress = fconvert.s(x87_r7_2)
00445fad        long double temp1_1 = fconvert.t(1f)
00445fad        x87_r7_2 - temp1_1
00445fb8        if ((((x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00445fb8        return 
00445fbc        state->progress = 0f
00445fbf        state->active = 0
00445fc2        state->selected_slot = 0
00445fc4        return
