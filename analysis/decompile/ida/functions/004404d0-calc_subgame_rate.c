/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: calc_subgame_rate @ 0x4404d0 */
/* selector: calc_subgame_rate */

void __thiscall calc_subgame_rate(Game *game)
{
  double v2; // st7
  int32_t level_mode; // eax
  double v4; // st7
  double v5; // st7
  int v6; // edx
  double v7; // st7
  float v8; // [esp+0h] [ebp-Ch]
  float v9; // [esp+8h] [ebp-4h]

  if ( game->subgame_state != 2 )
  {
    game->subgame_rate = *(float *)&game->_pad_00[48];
    return;
  }
  v2 = *(float *)&game->_pad_74622[3436978] / (double)game->completion_row_start;
  if ( v2 >= 0.0 )
  {
    if ( v2 > 1.0 )
      v2 = 1.0;
  }
  else
  {
    v2 = 0.0;
  }
  level_mode = game->level_mode;
  if ( level_mode == 1 || level_mode == 3 )
  {
    v5 = v2 * 0.55000001;
    goto LABEL_12;
  }
  if ( level_mode != 4 )
  {
    v5 = v2 * 0.2;
LABEL_12:
    v4 = v5 + *(float *)&game->_pad_00[48];
    goto LABEL_13;
  }
  v4 = v2 * 0.40000001 + *(float *)&game->_pad_00[48] + 0.2;
LABEL_13:
  v6 = *(_DWORD *)&game->_pad_74622[3437830];
  game->subgame_rate = v4;
  if ( v6 == 2 )
  {
    if ( level_mode == 1 || (v9 = 0.60000002, level_mode == 4) )
      v9 = 0.40000001;
    if ( *(float *)&game->_pad_74622[3437862] < 0.25 || *(float *)&game->_pad_74622[3437862] > 0.75 )
    {
      v8 = *(float *)&game->_pad_74622[3437862] * 12.566371 + 1.5707964;
      v7 = (1.0 - sine(v8)) * 0.5 * v9;
    }
    else
    {
      v7 = v9;
    }
    game->subgame_rate = v7 + game->subgame_rate;
  }
  if ( *(_DWORD *)&game->_pad_74622[3446942] == 1 )
    game->subgame_rate = *(float *)&game->_pad_74622[3447454] * 0.5 + game->subgame_rate;
}

