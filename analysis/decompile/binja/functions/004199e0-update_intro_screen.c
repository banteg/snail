/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_intro_screen @ 0x4199e0 */

004199e0        struct GameRoot* game_base_1 = g_game_base
004199ed        if (game_base_1->fade.state == 0)
004199fb        char eax_1
004199fb        if (((game_base_1->players[0].game_input->input.pressed_buttons).w:1.b & 0x40) == 0)
004199fd        eax_1 = read_pressed_text_input_key_code()
00419a04        if (((game_base_1->players[0].game_input->input.pressed_buttons).w:1.b & 0x40) != 0 || eax_1 == 0xb)
00419a11        begin_frontend_fade_out(&g_game_base->fade, 0)
00419a20        if (g_game_base->fade.state == 4)
00419a24        destroy_intro_screen(logo)
00419a29        int32_t state = logo->state
00419a2f        if (state == 0)
00419a63        long double x87_r7_4 = fconvert.t(logo->duration_seconds) * fconvert.t(60f)
00419a69        logo->progress = 0
00419a6f        logo->state = 1
00419a7c        logo->progress_step = fconvert.s(fconvert.t(1f) / x87_r7_4)
00419a32        if (state == 1)
00419a37        long double x87_r7_2 = fconvert.t(logo->progress_step) + fconvert.t(logo->progress)
00419a39        logo->progress = fconvert.s(x87_r7_2)
00419a3b        long double temp2_1 = fconvert.t(1f)
00419a3b        x87_r7_2 - temp2_1
00419a46        if ((((x87_r7_2 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp2_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00419a52        begin_frontend_fade_out(&g_game_base->fade, 0)
00419a5b        logo->state += 1
00419a80        return
