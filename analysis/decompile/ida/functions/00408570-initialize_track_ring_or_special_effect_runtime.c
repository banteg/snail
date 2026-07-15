/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_ring_or_special_effect_runtime @ 0x408570 */
/* selector: initialize_track_ring_or_special_effect_runtime */

// Exact Windows constructor wrapper for one authored `SubRing` (`cRSubRing` cross-port): constructs the inherited RenderableBod, installs the table whose entry is update_ring_or_special_effect_parent, and returns the receiver. SubgameRuntime owns two 0x1f8-byte records whose 0x3f0 total matches the native cRSubRing size ledger.
SubRing *__thiscall initialize_track_ring_or_special_effect_runtime(SubRing *ring)
{
  initialize_renderable_bod(ring);
  ring->body.bod.bod.vtable = &g_sub_ring_vtable;
  return ring;
}
