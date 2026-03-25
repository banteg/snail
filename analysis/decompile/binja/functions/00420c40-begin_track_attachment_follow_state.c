/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: begin_track_attachment_follow_state @ 0x420c40 */

00420c4b        follow_state->active = 1
00420c4e        struct PathTemplate* attachment_template_record = source_cell->attachment_template_record
00420c51        follow_state->source_cell = source_cell
00420c54        follow_state->template_record = attachment_template_record
00420c5b        follow_state->sample_index = 0
00420c68        follow_state->progress = fconvert.s(fconvert.t(world_position->z) - fconvert.t(source_cell->anchor_position.z))
00420c6e        long double x87_r7_3 = fconvert.t(world_position->y) - fconvert.t(0.49000001f)
00420c74        follow_state->player = player
00420c77        follow_state->vertical_offset = fconvert.s(x87_r7_3)
00420c7a        int32_t eax_1 = get_track_cell_row_index(source_cell)
00420c8e        struct PathTemplate* template_record = follow_state->template_record
00420c99        template_record->installed_heading_delta = *(data_4df904 + eax_1 * 0xf4 + 0x64118c)
00420c9f        return template_record
