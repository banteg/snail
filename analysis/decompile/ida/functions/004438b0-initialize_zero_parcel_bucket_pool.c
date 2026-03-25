/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_zero_parcel_bucket_pool @ 0x4438b0 */
/* selector: initialize_zero_parcel_bucket_pool */

// Initializes the 0x800-entry zero-parcel fallback bucket pool at `data_53d190`, clearing each 0x20c-byte entry with the shared gameplay slot initializer before `place_parcels_on_track` uses it for `0`-parcel filler rows.
int sub_4438B0()
{
  int *v0; // esi
  int v1; // edi
  int result; // eax

  v0 = MEMORY[0x53D190];
  v1 = 2048;
  do
  {
    result = initialize_array_with_constructor((int)v0, 16, 32, (int (__thiscall *)(int))Iostream_init::Iostream_init);
    v0 += 131;
    --v1;
  }
  while ( v1 );
  return result;
}

