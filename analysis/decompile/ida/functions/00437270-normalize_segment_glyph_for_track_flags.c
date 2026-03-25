/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: normalize_segment_glyph_for_track_flags @ 0x437270 */
/* selector: normalize_segment_glyph_for_track_flags */

char __thiscall sub_437270(int this, char a2, int a3, char a4)
{
  char result; // al
  int v5; // ecx
  int v6; // edx
  int v7; // edx
  int v8; // edx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx

  result = a2;
  if ( a3 <= *(_DWORD *)(this + 88) )
  {
    switch ( a2 )
    {
      case ' ':
        v5 = *(_DWORD *)(this + 76);
        if ( (v5 & 0x400) != 0 )
        {
          if ( (v5 & 1) == 0 )
            result = 46;
        }
        else
        {
          result = 44;
        }
        break;
      case '$':
        v13 = *(_DWORD *)(this + 76);
        if ( (v13 & 0x800) == 0 )
          result = (v13 & 0x40) != 0 ? 95 : 46;
        break;
      case '-':
        if ( (*(_DWORD *)(this + 76) & 0x4000) == 0 )
          result = 46;
        break;
      case '<':
      case '>':
        if ( (*(_DWORD *)(this + 76) & 0x200) == 0 )
          result = 46;
        break;
      case '=':
        v10 = *(_DWORD *)(this + 76);
        if ( (v10 & 0x100) == 0 )
        {
          if ( (v10 & 1) != 0 )
            result = (v10 & 0x400) != 0 ? 32 : 44;
          else
            result = 46;
        }
        break;
      case '[':
        v9 = *(_DWORD *)(this + 76);
        if ( (v9 & 0x200) != 0 )
        {
          if ( (v9 & 0x20) != 0 )
          {
            if ( *(_BYTE *)(this + 2) )
              result = 91;
          }
          else
          {
            result = 60;
          }
        }
        else
        {
          result = 46;
        }
        break;
      case ']':
        v8 = *(_DWORD *)(this + 76);
        if ( (v8 & 0x200) != 0 )
        {
          if ( (v8 & 0x20) != 0 )
            goto LABEL_23;
          result = 60;
        }
        else
        {
          result = 46;
        }
        break;
      case '_':
        if ( (*(_BYTE *)(this + 76) & 0x40) == 0 && !a4 )
          result = 46;
        break;
      case 'o':
        v12 = *(_DWORD *)(this + 76);
        if ( (v12 & 4) == 0 )
          result = (v12 & 0x40) != 0 ? 95 : 46;
        break;
      case '{':
        v7 = *(_DWORD *)(this + 76);
        if ( (v7 & 0x200) != 0 )
        {
          if ( (v7 & 0x20) != 0 )
          {
            if ( *(_BYTE *)(this + 2) )
              result = 125;
          }
          else
          {
            result = 62;
          }
        }
        else
        {
          result = 46;
        }
        break;
      case '|':
        v11 = *(_DWORD *)(this + 76);
        if ( (v11 & 0x100) == 0 )
        {
          if ( (v11 & 1) != 0 )
            result = (v11 & 0x400) != 0 ? 61 : 44;
          else
            result = 32;
        }
        break;
      case '}':
        v6 = *(_DWORD *)(this + 76);
        if ( (v6 & 0x200) != 0 )
        {
          if ( (v6 & 0x20) != 0 )
          {
LABEL_23:
            if ( *(_BYTE *)(this + 2) )
              result = 123;
          }
          else
          {
            result = 62;
          }
        }
        else
        {
          result = 46;
        }
        break;
      default:
        return result;
    }
  }
  return result;
}

