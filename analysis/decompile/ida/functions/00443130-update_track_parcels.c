/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_track_parcels @ 0x443130 */
/* selector: update_track_parcels */

// Walks the 50-slot `game->track_parcels` runtime array and dispatches `update_track_parcel` on each active parcel slot.
int __thiscall sub_443130(_DWORD *this)
{
  int v2; // edi
  int result; // eax

  v2 = 50;
  do
  {
    result = *(this + 14);
    if ( result )
      result = (*(int (__thiscall **)(_DWORD *))*this)(this);
    this += 35;
    --v2;
  }
  while ( v2 );
  return result;
}

