/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: change_backdrop_real @ 0x410dc0 */

00410dc5        int32_t pending_primary_texture_id = backdrop->pending_primary_texture_id
00410dca        if (pending_primary_texture_id == 0)
00410e03        uint8_t pending_flip_1 = backdrop->pending_flip
00410e06        uint8_t pending_split_backdrop_pair_1 = backdrop->pending_split_backdrop_pair
00410e09        backdrop->backdrop_render_enabled = 0
00410e0f        backdrop->active_flip = pending_flip_1
00410e12        backdrop->active_split_backdrop_pair = pending_split_backdrop_pair_1
00410e16        return
00410dcf        if (pending_primary_texture_id != backdrop->active_primary_texture_id)
00410dd1        backdrop->active_primary_texture_id = pending_primary_texture_id
00410dd7        backdrop->active_secondary_texture_id = backdrop->pending_secondary_texture_id
00410dda        backdrop->zoom = 0f
00410de6        set_backdrop_distort(backdrop, backdrop->pending_distort)
00410deb        uint8_t pending_flip = backdrop->pending_flip
00410dee        uint8_t pending_split_backdrop_pair = backdrop->pending_split_backdrop_pair
00410df1        backdrop->backdrop_render_enabled = 1
00410dfb        backdrop->active_flip = pending_flip
00410dfe        backdrop->active_split_backdrop_pair = pending_split_backdrop_pair
00410e02        return
