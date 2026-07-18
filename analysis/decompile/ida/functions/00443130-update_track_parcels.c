/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_track_parcels @ 0x443130 */
/* selector: update_track_parcels */

// Exact `ParcelManager` update: walks the 50 owned records and dispatches each active Parcel through its installed table. Android and iOS v1.9 retain `cRParcelManager::AI()`.
void __thiscall update_track_parcels(ParcelManager *manager)
{
  int v2; // edi

  v2 = 50;
  do
  {
    if ( manager->slots[0].state )
      (*(void (__thiscall **)(ParcelManager *))manager->slots[0].bod.bod.vtable)(manager);
    manager = (ParcelManager *)((char *)manager + 140);
    --v2;
  }
  while ( v2 );
}
