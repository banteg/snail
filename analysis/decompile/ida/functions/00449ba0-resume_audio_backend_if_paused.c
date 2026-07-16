/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: resume_audio_backend_if_paused @ 0x449ba0 */
/* selector: resume_audio_backend_if_paused */

// Restarts the global BASS backend only when the audio state flag at `backend + 0x18` says the backend is currently paused, then clears that paused flag.
void __thiscall resume_audio_backend_if_paused(AudioBackend *backend)
{
  if ( backend->is_paused == 1 )
  {
    g_bass_start();
    backend->is_paused = 0;
  }
}
