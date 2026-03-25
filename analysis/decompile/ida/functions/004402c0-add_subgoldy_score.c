/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: add_subgoldy_score @ 0x4402c0 */
/* selector: add_subgoldy_score */

// Adds one scored gameplay event onto Goldy's per-event buckets and total score, and awards a bonus life whenever the total crosses a 50,000-point threshold while the visible life stock is still below nine. Windows evidence matches the `cRSubGoldy::ScoreAdd(int,int)` shape directly.
void __thiscall sub_4402C0(int *this, int a2, int a3)
{
  int v4; // eax
  int v5; // edi
  int v6; // eax

  switch ( a2 )
  {
    case 0:
      v4 = 10;
      break;
    case 1:
      v4 = 500;
      break;
    case 2:
    case 3:
    case 4:
      v4 = 100;
      break;
    case 5:
      v4 = a3;
      break;
    default:
      report_errorf(aUnknownScoreTy);
      v4 = 0;
      break;
  }
  *(this + a2 + 196) += v4;
  v5 = *(this + 185);
  *(this + 185) = v5 + v4;
  if ( v5 / 50000 != (v5 + v4) / 50000 )
  {
    v6 = *(this + 4304);
    if ( v6 < 9 )
    {
      *(this + 4304) = v6 + 1;
      if ( !*((_DWORD *)MEMORY[0x4DF904] + 119190) && !*((_DWORD *)MEMORY[0x4DF904] + 9) )
        play_sound_effect(44);
    }
  }
}

