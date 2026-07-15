/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: close_galaxy_route @ 0x409bf0 */

00409bf3        struct FrontendWidget* bounds_frame_widget = galaxy->bounds_frame_widget
00409bf9        galaxy->route_state = 0
00409c00        galaxy->selected_index = 0xffffffff
00409c0a        hide_border_init(bounds_frame_widget)
00409c15        hide_border_init(galaxy->selected_title_widget)
00409c20        hide_border_init(galaxy->selected_detail_widget)
00409c2b        hide_border_init(galaxy->selected_description_widget)
00409c36        hide_border_init(galaxy->play_or_deliver_widget)
00409c41        hide_border_init(galaxy->replay_widget)
00409c47        return
