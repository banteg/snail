/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_speedup_runtime @ 0x4084b0 */
/* selector: initialize_track_speedup_runtime */

// Constructs the shared speed-up runtime record by running the shared renderable-body constructor and installing the speed-up vtable. Even though `spawn_track_speedup` is an empty stub in this build, the same `0x355db0` runtime lane is still consumed by `update_jetpack_gauge`, `handle_subgoldy_collisions`, and `remove_subgame_bods`, and its `0xb4` footprint matches the native `cRSubSpeedUp` size ledger.
_DWORD *__thiscall sub_4084B0(_DWORD *this)
{
  initialize_renderable_bod(this);
  *this = &off_497314;
  return this;
}

