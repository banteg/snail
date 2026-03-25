/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_completion_screen @ 0x406060 */
/* selector: destroy_completion_screen */

// Tears down the active completion-screen widgets and restores the owning front-end state once the current exit choice resolves. Cross-port Android and iOS symbols match this helper to `cRCompletion::UnInit()`.
int __thiscall sub_406060(int this)
{
  int result; // eax

  kill_border(*(_DWORD **)(this + 16));
  kill_border(*(_DWORD **)(this + 20));
  kill_border(*(_DWORD **)(this + 24));
  result = unhide_all_borders((int *)MEMORY[0x4DF904] + 723);
  *((_DWORD *)MEMORY[0x4DF904] + 110) = *(_DWORD *)(this + 8);
  return result;
}

