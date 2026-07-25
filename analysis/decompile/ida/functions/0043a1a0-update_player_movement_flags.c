/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_player_movement_flags @ 0x43a1a0 */
/* selector: update_player_movement_flags */

// Maps the player movement-flag selector at +0x308 onto shoot_flags and the movement-fire progress step at +0x2734, then refreshes the 0x2984 state machine when the mask changes.
void __thiscall update_player_movement_flags(Player *player)
{
  int32_t shooting_tier; // eax

  shooting_tier = player->shooting_tier;
  player->shoot_flags = 0;
  switch ( shooting_tier )
  {
    case 0:
      player->shoot_flags = 1;
      player->shoot_cooldown_step = 0.074074075;
      break;
    case 1:
      player->shoot_flags = 2;
      player->shoot_cooldown_step = 0.074074075;
      break;
    case 2:
      player->shoot_flags = 4;
      player->shoot_cooldown_step = 0.074074075;
      break;
    case 3:
      player->shoot_flags = 8;
      player->shoot_cooldown_step = 0.1111111;
      break;
    case 4:
      player->shoot_flags = 16;
      player->shoot_cooldown_step = 0.1111111;
      break;
    case 5:
      player->shoot_flags = 32;
      goto LABEL_12;
    case 6:
      player->shoot_flags = 64;
      player->shoot_cooldown_step = 0.13333334;
      break;
    case 7:
      player->shoot_flags = 192;
      player->shoot_cooldown_step = 0.13333334;
      break;
    case 8:
      player->shoot_flags = 144;
      player->shoot_cooldown_step = 0.1111111;
      break;
    default:
      player->shoot_flags = 129;
LABEL_12:
      player->shoot_cooldown_step = 0.06666667;
      break;
  }
  if ( player->shoot_flags != player->previous_shoot_flags )
    set_snail_weapon(&player->presentation, player->shoot_flags);
  player->previous_shoot_flags = player->shoot_flags;
}
