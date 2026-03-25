/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_registered_sound_sample_playing @ 0x449a40 */
/* selector: is_registered_sound_sample_playing */

// Returns whether one registered runtime sample index is currently playing by querying the shared sound-bank table entry in the lower audio backend.
bool __stdcall sub_449A40(int a1)
{
  return MEMORY[0x753CA8](unk_7537E0[a1]) == 1;
}

