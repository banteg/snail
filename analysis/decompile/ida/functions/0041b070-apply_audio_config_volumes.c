/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: apply_audio_config_volumes @ 0x41b070 */
/* selector: apply_audio_config_volumes */

// Pushes the saved sound and music scalar fields from SnailMail.cfg into the audio engine.
int sub_41B070()
{
  float v1; // [esp+0h] [ebp-4h]

  set_global_sample_volume_config(unk_4DF918);
  v1 = unk_753C64 * unk_4DF91C;
  return set_global_stream_volume_config(v1);
}

