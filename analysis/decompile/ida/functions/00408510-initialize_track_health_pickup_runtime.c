/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_health_pickup_runtime @ 0x408510 */
/* selector: initialize_track_health_pickup_runtime */

// Constructs one health-pickup runtime slot by seeding the shared bod header and installing the pickup vtable. `spawn_track_health_pickup` allocates from the 8-slot pool at `0x356000`, whose total `0x3a0` footprint matches the native `cRSubHealth` size ledger.
_DWORD *__thiscall sub_408510(_DWORD *this)
{
  initialize_bod_base(this);
  *this = &off_497320;
  return this;
}

