/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_loading_screen @ 0x418e50 */

00418e56        g_runtime_config.last_loading_budget = loading_bar->last_loading_budget
00418e5b        int32_t* loading_bar_on_texture_1 = g_loading_bar_on_texture
00418e63        (*(*loading_bar_on_texture_1 + 8))(loading_bar_on_texture_1)
00418e66        int32_t* loading_background_texture_1 = g_loading_background_texture
00418e6e        (*(*loading_background_texture_1 + 8))(loading_background_texture_1)
00418e71        loading_bar->active = 0
00418e78        return
