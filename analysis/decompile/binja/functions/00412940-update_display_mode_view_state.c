/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_display_mode_view_state @ 0x412940 */

0041294b        if (state->current_mode == 0)
0041294d        struct DisplayModeRecord* eax_1
0041294d        eax_1.b = 0
00412953        return 0
00412955        get_authored_view_width()
0041295c        get_authored_view_height()
00412961        int32_t probe_count_1 = state->probe_count
004129ae        int32_t probe_count
00412983        float y
00412983        float height
00412983        float width
00412983        float x
00412983        if (read_next_display_mode_view_sample(state, &x, &y, &width, &height).b == 0)
00412983        break
0041298d        int32_t eax_2
0041298d        int16_t x87control
0041298d        eax_2, x87control = ftol(x87control, fconvert.t(y) + fconvert.t(height))
00412995        int32_t edx_1 = 0
00412997        edx_1.w = state->current_mode->height
0041299d        probe_count = state->probe_count
004129a0        y = edx_1 - eax_2
004129aa        y = fconvert.s(float.t(y))
004129ae        do while (probe_count == probe_count_1)
004129b1        int32_t eax_3
004129b1        eax_3.b = 1
004129b7        return 1
