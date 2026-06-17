/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_vapour @ 0x442500 */

00442504        int32_t esi
00442504        int32_t var_4 = esi
0044250c        struct VapourTrailOwner* owner = trail->owner
0044250f        float arg_8
0044250f        trail->half_width = arg_8
00442515        int32_t eax
00442515        eax.b = owner->max_points.b
00442515        eax:1.b = owner->max_points:1.b
00442515        eax:2.b = owner->max_points:2.b
00442515        eax:3.b = owner->max_points:3.b
00442519        trail->capacity = eax + 1
00442523        struct TransformMatrix* eax_3
00442523        int32_t z_floor
00442523        eax_3, z_floor = allocate_tracked_memory((eax + 1) << 6, "Vapour Trail")
0044252d        trail->points = eax_3
0044253b        return reset_vapour(trail, z_floor)
