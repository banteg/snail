/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_backdrop @ 0x410e20 */

00410e28        backdrop->unknown_65c = 1
00410e32        backdrop->unknown_660 = 0
00410e38        backdrop->active_primary_texture_id = 0xffffffff
00410e3f        backdrop->backdrop_change_queued = 0
00410e42        backdrop->zoom = 0f
00410e48        backdrop->unknown_6c4 = 5
00410e52        backdrop->unknown_6bc = 0f
00410e58        backdrop->unknown_6c0 = 0.00333333341f
00410e62        set_backdrop_texture_target(backdrop, 5)
00410e73        if ((g_runtime_config.render_flags.b & 1) == 0)
00410e87        backdrop->backdrop_render_enabled = 0
00410e8d        backdrop->unknown_664 = 0f
00410e75        backdrop->backdrop_render_enabled = 1
00410e7f        backdrop->unknown_664 = 1f
00410e97        backdrop->unknown_668 = 0.020833334f
00410ea3        if (last_mode == 0)
00410eca        backdrop->unknown_66c = 0f
00410ed0        backdrop->unknown_670 = 0.00130899693f
00410eda        backdrop->unknown_674 = 0f
00410ee0        backdrop->unknown_678 = 0.00174532935f
00410eea        label_410eea:
00410eea        backdrop->primary_world_blend.previous_world = 0
00410ef0        backdrop->primary_world_blend.current_world = 0
00410ef6        backdrop->primary_world_blend.blend = 1f
00410efc        backdrop->primary_world_blend.blend_step = 0.00555555569f
00410f06        backdrop->secondary_world_blend.previous_world = 0
00410f0c        backdrop->secondary_world_blend.current_world = 0
00410f12        backdrop->secondary_world_blend.blend = 1f
00410f18        backdrop->secondary_world_blend.blend_step = 0.00416666688f
00410ea6        if (last_mode == 1)
00410ea8        backdrop->unknown_66c = 0f
00410eae        backdrop->unknown_670 = -0.00261799386f
00410eb8        backdrop->unknown_674 = 0f
00410ebe        backdrop->unknown_678 = -0.00349065871f
00410ec8        goto label_410eea
00410f25        set_backdrop_texture_target(backdrop, 0)
00410f2d        set_backdrop_distort(backdrop, 0f)
00410f34        return
