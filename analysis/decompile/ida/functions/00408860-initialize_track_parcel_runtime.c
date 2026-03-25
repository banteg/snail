/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_parcel_runtime @ 0x408860 */
/* selector: initialize_track_parcel_runtime */

// Constructs one gameplay parcel runtime slot by clearing the shared body object and installing the parcel-slot vtable. `initialize_runtime_pools_and_path_template_bank` uses it to seed the 50-slot array at `game->track_parcels`.
_DWORD *__thiscall sub_408860(_DWORD *this)
{
  initialize_bod_base(this);
  *this = off_497364;
  return this;
}

