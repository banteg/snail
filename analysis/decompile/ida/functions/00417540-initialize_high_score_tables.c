/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_high_score_tables @ 0x417540 */
/* selector: initialize_high_score_tables */

// Seeds the postal, challenge, and completion high-score banks with blank cRSubHighScore records before ScoreA/B/C overlays are loaded.
_WORD *__thiscall sub_417540(char *this)
{
  int v2; // esi
  char *v3; // edi
  int v4; // esi
  char *v5; // edi
  int v6; // esi
  char *v7; // edi

  v2 = 0;
  v3 = this + 8;
  do
  {
    initialize_high_score_entry(v3, 0, 0, 1065353216, 0, 0, v2++);
    v3 += 129728;
  }
  while ( v2 < 11 );
  v4 = 0;
  v5 = this + 1427016;
  do
  {
    initialize_high_score_entry(v5, 0, 0, 1065353216, 0, 1, v4++);
    v5 += 129728;
  }
  while ( v4 < 11 );
  v6 = 0;
  v7 = this + 2854024;
  do
  {
    initialize_high_score_entry(v7, 0, 0, 1065353216, 0, 2, v6++);
    v7 += 129728;
  }
  while ( v6 < 51 );
  return initialize_high_score_entry(this + 9470152, 0, 0, 1065353216, 0, 0, 0);
}

