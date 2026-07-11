/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: complete_subgame @ 0x438700 */
/* selector: complete_subgame */

// Snapshots the just-finished run into the working high-score/replay record, including the normalized garbage and salt frequencies, increments the per-run completion counter, and dispatches the mode-specific high-score handoff. Cross-port Android and iOS symbols match this helper to `cRSubGame::Complete(bool)`.
void __thiscall sub_438700(int this, char a2)
{
  int v3; // ecx
  int v4; // eax
  int v5; // esi
  int v6; // ecx
  int v7; // eax
  int v8; // esi
  int v9; // eax
  int v10; // esi
  int v11; // ecx
  int v12; // eax

  display_score_stats((int *)(this + 3913572));
  *(_BYTE *)(this + 6 * *(_DWORD *)(this + 16721372) + 16591748) |= 8u;
  v3 = *(_DWORD *)(this + 16721372) + 1;
  ++*(_DWORD *)(this + 16591740);
  *(_DWORD *)(this + 16721372) = v3;
  if ( (byte_4B2F40 & 1) == 0 )
  {
    v4 = *(_DWORD *)(this + 3914340);
    *(_DWORD *)(this + 16591636) = *(_DWORD *)(this + 3914312);
    qmemcpy((void *)(this + 16591640), (const void *)(this + 3914316), 0x18u);
    v5 = *(_DWORD *)(this + 52);
    v6 = *(_DWORD *)(this + 40);
    *(_DWORD *)(this + 16591664) = v4;
    *(_DWORD *)(this + 16591712) = *(_DWORD *)(this + 44);
    v7 = *(_DWORD *)(this + 48);
    *(_DWORD *)(this + 16591684) = v5;
    v8 = *(_DWORD *)(this + 19267544);
    *(_DWORD *)(this + 16591704) = v7;
    v9 = *(_DWORD *)(this + 64);
    *(_DWORD *)(this + 16721344) = v8;
    v10 = *(_DWORD *)(this + 19267548);
    *(_DWORD *)(this + 16591708) = v6;
    v11 = *(_DWORD *)(this + 3914344);
    *(_DWORD *)(this + 16721348) = v10;
    *(_DWORD *)(this + 16591632) = 1;
    *(_DWORD *)(this + 16591668) = v11;
    *(_DWORD *)(this + 16591676) = v9;
    if ( (v9 != 1 || v11) && !*(_BYTE *)(this + 16721360) && a2 == 1 )
    {
      if ( v9 )
      {
        v12 = v9 - 1;
        if ( v12 )
        {
          if ( v12 == 3 )
            add_time_trial_high_score(
              (int)&unk_68B4C8 + this,
              (_DWORD *)(this + 16591632),
              *(_DWORD *)(this + 68),
              *(_BYTE *)(this + 3914660));
        }
        else
        {
          add_survival_high_score((int *)((char *)&unk_68B4C8 + this), (_DWORD *)(this + 16591632));
        }
      }
      else
      {
        add_arcade_high_score((int *)((char *)&unk_68B4C8 + this), (_DWORD *)(this + 16591632), *(_DWORD *)(this + 68));
      }
    }
  }
}
