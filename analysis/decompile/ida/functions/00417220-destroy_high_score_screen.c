/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_high_score_screen @ 0x417220 */
/* selector: destroy_high_score_screen */

// Tears down the active high-score table widgets, preserves the selected bank index, and resets the shell-font scene before control returns to the owning front-end state. Cross-port Android symbols match this helper to `cRHighScore::UnInit()`.
int __thiscall sub_417220(_DWORD *this)
{
  unk_4DF9C0 = *(this + 2);
  kill_all_borders((int *)MEMORY[0x4DF904] + 723);
  *((_BYTE *)MEMORY[0x4DF904] + 781) = 0;
  *((_DWORD *)MEMORY[0x4DF904] + 196) = 0;
  return 0;
}

