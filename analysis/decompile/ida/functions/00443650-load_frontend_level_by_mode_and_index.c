/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_frontend_level_by_mode_and_index @ 0x443650 */
/* selector: load_frontend_level_by_mode_and_index */

// Formats the mode-specific level filename for postal, challenge, time-trial, or tutorial front-end launches and then loads that level definition file.
_DWORD *__thiscall sub_443650(char *this, int a2, int a3)
{
  char Buffer[128]; // [esp+4h] [ebp-80h] BYREF

  switch ( a2 )
  {
    case 0:
      if ( a3 > 50 )
      {
        if ( a3 == 51 )
          sprintf(Buffer, aArcadeextra000);
      }
      else
      {
        sprintf(Buffer, "Arcade%03i.txt", a3);
      }
      break;
    case 1:
      sprintf(Buffer, aChallenge000Tx);
      break;
    case 2:
    case 3:
      sprintf(Buffer, aArcade000Txt);
      break;
    case 4:
      if ( a3 > 50 )
        sprintf(Buffer, "TimeTrialExtra%03i.txt", a3 - 50);
      else
        sprintf(Buffer, "Arcade%03i.txt", a3);
      break;
    case 7:
      sprintf(Buffer, aTutorialTxt);
      break;
    default:
      return load_level_definition_file(this, Buffer);
  }
  return load_level_definition_file(this, Buffer);
}

