/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_parcel_set_bucket_pool @ 0x443870 */
/* selector: initialize_parcel_set_bucket_pool */

// Initializes the 0x800-entry positive-count parcel-set bucket pool at `data_6487e8`, clearing each 0x20c-byte entry with the shared gameplay slot initializer before `place_parcels_on_track` fills it from authored parcel requests.
int sub_443870()
{
  int *v0; // esi
  int v1; // edi
  int result; // eax

  v0 = unk_6487E8;
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

