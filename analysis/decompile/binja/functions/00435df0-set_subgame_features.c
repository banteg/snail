/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_subgame_features @ 0x435df0 */

00435df8        if (runtime->selected_level_record_active != 0)
00435dfa        struct SubSolution* selected_level_record = runtime->selected_level_record
00435e03        runtime->runtime_flags = selected_level_record->runtime_build_flags
00435e06        return selected_level_record
00435e07        int32_t level_mode = runtime->level_mode
00435e0a        runtime->runtime_flags = 0x484
00435e14        runtime->runtime_flags = &data_600484
00435e1d        switch (level_mode)
00435e24        case 0, 1
00435e24        runtime->runtime_flags = 0xf5cfff
00435e2c        case 4
00435e2c        runtime->runtime_flags = &g_font_queue[0x10d].v0:3
00435e34        case 7
00435e34        runtime->runtime_flags = 0xe4cfff
00435e3b        return level_mode
