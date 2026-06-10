/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_tutorial @ 0x448da0 */
/* selector: initialize_tutorial */

void __fastcall initialize_tutorial(TutorialController *controller)
{
  char *v1; // eax
  _DWORD *game; // ecx
  int v3; // eax

  controller->state = 0;
  v1 = (char *)MEMORY[0x4DF904] + 476696;
  controller->game = (char *)MEMORY[0x4DF904] + 476696;
  *((_DWORD *)v1 + 19) |= (unsigned int)&unk_600000;
  game = controller->game;
  v3 = game[19];
  LOBYTE(v3) = v3 & 0xFD;
  game[19] = v3;
}

