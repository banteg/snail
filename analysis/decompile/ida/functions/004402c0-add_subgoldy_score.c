/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: add_subgoldy_score @ 0x4402c0 */
/* selector: add_subgoldy_score */

// Adds one scored gameplay event onto Goldy's per-event buckets and total score, and awards a bonus life whenever the total crosses a 50,000-point threshold while the visible life stock is still below nine. Windows evidence matches the `cRSubGoldy::ScoreAdd(int,int)` shape directly.
void __thiscall add_subgoldy_score(Player *player, int score_kind, int bonus_score)
{
  int points; // eax
  int old_total; // edi
  int visible_life_stock; // eax

  switch ( score_kind )
  {
    case SUBGOLDY_SCORE_GARBAGE:
      points = 10;
      break;
    case SUBGOLDY_SCORE_SLUG:
      points = 500;
      break;
    case SUBGOLDY_SCORE_RING:
    case SUBGOLDY_SCORE_PARCEL_COLLECT:
    case SUBGOLDY_SCORE_PARCEL_DELIVER:
      points = 100;
      break;
    case SUBGOLDY_SCORE_BONUS:
      points = bonus_score;
      break;
    default:
      report_errorf(aUnknownScoreTy);
      points = 0;
      break;
  }
  player->score_buckets[score_kind] += points;
  old_total = player->total_score;
  player->total_score = old_total + points;
  if ( old_total / 50000 != (old_total + points) / 50000 )
  {
    visible_life_stock = player->visible_life_stock;
    if ( visible_life_stock < 9 )
    {
      player->visible_life_stock = visible_life_stock + 1;
      if ( !*((_DWORD *)MEMORY[0x4DF904] + 119190) && !*((_DWORD *)MEMORY[0x4DF904] + 9) )
        play_sound_effect(44);
    }
  }
}
