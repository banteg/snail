/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: read_next_display_mode_view_sample @ 0x407930 */

00407934        if (state->probe_count s>= 2)
0040798a        int32_t queued_view_sample_count = state->queued_view_sample_count
0040798e        if (queued_view_sample_count == 0)
004079d2        int32_t eax_17
004079d2        eax_17.b = 0
004079d4        return 0
00407995        state->queued_view_sample_count = queued_view_sample_count - 1
0040799e        *x = (&state->view_samples)[queued_view_sample_count - 1][0].x
004079ad        *y = *(((state->queued_view_sample_count + 1) << 4) + state)
004079bc        *width = state->view_samples[state->queued_view_sample_count].width
004079cb        int32_t eax_16
004079cb        eax_16.b = 1
004079cd        *height = state->view_samples[state->queued_view_sample_count].height
004079cf        return 1
0040793e        *x = 0f
00407944        *y = 0f
0040794d        float* edx_1 = nullptr
0040794f        edx_1.w = state->current_mode->width
0040795f        *width = fconvert.s(float.t(edx_1))
00407964        float* eax_3 = nullptr
00407966        eax_3.w = state->current_mode->height
00407976        *height = fconvert.s(float.t(eax_3))
00407978        int32_t probe_count = state->probe_count
0040797b        state->queued_view_sample_count = 0
00407982        state->probe_count = probe_count + 1
00407985        int32_t eax_5
00407985        eax_5.b = 1
00407987        return 1
