/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_player_movement_flags @ 0x43a1a0 */
/* selector: update_player_movement_flags */

// Maps the player movement-flag selector at +0x308 onto movement_flags and the movement-fire progress step at +0x2734, then refreshes the 0x2984 state machine when the mask changes.
int __thiscall sub_43A1A0(int *this)
{
  int v2; // eax
  int result; // eax

  v2 = *(this + 194);
  *(this + 206) = 0;
  switch ( v2 )
  {
    case 0:
      *(this + 206) = 1;
      *(this + 2509) = 1033352230;
      break;
    case 1:
      *(this + 206) = 2;
      *(this + 2509) = 1033352230;
      break;
    case 2:
      *(this + 206) = 4;
      *(this + 2509) = 1033352230;
      break;
    case 3:
      *(this + 206) = 8;
      *(this + 2509) = 1038323256;
      break;
    case 4:
      *(this + 206) = 16;
      *(this + 2509) = 1038323256;
      break;
    case 5:
      *(this + 206) = 32;
      goto LABEL_12;
    case 6:
      *(this + 206) = 64;
      *(this + 2509) = 1040746633;
      break;
    case 7:
      *(this + 206) = 192;
      *(this + 2509) = 1040746633;
      break;
    case 8:
      *(this + 206) = 144;
      *(this + 2509) = 1038323256;
      break;
    default:
      *(this + 206) = 129;
LABEL_12:
      *(this + 2509) = 1032358025;
      break;
  }
  result = *(this + 206);
  if ( result == *(this + 207) )
  {
    *(this + 207) = *(this + 206);
  }
  else
  {
    set_snail_weapon(this + 2657, *(this + 206));
    result = *(this + 206);
    *(this + 207) = result;
  }
  return result;
}

