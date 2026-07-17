/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_jetpack_pickup_runtime @ 0x4084d0 */
/* selector: initialize_track_jetpack_pickup_runtime */

// Exact Windows constructor for the authored `JetPack` (`cRJetPack` cross-port) singleton: constructs its inherited BOD, constructs two complete embedded 0x94-byte `cRVapour` children, and installs the table whose entry is `update_track_jetpack_pickup`. The complete 0x19c extent exactly matches the native `Size of cRJetPack` ledger.
JetPack *__thiscall initialize_track_jetpack_pickup_runtime(JetPack *jetpack)
{
  initialize_bod_base(&jetpack->bod);
  initialize_renderable_bod(&jetpack->vapour_a.body);
  jetpack->vapour_a.body.bod.bod.vtable = &g_vapour_vtable;
  initialize_renderable_bod(&jetpack->vapour_b.body);
  jetpack->vapour_b.body.bod.bod.vtable = &g_vapour_vtable;
  jetpack->bod.bod.vtable = &g_jet_pack_vtable;
  return jetpack;
}
