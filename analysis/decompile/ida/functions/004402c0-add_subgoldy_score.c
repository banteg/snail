/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: add_subgoldy_score @ 0x4402c0 */
/* selector: add_subgoldy_score */

// Void `Player` member that adds one scored gameplay event onto Goldy's per-event buckets and total score, and awards a bonus life whenever the total crosses a 50,000-point threshold while the visible life stock is still below nine. All 14 direct Windows callsites discard EAX. Cross-port evidence matches the `cRSubGoldy::ScoreAdd(int,int)` shape directly.
void __thiscall add_subgoldy_score(Player *player, int32_t score_kind, int32_t bonus_score)
{
  int32_t v4; // eax
  int32_t total_score; // edi
  int32_t visible_life_stock; // eax

  switch ( score_kind )
  {
    case 0:
      v4 = 10;
      break;
    case 1:
      v4 = 500;
      break;
    case 2:
    case 3:
    case 4:
      v4 = 100;
      break;
    case 5:
      v4 = bonus_score;
      break;
    default:
      report_errorf(aUnknownScoreTy);
      v4 = 0;
      break;
  }
  player->score_buckets[score_kind] += v4;
  total_score = player->total_score;
  player->total_score = total_score + v4;
  if ( total_score / 50000 != (total_score + v4) / 50000 )
  {
    visible_life_stock = player->visible_life_stock;
    if ( visible_life_stock < 9 )
    {
      player->visible_life_stock = visible_life_stock + 1;
      if ( !g_game_base->subgame.level_mode && !g_game_base->fade.state )
        play_sound_effect(44);
    }
  }
}
