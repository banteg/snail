/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_registered_sound_sample_scaled @ 0x4499a0 */
/* selector: play_registered_sound_sample_scaled */

// AudioBackend method that plays one registered runtime sample through BASS with the supplied normalized gain scale and the default pitch and pan parameters.
void __thiscall play_registered_sound_sample_scaled(AudioBackend *backend, int32_t sample_id, float volume)
{
  if ( volume >= 0.0 )
  {
    if ( volume <= 1.0 )
    {
      if ( volume == 0.0 )
        return;
    }
    else
    {
      volume = 1.0;
    }
    g_bass_sample_play_ex(g_registered_sound_sample_handles[sample_id], 0, -1, (__int64)(volume * 100.0), 0, -1);
  }
}
