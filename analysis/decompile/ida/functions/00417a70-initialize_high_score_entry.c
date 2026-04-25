/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_high_score_entry @ 0x417a70 */
/* selector: initialize_high_score_entry */

// Clears one cRSubHighScore record, seeds its score-mode metadata, and copies the current player-name buffer into the entry name field.
_WORD *__thiscall sub_417A70(char *this, int a2, int a3, int a4, int a5, int a6, int a7)
{
  _WORD *result; // eax
  int v9; // ecx

  *((_DWORD *)this + 26) = a2;
  *((_DWORD *)this + 27) = 0;
  *((_DWORD *)this + 1) = 0;
  zero_timer_counters((_DWORD *)this + 2);
  *((_DWORD *)this + 10) = a3;
  *((_DWORD *)this + 18) = a4;
  rstrcpy_checked_ascii(this + 84, (char *)MEMORY[0x4DF904] + 420);
  *((_DWORD *)this + 15) = a6;
  *((_DWORD *)this + 16) = a7;
  *(_DWORD *)this = 0;
  *((_DWORD *)this + 14) = a5;
  *((_DWORD *)this + 17) = 0;
  result = this + 114;
  v9 = 21600;
  do
  {
    *(result - 1) = 0;
    *result = 0;
    result[1] = 0;
    result += 3;
    --v9;
  }
  while ( v9 );
  return result;
}

