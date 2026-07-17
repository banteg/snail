/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_backdrop_texture_target @ 0x410f40 */

00410f58        backdrop->primary_world_blend.previous_world = backdrop->primary_world_blend.current_world
00410f62        backdrop->primary_world_blend.current_world = world
00410f68        backdrop->secondary_world_blend.previous_world = backdrop->secondary_world_blend.current_world
00410f6e        backdrop->primary_world_blend.blend = fconvert.s(fconvert.t(1f) - fconvert.t(backdrop->primary_world_blend.blend))
00410f80        backdrop->secondary_world_blend.current_world = world
00410f86        backdrop->secondary_world_blend.blend = fconvert.s(fconvert.t(1f) - fconvert.t(backdrop->secondary_world_blend.blend))
00410f8c        return
