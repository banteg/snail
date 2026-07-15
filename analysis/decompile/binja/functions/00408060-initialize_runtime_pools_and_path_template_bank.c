/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_runtime_pools_and_path_template_bank @ 0x408060 */

0040807f        initialize_array_with_constructor(arg1 + 0xb4, 0x3c, 0x2cb, initialize_active_bod)
00408097        initialize_array_with_constructor(arg1 + 0xa878, 0x4220, 0x64, noop_runtime_slot_constructor)
004080af        initialize_array_with_constructor(arg1 + 0x1a850c, 0x38, 0x100, noop_runtime_slot_constructor)
004080c7        initialize_array_with_constructor(arg1 + 0x1ac72c, 0x38, 0x100, noop_runtime_slot_constructor)
004080ea        initialize_array_with_constructor(arg1 + 0x1b01f0, 0x4220, 0x64, noop_runtime_slot_constructor)
00408102        initialize_array_with_constructor(arg1 + 0x34de84, 0x38, 0x100, noop_runtime_slot_constructor)
0040811a        initialize_array_with_constructor(arg1 + 0x3520a4, 0x38, 0x100, noop_runtime_slot_constructor)
00408130        initialize_bod_base(arg1 + 0x355b64)
0040813b        initialize_bod_base(arg1 + 0x355b9c)
00408146        initialize_bod_base(arg1 + 0x355bd4)
00408151        initialize_bod_base(arg1 + 0x355c0c)
0040815c        initialize_bod_base(arg1 + 0x355c44)
00408167        initialize_bod_base(arg1 + 0x355c7c)
00408172        initialize_bod_base(arg1 + 0x355cb4)
0040817d        initialize_bod_base(arg1 + 0x355cec)
00408188        initialize_bod_base(arg1 + 0x355d24)
00408193        initialize_bod_base(arg1 + 0x355d5c)
0040819e        initialize_track_speedup_runtime(arg1 + 0x355db0)
004081a9        initialize_track_jetpack_pickup_runtime(arg1 + 0x355e64)
004081ae        struct SubHealth* pickup = arg1 + 0x356000
004081b4        int32_t i_8 = 8
004081c4        int32_t i
004081bb        initialize_track_health_pickup_runtime(pickup)
004081c0        pickup = &pickup[1]
004081c3        i = i_8
004081c3        i_8 -= 1
004081c4        do while (i != 1)
004081c6        struct Slug* slug = arg1 + 0x3563a0
004081cc        int32_t i_9 = 8
004081df        int32_t i_1
004081d3        initialize_slug_hazard_runtime(slug)
004081d8        slug = &slug[1]
004081de        i_1 = i_9
004081de        i_9 -= 1
004081df        do while (i_1 != 1)
004081f4        initialize_array_with_constructor(arg1 + 0x356b00, 0xb0, 0x14, initialize_sub_lazer_runtime)
0040820c        initialize_array_with_constructor(arg1 + 0x3578c0, 0x98, 0x28, initialize_salt_hazard_runtime)
00408211        void*** bod = arg1 + 0x359080
00408217        int32_t i_10 = 2
0040822d        int32_t i_2
0040821e        initialize_bod_base(bod)
00408223        *bod = &g_banner_callback_table
00408229        bod = &bod[0x18]
0040822c        i_2 = i_10
0040822c        i_10 -= 1
0040822d        do while (i_2 != 1)
0040822f        struct SubGarbage* sub_garbage = arg1 + 0x359144
00408235        int32_t i_11 = 0x32
00408248        int32_t i_3
0040823c        initialize_garbage_hazard(sub_garbage)
00408241        sub_garbage = &sub_garbage[1]
00408247        i_3 = i_11
00408247        i_11 -= 1
00408248        do while (i_3 != 1)
0040824a        struct SubRing* ring = arg1 + 0x35b78c
00408250        int32_t i_12 = 2
00408263        int32_t i_4
00408257        initialize_track_ring_or_special_effect_runtime(ring)
0040825c        ring = &ring[1]
00408262        i_4 = i_12
00408262        i_12 -= 1
00408263        do while (i_4 != 1)
00408278        initialize_array_with_constructor(arg1 + 0x35bbbc, 0x38, 0x1b58, initialize_fringe_object)
00408285        initialize_renderable_bod(arg1 + 0x3bb764)
00408290        initialize_click_start_controller_runtime(arg1 + 0x3bb804)
004082be        initialize_array_with_constructor(arg1 + 0x3bbbb4, 0x2e8, 0xc, initialize_golb_shot)
004082c9        initialize_player_presentation_controller(arg1 + 0x3be0e8)
004082ce        *(arg1 + 0x3bb764) = &g_subgoldy_callback_table
004082d4        SubLoc* cell = arg1 + 0x3bfac8
004082da        int32_t i_13 = 0x6400
004082ea        int32_t i_5
004082e1        initialize_sub_loc(cell)
004082e6        cell = &cell[1]
004082e9        i_5 = i_13
004082e9        i_13 -= 1
004082ea        do while (i_5 != 1)
004082ec        void* edi_3 = arg1 + 0x5ccac8
004082f2        int32_t i_14 = 0xc80
00408305        int32_t i_6
004082f9        initialize_track_row_runtime(edi_3)
004082fe        edi_3 += 0xf4
00408304        i_6 = i_14
00408304        i_14 -= 1
00408305        do while (i_6 != 1)
00408307        struct BodBase* edi_4 = arg1 + 0xff2914
0040830d        int32_t i_15 = 0x7e
00408320        int32_t i_7
00408314        initialize_path_template_record_pair(edi_4)
00408319        edi_4 = &edi_4[3]
0040831f        i_7 = i_15
0040831f        i_15 -= 1
00408320        do while (i_7 != 1)
0040832a        initialize_bod_base(arg1 + 0xff7bc4)
0040832f        *(arg1 + 0xff7bc4) = &g_barrier_actor_callback_table
00408348        initialize_array_with_constructor(arg1 + 0xff7c00, 0x90, 0xa, initialize_active_landscape_entry)
00408363        initialize_array_with_constructor(arg1 + 0xff81a4, 0x124, 0x80, initialize_landscape_script_record)
00408370        initialize_bod_base(arg1 + 0x10013a4)
00408378        std::_Vector_iterator<class std::_Vector_val<struct std::_Simple_types<class std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<uint8_t,class Concurrency::details::_CancellationTokenState*> > > > > >::operator++(arg1 + 0x10013dc)
00408393        *(arg1 + 0x10013a4) = &g_smtracks_callback_table
00408399        initialize_array_with_constructor(arg1 + 0x10014d0, 0x4088, 0x96, noop_runtime_slot_constructor)
004083b1        initialize_array_with_constructor(arg1 + 0x125e480, 0x8c, 0x32, initialize_track_parcel_runtime)
004083c9        initialize_array_with_constructor(arg1 + 0x1260030, 0x2a0, 0x65, noop_runtime_slot_constructor)
004083e1        initialize_array_with_constructor(arg1 + 0x1270950, 0xa0, 0xa, initialize_galaxy_route_name_record)
004083f9        initialize_array_with_constructor(arg1 + 0x1270fd8, 0x18, 0x100, noop_runtime_slot_constructor)
00408403        return arg1
