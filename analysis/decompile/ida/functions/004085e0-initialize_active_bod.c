/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_active_bod @ 0x4085e0 */
/* selector: initialize_active_bod */

// Exact constructor for one 0x3c-byte TrackRenderCacheSlot: calls the inherited BodBase constructor and installs the callback table at `data_497338`. Its sole array-constructor use covers the complete 143x5 SegmentCache grid with stride 0x3c; the iOS cRSegTrack RTTI name independently supports this concrete track-cache owner.
TrackRenderCacheSlot *__thiscall initialize_active_bod(TrackRenderCacheSlot *slot)
{
  initialize_bod_base(&slot->bod);
  slot->bod.bod.vtable = &g_active_bod_vtable;
  return slot;
}
