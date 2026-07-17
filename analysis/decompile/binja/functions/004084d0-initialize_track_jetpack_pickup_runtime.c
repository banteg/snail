/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_track_jetpack_pickup_runtime @ 0x4084d0 */

004084d4        initialize_bod_base(jetpack)
004084de        initialize_renderable_bod(&jetpack->vapour_a)
004084e3        jetpack->vapour_a.body.bod.bod.vtable = &g_vapour_vtable
004084f1        initialize_renderable_bod(&jetpack->vapour_b)
004084f6        jetpack->vapour_b.body.bod.bod.vtable = &g_vapour_vtable
004084fc        jetpack->bod.bod.vtable = &g_jet_pack_vtable
00408506        return jetpack
