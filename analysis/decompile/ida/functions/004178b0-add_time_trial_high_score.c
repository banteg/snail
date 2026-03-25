/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: add_time_trial_high_score @ 0x4178b0 */
/* selector: add_time_trial_high_score */

// Records one per-route time-trial result into the completion bank, replacing the stored entry only when the new time beats the existing route record. Cross-port Android and iOS symbols match this helper to `cRSubHighScore::AddTimeTrial(int, bool)`.
void __thiscall sub_4178B0(int this, _DWORD *a2, int a3, char a4)
{
  int v4; // ebp

  a2[15] = 2;
  a2[16] = a3;
  a2[17] = 0;
  if ( !a4 )
    a2[2] = 0;
  qmemcpy((void *)(this + 9470152), a2, 0x1FAC0u);
  if ( a4 )
  {
    v4 = 129728 * a3 + this;
    if ( *((float *)a2 + 2) < (double)*(float *)(v4 + 2854032) || *(float *)(v4 + 2854032) == 0.0 )
    {
      qmemcpy((void *)(v4 + 2854024), a2, 0x1FAC0u);
      *(_DWORD *)(v4 + 2854088) = a3;
    }
  }
}

