/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: match_cheat_text @ 0x4047d0 */
/* selector: match_cheat_text */

char __thiscall sub_4047D0(char *this, const char *a2)
{
  unsigned int v3; // kr04_4
  int v4; // ecx
  int v6; // eax
  char *i; // edx

  v3 = strlen(a2) + 1;
  v4 = v3 - 1;
  if ( (int)(v3 - 1) >= 8 )
  {
    report_errorf(aCheatTextTooLo);
    return 0;
  }
  v6 = 0;
  if ( v4 > 0 )
  {
    for ( i = this + v4 + 7; a2[v6] == *i; --i )
    {
      if ( ++v6 >= (int)(v3 - 1) )
        return 1;
    }
    return 0;
  }
  return 1;
}

