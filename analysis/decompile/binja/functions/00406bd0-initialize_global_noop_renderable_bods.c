/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_global_noop_renderable_bods @ 0x406bd0 */

00406bd5        initialize_renderable_bod(&data_4b6fb4)
00406bdf        data_4b6fb4 = &g_noop_runtime_callback_table
00406be9        initialize_renderable_bod(&data_4b7078)
00406bf3        data_4b7078 = &g_noop_runtime_callback_table
00406bfd        struct RenderableBod* result = initialize_renderable_bod(&data_4b713c)
00406c02        data_4b713c = &g_noop_runtime_callback_table
00406c0c        return result
