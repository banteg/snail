/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_voice_backend @ 0x432e80 */
/* selector: play_voice_backend */

// Windows RShellVoicePlay entry point: normalizes one voice sample's gain and preserves the authored sample-id, gain, pitch, and pan dispatch contract before forwarding into the BASS registered-sample backend.
void __cdecl play_voice_backend(int sample_id, float gain, float pitch, float pan)
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
        v6 = g_audio_backend_voice_normalization_scale * gain;
        play_registered_sound_sample_scaled(sample_id, v6);
      }
      else
      {
        v5 = g_audio_backend_voice_normalization_scale * gain;
        play_registered_sound_sample_backend(sample_id, v5, pitch);
      }
    }
    else
    {
      v4 = g_audio_backend_voice_normalization_scale * gain;
      play_registered_sound_sample_scaled_panned(sample_id, v4, -1.0, pan);
    }
  }
}
