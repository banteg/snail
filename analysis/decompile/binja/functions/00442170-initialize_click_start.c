/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_click_start @ 0x442170 */

004421a4        controller->prompt = allocate_border(data_4df904 + 0xb4c)
004421aa        struct Color4f color
004421aa        struct Color4f* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 0.0299999993f)
004421c8        initialize_frontend_widget(controller->prompt, &__dos_header.e_cblp, "Click to Start", 0x14, 0f, 200f, color_1, 2, 0f)
004421d3        hide_border_init(controller->prompt)
004421d8        int32_t list_flags = controller->list_flags
004421e4        controller->hide_prompt = 1
004421ed        struct ClickStartPlayer* arg_4
004421ed        controller->player = arg_4
004421f3        if ((0x200 & list_flags) == 0)
00442209        struct ClickStartController** eax_2 = data_4df904 + 0x5ac
0044220e        struct ClickStartController* ecx_5 = *eax_2
00442212        if (ecx_5 != 0)
00442220        ecx_5->list_prev = controller
00442223        struct ClickStartController* ecx_6 = *eax_2
00442229        ecx_6->list_prev->list_next = ecx_6
0044222f        struct ClickStartController* list_prev = (*eax_2)->list_prev
00442232        *eax_2 = list_prev
00442234        list_prev->list_prev = nullptr
00442214        *eax_2 = controller
00442216        controller->list_prev = nullptr
0044221b        (*eax_2)->list_next = nullptr
00442237        controller->list_flags |= 0x200
004421fa        report_errorf("List ADD")
0044223a        struct ClickStartPlayer* player_1 = controller->player
00442240        controller->state = 2
0044224a        player_1->startup_track_index = 0
00442250        controller->render_arg_1c = 0
00442253        controller->render_arg_20 = 0f
00442263        struct FrontendWidget* prompt = controller->prompt
00442269        if (*(data_4df904 + 0x1066be8) == 0)
00442278        unhide_border_init(prompt)
00442282        return
0044226b        hide_border_init(prompt)
00442275        return
