/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_game_data_archive @ 0x430e40 */
/* selector: initialize_game_data_archive */

char initialize_game_data_archive()
{
  char result; // al
  float *v1; // eax
  __int128 Rect; // [esp+4h] [ebp-10h] BYREF

  LOBYTE(flt_4DFAFC[95038]) = 0;
  flt_4DFAFC[50030] = 0.0;
  initialize_enemy_manager((#94 *)&flt_4DFAFC[50033]);
  flt_4DFAFC[50031] = 0.0;
  flt_4DFAFC[36392] = 0.0;
  BYTE1(flt_4DFAFC[95038]) = 0;
  result = load_archive_index(FileName);
  if ( result )
  {
    sub_432D40();
    LODWORD(flt_4DFAFC[95036]) = allocate_tracked_memory(0x400000, (int)aScratchPad);
    LODWORD(flt_4DFAFC[95035]) = allocate_tracked_memory(409600, (int)aMusicMemoryBuf);
    v1 = &flt_4DFAFC[36369];
    do
    {
      *(v1 - 1) = 0.0;
      *v1 = 0.0;
      v1[1] = 0.0;
      v1[4] = 320.0;
      v1[5] = 240.0;
      v1[6] = 0.0;
      v1 += 14;
    }
    while ( (int)v1 < (int)&flt_4DFAFC[36397] );
    ((void (__stdcall *)(__int128 *))GetClipCursor)(&Rect);
    return 1;
  }
  return result;
}

