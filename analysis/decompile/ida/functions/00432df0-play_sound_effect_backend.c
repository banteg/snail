/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_sound_effect_backend @ 0x432df0 */
/* selector: play_sound_effect_backend */

// Windows RShellSoundPlay entry point: normalizes one effect's gain and preserves the authored sample-id, gain, pitch, and pan dispatch contract before forwarding into the BASS registered-sample backend.
void __cdecl play_sound_effect_backend(int sample_id, float gain, float pitch, float pan)
{
  float v4; // [esp+0h] [ebp-Ch]
  float v5; // [esp+4h] [ebp-8h]
  float v6; // [esp+8h] [ebp-4h]

  if ( sample_id != -1 )
  {
    if ( pan == 0.0 )
    {
      if ( pitch == -1.0 )
      {
        v6 = g_audio_backend_sfx_normalization_scale * gain;
        play_registered_sound_sample_scaled((AudioBackend *)g_audio_backend, sample_id, v6);
      }
      else
      {
        v5 = g_audio_backend_sfx_normalization_scale * gain;
        play_registered_sound_sample_backend((AudioBackend *)g_audio_backend, sample_id, v5, pitch);
      }
    }
    else
    {
      v4 = g_audio_backend_sfx_normalization_scale * gain;
      play_registered_sound_sample_scaled_panned((AudioBackend *)g_audio_backend, sample_id, v4, -1.0, pan);
    }
  }
}
