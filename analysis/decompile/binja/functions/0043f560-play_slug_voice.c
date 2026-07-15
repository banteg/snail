/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: play_slug_voice @ 0x43f560 */

0043f568        if (slug->voice_active != 0)
0043f568        return
0043f56a        struct GameRoot* game_base_1 = g_game_base
0043f577        if (game_base_1->subgame.slug_voice_manager.active != 0)
0043f577        return
0043f581        game_base_1->subgame.slug_voice_manager.progress = game_base_1->subgame.slug_voice_manager.step
0043f594        g_game_base->subgame.slug_voice_manager.active = 1
0043f59a        slug->voice_active = 1
0043f5aa        slug->voice_progress = 0f
0043f5b4        play_voice_backend(sample_index, sample_index, 1f, -1f, 0f)
0043f5bc        return
