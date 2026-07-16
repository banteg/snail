/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninitialize_bass_audio_backend @ 0x4496d0 */
/* selector: uninitialize_bass_audio_backend */

// Stops the global BASS backend, frees the loaded `Bass.dll` state, unloads the temporary DLL, and deletes the extracted `tBass.dll` copy.
void __thiscall uninitialize_bass_audio_backend(AudioBackend *backend)
{
  g_bass_stop();
  if ( !g_bass_free() )
    report_errorf(aCannotFreeBass);
  if ( !FreeLibrary(g_bass_module) )
    report_errorf(aCannotFreeBass_0);
  delete_file_path_with_directory_walk((char *)LibFileName);
}
