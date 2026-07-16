/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: start_invincible_shell @ 0x444ae0 */

00444ae0        enum InvincibleState state = invincible->state
00444aea        if (state == INVINCIBLE_STATE_INACTIVE)
00444b01        invincible->state = INVINCIBLE_STATE_FADING_IN
00444b0b        invincible->spin_phase = 0f
00444b11        invincible->spin_phase_step = 0.0333333351f
00444b17        invincible->fade_progress = 0f
00444b1d        invincible->fade_step = 0.0333333351f
00444b23        struct GameRoot* game_base_1 = g_game_base
00444b34        game_base_1->subgame.player.presentation.invincible_shell.body.bod.bod.list_flags |= 0x20
00444b3b        play_registered_sound_sample_scaled(&g_audio_backend, 0x30, 1f)
00444aef        if (state == INVINCIBLE_STATE_FADING_OUT)
00444af1        invincible->state = INVINCIBLE_STATE_FADING_IN
00444b40        return
