/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_voice_manager @ 0x448ee0 */
/* selector: initialize_voice_manager */

_DWORD *__thiscall sub_448EE0(_DWORD *this)
{
  float v1; // ebp
  const char *v2; // edi
  char *v3; // eax
  char *v4; // esi
  char *v5; // eax
  int v6; // edi
  int *v7; // ebp
  int k; // esi
  char *v9; // edx
  char *v10; // eax
  char m; // cl
  _BYTE *v12; // eax
  char *v13; // esi
  char *v14; // eax
  double v15; // st7
  _DWORD *v16; // ecx
  char *j; // [esp+10h] [ebp-214h] BYREF
  float v19; // [esp+14h] [ebp-210h]
  float i; // [esp+18h] [ebp-20Ch]
  _DWORD *v21; // [esp+1Ch] [ebp-208h]
  int v22; // [esp+20h] [ebp-204h]
  char ArgList[256]; // [esp+24h] [ebp-200h] BYREF
  char v24[6]; // [esp+124h] [ebp-100h] BYREF
  char v25; // [esp+12Ah] [ebp-FAh] BYREF

  v21 = this;
  ArgList[0] = 0;
  v19 = COERCE_FLOAT(get_archive_data_base());
  load_file_bytes_from_archive_or_fs(aVoiceVoiceTxt, (_BYTE *)LODWORD(v19), nullptr);
  v1 = 0.0;
  for ( i = 0.0; ; v1 = i )
  {
    sub_44E5B0(ArgList, aSet);
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
        v2 = aTutorial;
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
    v3 = find_case_insensitive_substring(ArgList, (char *)LODWORD(v19));
    j = v3;
    if ( !v3 )
      break;
    j = find_case_insensitive_substring(asc_4A1568, v3);
    v4 = find_case_insensitive_substring(asc_4AC1BC, j);
    v5 = (char *)sub_44E690(j);
    v6 = 0;
    for ( j = v5; v5 < v4; v5 = (char *)sub_44E690(v5) )
      ++v6;
    v7 = &v21[6 * LODWORD(v1)];
    initialize_voice_set(v7, v6);
    for ( k = 0; k < v6; ++k )
    {
      while ( *j == 9 || *j == 32 )
        ++j;
      sub_44E5B0(v24, aVoice);
      v9 = j;
      v10 = &v25;
      for ( m = *j; *v9 != 46; m = *v9 )
      {
        *v10++ = m;
        j = ++v9;
      }
      *v10 = 46;
      v12 = v10 + 1;
      *v12++ = 111;
      *v12++ = 103;
      *v12 = 103;
      v12[1] = 0;
      j = (char *)sub_44E690(v9);
      *(_DWORD *)(v7[3] + 4 * k) = register_sound_sample(v24, 1);
    }
    ++LODWORD(i);
    if ( SLODWORD(i) >= 16 )
    {
      v13 = (char *)LODWORD(v19);
      v14 = find_case_insensitive_substring(aNormalizemusic, (char *)LODWORD(v19));
      j = find_case_insensitive_substring(asc_4A1644, v14);
      v19 = COERCE_FLOAT(sub_44E710(&j));
      *(float *)&v22 = (double)SLODWORD(v19) * 0.0099999998;
      j = find_case_insensitive_substring(aNormalizesfx, v13);
      j = find_case_insensitive_substring(asc_4A1644, j);
      v19 = COERCE_FLOAT(sub_44E710(&j));
      i = (double)SLODWORD(v19) * 0.0099999998;
      j = find_case_insensitive_substring(aNormalizevoice, v13);
      j = find_case_insensitive_substring(asc_4A1644, j);
      v19 = (double)sub_44E710(&j) * 0.0099999998;
      set_audio_normalization_scales(unk_753C58, v22, SLODWORD(i), SLODWORD(v19));
      j = find_case_insensitive_substring(aFrequency, v13);
      j = find_case_insensitive_substring(asc_4A1644, j);
      v15 = parse_next_float32(&j);
      v16 = v21;
      *((float *)v21 + 97) = v15;
      return reset_voice_manager(v16);
    }
  }
  return (_DWORD *)report_errorf("Cannot find %s in _Voice.txt", ArgList);
}

