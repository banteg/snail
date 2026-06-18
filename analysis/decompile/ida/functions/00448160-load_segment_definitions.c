/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_segment_definitions @ 0x448160 */
/* selector: load_segment_definitions */

// Parses SEGMENTS/*.TXT into the segment catalog, storing the internal `Name:'...'` display label separately from the enumerated filename and recovering per-row parcel, model, velocity, path, ring, ring-speed, and jetpack-off metadata.
int __thiscall load_segment_definitions(int *this)
{
  int result; // eax
  int v3; // ebp
  char *v4; // edi
  char *case_insensitive_substring; // eax
  char v6; // cl
  char *v7; // eax
  int v8; // edx
  int *v9; // esi
  char *v10; // eax
  char *v11; // eax
  char v12; // cl
  char *v13; // eax
  int v14; // esi
  char *v15; // eax
  _BYTE *v16; // eax
  _BYTE *v17; // eax
  _BYTE *v18; // edi
  int v19; // ebp
  int *v20; // ecx
  char *v21; // edi
  int *v22; // esi
  int v23; // eax
  char v24; // bl
  int v25; // edx
  char *v26; // edi
  int v27; // eax
  char v28; // al
  char *i; // ecx
  char *v30; // eax
  char *v31; // eax
  char *v32; // ecx
  char j; // dl
  int v34; // eax
  _BYTE *v35; // ecx
  char *v36; // edx
  char *v37; // eax
  char *v38; // eax
  int v39; // edx
  char *v40; // eax
  int v41; // eax
  char *v42; // ecx
  char *v43; // eax
  char *v44; // eax
  char *v45; // edx
  char k; // cl
  int segment_path_index_by_name; // eax
  int v48; // eax
  int v49; // eax
  int v50; // eax
  int v51; // eax
  int v52; // eax
  int v53; // eax
  int v54; // eax
  char *v55; // eax
  double v56; // st7
  int v57; // eax
  bool v58; // cc
  const char *v59; // eax
  char *v60; // [esp+10h] [ebp-114E0h] BYREF
  int *v61; // [esp+14h] [ebp-114DCh]
  char *v62; // [esp+18h] [ebp-114D8h]
  int *v63; // [esp+1Ch] [ebp-114D4h]
  int v64; // [esp+20h] [ebp-114D0h]
  int v65; // [esp+24h] [ebp-114CCh]
  int v66; // [esp+28h] [ebp-114C8h]
  int v67; // [esp+2Ch] [ebp-114C4h]
  char ArgList[64]; // [esp+30h] [ebp-114C0h] BYREF
  char v69[512]; // [esp+70h] [ebp-11480h] BYREF
  char v70[128]; // [esp+270h] [ebp-11280h] BYREF
  char Buffer[512]; // [esp+2F0h] [ebp-11200h] BYREF
  char v72[4096]; // [esp+4F0h] [ebp-11000h] BYREF
  char v73[65536]; // [esp+14F0h] [ebp-10000h] BYREF

  v63 = this;
  *this = 0;
  enumerate_matching_archive_or_fs_entries(aSegments, aTxt, this, v73);
  result = *this;
  if ( *this >= 150 )
    return report_errorf(aTooManySegment);
  v3 = 0;
  v64 = 0;
  if ( result > 0 )
  {
    v4 = v73;
    v66 = 0;
    v65 = 0;
    v62 = v73;
    v61 = this + 34;
    while ( 2 )
    {
      sprintf(Buffer, "Segments/%s", v4);
      load_file_bytes_from_archive_or_fs(Buffer, v72, nullptr);
      case_insensitive_substring = find_case_insensitive_substring(aId, v72);
      if ( case_insensitive_substring )
      {
        v6 = case_insensitive_substring[3];
        v7 = case_insensitive_substring + 3;
        v8 = 0;
        if ( v6 >= 48 )
        {
          do
          {
            if ( v6 > 57 )
              break;
            ++v7;
            v8 = v6 + 10 * v8 - 48;
            v6 = *v7;
          }
          while ( *v7 >= 48 );
        }
        v9 = v61 - 17;
        v9[16] = v8;
        sprintf((char *const)v9, "%s", v4);
        v10 = find_case_insensitive_substring(aName, v72);
        if ( v10 )
        {
          v11 = find_case_insensitive_substring(asc_4AC244, v10);
          v12 = v11[1];
          v13 = v11 + 1;
          if ( v12 != 39 )
          {
            v14 = (char *)v9 - v13;
            do
            {
              v13[v14 - 64] = v12;
              v12 = *++v13;
            }
            while ( v12 != 39 );
          }
          v15 = find_case_insensitive_substring(aData, v72);
          if ( v15 )
          {
            v16 = (_BYTE *)advance_to_next_crlf_line(v15);
            if ( v16 )
            {
              v17 = (_BYTE *)advance_to_next_crlf_line(v16);
              v18 = v17;
              if ( v17 )
              {
                if ( *v17 == 64 )
                {
                  v67 = 0;
                  *v61 = 0;
                  while ( *v18 != 64 || v18[1] != 64 || v18[2] != 64 )
                  {
                    v19 = (__int16)v67 + v66;
                    v20 = v63;
                    v21 = v18 + 1;
                    v22 = &v63[14 * v19];
                    v23 = 0;
                    v22[547] = 0;
                    do
                    {
                      v24 = *v21++;
                      v25 = v23 + 8 * (v65 + *v61);
                      ++v23;
                      *((_BYTE *)v20 + v25 + 140) = v24;
                    }
                    while ( v23 < 8 );
                    if ( *v21 != 64 )
                      return report_errorf("Data line must end with '@' in Segment %s\n", &v73[128 * v64]);
                    v26 = v21 + 1;
                    ++*v61;
                    if ( *v26 == 42 )
                    {
                      v27 = v22[547];
                      LOBYTE(v27) = v27 | 4;
                      v22[547] = v27;
                    }
                    v28 = *v26;
                    for ( i = v69; v28 != 13; ++v26 )
                    {
                      *i = v28;
                      v28 = v26[1];
                      ++i;
                    }
                    *i = 0;
                    v30 = find_case_insensitive_substring(a3dmodel, v69);
                    v60 = v30;
                    if ( v30 )
                    {
                      v31 = find_case_insensitive_substring(asc_4A2094, v30) + 1;
                      v60 = v31;
                      v32 = v70;
                      for ( j = *v31; *v31 != 46; j = *v31 )
                      {
                        *v32++ = j;
                        v60 = ++v31;
                      }
                      v34 = v22[547];
                      *v32 = 46;
                      v35 = v32 + 1;
                      LOBYTE(v34) = v34 | 2;
                      v22[547] = v34;
                      v36 = (char *)MEMORY[0x4DF904];
                      *v35 = 120;
                      v35[1] = 0;
                      v22[552] = load_or_reuse_cached_x_mesh(v36 + 298496, v70);
                      v60 = find_case_insensitive_substring(asc_4AC438, v60);
                      *((float *)v22 + 553) = parse_next_float32(&v60);
                      *((float *)v22 + 554) = parse_next_float32(&v60);
                      *((float *)v22 + 555) = parse_next_float32(&v60);
                      v37 = find_case_insensitive_substring(aVelocity, v69);
                      v60 = v37;
                      if ( v37 )
                      {
                        v38 = find_case_insensitive_substring(asc_4A2094, v37);
                        v39 = v22[547] | 8;
                        v60 = v38 + 1;
                        v22[547] = v39;
                        v60 = find_case_insensitive_substring(asc_4AC438, v38 + 1);
                        *((float *)v22 + 556) = parse_next_float32(&v60);
                        *((float *)v22 + 557) = parse_next_float32(&v60);
                        *((float *)v22 + 558) = parse_next_float32(&v60);
                      }
                    }
                    v40 = find_case_insensitive_substring(aParcel, v69);
                    v60 = v40;
                    if ( v40 )
                    {
                      v22[547] |= 1u;
                      v60 = find_case_insensitive_substring(asc_4A2094, v40) + 1;
                      v41 = parse_next_signed_int(&v60);
                      v42 = v60;
                      v22[548] = v41;
                      v60 = find_case_insensitive_substring(asc_4AC438, v42) + 1;
                      *((float *)v22 + 549) = parse_next_float32(&v60);
                      *((float *)v22 + 550) = parse_next_float32(&v60);
                      *((float *)v22 + 551) = parse_next_float32(&v60);
                    }
                    v43 = find_case_insensitive_substring(aPath, v69);
                    v60 = v43;
                    if ( v43 )
                    {
                      v44 = find_case_insensitive_substring(asc_4A2094, v43) + 1;
                      v60 = v44;
                      v45 = ArgList;
                      for ( k = *v44; *v44 >= 32; k = *v44 )
                      {
                        *v45++ = k;
                        v60 = ++v44;
                      }
                      *v45 = 0;
                      segment_path_index_by_name = find_segment_path_index_by_name(ArgList);
                      v22[559] = segment_path_index_by_name;
                      if ( segment_path_index_by_name == -1 )
                      {
                        report_errorf("Unknown path %s in %s", ArgList, v62);
                      }
                      else
                      {
                        v48 = v22[547];
                        LOBYTE(v48) = v48 | 8;
                        v22[547] = v48;
                      }
                    }
                    v60 = find_case_insensitive_substring(aNofall, v69);
                    if ( v60 )
                    {
                      v49 = v22[547];
                      BYTE1(v49) |= 1u;
                      v22[547] = v49;
                    }
                    v60 = find_case_insensitive_substring(aRingNone, v69);
                    if ( v60 )
                    {
                      v50 = v22[547];
                      BYTE1(v50) |= 2u;
                      v22[547] = v50;
                    }
                    v60 = find_case_insensitive_substring(aRingNormal, v69);
                    if ( v60 )
                    {
                      v51 = v22[547];
                      BYTE1(v51) |= 4u;
                      v22[547] = v51;
                    }
                    v60 = find_case_insensitive_substring(aRingPowerup, v69);
                    if ( v60 )
                    {
                      v52 = v22[547];
                      BYTE1(v52) |= 0x20u;
                      v22[547] = v52;
                    }
                    v60 = find_case_insensitive_substring(aRingExplode, v69);
                    if ( v60 )
                    {
                      v53 = v22[547];
                      BYTE1(v53) |= 8u;
                      v22[547] = v53;
                    }
                    v60 = find_case_insensitive_substring(aRingSlow, v69);
                    if ( v60 )
                    {
                      v54 = v22[547];
                      BYTE1(v54) |= 0x10u;
                      v22[547] = v54;
                    }
                    v55 = find_case_insensitive_substring(aRingspeed, v69);
                    v60 = v55;
                    if ( v55 )
                    {
                      v60 = find_case_insensitive_substring(asc_4A2094, v55) + 1;
                      v56 = parse_next_float32(&v60);
                      *(float *)&v63[14 * v19 + 560] = v56;
                    }
                    else
                    {
                      v63[14 * v19 + 560] = 0;
                    }
                    v60 = find_case_insensitive_substring(aJetpackOff, v69);
                    if ( v60 )
                    {
                      v57 = v22[547];
                      BYTE1(v57) |= 0x80u;
                      v22[547] = v57;
                    }
                    v18 = (_BYTE *)advance_to_next_crlf_line(v26);
                    if ( !v18 )
                    {
                      v59 = &v73[128 * v64];
                      return report_errorf("Unexpected end of file in Segment %s\n", v59);
                    }
                    v3 = v64;
                    ++v67;
                  }
                  ++v3;
                  v66 += 295;
                  result = *v63;
                  v58 = v3 < *v63;
                  v64 = v3;
                  v65 += 2065;
                  v61 += 4130;
                  v62 += 128;
                  if ( v58 )
                  {
                    v4 = v62;
                    continue;
                  }
                }
                else
                {
                  return report_errorf("Data line must start with '@' in Segment %s\n", &v73[128 * v3]);
                }
              }
              else
              {
                v59 = &v73[128 * v3];
                return report_errorf("Unexpected end of file in Segment %s\n", v59);
              }
            }
            else
            {
              return report_errorf("Unexpected end of file in Segment %s\n", &v73[128 * v3]);
            }
          }
          else
          {
            return report_errorf("Cannot find Data: in Segment %s\n", &v73[128 * v3]);
          }
        }
        else
        {
          return report_errorf("Cannot find Name: in Segment %s\n", &v73[128 * v3]);
        }
      }
      else
      {
        return report_errorf("Cannot find ID: in Segment %s\n", &v73[128 * v3]);
      }
      break;
    }
  }
  return result;
}
