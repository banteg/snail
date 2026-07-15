/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: apply_audio_config_volumes @ 0x41b070 */
/* selector: apply_audio_config_volumes */

// Pushes the saved sound and music scalar fields from SnailMail.cfg into the audio engine through the root-owned cROptions receiver. Cross-port `cROptions::Apply(bool)` is a broader lifecycle member; Windows retains this exact no-argument audio subset.
void __thiscall apply_audio_config_volumes(Options *options)
{
  float v1; // [esp+0h] [ebp-4h]

  set_global_sample_volume_config(g_runtime_config.sample_volume);
  v1 = g_stream_volume_scale * g_runtime_config.stream_volume;
  set_global_stream_volume_config(v1);
}
