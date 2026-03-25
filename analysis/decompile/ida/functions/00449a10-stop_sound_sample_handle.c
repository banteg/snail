/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: stop_sound_sample_handle @ 0x449a10 */
/* selector: stop_sound_sample_handle */

// Forwards one raw runtime sample handle directly into `BASS_SampleStop`, underneath the registered-sample and warning-owned stop wrappers.
int __stdcall sub_449A10(int a1)
{
  return MEMORY[0x753C94](a1);
}

