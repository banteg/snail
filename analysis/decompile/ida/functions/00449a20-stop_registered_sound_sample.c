/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: stop_registered_sound_sample @ 0x449a20 */
/* selector: stop_registered_sound_sample */

// Stops playback for one registered runtime sample index by resolving it through the shared sound-bank table before forwarding into the lower audio backend.
int __stdcall sub_449A20(int a1)
{
  return MEMORY[0x753C94](unk_7537E0[a1]);
}

