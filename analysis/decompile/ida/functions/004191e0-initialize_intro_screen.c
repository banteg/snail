/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_intro_screen @ 0x4191e0 */
/* selector: initialize_intro_screen */

// Windows cRLogo::Init(char*): loads SpaceRed plus INTROTEXT.OGG, parses the intro or credits script into LogoLetters on the tilted crawl plane, derives the shared scroll delta from Duration, and releases the script buffer.
int __thiscall sub_4191E0(_DWORD *this, char *FileName)
{
  int v2; // ebx
  int v4; // eax
  char *v5; // esi
  char *v6; // eax
  char *v7; // eax
  char *v8; // ecx
  char v9; // al
  float v10; // edi
  bool v11; // zf
  char *v12; // esi
  char *v13; // ecx
  char *v14; // eax
  char i; // dl
  _BYTE *v16; // eax
  int v17; // ecx
  int v18; // eax
  char *v19; // ecx
  int v20; // edx
  int v21; // edx
  float v22; // esi
  int v23; // eax
  _DWORD *v24; // ecx
  double v25; // st7
  int v26; // edx
  double v27; // st7
  double v28; // st7
  double v29; // st6
  int v30; // ecx
  _DWORD *v31; // eax
  double v32; // st7
  char v33; // al
  double v34; // st7
  int v35; // ecx
  int v36; // eax
  int v37; // ecx
  char *v38; // eax
  int v39; // edx
  int v40; // edx
  int v41; // eax
  int v42; // eax
  double v43; // st7
  float *v44; // eax
  int v45; // edx
  float v46; // ecx
  _DWORD *v47; // eax
  int v48; // eax
  double v49; // st7
  double v50; // st7
  int v51; // eax
  int v52; // ecx
  float *v53; // eax
  float *v54; // edx
  float v55; // edi
  char *v57; // [esp+10h] [ebp-178h] BYREF
  float v58; // [esp+14h] [ebp-174h]
  float v59; // [esp+18h] [ebp-170h]
  float v60; // [esp+1Ch] [ebp-16Ch]
  float v61; // [esp+20h] [ebp-168h]
  float v62; // [esp+24h] [ebp-164h]
  int v63; // [esp+28h] [ebp-160h]
  int v64; // [esp+2Ch] [ebp-15Ch]
  float v65; // [esp+30h] [ebp-158h]
  char *v66; // [esp+34h] [ebp-154h]
  int v67; // [esp+38h] [ebp-150h]
  int v68; // [esp+3Ch] [ebp-14Ch]
  int v69; // [esp+40h] [ebp-148h]
  char *v70; // [esp+44h] [ebp-144h]
  int v71[16]; // [esp+48h] [ebp-140h] BYREF
  char v72[128]; // [esp+88h] [ebp-100h] BYREF
  char Buffer[128]; // [esp+108h] [ebp-80h] BYREF

  v2 = 0;
  cache_music_file(aMusicIntrotext);
  v4 = load_landscape_script_by_name((char *)MEMORY[0x4DF904] + 17220120, aSpaceredTxt);
  change_backdrop((int)MEMORY[0x4DF904] + 322576, (int)MEMORY[0x4DF904] + 292 * v4 + 17221564, 0);
  set_border_justify_centre((_DWORD *)MEMORY[0x4DF904] + 723, 0);
  unhide_star_field((int *)MEMORY[0x4DF904] + 81103);
  v66 = load_file_bytes(FileName, nullptr);
  *(this + 3) = byte_4DF934;
  qmemcpy(
    (char *)MEMORY[0x4DF904] + 348,
    initialize_matrix_from_values(
      v71,
      1065353216,
      0,
      0,
      0,
      0,
      1059219348,
      1061544956,
      0,
      0,
      -1085938692,
      1059219348,
      0,
      0,
      0,
      0,
      1065353216),
    0x40u);
  *((_DWORD *)MEMORY[0x4DF904] + 161) = 1120403456;
  *this = 0;
  *(this + 1) = 987395086;
  release_mouse_cursor((_DWORD *)MEMORY[0x4DF904] + 164);
  v5 = v66;
  *(this + 2) = 0;
  v60 = 0.2;
  *(this + 5) = 0;
  v6 = find_case_insensitive_substring(aTextStart, v5);
  v57 = find_case_insensitive_substring(asc_4A1644, v6) + 1;
  v7 = find_case_insensitive_substring(aTextEnd, v5);
  v8 = v57;
  v70 = v7;
  if ( v57 < v7 )
  {
    LODWORD(v61) = this + 36879;
    do
    {
      v9 = *v8;
      v10 = 0.0;
      v11 = *v8 == 42;
      v62 = 0.0;
      v12 = v8;
      if ( v11 )
      {
        v13 = v8 + 1;
        v14 = v72;
        v57 = v13;
        for ( i = *v13; *v13 != 46; i = *v13 )
        {
          *v14++ = i;
          v57 = ++v13;
        }
        *v14 = 46;
        v16 = v14 + 1;
        *v16++ = 116;
        *v16++ = 103;
        *v16 = 97;
        v16[1] = 0;
        v57 = v13 + 1;
        v59 = parse_next_float32(&v57);
        v58 = parse_next_float32(&v57);
        sprintf(Buffer, "Intro/%s", v72);
        v17 = 144 * *(this + 5);
        v18 = (int)this + v17 + 24;
        if ( (*(_DWORD *)((char *)this + v17 + 28) & 0x200) != 0 )
        {
          report_errorf(aListAdd);
        }
        else
        {
          v19 = (char *)MEMORY[0x4DF904] + 1452;
          v20 = *((_DWORD *)MEMORY[0x4DF904] + 363);
          if ( v20 )
          {
            *(_DWORD *)(v20 + 8) = v18;
            *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v19 + 8) + 12) = *(_DWORD *)v19;
            v21 = *(_DWORD *)(*(_DWORD *)v19 + 8);
            *(_DWORD *)v19 = v21;
            *(_DWORD *)(v21 + 8) = 0;
          }
          else
          {
            *(_DWORD *)v19 = v18;
            *(_DWORD *)(v18 + 8) = 0;
            *(_DWORD *)(*(_DWORD *)v19 + 12) = 0;
          }
          *(_DWORD *)(v18 + 4) |= 0x200u;
        }
        v22 = v61;
        set_bod_object(this + 36 * *(this + 5) + 6, *(_DWORD *)LODWORD(v61));
        *(_DWORD *)(*(_DWORD *)(*(this + 36 * *(this + 5) + 15) + 92) + 12) = get_or_create_texture_ref(
                                                                                &texture_list,
                                                                                Buffer,
                                                                                0,
                                                                                0);
        set_matrix_identity(this + 36 * *(this + 5) + 20);
        v23 = *(this + 5);
        v67 = 0;
        v68 = -1065353216;
        v69 = 0;
        v24 = this + 36 * v23 + 32;
        v25 = v58 * 0.5;
        *v24 = 0;
        v26 = v69;
        v24[1] = -1065353216;
        v61 = v25;
        v27 = v60;
        v24[2] = v26;
        *((float *)this + 36 * *(this + 5) + 34) = v27 - v61 + *((float *)this + 36 * *(this + 5) + 34);
        set_color_white(this + 36 * *(this + 5) + 16);
        v28 = v59 * 0.5;
        *(this + 36 * *(this + 5) + 19) = 1065336439;
        *((_BYTE *)this + 144 * *(this + 5) + 164) = -1;
        **(float **)(*(this + 36 * *(this + 5) + 15) + 56) = v28;
        v29 = v59 * -0.5;
        *(float *)(*(_DWORD *)(*(this + 36 * *(this + 5) + 15) + 56) + 8) = v61;
        *(float *)(*(_DWORD *)(*(this + 36 * *(this + 5) + 15) + 56) + 12) = v29;
        *(float *)(*(_DWORD *)(*(this + 36 * *(this + 5) + 15) + 56) + 20) = v61;
        *(float *)(*(_DWORD *)(*(this + 36 * *(this + 5) + 15) + 56) + 24) = v29;
        v30 = *(this + 36 * *(this + 5) + 15);
        v59 = v58 * -0.5;
        *(float *)(*(_DWORD *)(v30 + 56) + 32) = v59;
        *(float *)(*(_DWORD *)(*(this + 36 * *(this + 5) + 15) + 56) + 36) = v28;
        *(float *)(*(_DWORD *)(*(this + 36 * *(this + 5) + 15) + 56) + 44) = v59;
        v31 = this + 36 * *(this + 5) + 38;
        v31[2] = 0;
        v31[1] = 0;
        *v31 = 0;
        (*(void (__thiscall **)(_DWORD *))*(this + 36 * *(this + 5) + 6))(this + 36 * *(this + 5) + 6);
        v8 = v57;
        v32 = v60 - v58;
        LODWORD(v61) = LODWORD(v22) + 144;
        ++*(this + 5);
        v33 = *v8;
        v60 = v32;
        if ( v33 )
        {
          do
          {
            if ( v33 == 13 )
              break;
            v57 = ++v8;
            v33 = *v8;
          }
          while ( *v8 );
        }
      }
      else if ( v9 )
      {
        do
        {
          if ( v9 == 13 )
            break;
          v34 = v62 + unk_7770E8[font_slot_index_for_char(v9)];
          ++LODWORD(v10);
          v8 = v57 + 1;
          v57 = v8;
          v9 = *v8;
          v62 = v34;
        }
        while ( v9 );
        if ( SLODWORD(v10) > 0 )
        {
          v63 = 0;
          v64 = -1065353216;
          v65 = 0.0;
          v59 = v10;
          v58 = v62 * 0.5 * 0.80000001;
          do
          {
            v35 = 144 * *(this + 5);
            v36 = *(_DWORD *)((char *)this + v35 + 28);
            v37 = (int)this + v35 + 24;
            if ( (v36 & 0x200) != 0 )
            {
              report_errorf(aListAdd);
            }
            else
            {
              v38 = (char *)MEMORY[0x4DF904] + 1452;
              v39 = *((_DWORD *)MEMORY[0x4DF904] + 363);
              if ( v39 )
              {
                *(_DWORD *)(v39 + 8) = v37;
                *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v38 + 8) + 12) = *(_DWORD *)v38;
                v40 = *(_DWORD *)(*(_DWORD *)v38 + 8);
                *(_DWORD *)v38 = v40;
                *(_DWORD *)(v40 + 8) = 0;
              }
              else
              {
                *(_DWORD *)v38 = v37;
                *(_DWORD *)(v37 + 8) = 0;
                *(_DWORD *)(*(_DWORD *)v38 + 12) = 0;
              }
              v41 = *(_DWORD *)(v37 + 4);
              BYTE1(v41) |= 2u;
              *(_DWORD *)(v37 + 4) = v41;
            }
            v42 = font_slot_index_for_char(*v12);
            set_bod_object(this + 36 * *(this + 5) + 6, unk_77550C[14 * v42]);
            set_matrix_identity(this + 36 * *(this + 5) + 20);
            v43 = v58;
            v44 = (float *)(this + 36 * *(this + 5) + 32);
            v45 = v64;
            *(_DWORD *)v44 = v63;
            v46 = v65;
            *((_DWORD *)v44 + 1) = v45;
            v44[2] = v46;
            *((float *)this + 36 * *(this + 5) + 32) = v43 + *((float *)this + 36 * *(this + 5) + 32);
            *((float *)this + 36 * *(this + 5) + 34) = v60 + *((float *)this + 36 * *(this + 5) + 34);
            set_color_white(this + 36 * *(this + 5) + 16);
            *(this + 36 * *(this + 5) + 19) = 1065336439;
            v47 = this + 36 * *(this + 5) + 38;
            v47[2] = 0;
            v47[1] = 0;
            *v47 = 0;
            *((_BYTE *)this + 144 * *(this + 5) + 164) = *v12;
            (*(void (__thiscall **)(_DWORD *))*(this + 36 * *(this + 5) + 6))(this + 36 * *(this + 5) + 6);
            v48 = font_slot_index_for_char(*v12++);
            v49 = v58 - unk_7770E8[v48] * 0.80000001;
            ++*(this + 5);
            v58 = v49;
            --LODWORD(v59);
          }
          while ( v59 != 0.0 );
          v8 = v57;
        }
      }
      if ( *v8 == 13 )
      {
        v8 += 2;
        v57 = v8;
        v60 = v60 - 1.0;
      }
    }
    while ( v8 < v70 );
    v5 = v66;
  }
  v57 = find_case_insensitive_substring(aDuration, v5);
  v57 = find_case_insensitive_substring(asc_4A1644, v57);
  v50 = parse_next_float32(&v57);
  *((float *)this + 4) = v50;
  v51 = *(this + 5);
  v63 = 0;
  v64 = 0;
  v65 = 1.0 / (v50 * 60.0) * (3.0 - v60);
  if ( v51 > 0 )
  {
    v52 = v64;
    v53 = (float *)(this + 38);
    do
    {
      v54 = v53;
      ++v2;
      v53 += 36;
      *(_DWORD *)v54 = v63;
      v55 = v65;
      *((_DWORD *)v54 + 1) = v52;
      v54[2] = v55;
    }
    while ( v2 < *(this + 5) );
  }
  return free_tracked_memory((int)v5);
}
