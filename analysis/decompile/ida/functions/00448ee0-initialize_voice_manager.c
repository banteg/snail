/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_voice_manager @ 0x448ee0 */
/* selector: initialize_voice_manager */

// Recovered `cRVoiceManager::Init()` member: parses the authored 16-set Voice/_Voice.txt bank, registers each sample, applies normalization and frequency settings, and resets cooldown state.
void __thiscall initialize_voice_manager(VoiceManager *manager)
{
  float v1; // ebp
  const char *v2; // edi
  char *case_insensitive_substring; // eax
  char *v4; // esi
  char *crlf_line; // eax
  int32_t v6; // edi
  VoiceSet *v7; // ebp
  int32_t i; // esi
  char *v9; // edx
  char *v10; // eax
  char j; // cl
  _BYTE *v12; // eax
  char *v13; // esi
  char *v14; // eax
  double v15; // st7
  VoiceManager *v16; // ecx
  char *cursor; // [esp+10h] [ebp-214h] BYREF
  float voice_scale; // [esp+14h] [ebp-210h]
  float sfx_scale; // [esp+18h] [ebp-20Ch]
  VoiceManager *v20; // [esp+1Ch] [ebp-208h]
  float music_scale; // [esp+20h] [ebp-204h]
  char ArgList[256]; // [esp+24h] [ebp-200h] BYREF
  char path[6]; // [esp+124h] [ebp-100h] BYREF
  char v24; // [esp+12Ah] [ebp-FAh] BYREF

  v20 = manager;
  ArgList[0] = 0;
  voice_scale = COERCE_FLOAT(get_archive_data_base());
  load_file_bytes_from_archive_or_fs(aVoiceVoiceTxt, (void *)LODWORD(voice_scale), nullptr);
  v1 = 0.0;
  for ( sfx_scale = 0.0; ; v1 = sfx_scale )
  {
    rstrcpy_checked_ascii(ArgList, aSet);
    switch ( LODWORD(v1) )
    {
      case 0:
        v2 = aDamage;
        goto LABEL_20;
      case 1:
        v2 = aDying;
        goto LABEL_20;
      case 2:
        v2 = aEnemies;
        goto LABEL_20;
      case 3:
        v2 = aFall;
        goto LABEL_20;
      case 4:
        v2 = aMisc;
        goto LABEL_20;
      case 5:
        v2 = aPowerup;
        goto LABEL_20;
      case 6:
        v2 = aSlow;
        goto LABEL_20;
      case 7:
        v2 = aStart;
        goto LABEL_20;
      case 8:
        v2 = aVictory;
        goto LABEL_20;
      case 9:
        v2 = aOuch;
        goto LABEL_20;
      case 0xA:
        v2 = aPackage;
        goto LABEL_20;
      case 0xB:
        v2 = aSlugged;
        goto LABEL_20;
      case 0xC:
        v2 = aWormtunnel;
        goto LABEL_20;
      case 0xD:
        v2 = g_tutorial_text;
        goto LABEL_20;
      case 0xE:
        v2 = aPostal;
        goto LABEL_20;
      case 0xF:
        v2 = aSupertramp;
LABEL_20:
        strcat(ArgList, v2);
        break;
      default:
        break;
    }
    case_insensitive_substring = find_case_insensitive_substring(ArgList, (char *)LODWORD(voice_scale));
    cursor = case_insensitive_substring;
    if ( !case_insensitive_substring )
      break;
    cursor = find_case_insensitive_substring(asc_4A1568, case_insensitive_substring);
    v4 = find_case_insensitive_substring(asc_4AC1BC, cursor);
    crlf_line = (char *)advance_to_next_crlf_line(cursor);
    v6 = 0;
    for ( cursor = crlf_line; crlf_line < v4; crlf_line = (char *)advance_to_next_crlf_line(crlf_line) )
      ++v6;
    v7 = &v20->sets[LODWORD(v1)];
    initialize_voice_set(v7, v6);
    for ( i = 0; i < v6; ++i )
    {
      while ( *cursor == 9 || *cursor == 32 )
        ++cursor;
      rstrcpy_checked_ascii(path, aVoice);
      v9 = cursor;
      v10 = &v24;
      for ( j = *cursor; *v9 != 46; j = *v9 )
      {
        *v10++ = j;
        cursor = ++v9;
      }
      *v10 = 46;
      v12 = v10 + 1;
      *v12++ = 111;
      *v12++ = 103;
      *v12 = 103;
      v12[1] = 0;
      cursor = (char *)advance_to_next_crlf_line(v9);
      v7->bites[i] = register_sound_sample(path, 1);
    }
    ++LODWORD(sfx_scale);
    if ( SLODWORD(sfx_scale) >= 16 )
    {
      v13 = (char *)LODWORD(voice_scale);
      v14 = find_case_insensitive_substring(aNormalizemusic, (char *)LODWORD(voice_scale));
      cursor = find_case_insensitive_substring(asc_4A1644, v14);
      voice_scale = COERCE_FLOAT(parse_next_signed_int(&cursor));
      music_scale = (double)SLODWORD(voice_scale) * 0.0099999998;
      cursor = find_case_insensitive_substring(aNormalizesfx, v13);
      cursor = find_case_insensitive_substring(asc_4A1644, cursor);
      voice_scale = COERCE_FLOAT(parse_next_signed_int(&cursor));
      sfx_scale = (double)SLODWORD(voice_scale) * 0.0099999998;
      cursor = find_case_insensitive_substring(aNormalizevoice, v13);
      cursor = find_case_insensitive_substring(asc_4A1644, cursor);
      voice_scale = (double)parse_next_signed_int(&cursor) * 0.0099999998;
      set_audio_normalization_scales(&g_audio_backend, music_scale, sfx_scale, voice_scale);
      cursor = find_case_insensitive_substring(aFrequency, v13);
      cursor = find_case_insensitive_substring(asc_4A1644, cursor);
      v15 = parse_next_float32(&cursor);
      v16 = v20;
      v20->global_frequency_seconds = v15;
      reset_voice_manager(v16);
      return;
    }
  }
  report_errorf("Cannot find %s in _Voice.txt", ArgList);
}
