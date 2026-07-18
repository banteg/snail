/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_frontend_level_by_mode_and_index @ 0x443650 */
/* selector: load_frontend_level_by_mode_and_index */

// Formats the mode-specific level filename for postal, challenge, time-trial, or tutorial front-end launches and loads it through the owning SubTracks object. Symbol-preserving iOS builds name the corresponding void member `cRSubTracks::Load(int, int)`; every Windows caller also discards the incidental value left in EAX.
void __thiscall load_frontend_level_by_mode_and_index(SubTracks *tracks, int mode, int level_index)
{
  char Buffer[128]; // [esp+4h] [ebp-80h] BYREF

  switch ( mode )
  {
    case 0:
      if ( level_index > 50 )
      {
        if ( level_index == 51 )
          sprintf(Buffer, g_arcade_extra_level_path);
      }
      else
      {
        sprintf(Buffer, "Arcade%03i.txt", level_index);
      }
      break;
    case 1:
      sprintf(Buffer, g_challenge_level_path);
      break;
    case 2:
    case 3:
      sprintf(Buffer, g_arcade000_level_path);
      break;
    case 4:
      if ( level_index > 50 )
        sprintf(Buffer, "TimeTrialExtra%03i.txt", level_index - 50);
      else
        sprintf(Buffer, "Arcade%03i.txt", level_index);
      break;
    case 7:
      sprintf(Buffer, g_tutorial_level_path);
      break;
    default:
      break;
  }
  load_level_definition_file(tracks, Buffer);
}
