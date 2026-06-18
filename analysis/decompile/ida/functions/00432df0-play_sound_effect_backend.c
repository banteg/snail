/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_sound_effect_backend @ 0x432df0 */
/* selector: play_sound_effect_backend */

// Shared SFX backend wrapper that plays one effect id with an explicit gain scale plus optional extra playback parameters before forwarding into the lower sound-bank calls.
void __cdecl play_sound_effect_backend(int a1, float a2, float a3, float a4)
{
  float v4; // [esp+0h] [ebp-Ch]
  float v5; // [esp+4h] [ebp-8h]
  float v6; // [esp+8h] [ebp-4h]

  if ( a1 != -1 )
  {
    if ( a4 == 0.0 )
    {
      if ( a3 == -1.0 )
      {
        v6 = g_audio_backend_sfx_normalization_scale * a2;
        play_registered_sound_sample_scaled(a1, v6);
      }
      else
      {
        v5 = g_audio_backend_sfx_normalization_scale * a2;
        play_registered_sound_sample_backend(a1, v5, a3);
      }
    }
    else
    {
      v4 = g_audio_backend_sfx_normalization_scale * a2;
      play_registered_sound_sample_scaled_panned(a1, v4, -1.0, a4);
    }
  }
}
