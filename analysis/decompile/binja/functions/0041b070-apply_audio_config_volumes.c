/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: apply_audio_config_volumes @ 0x41b070 */

0041b08c        int32_t var_4_1 = set_global_sample_volume_config(&g_audio_backend, g_runtime_config.sample_volume)
0041b095        set_global_stream_volume_config(&g_audio_backend, fconvert.s(fconvert.t(g_stream_volume_scale) * fconvert.t(g_runtime_config.stream_volume)))
0041b09a        return
