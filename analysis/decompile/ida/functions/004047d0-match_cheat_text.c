/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: match_cheat_text @ 0x4047d0 */
/* selector: match_cheat_text */

bool __thiscall match_cheat_text(CheatState *cheat, char *text)
{
  unsigned int v3; // kr04_4
  int v4; // ecx
  int v6; // eax
  char *recent_text_cursor; // edx

  v3 = strlen(text) + 1;
  v4 = v3 - 1;
  if ( (int)(v3 - 1) >= 8 )
  {
    report_errorf(aCheatTextTooLo);
    return 0;
  }
  v6 = 0;
  if ( v4 > 0 )
  {
    for ( recent_text_cursor = (char *)&cheat->unused_04 + v4 + 3; text[v6] == *recent_text_cursor; --recent_text_cursor )
    {
      if ( ++v6 >= (int)(v3 - 1) )
        return 1;
    }
    return 0;
  }
  return 1;
}
