/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_subgoldy_death @ 0x446e30 */
/* selector: initialize_subgoldy_death */

// Void `Player` member that chooses Goldy's death outcome from the current gameplay mode and visible life stock, then enters the resurrect state machine in either respawn or final-loss mode. Both direct callers discard EAX; its tail paths only preserve the downstream selector residue. Cross-port Android and iOS symbols match this helper to `cRSubGoldy::DeathInit()`.
void __thiscall initialize_subgoldy_death(Player *player)
{
  switch ( player->game->level_mode )
  {
    case 0:
      if ( player->visible_life_stock > 0 )
        goto LABEL_4;
      goto LABEL_3;
    case 1:
    case 4:
LABEL_3:
      initialize_subgoldy_resurrect(player, 1);
      break;
    case 7:
LABEL_4:
      initialize_subgoldy_resurrect(player, 0);
      break;
    default:
      return;
  }
}
