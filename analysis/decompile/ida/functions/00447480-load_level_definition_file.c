/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_level_definition_file @ 0x447480 */
/* selector: load_level_definition_file */

_DWORD *__thiscall sub_447480(char *this, char *a2)
{
  char *v3; // eax
  char *v4; // eax
  char v5; // cl
  char *i; // edx
  char *v7; // eax
  int v8; // edi
  char *v9; // eax
  char *v10; // eax
  char *v11; // eax
  unsigned int v12; // eax
  char *v13; // edx
  char *j; // ecx
  char *v15; // eax
  char *v17; // eax
  char v18; // cl
  int v19; // edx
  char *v20; // eax
  char *v21; // eax
  char *v22; // ecx
  char k; // dl
  _BYTE *v24; // ecx
  char *v25; // edx
  char *v26; // eax
  char *v27; // eax
  char v28; // al
  char *v29; // eax
  char *v30; // eax
  char *v31; // eax
  char *v32; // edi
  char *v33; // eax
  char v34; // dl
  char *ii; // ecx
  int v36; // eax
  _BYTE *v37; // ecx
  char *v38; // ecx
  char *v39; // edx
  char v40; // al
  char *v41; // eax
  char *v42; // eax
  char *v43; // eax
  char *v44; // eax
  unsigned int v45; // edx
  char v46; // cl
  char *v47; // ecx
  char *v48; // eax
  char *v49; // edx
  char jj; // cl
  char *v51; // eax
  char *v52; // eax
  char v53; // dl
  char *m; // ecx
  _BYTE *v55; // ecx
  char *v56; // eax
  char *v57; // eax
  char v58; // dl
  char *n; // ecx
  _BYTE *v60; // ecx
  char *v61; // [esp-4h] [ebp-724h]
  char *v62; // [esp+10h] [ebp-710h] BYREF
  char *v63; // [esp+14h] [ebp-70Ch] BYREF
  int v64; // [esp+18h] [ebp-708h]
  char *v65; // [esp+1Ch] [ebp-704h]
  char Buffer[512]; // [esp+20h] [ebp-700h] BYREF
  char v67[128]; // [esp+220h] [ebp-500h] BYREF
  char ArgList[128]; // [esp+2A0h] [ebp-480h] BYREF
  char v69[512]; // [esp+320h] [ebp-400h] BYREF
  char v70[512]; // [esp+520h] [ebp-200h] BYREF

  unk_74EC74 = (int)a2;
  sprintf(Buffer, "Levels/%s", a2);
  if ( !load_file_bytes_from_archive_or_fs(Buffer, unk_74EC78, nullptr) )
  {
    report_errorf("Cannot find %s reverting to default.txt", Buffer);
    sprintf(Buffer, aLevelsDefaultT);
    load_file_bytes_from_archive_or_fs(Buffer, unk_74EC78, nullptr);
  }
  v3 = find_case_insensitive_substring(aName, unk_74EC78);
  v62 = v3;
  if ( !v3 )
  {
    report_errorf("Cannot find Name:' in %s", Buffer);
    v3 = nullptr;
  }
  v4 = find_case_insensitive_substring(asc_4AC244, v3) + 1;
  v62 = v4;
  v5 = *v4;
  for ( i = this + 1726684; *v4 != 39; v5 = *v4 )
  {
    if ( v5 < 32 )
      break;
    *i++ = v5;
    v62 = ++v4;
  }
  *i = 0;
  if ( !*((_BYTE *)MEMORY[0x4DF904] + 19744312) )
  {
    v7 = find_case_insensitive_substring(aArcade, a2);
    v62 = v7;
    if ( v7 )
    {
      v62 = find_case_insensitive_substring(aE, v7) + 1;
      v8 = 672 * parse_next_signed_int(&v62);
      sprintf((char *const)MEMORY[0x4DF904] + v8 + 19744360, "%s", this + 1726684);
      v9 = find_case_insensitive_substring(aGalaxytext, unk_74EC78);
      v62 = v9;
      if ( v9 )
      {
        v10 = find_case_insensitive_substring(asc_4A1568, v9);
        v62 = v10;
        if ( v10 )
        {
          v62 = (char *)sub_44E690(v10);
          v11 = find_case_insensitive_substring(asc_4AC1BC, v62);
          if ( v11 )
          {
            v12 = (unsigned int)(v11 - 2);
            v13 = (char *)MEMORY[0x4DF904] + v8 + 19744488;
            for ( j = v62; (unsigned int)v62 < v12; ++v62 )
            {
              if ( *j < 32 )
              {
                *v13 = 62;
                j = v62;
                ++v13;
                if ( *v62 < 32 )
                {
                  do
                    v62 = ++j;
                  while ( *j < 32 );
                }
              }
              *v13++ = *j;
              j = v62 + 1;
            }
            *v13 = 0;
          }
          else
          {
            report_warningf("Cannot find } for GalaxyText: in %s", a2);
            rstrcpy_checked_ascii((char *)MEMORY[0x4DF904] + v8 + 19744488, aTextErrorMissi_0);
          }
        }
        else
        {
          report_warningf("Cannot find { for GalaxyText: in %s", a2);
          rstrcpy_checked_ascii((char *)MEMORY[0x4DF904] + v8 + 19744488, aTextErrorMissi);
        }
      }
      else
      {
        report_warningf("Cannot find GalaxyText: in %s", a2);
        rstrcpy_checked_ascii((char *)MEMORY[0x4DF904] + v8 + 19744488, aTextMissing);
      }
    }
  }
  v62 = find_case_insensitive_substring(aRandomYes, unk_74EC78);
  if ( v62 )
  {
    *(this + 1726664) = 1;
    v15 = find_case_insensitive_substring(aLength, unk_74EC78);
    v62 = v15;
    if ( !v15 )
      return (_DWORD *)report_errorf("Cannot Length: in %s", Buffer);
    v17 = find_case_insensitive_substring(asc_4A1644, v15) + 1;
    v62 = v17;
    *((_DWORD *)this + 431665) = 0;
    v18 = *v17;
    if ( *v17 != 97 && v18 != 65 && v18 >= 48 )
    {
      do
      {
        if ( v18 > 57 )
          break;
        ++v17;
        v19 = 5 * *((_DWORD *)this + 431665);
        v62 = v17;
        *((_DWORD *)this + 431665) = v18 + 2 * v19 - 48;
        v18 = *v17;
      }
      while ( *v17 >= 48 );
    }
  }
  else
  {
    *(this + 1726664) = 0;
    *((_DWORD *)this + 431665) = 0;
  }
  v20 = find_case_insensitive_substring(aBackground, unk_74EC78);
  v62 = v20;
  if ( !v20 )
    return (_DWORD *)report_errorf("No Background: in %s", Buffer);
  v21 = find_case_insensitive_substring(asc_4A1644, v20) + 1;
  v62 = v21;
  v22 = v70;
  for ( k = *v21; *v21 != 46; k = *v21 )
  {
    *v22++ = k;
    v62 = ++v21;
  }
  *v22 = 46;
  v24 = v22 + 1;
  v25 = (char *)MEMORY[0x4DF904];
  *v24++ = 116;
  *v24++ = 120;
  *v24 = 116;
  v24[1] = 0;
  *((_DWORD *)this + 431706) = load_landscape_script_by_name(v25 + 17220120, v70);
  v26 = find_case_insensitive_substring(aFringe, unk_74EC78);
  v62 = v26;
  if ( v26 )
  {
    v62 = find_case_insensitive_substring(asc_4A1644, v26) + 1;
    v64 = parse_next_signed_int(&v62);
    *((float *)this + 431667) = (double)v64 * 0.0039215689;
    v64 = parse_next_signed_int(&v62);
    *((float *)this + 431668) = (double)v64 * 0.0039215689;
    v64 = parse_next_signed_int(&v62);
    *((float *)this + 431669) = (double)v64 * 0.0039215689;
  }
  else
  {
    report_errorf("No Fringe: in %s using white", Buffer);
    store_color4f((_DWORD *)this + 431667, 1065353216, 1065353216, 1065353216, 1065353216);
  }
  v27 = find_case_insensitive_substring(aTrack, unk_74EC78);
  v62 = v27;
  if ( v27 )
  {
    v62 = find_case_insensitive_substring(asc_4A1644, v27) + 1;
    v28 = *v62;
    if ( *v62 == 48 )
    {
      *((_DWORD *)this + 431708) = 0;
    }
    else
    {
      switch ( v28 )
      {
        case '1':
          *((_DWORD *)this + 431708) = 1;
          break;
        case '2':
          *((_DWORD *)this + 431708) = 2;
          break;
        case '3':
          *((_DWORD *)this + 431708) = 3;
          break;
        case 'r':
          *((_DWORD *)this + 431708) = 5;
          break;
      }
    }
  }
  else
  {
    report_errorf("No Track: in %s using Track0.tga", Buffer);
    *((_DWORD *)this + 431708) = 0;
  }
  v29 = find_case_insensitive_substring(aParcels, unk_74EC78);
  v62 = v29;
  if ( !v29 )
  {
    *((_DWORD *)this + 431707) = 0;
    return (_DWORD *)report_errorf("No Parcel: in %s", Buffer);
  }
  v62 = find_case_insensitive_substring(asc_4A1644, v29);
  *((_DWORD *)this + 431707) = parse_next_signed_int(&v62);
  v30 = find_case_insensitive_substring(aQuota, unk_74EC78);
  v62 = v30;
  if ( !v30 )
  {
    *((_DWORD *)this + 431709) = 0;
    return (_DWORD *)report_errorf("No Quota: in %s", Buffer);
  }
  v62 = find_case_insensitive_substring(asc_4A1644, v30);
  *((_DWORD *)this + 431709) = parse_next_signed_int(&v62);
  v62 = find_case_insensitive_substring(aSpeedSelect, unk_74EC78);
  if ( v62 )
  {
    *((_DWORD *)this + 431703) = -1082130432;
  }
  else
  {
    v31 = find_case_insensitive_substring(aSpeed, unk_74EC78);
    v62 = v31;
    if ( v31 )
    {
      v62 = find_case_insensitive_substring(asc_4A1644, v31) + 1;
      *((float *)this + 431703) = parse_next_float32(&v62);
    }
    else
    {
      report_errorf("Cannot find Speed: in Segment %s\n", Buffer);
      *((_DWORD *)this + 431703) = 1120403456;
    }
  }
  v62 = find_case_insensitive_substring(aGarbage, unk_74EC78);
  if ( v62 )
    *((float *)this + 431704) = parse_next_float32(&v62);
  else
    *((_DWORD *)this + 431704) = -1082130432;
  v62 = find_case_insensitive_substring(aSalt, unk_74EC78);
  if ( v62 )
    *((float *)this + 431705) = parse_next_float32(&v62);
  else
    *((_DWORD *)this + 431705) = -1082130432;
  *(_DWORD *)this = 0;
  v62 = find_case_insensitive_substring(aSegmentsBegin, unk_74EC78);
  if ( !v62 )
    return (_DWORD *)report_errorf("Cannot find Segments Begin: in %s", Buffer);
  v32 = find_case_insensitive_substring(aSegmentsEnd, unk_74EC78);
  v65 = v32;
  if ( !v32 )
    return (_DWORD *)report_errorf("Cannot find Segments End: in %s", Buffer);
  v33 = (char *)sub_44E690(v62);
  v62 = v33;
  if ( !v33 )
    return (_DWORD *)report_errorf("Unexpected end of file in %s", Buffer);
  if ( v33 >= v32 )
  {
LABEL_94:
    v51 = find_case_insensitive_substring(aFirst, unk_74EC78);
    v62 = v51;
    if ( !v51 )
      return (_DWORD *)report_errorf("Cannot find 'First:' in %s", Buffer);
    v52 = (char *)sub_44E690(v51);
    v62 = v52;
    if ( v52 )
    {
      v53 = *v52;
      for ( m = v69; *v52 != 46; v53 = *v52 )
      {
        *m++ = v53;
        v62 = ++v52;
      }
      *m = 46;
      v55 = m + 1;
      *v55++ = 116;
      *v55++ = 120;
      *v55 = 116;
      v55[1] = 0;
      copy_segment_definition_to_level_slot(v69, (_DWORD *)this + 423201);
      v56 = find_case_insensitive_substring(aLast, unk_74EC78);
      v62 = v56;
      if ( !v56 )
        return (_DWORD *)report_errorf("Cannot find 'Last:' in %s", Buffer);
      v57 = (char *)sub_44E690(v56);
      v62 = v57;
      if ( v57 )
      {
        v58 = *v57;
        for ( n = v69; *v57 != 46; v58 = *v57 )
        {
          *n++ = v58;
          v62 = ++v57;
        }
        *n = 46;
        v60 = n + 1;
        *v60++ = 116;
        *v60++ = 120;
        *v60 = 116;
        v60[1] = 0;
        return copy_segment_definition_to_level_slot(v69, (_DWORD *)this + 427433);
      }
    }
    return (_DWORD *)report_errorf("Unexpected end of file in %s", Buffer);
  }
  while ( 1 )
  {
    v34 = *v33;
    for ( ii = v69; *v33 != 46; v34 = *v33 )
    {
      *ii++ = v34;
      v62 = ++v33;
    }
    v36 = *(_DWORD *)this;
    *ii = 46;
    v37 = ii + 1;
    *v37++ = 116;
    *v37++ = 120;
    *v37 = 116;
    v37[1] = 0;
    copy_segment_definition_to_level_slot(v69, (_DWORD *)this + 4232 * v36 + 1);
    v38 = v62 + 3;
    v39 = v67;
    v63 = v62 + 3;
    v40 = v62[3];
    if ( v40 >= 32 )
    {
      do
      {
        *v39++ = v40;
        v63 = ++v38;
        v40 = *v38;
      }
      while ( *v38 >= 32 );
    }
    *v39 = 0;
    v41 = find_case_insensitive_substring(aAngle, v67);
    v63 = v41;
    if ( v41 )
    {
      v63 = find_case_insensitive_substring(asc_4A2094, v41);
      v64 = parse_next_signed_int(&v63);
      *((float *)this + 4232 * *(_DWORD *)this + 4102) = (double)v64 * 0.017453292;
    }
    else
    {
      *((_DWORD *)this + 4232 * *(_DWORD *)this + 4102) = 0;
    }
    *(this + 16928 * *(_DWORD *)this + 16412) = 0;
    v42 = find_case_insensitive_substring(aMessage, v67);
    v63 = v42;
    if ( v42 )
    {
      v43 = find_case_insensitive_substring(asc_4A2094, v42) + 1;
      v63 = v43;
      if ( *v43 != 34 )
        return (_DWORD *)report_errorf(aNeedAfterMessa);
      v44 = v43 + 1;
      v63 = v44;
      v45 = (unsigned int)v44;
      if ( *v44 != 34 )
      {
        do
          v46 = *(_BYTE *)++v45;
        while ( v46 != 34 );
      }
      v47 = this + 16928 * *(_DWORD *)this + 16412;
      if ( (unsigned int)v44 < v45 )
      {
        do
        {
          *v47++ = *v44;
          v44 = ++v63;
        }
        while ( (unsigned int)v63 < v45 );
      }
      *v47 = 0;
      v63 = find_case_insensitive_substring(aDuration_0, v67);
      *((_DWORD *)this + 4232 * *(_DWORD *)this + 4231) = 1082130432;
      if ( v63 )
      {
        v63 = find_case_insensitive_substring(asc_4A2094, v63) + 1;
        *((float *)this + 4232 * *(_DWORD *)this + 4231) = parse_next_float32(&v63);
      }
      v63 = find_case_insensitive_substring(aSample, v67);
      *((_DWORD *)this + 4232 * *(_DWORD *)this + 4232) = -1;
      if ( v63 )
      {
        v48 = find_case_insensitive_substring(asc_4A2094, v63) + 2;
        v63 = v48;
        v49 = ArgList;
        for ( jj = *v48; *v48 != 34; jj = *v48 )
        {
          *v49++ = jj;
          v63 = ++v48;
        }
        *v49 = 0;
        *((_DWORD *)this + 4232 * *(_DWORD *)this + 4232) = sub_432FC0(ArgList);
        if ( *((_DWORD *)this + 4232 * *(_DWORD *)this + 4232) == -1 )
          report_errorf("Cannot find sample %s in %s", ArgList, Buffer);
      }
    }
    v61 = v62;
    ++*(_DWORD *)this;
    v33 = (char *)sub_44E690(v61);
    v62 = v33;
    if ( !v33 )
      return (_DWORD *)report_errorf("Unexpected end of file in %s", a2);
    if ( v33 >= v65 )
      goto LABEL_94;
  }
}

