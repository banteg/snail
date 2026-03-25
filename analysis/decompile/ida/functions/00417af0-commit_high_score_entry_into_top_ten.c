/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: commit_high_score_entry_into_top_ten @ 0x417af0 */
/* selector: commit_high_score_entry_into_top_ten */

// Copies the edited scratch high-score entry into the selected insertion row and shifts the remaining top-10 rows down.
void __thiscall sub_417AF0(_DWORD *this, int a2)
{
  int v2; // ebp
  int v3; // eax
  int v4; // ebx
  void *v5; // edi
  const void *v6; // esi

  v2 = a2;
  if ( a2 < 10 )
  {
    v3 = 129728 * a2;
    v4 = (int)(this + 32432 * a2 + 389186);
    do
    {
      v5 = (void *)(*this + v3);
      v6 = (const void *)v4;
      v3 += 129728;
      v4 += 129728;
      qmemcpy(v5, v6, 0x1FAC0u);
      *(_DWORD *)(v3 + *this - 129664) = v2++;
    }
    while ( v3 < 1297280 );
  }
}

