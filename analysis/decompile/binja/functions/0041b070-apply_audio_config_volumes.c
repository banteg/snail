/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: apply_audio_config_volumes @ 0x41b070 */

0041b08c        int32_t var_4_1 = set_global_sample_volume_config(data_4df918)
0041b09a        return set_global_stream_volume_config(fconvert.s(fconvert.t(data_753c64) * fconvert.t(data_4df91c)))
