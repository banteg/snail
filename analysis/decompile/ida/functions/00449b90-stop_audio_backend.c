/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: stop_audio_backend @ 0x449b90 */
/* selector: stop_audio_backend */

// Forwards directly into the global BASS stop export to halt active backend playback during shutdown or full audio resets.
// attributes: thunk
int32_t __thiscall stop_audio_backend(AudioBackend *backend)
{
  return g_bass_stop();
}
