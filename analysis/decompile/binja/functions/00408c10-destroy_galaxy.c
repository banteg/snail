/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_galaxy @ 0x408c10 */

00408c26        kill_border(&g_game_base->border_manager, galaxy->route_title_widget)
00408c3d        kill_border(&g_game_base->border_manager, galaxy->route_icon_widget)
00408c55        kill_border(&g_game_base->border_manager, galaxy->exit_or_back_widget)
00408c6d        kill_border(&g_game_base->border_manager, galaxy->bounds_frame_widget)
00408c84        kill_border(&g_game_base->border_manager, galaxy->selected_title_widget)
00408c9c        kill_border(&g_game_base->border_manager, galaxy->selected_description_widget)
00408cb4        kill_border(&g_game_base->border_manager, galaxy->selected_detail_widget)
00408ccb        kill_border(&g_game_base->border_manager, galaxy->play_or_deliver_widget)
00408ce3        kill_border(&g_game_base->border_manager, galaxy->replay_widget)
00408ce9        return
