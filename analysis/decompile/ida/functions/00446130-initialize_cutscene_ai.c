/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_cutscene_ai @ 0x446130 */
/* selector: initialize_cutscene_ai */

// Constructs the embedded player-side cutscene AI/controller at `player + 0x42dc`, seeding its shared pointers and clearing the live cutscene state before `initialize_subgoldy` selects the startup leg.
int32_t __fastcall initialize_cutscene_ai(CutsceneAI *cutscene_ai)
{
  int32_t result; // eax
  char *v2; // edx

  result = (int32_t)MEMORY[0x4DF904] + 4400896;
  cutscene_ai->shared_state = (char *)MEMORY[0x4DF904] + 4400896;
  v2 = (char *)&loc_42FD7C + (_DWORD)MEMORY[0x4DF904];
  cutscene_ai->active = 0;
  cutscene_ai->intro_talk_anchor = v2;
  return result;
}

