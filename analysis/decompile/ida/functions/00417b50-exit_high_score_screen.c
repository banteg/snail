/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: exit_high_score_screen @ 0x417b50 */
/* selector: exit_high_score_screen */

// Leaves the high-score screen and resumes the front-end state that owns the postal or challenge table. Cross-port Android symbols match this helper to `cRHighScore::Exit()`.
_DWORD *sub_417B50()
{
  _DWORD *result; // eax

  result = MEMORY[0x4DF904];
  if ( !*((_DWORD *)MEMORY[0x4DF904] + 119190) )
  {
    *((_DWORD *)MEMORY[0x4DF904] + 110) = 2;
    *((_DWORD *)MEMORY[0x4DF904] + 4953464) = 2;
    *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
    result = MEMORY[0x4DF904];
  }
  if ( result[119190] == 1 )
  {
    result[110] = 10;
    result = MEMORY[0x4DF904];
    *((_DWORD *)MEMORY[0x4DF904] + 4953464) = 2;
    *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
  }
  return result;
}

