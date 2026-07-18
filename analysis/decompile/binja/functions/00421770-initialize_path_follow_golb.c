/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_path_follow_golb @ 0x421770 */

00421774        state->active = 1
00421777        struct Path* attachment_template_record = source_cell->attachment_template_record
0042177a        state->source_cell = source_cell
0042177d        state->template_record = attachment_template_record
00421784        state->sample_index = 0
0042178e        long double x87_r7_1 = fconvert.t(position->z) - fconvert.t(source_cell->anchor_position.z)
00421795        state->shot = shot
00421798        state->progress = fconvert.s(x87_r7_1)
004217a4        state->vertical_offset = fconvert.s(fconvert.t(position->y) - fconvert.t(0.49000001f))
004217a7        return shot
