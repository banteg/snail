/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: stop_music_stream @ 0x4498d0 */
/* selector: stop_music_stream */

// Stops the active BASS music stream, removes any registered sync callback, frees the stream handle, and clears the active-stream flag.
void __thiscall stop_music_stream(AudioBackend *backend)
{
  if ( backend->music_stream_active )
  {
    if ( g_active_music_stream_sync )
    {
      g_bass_channel_remove_sync(g_active_music_stream, g_active_music_stream_sync);
      g_active_music_stream_sync = 0;
    }
    g_bass_channel_stop(g_active_music_stream);
    g_bass_stream_free(g_active_music_stream);
    backend->music_stream_active = 0;
  }
}
