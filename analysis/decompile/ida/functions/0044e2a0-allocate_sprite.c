/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: allocate_sprite @ 0x44e2a0 */
/* selector: allocate_sprite */

void *__thiscall allocate_sprite(_DWORD *manager, int owner, int texture_id, int texture_a, int texture_b)
{
  int free_sprite; // esi
  int active_head; // eax
  int flags; // ecx
  int animation_flags; // edi
  int final_flags; // ecx

  free_sprite = *(manager + 135006);
  if ( !free_sprite )
    return &unk_814CB0;
  *(manager + 135006) = *(_DWORD *)(free_sprite + 12);
  *(_DWORD *)(free_sprite + 8) = owner;
  active_head = *(manager + owner + 135001);
  if ( active_head )
    *(_DWORD *)(active_head + 16) = free_sprite;
  *(_DWORD *)(free_sprite + 16) = 0;
  *(_DWORD *)(free_sprite + 12) = *(manager + owner + 135001);
  *(manager + owner + 135001) = free_sprite;
  initialize_sprite((_DWORD *)free_sprite);
  flags = (1 << (owner + 24)) | *(_DWORD *)(free_sprite + 4);
  *(_DWORD *)(free_sprite + 4) = flags;
  *(float *)(free_sprite + 28) = unk_78FF90[texture_id];
  if ( texture_b == -1 )
  {
    if ( texture_a != -1 )
    {
      *(_DWORD *)(free_sprite + 4) = flags | 0x10;
      *(float *)(free_sprite + 32) = unk_78FF90[texture_a];
    }
  }
  else
  {
    *(_DWORD *)(free_sprite + 4) = flags | 0x20;
    *(float *)(free_sprite + 32) = unk_78FF90[texture_a];
    *(float *)(free_sprite + 36) = unk_78FF90[texture_b];
  }
  *(_DWORD *)(free_sprite + 100) = 0;
  *(_DWORD *)(free_sprite + 156) = texture_id;
  *(_DWORD *)(free_sprite + 172) = 0;
  *(_DWORD *)(free_sprite + 176) = 0;
  *(_DWORD *)(free_sprite + 160) = *(_DWORD *)(LODWORD(unk_78FF90[texture_id]) + 144);
  if ( (*(_DWORD *)LODWORD(unk_78FF90[texture_id]) & 0x2000) != 0 )
  {
    animation_flags = *(_DWORD *)(free_sprite + 4) | 0x2000;
    *(_DWORD *)(free_sprite + 4) = animation_flags;
    final_flags = animation_flags;
    *(_DWORD *)(free_sprite + 176) = *(_DWORD *)(LODWORD(unk_78FF90[texture_id]) + 148);
    if ( (*(_DWORD *)LODWORD(unk_78FF90[texture_id]) & 0x4000) != 0 )
    {
      BYTE1(final_flags) = BYTE1(animation_flags) | 0x40;
      *(_DWORD *)(free_sprite + 4) = final_flags;
    }
  }
  return (void *)free_sprite;
}
