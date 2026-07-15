/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_galaxy @ 0x408cf0 */

00408d03        hide_star_field(&g_game_base->star_manager)
00408d15        cache_music_file("music/mainmenu.ogg", 0, &g_blank_text)
00408d2e        int32_t eax = load_landscape_script_by_name(&g_game_base->subgame.landscape_manager, "StarMap.txt")
00408d3a        struct GameRoot* game_base_1 = g_game_base
00408d4d        change_backdrop(&game_base_1->backdrop, &game_base_1->unknown_000000[eax * 0x124 + 0x106c7bc], 0)
00408d5e        set_border_justify_centre(&g_game_base->border_manager, 0f)
00408d6f        capture_mouse_cursor(&g_game_base->players[0].mouse_cursor)
00408d7f        g_game_base->render_skip_count = 2
00408d89        struct SubgameRuntime* level_progress_base = galaxy->level_progress_base
00408d92        if (level_progress_base->level_mode == 0)
00408d94        int32_t subgame_rebuild_selector = level_progress_base->subgame_rebuild_selector
00408da2        if (subgame_rebuild_selector == 3 || subgame_rebuild_selector == 2)
00408da4        galaxy->route_state = 0
00408da7        galaxy->route_mode = 0
00408db0        galaxy->selected_index = g_runtime_config.landscape_backdrop_variant_selector
00408dbc        if (level_progress_base->subgame_rebuild_selector == 1)
00408dbe        galaxy->route_state = 1
00408dc1        galaxy->route_mode = 1
00408dc7        galaxy->selected_index = level_progress_base->level_mode_arg
00408dd1        if (level_progress_base->level_mode == 4)
00408dd3        galaxy->route_state = 0
00408dd6        galaxy->route_mode = 2
00408de2        galaxy->selected_index = g_runtime_config.landscape_backdrop_variant_selector
00408e13        galaxy->route_title_widget = allocate_border(&g_game_base->border_manager)
00408e19        struct tColour color_2
00408e19        struct tColour* color_3 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00408e3b        initialize_frontend_widget(galaxy->route_title_widget, &__dos_header, "Intergalactic Delivery Route", 0x14, 15f, 15f, color_3, 0, 0f)
00408e46        galaxy->route_title_widget->font_scale = 0.829999983f
00408e7b        galaxy->route_icon_widget = allocate_border(&g_game_base->border_manager)
00408e81        struct tColour* eax_6 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00408ea1        initialize_frontend_sprite_button(galaxy->route_icon_widget, 0x20400802, 0x8a, 370f, 10f, eax_6, 0f, 4)
00408eb8        galaxy->exit_or_back_widget = allocate_border(&g_game_base->border_manager)
00408ed8        uint32_t widget_flags
00408ed8        char* text
00408ed8        struct tColour* color
00408ed8        if (galaxy->route_mode != 1)
00408f05        color = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00408f06        int32_t var_2c_1 = 0x43d20000
00408f0b        int32_t var_30_1 = 0x41a00000
00408f10        int32_t var_34_1 = 0x14
00408f12        text = "Back"
00408f17        widget_flags = 0x60000014
00408ee3        color = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00408ee4        int32_t var_2c = 0x43d20000
00408ee9        int32_t var_30 = 0x41a00000
00408eee        int32_t var_34 = 0x14
00408ef0        text = "Exit"
00408ef5        widget_flags = 0x20000014
00408f22        initialize_frontend_widget(galaxy->exit_or_back_widget, widget_flags, text, 0x14, 20f, 420f, color, 0, 0f)
00408f2a        int32_t i = 0
00408f2e        if (galaxy->record_count s> 0)
00408f30        float* eax_12 = &galaxy->route_slots[0].record.highlight_target
00408f33        (eax_12 - 0x2c)->route_slots[0].record.route_tint_alpha = 0f
00408f36        (eax_12 - 0x2c)->route_slots[0].record.highlight_target = 0f
00408f3b        i += 1
00408f3c        eax_12 = &eax_12[0xa8]
00408f43        do while (i s< galaxy->record_count)
00408f70        galaxy->bounds_frame_widget = allocate_border(&g_game_base->border_manager)
00408f76        struct tColour* color_4 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00408f98        initialize_frontend_widget(galaxy->bounds_frame_widget, 0x20010002, &g_blank_text, 0x14, 30f, 80f, color_4, 0, 0f)
00408fbd        store_color4f(&galaxy->bounds_frame_widget->hot_fill_color, 1f, 1f, 1f, 1f)
00408fc8        hide_border_init(galaxy->bounds_frame_widget)
00408fd3        galaxy->bounds_frame_widget->border_texture_id = 0x98
00408fda        struct FrontendWidget* bounds_frame_widget = galaxy->bounds_frame_widget
00408fe0        bounds_frame_widget->authored_left.b = 0
00408fe0        bounds_frame_widget->authored_left:1.b = 0
00408fe0        bounds_frame_widget->authored_left:2.b = 0xa0
00408fe0        bounds_frame_widget->authored_left:3.b = 0x43
00408fed        galaxy->bounds_frame_widget->authored_top = 240f
00408ffa        galaxy->bounds_frame_widget->authored_width = 200f
00409001        struct FrontendWidget* bounds_frame_widget_1 = galaxy->bounds_frame_widget
00409007        bounds_frame_widget_1->authored_height.b = 0
00409007        bounds_frame_widget_1->authored_height:1.b = 0
00409007        bounds_frame_widget_1->authored_height:2.b = 0xc8
00409007        bounds_frame_widget_1->authored_height:3.b = 0x42
00409039        galaxy->selected_title_widget = allocate_border(&g_game_base->border_manager)
0040903f        struct tColour* color_5 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00409061        initialize_frontend_widget(galaxy->selected_title_widget, 0x20400002, &g_blank_text, 0x14, 100f, 80f, color_5, 0, 0f)
0040906c        hide_border_init(galaxy->selected_title_widget)
0040907c        __builtin_strncpy(&galaxy->selected_title_widget->font_scale, "fff?", 4)
00409082        struct FrontendWidget* selected_title_widget = galaxy->selected_title_widget
00409088        selected_title_widget->stack_gap.b = 0
00409088        selected_title_widget->stack_gap:1.b = 0
00409088        selected_title_widget->stack_gap:2.b = 0
00409088        selected_title_widget->stack_gap:3.b = 0
004090b9        galaxy->selected_detail_widget = allocate_border(&g_game_base->border_manager)
004090bf        struct tColour* color_6 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
004090e1        initialize_frontend_widget(galaxy->selected_detail_widget, 0x20400002, &g_blank_text, 0x14, 300f, 440f, color_6, 0, 0f)
004090ec        hide_border_init(galaxy->selected_detail_widget)
004090f7        __builtin_strncpy(&galaxy->selected_detail_widget->font_scale, "fff?", 4)
004090fd        struct FrontendWidget* selected_detail_widget = galaxy->selected_detail_widget
00409103        selected_detail_widget->stack_gap.b = 0
00409103        selected_detail_widget->stack_gap:1.b = 0
00409103        selected_detail_widget->stack_gap:2.b = 0
00409103        selected_detail_widget->stack_gap:3.b = 0
00409134        galaxy->selected_description_widget = allocate_border(&g_game_base->border_manager)
0040913a        struct tColour* color_7 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
0040915c        initialize_frontend_widget(galaxy->selected_description_widget, 0x20400002, &g_blank_text, 0x14, 300f, 440f, color_7, 0, 0f)
00409167        hide_border_init(galaxy->selected_description_widget)
00409172        __builtin_strncpy(&galaxy->selected_description_widget->font_scale, "333?", 4)
0040917c        struct FrontendWidget* selected_description_widget = galaxy->selected_description_widget
00409182        selected_description_widget->stack_gap.b = 0
00409182        selected_description_widget->stack_gap:1.b = 0
00409182        selected_description_widget->stack_gap:2.b = 0
00409182        selected_description_widget->stack_gap:3.b = 0
00409199        galaxy->play_or_deliver_widget = allocate_border(&g_game_base->border_manager)
004091c5        char* text_1
004091c5        struct tColour* color_1
004091c5        if (galaxy->level_progress_base->level_mode != 0)
004091ed        color_1 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
004091ee        int32_t var_2c_3 = 0x43dc0000
004091f3        int32_t var_30_3 = 0x43960000
004091f8        int32_t var_34_3 = 0x14
004091fa        text_1 = "Play"
004091d0        color_1 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
004091d1        int32_t var_2c_2 = 0x43dc0000
004091d6        int32_t var_30_2 = 0x43960000
004091db        int32_t var_34_2 = 0x14
004091dd        text_1 = "Deliver!"
0040920a        initialize_frontend_widget(galaxy->play_or_deliver_widget, 0x60000014, text_1, 0x14, 300f, 440f, color_1, 2, 100f)
00409215        hide_border_init(galaxy->play_or_deliver_widget)
0040921a        struct FrontendWidget* play_or_deliver_widget = galaxy->play_or_deliver_widget
00409220        play_or_deliver_widget->stack_gap.b = 0
00409220        play_or_deliver_widget->stack_gap:1.b = 0
00409220        play_or_deliver_widget->stack_gap:2.b = 0xa0
00409220        play_or_deliver_widget->stack_gap:3.b = 0x41
00409256        galaxy->replay_widget = allocate_border(&g_game_base->border_manager)
0040925c        struct tColour* color_8 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
0040927e        initialize_frontend_widget(galaxy->replay_widget, 0x60000014, "Watch Best Trial", 0x14, 300f, 440f, color_8, 2, 0f)
00409289        hide_border_init(galaxy->replay_widget)
00409294        galaxy->replay_widget->stack_gap = 10f
0040929e        struct FrontendWidget* replay_widget = galaxy->replay_widget
004092a4        replay_widget->font_scale.b = 0xcd
004092a4        replay_widget->font_scale:1.b = 0xcc
004092a4        replay_widget->font_scale:2.b = 0x4c
004092a4        replay_widget->font_scale:3.b = 0x3f
004092b4        galaxy->replay_widget->idle_padding = 4f
004092c4        galaxy->replay_widget->idle_padding = 8f
004092d7        open_galaxy_route(galaxy, galaxy->selected_index)
004092e2        return
