/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: change_snail_skin @ 0x445fd0 */

00445fd0        long double x87_r7 = fconvert.t(duration_seconds)
00445fd4        long double temp1 = fconvert.t(0f)
00445fd4        x87_r7 - temp1
00445fdc        state->active = 1
00445fe3        state->progress = 0f
00445feb        if ((((x87_r7 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1) ? 1 : 0) << 0xa | (x87_r7 == temp1 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
00446007        state->selected_slot = slot_id
0044600f        state->progress_step = fconvert.s(fconvert.t(1f) / (fconvert.t(duration_seconds) * fconvert.t(60f)))
00446012        return 
00445ff1        state->progress_step = 0f
00445ff4        state->selected_slot = slot_id
00445ff6        return
