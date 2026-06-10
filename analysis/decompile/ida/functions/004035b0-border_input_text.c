/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: border_input_text @ 0x4035b0 */
/* selector: border_input_text */

void __thiscall border_input_text(int this)
{
  char repeating_text_input_key_code; // bl
  int v3; // eax
  int v4; // eax
  char v5; // bl
  char v6; // cl
  char *v7; // eax
  char v8; // dl
  int v9; // eax
  char v10; // dl
  int v11; // eax
  char v12; // dl
  int v13; // eax
  int i; // edi
  int j; // ecx
  _BYTE *v16; // ecx
  int v18; // eax
  char v19; // cl
  _BYTE *v20; // eax
  char v21; // dl
  int v22; // eax
  int k; // ebp
  int v24; // edx
  char v25; // al
  int v26; // edx
  int v27; // eax
  char m; // cl
  _BYTE *v29; // ecx
  int v31; // eax
  char v32; // cl
  _BYTE *v33; // eax
  char v34; // dl
  int v35; // ecx
  char v36; // al
  _BYTE *v37; // eax
  int v39; // eax
  char v40; // cl
  _BYTE *v41; // eax
  char v42; // dl
  int n; // eax
  int v44; // ecx
  char v45; // dl
  _BYTE *v46; // ecx
  char v48; // cl
  _BYTE *v49; // eax
  char v50; // dl
  int v51; // eax
  int v52; // eax
  char v53; // cl
  _BYTE *v54; // eax
  int v56; // eax
  int v57; // eax
  char v58; // cl
  _BYTE *v59; // eax
  int v61; // eax
  char v62; // bl
  char v63; // cl
  int v64; // ecx
  char v65; // dl
  _BYTE *v66; // eax
  int v68; // eax
  char v69; // al
  double v70; // st7
  int v71; // ecx
  int v72; // eax
  char v73; // cl
  _BYTE *v74; // eax
  int v76; // edx
  int v77; // eax
  int v78; // edi

  repeating_text_input_key_code = read_repeating_text_input_key_code();
  if ( (*(_DWORD *)(this + 1804) & 0xC) == 0
    || (update_input_ok((float **)(this + 680)), (*(_BYTE *)(*(_DWORD *)(this + 712) + 416) & 0x20) == 0) )
  {
    if ( repeating_text_input_key_code != 5 && (*(_DWORD *)(this + 416) & 0x8000000) == 0 )
    {
      switch ( repeating_text_input_key_code )
      {
        case 6:
          v3 = *(_DWORD *)(this + 1804);
          if ( (v3 & 1) == 0 )
          {
            if ( (v3 & 2) != 0 )
              goto LABEL_99;
            *(_BYTE *)(*(_DWORD *)(this + 1788) + this + 716) = 62;
            v4 = *(_DWORD *)(this + 1788) + 1;
            *(_DWORD *)(this + 1788) = v4;
            v5 = 32;
            v6 = *(_BYTE *)(v4 + this + 716);
            v7 = (char *)(v4 + this + 716);
            v8 = 32;
            if ( v6 )
            {
              do
              {
                *v7++ = v5;
                v8 = v6;
                v6 = *v7;
                v5 = v8;
              }
              while ( *v7 );
            }
            goto LABEL_97;
          }
          break;
        case 3:
          v9 = *(_DWORD *)(this + 1788);
          if ( v9 > 0 )
          {
            v10 = *(_BYTE *)(v9 + this + 716);
            *(_BYTE *)(v9 + this + 716) = *(_BYTE *)(v9 + this + 715);
            *(_BYTE *)(v9 + this + 715) = v10;
            --*(_DWORD *)(this + 1788);
          }
          goto LABEL_99;
        case 4:
          v11 = *(_DWORD *)(this + 1788);
          if ( v11 < *(_DWORD *)(this + 1808) )
          {
            v12 = *(_BYTE *)(v11 + this + 716);
            *(_BYTE *)(v11 + this + 716) = *(_BYTE *)(v11 + this + 717);
            *(_BYTE *)(v11 + this + 717) = v12;
            ++*(_DWORD *)(this + 1788);
          }
          goto LABEL_99;
        case 7:
          v13 = *(_DWORD *)(this + 1788);
          for ( i = -1; v13 > 0; --v13 )
          {
            if ( *(_BYTE *)(this + v13 + 716) == 62 )
              break;
            ++i;
          }
          if ( *(_BYTE *)(v13 + this + 716) == 62 )
            --v13;
          if ( v13 )
          {
            for ( j = 0; v13 > 0; --v13 )
            {
              if ( *(_BYTE *)(this + v13 + 716) == 62 )
                break;
              ++j;
            }
            if ( *(_BYTE *)(v13 + this + 716) == 62 )
              ++v13;
            if ( i > j )
              i = j;
            v16 = (_BYTE *)(*(_DWORD *)(this + 1788) + this + 716);
            if ( *v16 )
            {
              do
                *v16 = v16[1];
              while ( *++v16 );
            }
            v18 = i + v13;
            *(_DWORD *)(this + 1788) = v18;
            v19 = *(_BYTE *)(v18 + this + 716);
            v20 = (_BYTE *)(v18 + this + 716);
            do
            {
              v21 = v20[1];
              *++v20 = v19;
              v19 = v21;
            }
            while ( *v20 );
          }
          goto LABEL_99;
        case 8:
          v22 = *(_DWORD *)(this + 1788);
          for ( k = 0; v22 > 0; --v22 )
          {
            if ( *(_BYTE *)(this + v22 + 716) == 62 )
              break;
            ++k;
          }
          if ( *(_BYTE *)(v22 + this + 716) == 62 )
          {
            ++v22;
            --k;
          }
          v24 = v22;
          if ( *(_BYTE *)(v22 + this + 716) )
          {
            v25 = *(_BYTE *)(this + v22 + 716);
            do
            {
              if ( v25 == 62 )
                break;
              v25 = *(_BYTE *)(this + v24++ + 717);
            }
            while ( v25 );
          }
          if ( *(_BYTE *)(v24 + this + 716) == 62 )
          {
            v26 = v24 + 1;
            v27 = 0;
            for ( m = *(_BYTE *)(v26 + this + 716); m; m = *(_BYTE *)(v26 + this + 716 + v27++ + 1) )
            {
              if ( m == 62 )
                break;
            }
            if ( k > v27 )
              k = v27;
            v29 = (_BYTE *)(*(_DWORD *)(this + 1788) + this + 716);
            if ( *v29 )
            {
              do
                *v29 = v29[1];
              while ( *++v29 );
            }
            v31 = v26 + k - 1;
            *(_DWORD *)(this + 1788) = v31;
            v32 = *(_BYTE *)(v31 + this + 716);
            v33 = (_BYTE *)(v31 + this + 716);
            do
            {
              v34 = v33[1];
              *++v33 = v32;
              v32 = v34;
            }
            while ( *v33 );
          }
          goto LABEL_99;
        case 9:
          v35 = *(_DWORD *)(this + 1788);
          if ( *(_BYTE *)(v35 + this + 716) )
          {
            v36 = *(_BYTE *)(this + v35 + 716);
            do
            {
              if ( v36 == 62 )
                break;
              v36 = *(_BYTE *)(this + v35++ + 717);
            }
            while ( v36 );
          }
          v37 = (_BYTE *)(*(_DWORD *)(this + 1788) + this + 716);
          if ( *v37 )
          {
            do
              *v37 = v37[1];
            while ( *++v37 );
          }
          v39 = v35 - 1;
          *(_DWORD *)(this + 1788) = v35 - 1;
          v40 = *(_BYTE *)(v35 - 1 + this + 716);
          v41 = (_BYTE *)(v39 + this + 716);
          do
          {
            v42 = v41[1];
            *++v41 = v40;
            v40 = v42;
          }
          while ( *v41 );
          goto LABEL_99;
        case 10:
          for ( n = *(_DWORD *)(this + 1788); n > 0; --n )
          {
            if ( *(_BYTE *)(this + n + 716) == 62 )
              break;
          }
          if ( *(_BYTE *)(n + this + 716) == 62 )
            ++n;
          v44 = *(_DWORD *)(this + 1788);
          v45 = *(_BYTE *)(v44 + this + 716);
          v46 = (_BYTE *)(v44 + this + 716);
          if ( v45 )
          {
            do
              *v46 = v46[1];
            while ( *++v46 );
          }
          *(_DWORD *)(this + 1788) = n;
          v48 = *(_BYTE *)(n + this + 716);
          v49 = (_BYTE *)(n + this + 716);
          do
          {
            v50 = v49[1];
            *++v49 = v48;
            v48 = v50;
          }
          while ( *v49 );
          goto LABEL_99;
        case 1:
          v51 = *(_DWORD *)(this + 1788);
          if ( v51 <= 0 )
            goto LABEL_99;
          v52 = v51 - 1;
          *(_DWORD *)(this + 1788) = v52;
          v53 = *(_BYTE *)(v52 + this + 716);
          v54 = (_BYTE *)(v52 + this + 716);
          if ( v53 )
          {
            do
              *v54 = v54[1];
            while ( *++v54 );
          }
          v56 = *(_DWORD *)(this + 1808) - 1;
          goto LABEL_98;
        case 2:
          v57 = *(_DWORD *)(this + 1788);
          if ( v57 >= *(_DWORD *)(this + 1808) )
            goto LABEL_99;
          v58 = *(_BYTE *)(v57 + this + 716);
          v59 = (_BYTE *)(v57 + this + 716);
          if ( v58 )
          {
            do
              *v59 = v59[1];
            while ( *++v59 );
          }
          v56 = *(_DWORD *)(this + 1808) - 1;
          goto LABEL_98;
        case 0:
          goto LABEL_99;
      }
      if ( *(_DWORD *)(this + 1808) >= *(_DWORD *)(this + 1812)
        || repeating_text_input_key_code == 32 && (*(_BYTE *)(this + 1804) & 1) != 0
        || (*(_BYTE *)(this + 1804) & 2) != 0
        && (repeating_text_input_key_code == 44 || repeating_text_input_key_code == 46) )
      {
        goto LABEL_99;
      }
      *(_BYTE *)(*(_DWORD *)(this + 1788) + this + 716) = repeating_text_input_key_code;
      v61 = *(_DWORD *)(this + 1788) + 1;
      *(_DWORD *)(this + 1788) = v61;
      v62 = 32;
      v63 = *(_BYTE *)(v61 + this + 716);
      v7 = (char *)(v61 + this + 716);
      v8 = 32;
      if ( v63 )
      {
        do
        {
          *v7++ = v62;
          v8 = v63;
          v63 = *v7;
          v62 = v8;
        }
        while ( *v7 );
      }
LABEL_97:
      *v7 = v8;
      v7[1] = 0;
      v56 = *(_DWORD *)(this + 1808) + 1;
LABEL_98:
      *(_DWORD *)(this + 1808) = v56;
LABEL_99:
      if ( (*(_BYTE *)(this + 1804) & 2) != 0 )
      {
        v64 = 0;
        if ( *(_BYTE *)(this + 716) )
        {
          do
          {
            v65 = *(_BYTE *)(v64 + this + 716);
            v66 = (_BYTE *)(v64 + this + 716);
            if ( v65 != 32 && v64 != *(_DWORD *)(this + 1788) )
              break;
            if ( v64 != *(_DWORD *)(this + 1788) )
            {
              if ( v65 )
              {
                do
                  *v66 = v66[1];
                while ( *++v66 );
              }
              v68 = *(_DWORD *)(this + 1788);
              if ( v64 <= v68 )
                *(_DWORD *)(this + 1788) = v68 - 1;
              --*(_DWORD *)(this + 1808);
            }
            v69 = *(_BYTE *)(v64 + this + 717);
            ++v64;
          }
          while ( v69 );
        }
      }
      v70 = *(float *)(this + 1800) + *(float *)(this + 1796);
      *(float *)(this + 1796) = v70;
      if ( v70 > 1.0 )
      {
        v71 = *(_DWORD *)(this + 1792);
        *(_DWORD *)(this + 1796) = 0;
        *(_DWORD *)(this + 1792) = v71 == 0;
      }
      if ( *(_DWORD *)(this + 1792) == 1 )
        *(_BYTE *)(*(_DWORD *)(this + 1788) + this + 716) = 124;
      else
        *(_BYTE *)(*(_DWORD *)(this + 1788) + this + 716) = 32;
      layout_frontend_widget((FrontendWidget *)this);
      return;
    }
  }
  v72 = *(_DWORD *)(this + 1788);
  v73 = *(_BYTE *)(v72 + this + 716);
  v74 = (_BYTE *)(v72 + this + 716);
  if ( v73 )
  {
    do
      *v74 = v74[1];
    while ( *++v74 );
  }
  v76 = *(_DWORD *)(this + 416);
  BYTE1(v76) &= ~0x20u;
  v77 = v76;
  v78 = *(_DWORD *)(this + 1808) - 1;
  BYTE1(v77) = BYTE1(v76) | 0x40;
  *(_DWORD *)(this + 416) = v76;
  *(_DWORD *)(this + 1808) = v78;
  *(_DWORD *)(this + 416) = v77;
  layout_frontend_widget((FrontendWidget *)this);
  if ( (*(_BYTE *)(this + 1804) & 0xC) != 0 )
    kill_border(*(_DWORD **)(this + 712));
}

