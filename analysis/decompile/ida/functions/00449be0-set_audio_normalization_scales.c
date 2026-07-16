/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_audio_normalization_scales @ 0x449be0 */
/* selector: set_audio_normalization_scales */

// Stores the normalized music, SFX, and voice gain scales parsed from `VOICE/_VOICE.TXT` into the shared backend lanes that the music, sound, and voice wrappers multiply into live playback volume.
void __thiscall set_audio_normalization_scales(
        AudioBackend *backend,
        float music_scale,
        float sfx_scale,
        float voice_scale)
{
  backend->music_normalization_scale = music_scale;
  backend->sfx_normalization_scale = sfx_scale;
  backend->voice_normalization_scale = voice_scale;
}
