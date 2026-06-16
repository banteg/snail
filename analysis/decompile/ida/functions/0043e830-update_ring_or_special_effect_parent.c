/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_ring_or_special_effect_parent @ 0x43e830 */
/* selector: update_ring_or_special_effect_parent */

void __thiscall sub_43E830(int this)
{
  int v2; // eax
  int v3; // ecx
  double v4; // st7
  unsigned __int8 v6; // c0
  unsigned __int8 v7; // c3
  int v8; // ebp
  int v9; // edi
  int v10; // ecx
  int v11; // eax
  char *v12; // ecx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int *v16; // esi
  int v17; // edi
  int v18; // ebp
  int v19; // edi
  double v20; // st7
  int v21; // eax
  char *v22; // ecx
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int *v26; // esi
  int v27; // edi
  int v28; // edx
  float *v29; // eax
  float *v30; // ecx
  double v31; // st7
  float *v32; // esi
  int v33; // ebp
  int v34; // edi
  double v35; // st7
  int v36; // eax
  char *v37; // ecx
  int v38; // eax
  int v39; // eax
  int v40; // eax
  int *v41; // esi
  int v42; // edi
  float *v43; // edx
  float *v44; // eax
  int v45; // ecx
  double v46; // st7
  float *v47; // esi
  float v48; // [esp+14h] [ebp-14h]
  float v49; // [esp+18h] [ebp-10h]
  float v50; // [esp+18h] [ebp-10h]
  float v51; // [esp+20h] [ebp-8h]
  float v52; // [esp+24h] [ebp-4h]

  v2 = *(_DWORD *)(this + 464);
  if ( !*(_BYTE *)(v2 + 9) )
  {
    v3 = *(_DWORD *)(this + 488) + 1;
    *(_DWORD *)(this + 488) = v3;
    if ( v3 == 3 )
      *(_DWORD *)(this + 488) = 0;
    switch ( *(_DWORD *)(this + 128) )
    {
      case 1:
        if ( *(_BYTE *)(this + 476) )
        {
          v4 = *(float *)(this + 484) + *(float *)(this + 480);
          *(float *)(this + 480) = v4;
          if ( v6 | v7 )
          {
            if ( v4 < 0.0 )
              *(float *)(this + 480) = v4 + 6.2831855;
          }
          else
          {
            *(float *)(this + 480) = v4 - 6.2831855;
          }
          *(float *)(this + 104) = sine(*(float *)(this + 480)) * 3.0;
        }
        v8 = 10;
        v9 = this + 144;
        do
        {
          update_ring_or_special_effect_particle(v9);
          v9 += 32;
          --v8;
        }
        while ( v8 );
        v10 = *(_DWORD *)(this + 132);
        if ( *(float *)(this + 112) >= (double)*(float *)(v10 + 10624) )
        {
          if ( *(_DWORD *)(v10 + 1028) < *(_DWORD *)(this + 140) )
            *(_DWORD *)(this + 128) = 4;
        }
        else
        {
          v11 = *(_DWORD *)(this + 4);
          *(_DWORD *)(this + 128) = 0;
          v12 = (char *)MEMORY[0x4DF904] + 1448;
          if ( (v11 & 0x200) != 0 )
          {
            if ( (v11 & 0x40) != 0 )
            {
              report_errorf(aListRemoveNext);
            }
            else
            {
              v13 = *(_DWORD *)(this + 12);
              if ( v13 )
                *(_DWORD *)(v13 + 8) = *(_DWORD *)(this + 8);
              v14 = *(_DWORD *)(this + 8);
              if ( v14 )
                *(_DWORD *)(v14 + 12) = *(_DWORD *)(this + 12);
              else
                *((_DWORD *)v12 + 1) = *(_DWORD *)(this + 12);
              *(_DWORD *)(this + 12) = *((_DWORD *)v12 + 2);
              *((_DWORD *)v12 + 2) = this;
              v15 = *(_DWORD *)(this + 4);
              BYTE1(v15) &= ~2u;
              *(_DWORD *)(this + 4) = v15;
            }
          }
          else
          {
            report_errorf(aListRemove);
          }
          v16 = (int *)(this + 144);
          v17 = 10;
          do
          {
            kill_sprite(*v16);
            v16 += 8;
            --v17;
          }
          while ( v17 );
        }
        return;
      case 2:
        *(_DWORD *)(this + 128) = 3;
        *(_DWORD *)(this + 468) = 0;
        *(float *)(this + 472) = *(float *)(v2 + 56) * 0.069444448;
        goto LABEL_30;
      case 3:
LABEL_30:
        v18 = 10;
        v19 = this + 144;
        do
        {
          update_ring_or_special_effect_particle(v19);
          v19 += 32;
          --v18;
        }
        while ( v18 );
        v20 = *(float *)(this + 472) + *(float *)(this + 468);
        *(float *)(this + 468) = v20;
        if ( v20 <= 1.0 )
        {
          v28 = 10;
          v29 = (float *)(this + 104);
          v30 = (float *)(this + 172);
          v49 = *(float *)(*(_DWORD *)(this + 132) + 10604) + 0.2;
          v51 = *(float *)(*(_DWORD *)(this + 132) + 10600) - *(float *)(this + 108);
          v52 = v49 - *(float *)(this + 112);
          v48 = v51 * 0.94;
          v50 = v52 * 0.94;
          *(float *)(this + 104) = (*(float *)(*(_DWORD *)(this + 132) + 10596) - *(float *)(this + 104)) * 0.94
                                 + *(float *)(this + 104);
          *(float *)(this + 108) = v48 + *(float *)(this + 108);
          *(float *)(this + 112) = v50 + *(float *)(this + 112);
          do
          {
            v31 = *v30 * 0.94;
            v32 = v30 - 5;
            v30 += 8;
            --v28;
            *(v30 - 8) = v31;
            *v32 = *v29;
            v32[1] = v29[1];
            v32[2] = v29[2];
          }
          while ( v28 );
        }
        else
        {
          v21 = *(_DWORD *)(this + 4);
          *(_DWORD *)(this + 128) = 0;
          v22 = (char *)MEMORY[0x4DF904] + 1448;
          if ( (v21 & 0x200) != 0 )
          {
            if ( (v21 & 0x40) != 0 )
            {
              report_errorf(aListRemoveNext);
            }
            else
            {
              v23 = *(_DWORD *)(this + 12);
              if ( v23 )
                *(_DWORD *)(v23 + 8) = *(_DWORD *)(this + 8);
              v24 = *(_DWORD *)(this + 8);
              if ( v24 )
                *(_DWORD *)(v24 + 12) = *(_DWORD *)(this + 12);
              else
                *((_DWORD *)v22 + 1) = *(_DWORD *)(this + 12);
              *(_DWORD *)(this + 12) = *((_DWORD *)v22 + 2);
              *((_DWORD *)v22 + 2) = this;
              v25 = *(_DWORD *)(this + 4);
              BYTE1(v25) &= ~2u;
              *(_DWORD *)(this + 4) = v25;
            }
          }
          else
          {
            report_errorf(aListRemove);
          }
          v26 = (int *)(this + 144);
          v27 = 10;
          do
          {
            kill_sprite(*v26);
            v26 += 8;
            --v27;
          }
          while ( v27 );
        }
        return;
      case 4:
        *(_DWORD *)(this + 128) = 5;
        *(_DWORD *)(this + 468) = 0;
        *(float *)(this + 472) = *(float *)(v2 + 56) * 0.069444448;
        goto LABEL_50;
      case 5:
LABEL_50:
        v33 = 10;
        v34 = this + 144;
        do
        {
          update_ring_or_special_effect_particle(v34);
          v34 += 32;
          --v33;
        }
        while ( v33 );
        v35 = *(float *)(this + 472) + *(float *)(this + 468);
        *(float *)(this + 468) = v35;
        if ( v35 <= 1.0 )
        {
          v43 = (float *)(this + 104);
          v44 = (float *)(this + 172);
          v45 = 10;
          do
          {
            v46 = *v44 * 1.1;
            v47 = v44 - 5;
            v44 += 8;
            --v45;
            *(v44 - 8) = v46;
            *v47 = *v43;
            v47[1] = v43[1];
            v47[2] = v43[2];
          }
          while ( v45 );
        }
        else
        {
          v36 = *(_DWORD *)(this + 4);
          *(_DWORD *)(this + 128) = 0;
          v37 = (char *)MEMORY[0x4DF904] + 1448;
          if ( (v36 & 0x200) != 0 )
          {
            if ( (v36 & 0x40) != 0 )
            {
              report_errorf(aListRemoveNext);
            }
            else
            {
              v38 = *(_DWORD *)(this + 12);
              if ( v38 )
                *(_DWORD *)(v38 + 8) = *(_DWORD *)(this + 8);
              v39 = *(_DWORD *)(this + 8);
              if ( v39 )
                *(_DWORD *)(v39 + 12) = *(_DWORD *)(this + 12);
              else
                *((_DWORD *)v37 + 1) = *(_DWORD *)(this + 12);
              *(_DWORD *)(this + 12) = *((_DWORD *)v37 + 2);
              *((_DWORD *)v37 + 2) = this;
              v40 = *(_DWORD *)(this + 4);
              BYTE1(v40) &= ~2u;
              *(_DWORD *)(this + 4) = v40;
            }
          }
          else
          {
            report_errorf(aListRemove);
          }
          v41 = (int *)(this + 144);
          v42 = 10;
          do
          {
            kill_sprite(*v41);
            v41 += 8;
            --v42;
          }
          while ( v42 );
        }
        break;
      default:
        return;
    }
  }
}
