/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_health_pickup_runtime @ 0x408510 */
/* selector: initialize_track_health_pickup_runtime */

// Exact Windows constructor for one authored `SubHealth` (`cRSubHealth` cross-port): constructs the inherited BOD and installs the table whose entry is `update_track_health_pickup`. `SubgameRuntime` owns eight inline 0x74-byte records whose 0x3a0 extent exactly matches the native `Size of cRSubHealth` ledger.
SubHealth *__thiscall initialize_track_health_pickup_runtime(SubHealth *pickup)
{
  initialize_bod_base(&pickup->bod);
  pickup->bod.bod.vtable = &g_sub_health_vtable;
  return pickup;
}
