/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_jetpack_pickup_runtime @ 0x4084d0 */
/* selector: initialize_track_jetpack_pickup_runtime */

// Constructs the single jetpack-pickup runtime record by seeding its shared bod header plus two embedded renderable bodies. `spawn_track_jetpack_pickup` uses the resulting `game->jetpack_pickup` lane at `0x355e64`, whose `0x19c` footprint matches the native `cRJetPack` size ledger.
_DWORD *__thiscall sub_4084D0(_DWORD *this)
{
  initialize_bod_base(this);
  initialize_renderable_bod(this + 29);
  *(this + 29) = &off_49731C;
  initialize_renderable_bod(this + 66);
  *(this + 66) = &off_49731C;
  *this = &off_497318;
  return this;
}

