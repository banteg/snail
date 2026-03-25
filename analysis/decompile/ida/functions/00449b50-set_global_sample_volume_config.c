/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_global_sample_volume_config @ 0x449b50 */
/* selector: set_global_sample_volume_config */

// Scales one normalized [0,1] sample-volume scalar onto BASS config option `4` (`BASS_CONFIG_GVOL_SAMPLE`) before the backend stores it as the live global SFX sample volume.
int __stdcall sub_449B50(float a1)
{
  return MEMORY[0x753C1C](4, (__int64)(a1 * 100.0));
}

