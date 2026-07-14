/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_speedup_runtime @ 0x4084b0 */
/* selector: initialize_track_speedup_runtime */

// Exact Windows constructor for the authored `SubSpeedUp` (`cRSubSpeedUp` cross-port) singleton: constructs the inherited renderable BOD and installs the table whose entry is the exact `update_track_speedup`. Its 0xb4 extent exactly matches the native `Size of cRSubSpeedUp` ledger.
_DWORD *__thiscall initialize_track_speedup_runtime(_DWORD *this)
{
  initialize_renderable_bod(this);
  *this = g_track_speedup_vtable;
  return this;
}

