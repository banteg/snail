/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_global_stream_volume_config @ 0x449b70 */
/* selector: set_global_stream_volume_config */

// Scales one normalized [0,1] stream-volume scalar onto BASS config option `5` (`BASS_CONFIG_GVOL_STREAM`) before the backend stores it as the live music or stream volume.
int __stdcall sub_449B70(float a1)
{
  return MEMORY[0x753C1C](5, (__int64)(a1 * 100.0));
}

