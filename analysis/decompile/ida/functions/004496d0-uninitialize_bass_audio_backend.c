/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninitialize_bass_audio_backend @ 0x4496d0 */
/* selector: uninitialize_bass_audio_backend */

// Stops the global BASS backend, frees the loaded `Bass.dll` state, unloads the temporary DLL, and deletes the extracted `tBass.dll` copy.
int uninitialize_bass_audio_backend()
{
  MEMORY[0x753BFC]();
  if ( !MEMORY[0x7537D8]() )
    report_errorf(aCannotFreeBass);
  if ( !((int (__stdcall *)(_DWORD))FreeLibrary)(MEMORY[0x753C90]) )
    report_errorf(aCannotFreeBass_0);
  return delete_file_path_with_directory_walk(LibFileName);
}

