/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: start_invincible_shell @ 0x444ae0 */

00444ae0        int32_t state = shell->state
00444aea        if (state == 0)
00444b01        shell->state = 1
00444b0b        shell->spin_phase = 0f
00444b11        shell->spin_phase_step = 0.0333333351f
00444b17        shell->fade_progress = 0f
00444b1d        shell->fade_step = 0.0333333351f
00444b23        void* eax = data_4df904
00444b34        *(eax + 0x433f98) |= 0x20
00444b3b        play_registered_sound_sample_scaled(0x30, 1f)
00444aef        if (state == 3)
00444af1        shell->state = 1
00444b40        return
