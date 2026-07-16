/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_zero_parcel_bucket_pool @ 0x4438b0 */
/* selector: initialize_zero_parcel_bucket_pool */

// Initializes the 0x800-entry zero-parcel fallback bucket pool at `data_53d190`, clearing each 0x20c-byte entry with the shared gameplay slot initializer before `place_parcels_on_track` uses it for `0`-parcel filler rows.
void __cdecl initialize_zero_parcel_bucket_pool()
{
  ParcelBucket *v0; // esi
  int v1; // edi

  v0 = g_zero_parcel_buckets;
  v1 = 2048;
  do
  {
    initialize_array_with_constructor(v0++, 16, 32, noop_runtime_slot_constructor);
    --v1;
  }
  while ( v1 );
}
