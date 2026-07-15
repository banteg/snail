/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_intro_screen @ 0x4191e0 */

004191ea        int32_t i_1 = 0
004191f9        cache_music_file("music/introtext.ogg", 0, &g_blank_text)
004191fe        g_game_base
00419211        int32_t eax_1 = load_landscape_script_by_name("SpaceRed.txt")
0041921d        struct GameRoot* game_base_1 = g_game_base
00419230        change_backdrop(&game_base_1->backdrop, &game_base_1->unknown_000000[eax_1 * 0x124 + 0x106c7bc], 0)
00419242        set_border_justify_centre(&g_game_base->border_manager, 0f)
00419252        unhide_star_field(&g_game_base->star_manager)
00419260        void* pointer_1 = load_file_bytes(file_name, nullptr)
0041929e        logo->saved_render_flags = g_runtime_config.render_flags
004192a1        struct TransformMatrix transform
004192a1        struct TransformMatrix* eax_3 = initialize_matrix_from_values(&transform, 1f, 0f, 0f, 0f, 0f, 0.634392977f, 0.773010015f, 0f, 0f, -0.773010015f, 0.634392977f, 0f, 0f, 0f, 0f, 1f)
004192b9        __builtin_memcpy(&g_game_base->players[0].transform, eax_3, 0x40)
004192c1        g_game_base->players[0].camera.fov_degrees = 100f
004192cb        logo->progress = 0
004192ce        logo->progress_step = 0.00166666671f
004192e0        release_mouse_cursor(&g_game_base->players[0].mouse_cursor)
004192e5        void* pointer = pointer_1
004192e9        logo->state = 0
004192f2        float var_16c = 0.200000003f
004192fa        logo->renderable_count = 0
004192fd        char* cursor_1 = find_case_insensitive_substring("Text Start:", pointer)
00419308        char* cursor = cursor_1
00419312        cursor = &find_case_insensitive_substring(":", cursor_1)[1]
0041931c        char* eax_7 = find_case_insensitive_substring("Text End:", pointer)
00419321        char* cursor_3 = cursor
0041932a        char* var_144 = eax_7
0041932e        if (cursor_3 u< eax_7)
0041933a        struct Object** var_168_1 = &logo->image_donors[0].renderable.bod.object
0041933e        eax_7.b = *cursor_3
00419340        char* edi_1 = nullptr
00419344        float var_164_1 = 0f
00419348        char* cursor_5 = cursor_3
0041934a        if (eax_7.b == 0x2a)
00419350        char* cursor_4 = &cursor_3[1]
00419351        void var_100
00419351        char* eax_8 = &var_100
00419358        cursor = cursor_4
0041935c        char i = *cursor_4
00419361        while (i != 0x2e)
00419363        *eax_8 = i
00419365        eax_8 = &eax_8[1]
00419366        cursor_4 = &cursor_4[1]
00419367        cursor = cursor_4
0041936b        i = *cursor_4
00419372        *eax_8 = 0x2e
00419376        eax_8[1] = 0x74
0041937a        eax_8[2] = 0x67
0041937f        eax_8[3] = 0x61
00419382        eax_8[4] = 0
00419389        cursor = &cursor_4[1]
00419393        float var_170_1 = fconvert.s(parse_next_float32(&cursor))
004193a1        float var_174_1 = fconvert.s(parse_next_float32(&cursor))
004193b3        void* var_194_1 = &var_100
004193ba        void texture_path
004193ba        sprintf(&texture_path, "Intro/%s")
004193bf        logo->renderable_count
004193da        if ((0x200 & logo->letters[logo->:0x14.d].renderable.bod.bod.list_flags) == 0)
004193eb        struct GameRoot* game_base_2 = g_game_base
004193f7        struct FrameBodBase* first = game_base_2->active_bod_list.first
004193ff        if (first != 0)
0041940d        first->bod.list_prev = &logo->letters[logo->:0x14.d]
00419410        void* first_1 = game_base_2->active_bod_list.first
00419415        *(*(first_1 + 8) + 0xc) = first_1
0041941a        void* list_prev = game_base_2->active_bod_list.first->bod.list_prev
0041941d        game_base_2->active_bod_list.first = list_prev
0041941f        *(list_prev + 8) = 0
00419401        game_base_2->active_bod_list.first = &logo->letters[logo->:0x14.d]
00419403        logo->letters[logo->:0x14.d].renderable.o.list_prev = nullptr
00419408        game_base_2->active_bod_list.first->bod.list_next = 0
00419422        logo->letters[logo->:0x14.d].renderable.o.list_flags |= 0x200
004193e1        report_errorf("List ADD")
00419439        set_bod_object(&logo->letters[logo->renderable_count], (var_168_1 - 0x2403c)->image_donors[0].renderable.bod.object)
00419462        logo->letters[logo->renderable_count].renderable.bod.object->facequads->texture_ref = get_or_create_texture_ref(&g_texture_refs, &texture_path, 0, 0)
00419472        set_matrix_identity(&logo->letters[logo->renderable_count].renderable.transform)
00419477        int32_t renderable_count = logo->renderable_count
004194b1        logo->letters[renderable_count].renderable.transform.position.x = 0
004194b7        logo->letters[renderable_count].renderable.transform.position.y = 0xc0800000
004194ba        float var_168_2 = fconvert.s(fconvert.t(var_174_1) * fconvert.t(0.5f))
004194c2        logo->letters[renderable_count].renderable.transform.position.z = 0
004194c5        logo->renderable_count
004194e0        logo->letters[logo->:0x14.d].renderable.transform.position.z = fconvert.s(fconvert.t(var_16c) - fconvert.t(var_168_2) + fconvert.t(logo->letters[logo->:0x14.d].renderable.transform.position.z))
004194ef        set_color_white(&logo->letters[logo->renderable_count].renderable.bod.color)
00419501        long double x87_r7_9 = fconvert.t(var_170_1) * fconvert.t(0.5f)
00419507        logo->letters[logo->renderable_count].renderable.bod.color.a = 0x3f7fbe77
00419518        logo->letters[logo->renderable_count].glyph = 0xff
00419530        logo->letters[logo->renderable_count].renderable.bod.object->vertices->x = fconvert.s(x87_r7_9)
0041953f        long double x87_r6_2 = fconvert.t(var_170_1) * fconvert.t(-0.5f)
00419550        logo->letters[logo->renderable_count].renderable.bod.object->vertices->z = var_168_2
00419563        logo->letters[logo->renderable_count].renderable.bod.object->vertices[1].x = fconvert.s(x87_r6_2)
0041957a        *(logo->letters[logo->renderable_count].renderable.bod.object->vertices + 0x14) = var_168_2
0041958d        logo->letters[logo->renderable_count].renderable.bod.object->vertices[2].x = fconvert.s(x87_r6_2)
00419597        long double x87_r6_4 = fconvert.t(var_174_1) * fconvert.t(-0.5f)
004195a7        float var_170_2 = fconvert.s(x87_r6_4)
004195ae        *(logo->letters[logo->renderable_count].renderable.bod.object->vertices + 0x20) = fconvert.s(x87_r6_4)
004195c1        logo->letters[logo->renderable_count].renderable.bod.object->vertices[3].x = fconvert.s(x87_r7_9)
004195d8        *(logo->letters[logo->renderable_count].renderable.bod.object->vertices + 0x2c) = var_170_2
004195db        int32_t renderable_count_1 = logo->renderable_count
004195eb        logo->letters[renderable_count_1].velocity.z = 0
004195ee        logo->letters[renderable_count_1].velocity.y = 0
004195f1        logo->letters[renderable_count_1].velocity.x = 0
00419604        eax_7 = (*logo->letters[logo->renderable_count].renderable.bod.bod.vtable)()
0041960a        cursor_3 = cursor
00419618        var_168_1 = &var_168_1[0x24]
00419620        logo->renderable_count += 1
00419623        eax_7.b = *cursor_3
00419625        var_16c = fconvert.s(fconvert.t(var_16c) - fconvert.t(var_174_1))
0041962b        if (eax_7.b != 0)
00419633        while (eax_7.b != 0xd)
00419639        cursor_3 = &cursor_3[1]
0041963a        cursor = cursor_3
0041963e        eax_7.b = *cursor_3
00419642        if (eax_7.b == 0)
00419642        break
0041964b        if (eax_7.b != 0)
00419653        while (eax_7.b != 0xd)
00419656        eax_7 = font_slot_index_for_char(eax_7.b)
00419666        long double x87_r7_13 = fconvert.t(var_164_1) + fconvert.t(g_font3d_scales[eax_7])
0041966d        edi_1 = &edi_1[1]
0041966e        cursor_3 = &cursor[1]
0041966f        cursor = cursor_3
00419673        eax_7.b = *cursor_3
00419675        var_164_1 = fconvert.s(x87_r7_13)
0041967b        if (eax_7.b == 0)
0041967b        break
0041967f        if (edi_1 s> 0)
0041968f        int32_t var_160_1 = 0
00419697        int32_t var_15c_1 = 0xc0800000
0041969f        int32_t var_158_1 = 0
004196a7        char* var_170_3 = edi_1
004196b1        float var_174_2 = fconvert.s(fconvert.t(var_164_1) * fconvert.t(0.5f) * fconvert.t(0.800000012f))
00419849        bool cond:3_1
004196b5        logo->renderable_count
004196c9        uint32_t list_flags
004196c9        if (((logo->letters[logo->:0x14.d].renderable.bod.bod.list_flags).w:1.b & 2) == 0)
004196da        struct GameRoot* game_base_3 = g_game_base
004196e6        struct FrameBodBase* first_2 = game_base_3->active_bod_list.first
004196ee        if (first_2 != 0)
004196fc        first_2->bod.list_prev = &logo->letters[logo->:0x14.d]
004196ff        void* first_3 = game_base_3->active_bod_list.first
00419704        *(*(first_3 + 8) + 0xc) = first_3
00419709        void* list_prev_1 = game_base_3->active_bod_list.first->bod.list_prev
0041970c        game_base_3->active_bod_list.first = list_prev_1
0041970e        *(list_prev_1 + 8) = 0
004196f0        game_base_3->active_bod_list.first = &logo->letters[logo->:0x14.d]
004196f2        logo->letters[logo->:0x14.d].renderable.o.list_prev = nullptr
004196f7        game_base_3->active_bod_list.first->bod.list_next = 0
00419711        list_flags = logo->letters[logo->:0x14.d].renderable.o.list_flags
00419714        list_flags:1.b |= 2
00419717        logo->letters[logo->:0x14.d].renderable.o.list_flags = list_flags
004196d0        list_flags = report_errorf("List ADD")
0041971a        list_flags.b = *cursor_5
0041971d        int32_t eax_57 = font_slot_index_for_char(list_flags.b)
00419743        set_bod_object(&logo->letters[logo->renderable_count], g_font3d_bods[eax_57].object)
00419755        set_matrix_identity(&logo->letters[logo->renderable_count].renderable.transform)
0041975a        int32_t renderable_count_2 = logo->renderable_count
00419776        logo->letters[renderable_count_2].renderable.transform.position.x = var_160_1
0041977c        logo->letters[renderable_count_2].renderable.transform.position.y = var_15c_1
0041977f        logo->letters[renderable_count_2].renderable.transform.position.z = var_158_1
00419782        logo->renderable_count
00419799        logo->letters[logo->:0x14.d].renderable.transform.position.x = fconvert.s(fconvert.t(var_174_2) + fconvert.t(logo->letters[logo->:0x14.d].renderable.transform.position.x))
0041979b        logo->renderable_count
004197b6        logo->letters[logo->:0x14.d].renderable.transform.position.z = fconvert.s(fconvert.t(var_16c) + fconvert.t(logo->letters[logo->:0x14.d].renderable.transform.position.z))
004197c5        set_color_white(&logo->letters[logo->renderable_count].renderable.bod.color)
004197d3        logo->letters[logo->renderable_count].renderable.bod.color.a = 0x3f7fbe77
004197db        int32_t renderable_count_3 = logo->renderable_count
004197eb        logo->letters[renderable_count_3].velocity.z = 0
004197ee        logo->letters[renderable_count_3].velocity.y = 0
004197f1        logo->letters[renderable_count_3].velocity.x = 0
004197fe        logo->letters[logo->renderable_count].glyph = *cursor_5
00419816        (*logo->letters[logo->renderable_count].renderable.bod.bod.vtable)()
00419827        long double x87_r7_22 = fconvert.t(g_font3d_scales[font_slot_index_for_char(*cursor_5)]) * fconvert.t(0.800000012f)
00419833        cursor_5 = &cursor_5[1]
00419839        logo->renderable_count += 1
0041983c        var_174_2 = fconvert.s(fconvert.t(var_174_2) - x87_r7_22)
00419844        eax_7 = var_170_3 - 1
00419844        cond:3_1 = var_170_3 != 1
00419845        var_170_3 = eax_7
00419849        do while (cond:3_1)
0041984f        cursor_3 = cursor
00419856        if (*cursor_3 == 0xd)
00419862        cursor_3 = &cursor_3[2]
00419865        cursor = cursor_3
00419869        var_16c = fconvert.s(fconvert.t(var_16c) - fconvert.t(1f))
00419871        do while (cursor_3 u< var_144)
00419877        pointer = pointer_1
00419881        char* cursor_2 = find_case_insensitive_substring("Duration:", pointer)
0041988c        cursor = cursor_2
00419899        cursor = find_case_insensitive_substring(":", cursor_2)
0041989e        long double st0_3 = parse_next_float32(&cursor)
004198a3        logo->duration_seconds = fconvert.s(st0_3)
004198b4        int32_t var_160_2 = 0
004198d6        float var_158_2 = fconvert.s(fconvert.t(1f) / (st0_3 * fconvert.t(60f)) * (fconvert.t(3f) - fconvert.t(var_16c)))
004198da        if (logo->renderable_count s> 0)
004198e0        int32_t* eax_83 = &logo->letters[0].velocity
004198ea        int32_t* edx_36 = eax_83
004198ec        i_1 += 1
004198ed        eax_83 = &eax_83[0x24]
004198f2        *edx_36 = var_160_2
004198f8        edx_36[1] = 0
004198fb        edx_36[2] = var_158_2
00419903        do while (i_1 s< logo->renderable_count)
00419906        free_tracked_memory(pointer)
00419918        return
