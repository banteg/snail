/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: allocate_track_parcel_slot @ 0x443190 */
/* selector: allocate_track_parcel_slot */

// Scans the gameplay parcel array for the first inactive slot and returns it, logging `Too Many Parcels increase RPARCEL_MAXIMUM` if the 50-slot pool is exhausted.
char *__thiscall sub_443190(_DWORD *this)
{
  int v1; // eax
  _DWORD *i; // edx

  v1 = 0;
  for ( i = this + 14; *i; i += 35 )
  {
    if ( ++v1 >= 50 )
    {
      report_errorf(aTooManyParcels);
      return nullptr;
    }
  }
  return (char *)(this + 35 * v1);
}

