/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_track_runtime_cell_at_world_z @ 0x43d480 */
/* selector: get_track_runtime_cell_at_world_z */

// Clamps world z into the generated row array and returns the authored `SubRow` runtime record. The exact 0xf4 stride and 3200-row slab agree with the Windows constructor ledger's `Size of cRSubRow` total of 0xbea00 bytes.
TrackAttachmentRuntimeRow *__thiscall get_track_runtime_cell_at_world_z(SubgameRuntime *game, Vec3 *position)
{
  __int64 z; // rax

  z = (__int64)position->z;
  if ( (int)z < 0 )
    return (TrackAttachmentRuntimeRow *)&byte_5CCAC8[(_DWORD)game];
  if ( (int)z > 3199 )
    LODWORD(z) = 3199;
  return (TrackAttachmentRuntimeRow *)&byte_5CCAC8[(_DWORD)((_DWORD)game + 244 * z)];
}
