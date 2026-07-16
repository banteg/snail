/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_parcel_set_bucket_pool @ 0x443870 */
/* selector: initialize_parcel_set_bucket_pool */

// Initializes the 0x800-entry positive-count parcel-set bucket pool at `data_6487e8`, clearing each 0x20c-byte entry with the shared gameplay slot initializer before `place_parcels_on_track` fills it from authored parcel requests.
void __cdecl initialize_parcel_set_bucket_pool()
{
  ParcelBucket *v0; // esi
  int v1; // edi

  v0 = g_parcel_set_buckets;
  v1 = 2048;
  do
  {
    initialize_array_with_constructor(v0++, 16, 32, noop_runtime_slot_constructor);
    --v1;
  }
  while ( v1 );
}
