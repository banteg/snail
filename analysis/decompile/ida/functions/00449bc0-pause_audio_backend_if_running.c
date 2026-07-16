/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: pause_audio_backend_if_running @ 0x449bc0 */
/* selector: pause_audio_backend_if_running */

// Pauses the global BASS backend only when the audio state flag at `backend + 0x18` says the backend is currently running, then marks it paused.
char __thiscall pause_audio_backend_if_running(AudioBackend *backend)
{
  char result; // al

  result = backend->is_paused;
  if ( !result )
  {
    result = g_bass_pause();
    backend->is_paused = 1;
  }
  return result;
}
