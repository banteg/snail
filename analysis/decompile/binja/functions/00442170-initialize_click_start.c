/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_click_start @ 0x442170 */

004421a4        click_start->prompt = allocate_border(&g_game_base->border_manager)
004421aa        struct tColour color
004421aa        struct tColour* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 0.0299999993f)
004421c8        initialize_frontend_widget(click_start->prompt, &__dos_header.e_cblp, "Click to Start", 0x14, 0f, 200f, color_1, 2, 0f)
004421d3        hide_border_init(click_start->prompt)
004421d8        uint32_t list_flags = click_start->bod.bod.bod.list_flags
004421e4        click_start->hide_prompt = 1
004421ed        click_start->owner_player = player
004421f3        if ((0x200 & list_flags) == 0)
00442209        struct ClickStart** eax_2 = &g_game_base->active_bod_list.first
0044220e        struct ClickStart* ecx_5 = *eax_2
00442212        if (ecx_5 != 0)
00442220        ecx_5->bod.bod.bod.list_prev = click_start
00442223        struct ClickStart* ecx_6 = *eax_2
00442229        ecx_6->bod.bod.bod.list_prev->list_next = ecx_6
0044222f        struct ClickStart* list_prev = (*eax_2)->bod.bod.bod.list_prev
00442232        *eax_2 = list_prev
00442234        list_prev->bod.bod.bod.list_prev = nullptr
00442214        *eax_2 = click_start
00442216        click_start->bod.bod.bod.list_prev = nullptr
0044221b        (*eax_2)->bod.bod.bod.list_next = nullptr
00442237        click_start->bod.bod.bod.list_flags |= 0x200
004421fa        report_errorf("List ADD")
0044223a        struct Player* owner_player = click_start->owner_player
00442240        click_start->state = CLICK_START_STATE_WAITING_FOR_START
0044224a        owner_player->startup_track_index = 0
00442250        click_start->bod.bod.render_arg_1c = 0f
00442253        click_start->bod.bod.render_arg_20 = 0f
00442263        struct FrontendWidget* prompt = click_start->prompt
00442269        if (g_game_base->subgame.selected_level_record_active == 0)
00442278        unhide_border_init(prompt)
00442282        return
0044226b        hide_border_init(prompt)
00442275        return
