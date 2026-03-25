/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_registered_sound_sample_from_path @ 0x449920 */
/* selector: load_registered_sound_sample_from_path */

// Loads one sample directly from a filesystem path into the shared runtime sound-bank slot table via `BASS_SampleLoad(mem=0, ...)`, storing the resulting sample handle at the requested registered-sample index.
int __stdcall sub_449920(int a1, int a2, int a3)
{
  int result; // eax

  result = MEMORY[0x7537CC](0, a1, 0, 0, a3, 131088);
  unk_7537E0[a2] = result;
  if ( !result )
    return sub_449C00();
  return result;
}

