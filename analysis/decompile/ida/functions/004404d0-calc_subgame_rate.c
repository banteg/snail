/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: calc_subgame_rate @ 0x4404d0 */
/* selector: calc_subgame_rate */

// Exact void Windows `cRSubGame::CalcRate()`: recomputes the live subgame rate from base speed, active-state track progress, mode-specific ramps, Goldy's damage-gauge envelope, and hover bonus. Android preserves the same owner and control graph with port-specific constants and layout.
void __thiscall calc_subgame_rate(SubgameRuntime *game)
{
  double v2; // st7
  int32_t level_mode; // eax
  double v4; // st7
  double v5; // st7
  DamageGuageState state; // edx
  double v7; // st7
  float v8; // [esp+0h] [ebp-Ch]
  float v9; // [esp+8h] [ebp-4h]

  if ( game->subgame_state != 2 )
  {
    LODWORD(game->subgame_rate) = game->rate_or_level_arg.level_arg_tail;
    return;
  }
  v2 = game->player.body.transform.position.z / (double)game->completion_row_start;
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
    v4 = v5 + game->rate_or_level_arg.base_rate;
    goto LABEL_13;
  }
  v4 = v2 * 0.40000001 + game->rate_or_level_arg.base_rate + 0.2;
LABEL_13:
  state = game->player.damage_gauge.state;
  game->subgame_rate = v4;
  if ( state == DAMAGE_GUAGE_STATE_DRAINING )
  {
    if ( level_mode == 1 || (v9 = 0.60000002, level_mode == 4) )
      v9 = 0.40000001;
    if ( game->player.damage_gauge.display_fill < 0.25 || game->player.damage_gauge.display_fill > 0.75 )
    {
      v8 = game->player.damage_gauge.display_fill * 12.566371 + 1.5707964;
      v7 = (1.0 - sine(v8)) * 0.5 * v9;
    }
    else
    {
      v7 = v9;
    }
    game->subgame_rate = v7 + game->subgame_rate;
  }
  if ( game->player.sub_hover.state == SUB_HOVER_STATE_ACTIVE )
    game->subgame_rate = game->player.sub_hover.warning_intensity_latch * 0.5 + game->subgame_rate;
}
