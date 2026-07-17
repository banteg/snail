/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: change_backdrop @ 0x410d50 */

00410d55        int32_t edx = 0
00410d5e        int32_t backdrop_texture_id = record->backdrop_texture_id
00410d66        if (record->split_backdrop_texture_pair == 0)
00410d8e        if (backdrop_texture_id != 0)
00410d90        backdrop->pending_split_backdrop_pair = 0
00410d93        edx = 1
00410d98        backdrop->backdrop_change_queued = 1
00410da1        backdrop->pending_primary_texture_id = record->backdrop_texture_id
00410daa        backdrop->pending_distort = record->distort
00410db1        backdrop->pending_flip = flip
00410d6a        if (backdrop_texture_id != 0)
00410d6c        edx = 1
00410d71        backdrop->pending_split_backdrop_pair = 1
00410d74        backdrop->backdrop_change_queued = 1
00410d7d        backdrop->pending_primary_texture_id = record->backdrop_texture_id
00410d87        backdrop->pending_secondary_texture_id = record->backdrop_texture_id + 1
00410daa        backdrop->pending_distort = record->distort
00410db1        backdrop->pending_flip = flip
00410db5        backdrop->backdrop_render_enabled = edx
00410dbc        return
