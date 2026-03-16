/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_subgame_features @ 0x435df0 */
/* selector: set_subgame_features */

int __thiscall sub_435DF0(int this)
{
  int result; // eax

  if ( *(_BYTE *)(this + 16721360) )
  {
    result = *(_DWORD *)(this + 16721364);
    *(_DWORD *)(this + 76) = *(_DWORD *)(result + 56);
  }
  else
  {
    result = *(_DWORD *)(this + 64);
    *(_DWORD *)(this + 76) = 1156;
    *(_DWORD *)(this + 76) = &unk_600484;
    switch ( result )
    {
      case 0:
      case 1:
        *(_DWORD *)(this + 76) = 16109567;
        break;
      case 4:
        *(_DWORD *)(this + 76) = &unk_75CFFF;
        break;
      case 7:
        *(_DWORD *)(this + 76) = 14995455;
        break;
      default:
        return result;
    }
  }
  return result;
}

