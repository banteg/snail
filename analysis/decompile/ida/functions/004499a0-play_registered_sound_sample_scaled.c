/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_registered_sound_sample_scaled @ 0x4499a0 */
/* selector: play_registered_sound_sample_scaled */

// AudioBackend method that plays one registered runtime sample through BASS with the supplied normalized gain scale and the default pitch and pan parameters.
void __stdcall play_registered_sound_sample_scaled(int a1, float a2)
{
  if ( a2 >= 0.0 )
  {
    if ( a2 <= 1.0 )
    {
      if ( a2 == 0.0 )
        return;
    }
    else
    {
      a2 = 1.0;
    }
    g_bass_sample_play_ex(g_registered_sound_sample_handles[a1], 0, -1, (__int64)(a2 * 100.0), 0, -1);
  }
}
