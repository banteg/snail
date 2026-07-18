/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: normalize_segment_glyph_for_track_flags @ 0x437270 */
/* selector: normalize_segment_glyph_for_track_flags */

char __thiscall normalize_segment_glyph_for_track_flags(
        SubgameRuntime *runtime,
        char glyph,
        int32_t row,
        char edge_row)
{
  char result; // al
  uint32_t runtime_flags; // ecx
  uint32_t v6; // edx
  uint32_t v7; // edx
  uint32_t v8; // edx
  uint32_t v9; // edx
  uint32_t v10; // ecx
  uint32_t v11; // ecx
  uint32_t v12; // ecx
  uint32_t v13; // ecx

  result = glyph;
  if ( row <= runtime->completion_row_start )
  {
    switch ( glyph )
    {
      case ' ':
        runtime_flags = runtime->runtime_flags;
        if ( (runtime_flags & 0x400) != 0 )
        {
          if ( (runtime_flags & 1) == 0 )
            result = 46;
        }
        else
        {
          result = 44;
        }
        break;
      case '$':
        v13 = runtime->runtime_flags;
        if ( (v13 & 0x800) == 0 )
          result = (v13 & 0x40) != 0 ? 95 : 46;
        break;
      case '-':
        if ( (runtime->runtime_flags & 0x4000) == 0 )
          result = 46;
        break;
      case '<':
      case '>':
        if ( (runtime->runtime_flags & 0x200) == 0 )
          result = 46;
        break;
      case '=':
        v10 = runtime->runtime_flags;
        if ( (v10 & 0x100) == 0 )
        {
          if ( (v10 & 1) != 0 )
            result = (v10 & 0x400) != 0 ? 32 : 44;
          else
            result = 46;
        }
        break;
      case '[':
        v9 = runtime->runtime_flags;
        if ( (v9 & 0x200) != 0 )
        {
          if ( (v9 & 0x20) != 0 )
          {
            if ( runtime->track_mirror_enabled )
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
        v8 = runtime->runtime_flags;
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
        if ( (runtime->runtime_flags & 0x40) == 0 && !edge_row )
          result = 46;
        break;
      case 'o':
        v12 = runtime->runtime_flags;
        if ( (v12 & 4) == 0 )
          result = (v12 & 0x40) != 0 ? 95 : 46;
        break;
      case '{':
        v7 = runtime->runtime_flags;
        if ( (v7 & 0x200) != 0 )
        {
          if ( (v7 & 0x20) != 0 )
          {
            if ( runtime->track_mirror_enabled )
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
        v11 = runtime->runtime_flags;
        if ( (v11 & 0x100) == 0 )
        {
          if ( (v11 & 1) != 0 )
            result = (v11 & 0x400) != 0 ? 61 : 44;
          else
            result = 32;
        }
        break;
      case '}':
        v6 = runtime->runtime_flags;
        if ( (v6 & 0x200) != 0 )
        {
          if ( (v6 & 0x20) != 0 )
          {
LABEL_23:
            if ( runtime->track_mirror_enabled )
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
