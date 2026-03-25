/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_ring_or_special_effect_runtime @ 0x408570 */
/* selector: initialize_track_ring_or_special_effect_runtime */

// Constructs one authored-ring runtime slot by seeding the shared bod header and installing the ring-or-special-effect vtable. `spawn_track_ring_or_special_effect` allocates from the 2-slot pool at `0x35b78c` before initializing the child particle sprites.
_DWORD *__thiscall sub_408570(_DWORD *this)
{
  initialize_renderable_bod(this);
  *this = &off_49732C;
  return this;
}

