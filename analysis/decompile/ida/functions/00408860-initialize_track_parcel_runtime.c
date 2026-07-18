/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_parcel_runtime @ 0x408860 */
/* selector: initialize_track_parcel_runtime */

// Exact Windows constructor for one authored `Parcel` (`cRParcel` cross-port): constructs the inherited BOD and installs the table whose entry is `update_track_parcel`. `ParcelManager` owns 50 inline 0x8c-byte records whose 0x1b58 extent exactly matches the native manager ledger.
Parcel *__thiscall initialize_track_parcel_runtime(Parcel *parcel)
{
  initialize_bod_base(&parcel->bod);
  parcel->bod.bod.vtable = &g_parcel_vtable;
  return parcel;
}
