/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_global_sample_volume_config @ 0x449b50 */
/* selector: set_global_sample_volume_config */

// Scales one normalized [0,1] sample-volume scalar onto BASS config option `4` (`BASS_CONFIG_GVOL_SAMPLE`) before the backend stores it as the live global SFX sample volume.
int32_t __thiscall set_global_sample_volume_config(AudioBackend *backend, float volume)
{
  return g_bass_set_config(4, (__int64)(volume * 100.0));
}
