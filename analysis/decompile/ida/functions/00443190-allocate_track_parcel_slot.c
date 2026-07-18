/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: allocate_track_parcel_slot @ 0x443190 */
/* selector: allocate_track_parcel_slot */

// Exact `ParcelManager` allocator: returns the first inactive Parcel or logs `Too Many Parcels increase RPARCEL_MAXIMUM` and returns null. Android retains `cRParcelManager::New()`.
Parcel *__thiscall allocate_track_parcel_slot(ParcelManager *manager)
{
  int v1; // eax
  ParcelState *i; // edx

  v1 = 0;
  for ( i = &manager->slots[0].state; *i; i += 35 )
  {
    if ( ++v1 >= 50 )
    {
      report_errorf(aTooManyParcels);
      return nullptr;
    }
  }
  return &manager->slots[v1];
}
