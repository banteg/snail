/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: show_times_up_message @ 0x445e90 */

00445e99        if (times_up->state != TIMES_UP_STATE_INACTIVE)
00445e99        return
00445ec7        times_up->border = allocate_border(&g_game_base->border_manager)
00445eca        struct tColour color
00445eca        struct tColour* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 0.0299999993f)
00445ee6        initialize_frontend_widget(times_up->border, &__dos_header.e_cblp, "Time's Up", 0x14, 0f, 200f, color_1, 2, 0f)
00445eeb        times_up->progress = 0f
00445ef2        times_up->progress_step = 0.00555555569f
00445ef9        times_up->state = 1
00445f03        return
