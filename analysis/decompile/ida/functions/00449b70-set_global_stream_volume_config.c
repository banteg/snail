/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_global_stream_volume_config @ 0x449b70 */
/* selector: set_global_stream_volume_config */

// Scales one normalized [0,1] stream-volume scalar onto BASS config option `5` (`BASS_CONFIG_GVOL_STREAM`) before the backend stores it as the live music or stream volume.
int32_t __thiscall set_global_stream_volume_config(AudioBackend *backend, float volume)
{
  return g_bass_set_config(5, (__int64)(volume * 100.0));
}
