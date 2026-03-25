/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: begin_track_attachment_follow_state @ 0x420c40 */
/* selector: begin_track_attachment_follow_state */

// Starts one live attachment-follow session from the selected runtime attachment cell by marking the follow struct active, storing the template and owner cell, zeroing the segment index, seeding progress from `world_z - cell_anchor_z`, seeding local height from `world_y - 0.49`, caching the player pointer, and copying the row payload into template `+0x98`. Windows `cdb` confirmed shipped `ARCADE007` HalfPipe entries hit this helper with entry progress around `0.03595` and near-zero entry height.
int __thiscall sub_420C40(float *this, int a2, int a3, int a4)
{
  int v5; // eax
  double v6; // st7
  int v7; // edx
  int result; // eax

  *(_BYTE *)this = 1;
  v5 = *(_DWORD *)(a2 + 56);
  *((_DWORD *)this + 2) = a2;
  *((_DWORD *)this + 1) = v5;
  *(this + 3) = 0.0;
  *(this + 4) = *(float *)(a3 + 8) - *(float *)(a2 + 24);
  v6 = *(float *)(a3 + 4) - 0.49000001;
  *((_DWORD *)this + 14) = a4;
  *(this + 5) = v6;
  v7 = 61 * get_track_cell_row_index((_DWORD *)a2);
  result = *((_DWORD *)this + 1);
  *(_DWORD *)(result + 152) = *(int *)((char *)&unk_64118C + (_DWORD)MEMORY[0x4DF904] + 4 * v7);
  return result;
}

