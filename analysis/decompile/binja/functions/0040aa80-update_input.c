/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_input @ 0x40aa80 */

0040aa80        int32_t current_buttons = state->current_buttons
0040aa86        int32_t edx_1 = state->previous_buttons ^ current_buttons
0040aa8e        state->previous_buttons = current_buttons
0040aa91        state->pressed_buttons = edx_1 & current_buttons
0040aa96        int32_t esi_3 = not.d(current_buttons)
0040aa9a        state->inverse_current_buttons = esi_3
0040aa9f        state->current_buttons = 0
0040aaa6        state->released_buttons = esi_3 & edx_1
0040aaab        return
