/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_player_movement_flags @ 0x43a1a0 */
/* selector: update_player_movement_flags */

// Maps the player movement-flag selector at +0x308 onto movement_flags and the movement-fire progress step at +0x2734, then refreshes the 0x2984 state machine when the mask changes.
int __thiscall update_player_movement_flags(Player *player)
{
  int selector; // eax
  unsigned int result; // eax

  selector = player->movement_flag_selector;
  player->movement_flags = 0;
  switch ( selector )
  {
    case 0:
      player->movement_flags = 1;
      player->movement_fire_progress_step = 0.074074075;
      break;
    case 1:
      player->movement_flags = 2;
      player->movement_fire_progress_step = 0.074074075;
      break;
    case 2:
      player->movement_flags = 4;
      player->movement_fire_progress_step = 0.074074075;
      break;
    case 3:
      player->movement_flags = 8;
      player->movement_fire_progress_step = 0.1111111;
      break;
    case 4:
      player->movement_flags = 16;
      player->movement_fire_progress_step = 0.1111111;
      break;
    case 5:
      player->movement_flags = 32;
      goto LABEL_12;
    case 6:
      player->movement_flags = 64;
      player->movement_fire_progress_step = 0.13333334;
      break;
    case 7:
      player->movement_flags = 192;
      player->movement_fire_progress_step = 0.13333334;
      break;
    case 8:
      player->movement_flags = 144;
      player->movement_fire_progress_step = 0.1111111;
      break;
    default:
      player->movement_flags = 129;
LABEL_12:
      player->movement_fire_progress_step = 0.06666667;
      break;
  }
  result = player->movement_flags;
  if ( result == player->previous_movement_flags )
  {
    player->previous_movement_flags = player->movement_flags;
  }
  else
  {
    set_snail_weapon(&player->presentation, player->movement_flags);
    result = player->movement_flags;
    player->previous_movement_flags = result;
  }
  return result;
}
