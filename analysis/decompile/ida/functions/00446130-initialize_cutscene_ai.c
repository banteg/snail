/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_cutscene_ai @ 0x446130 */
/* selector: initialize_cutscene_ai */

// Constructs the embedded player-side cutscene AI/controller at `player + 0x42dc`, seeding its shared pointers and clearing the live cutscene state before `initialize_subgoldy` selects the startup leg.
char *__thiscall sub_446130(_DWORD *this)
{
  char *result; // eax
  char *v2; // edx

  result = (char *)MEMORY[0x4DF904] + 4400896;
  *this = (char *)MEMORY[0x4DF904] + 4400896;
  v2 = (char *)&loc_42FD7C + (_DWORD)MEMORY[0x4DF904];
  *(this + 3) = 0;
  *(this + 1) = v2;
  return result;
}

