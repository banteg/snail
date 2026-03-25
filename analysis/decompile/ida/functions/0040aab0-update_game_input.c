/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_game_input @ 0x40aab0 */
/* selector: update_game_input */

void *__thiscall update_game_input(int this)
{
  void *result; // eax
  _DWORD *v2; // esi

  result = MEMORY[0x4DF904];
  if ( *((_BYTE *)MEMORY[0x4DF904] + 1312) )
  {
    v2 = (_DWORD *)(this + 56);
    copy_active_input_controller_state(
      *(_DWORD *)(this + 56),
      (_DWORD *)(this + 108),
      (float *)(this + 76),
      (float *)(this + 80),
      (float *)(this + 96),
      (float *)(this + 100),
      (float *)(this + 104),
      (float *)(this + 88),
      (float *)(this + 92));
    return (void *)update_input(v2);
  }
  return result;
}

