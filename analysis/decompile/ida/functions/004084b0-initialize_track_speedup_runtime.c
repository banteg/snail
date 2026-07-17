/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_speedup_runtime @ 0x4084b0 */
/* selector: initialize_track_speedup_runtime */

// Exact Windows constructor for the authored `SubSpeedUp` (`cRSubSpeedUp` cross-port) singleton: constructs the inherited renderable BOD and installs the table whose entry is the exact `update_track_speedup`. Its 0xb4 extent exactly matches the native `Size of cRSubSpeedUp` ledger.
SubSpeedUp *__thiscall initialize_track_speedup_runtime(SubSpeedUp *speedup)
{
  initialize_renderable_bod(&speedup->body);
  speedup->body.bod.bod.vtable = &g_sub_speed_up_vtable;
  return speedup;
}
