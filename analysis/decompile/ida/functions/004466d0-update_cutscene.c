/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_cutscene @ 0x4466d0 */
/* selector: update_cutscene */

// Advances the player-side cutscene controller, consuming the live snail hotspot bank as the intro/completion/death camera anchor source, including the authored `CameraSkidStop -> CameraIntroTalk` blend path, and handling the handoff into `initialize_completion_screen`. Cross-port Android and iOS symbols match this helper to `cRCutScene::AI()`.
void __thiscall sub_4466D0(int this)
{
  int v2; // eax
  int v3; // ecx
  _DWORD *v4; // ecx
  double v5; // st7
  double v6; // st7
  int *v7; // eax
  double v8; // st7
  double v9; // st7
  long double v10; // st7
  long double v11; // st7
  long double v12; // st7
  double v13; // st7
  int v14; // ecx
  double v15; // st7
  int *v16; // edx
  double v17; // st7
  double v18; // st7
  double v19; // st7
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // eax
  int v24; // eax
  int *v25; // ecx
  float *v26; // eax
  float v27; // edx
  float v28; // eax
  double v29; // st7
  double v30; // st7
  double v31; // st7
  _DWORD *v32; // edx
  float *v33; // [esp+0h] [ebp-FCh]
  float v34; // [esp+0h] [ebp-FCh]
  float *v35; // [esp+0h] [ebp-FCh]
  float v36; // [esp+0h] [ebp-FCh]
  float v37; // [esp+0h] [ebp-FCh]
  float v38; // [esp+0h] [ebp-FCh]
  float v39; // [esp+0h] [ebp-FCh]
  float v40; // [esp+0h] [ebp-FCh]
  float v41; // [esp+0h] [ebp-FCh]
  float *v42; // [esp+0h] [ebp-FCh]
  float v43; // [esp+0h] [ebp-FCh]
  float v44; // [esp+0h] [ebp-FCh]
  float *v45; // [esp+0h] [ebp-FCh]
  float v46; // [esp+14h] [ebp-E8h]
  float v47; // [esp+14h] [ebp-E8h]
  int v48; // [esp+14h] [ebp-E8h]
  float v49; // [esp+18h] [ebp-E4h]
  float v50; // [esp+18h] [ebp-E4h]
  float v51; // [esp+18h] [ebp-E4h]
  int v52; // [esp+18h] [ebp-E4h]
  float v53; // [esp+1Ch] [ebp-E0h]
  float v54; // [esp+1Ch] [ebp-E0h]
  int v55; // [esp+1Ch] [ebp-E0h]
  float v56; // [esp+24h] [ebp-D8h] BYREF
  float v57; // [esp+28h] [ebp-D4h]
  float v58; // [esp+2Ch] [ebp-D0h]
  float v59; // [esp+34h] [ebp-C8h]
  float v60; // [esp+38h] [ebp-C4h]
  int v61[16]; // [esp+3Ch] [ebp-C0h] BYREF
  int v62[28]; // [esp+7Ch] [ebp-80h] BYREF
  float v63; // [esp+ECh] [ebp-10h]
  float v64; // [esp+F0h] [ebp-Ch]
  float v65; // [esp+F4h] [ebp-8h]

  v2 = *(_DWORD *)(this + 12);
  *(_BYTE *)(this + 88) = 0;
  switch ( v2 )
  {
    case 1:
      v3 = *(_DWORD *)this;
      *(_DWORD *)(this + 12) = 2;
      *(_DWORD *)(this + 80) = 0;
      *(_DWORD *)(this + 84) = 1007192201;
      *(_BYTE *)(this + 88) = 1;
      dispatch_cutscene_animation(v3, 9, 1, -1);
      dispatch_cutscene_animation(*(_DWORD *)this, 9, 0, -1);
      dispatch_cutscene_animation(*(_DWORD *)this, 1, 0, -1);
      goto LABEL_3;
    case 2:
LABEL_3:
      *(_DWORD *)(this + 8) = 1;
      set_matrix_identity((_DWORD *)(this + 16));
      v4 = (_DWORD *)(*(_DWORD *)this + 6280);
      v33 = (float *)(*(_DWORD *)this + 104);
      *(_DWORD *)(this + 64) = *v4;
      *(_DWORD *)(this + 68) = v4[1];
      *(_DWORD *)(this + 72) = v4[2];
      look_at_point((float *)(this + 16), v33);
      v5 = *(float *)(this + 80) + *(float *)(this + 84);
      *(float *)(this + 80) = v5;
      if ( v5 > 1.0 )
      {
        *(_DWORD *)(this + 84) = 1007192201;
        *(_DWORD *)(this + 12) = 8;
        *(_DWORD *)(this + 80) = 0;
      }
      return;
    case 5:
      v22 = *(_DWORD *)this;
      *(_DWORD *)(this + 12) = 7;
      *(_DWORD *)(this + 8) = -1;
      dispatch_cutscene_animation(v22, 8, 1, -1);
      dispatch_cutscene_animation(*(_DWORD *)this, 9, 0, -1);
      dispatch_cutscene_animation(*(_DWORD *)this, 9, 0, -1);
      v23 = *(_DWORD *)this;
      *(_DWORD *)(this + 12) = 6;
      *(_DWORD *)(this + 80) = 0;
      *(_DWORD *)(this + 84) = 1007192201;
      *(_DWORD *)(v23 + 6448) = 1015580809;
      *(_DWORD *)(*(_DWORD *)this + 6444) = *(_DWORD *)(*(_DWORD *)this + 6448);
      *(_BYTE *)(this + 88) = 1;
      v24 = *((_DWORD *)MEMORY[0x4DF904] + 119190);
      if ( v24 )
      {
        if ( v24 == 1 )
          initialize_completion_screen((int)MEMORY[0x4DF904] + 19820016, *(_DWORD *)(*(_DWORD *)(this + 4) + 17208), 1u);
      }
      else
      {
        initialize_completion_screen(
          (int)MEMORY[0x4DF904] + 19820016,
          *(_DWORD *)(*(_DWORD *)(this + 4) + 17208),
          *(_DWORD *)(*(_DWORD *)(this + 4) + 17208) == *((_DWORD *)MEMORY[0x4DF904] + 561662));
      }
      play_sound_effect(46);
      goto LABEL_25;
    case 6:
LABEL_25:
      *(_DWORD *)(this + 8) = -1;
      set_matrix_identity(v62);
      v25 = (int *)(*(_DWORD *)this + 6208);
      v26 = (float *)(*(_DWORD *)this + 6280);
      v61[12] = *v25;
      v61[13] = v25[1];
      v61[14] = v25[2];
      v63 = *v26;
      v27 = v26[2];
      v64 = v26[1];
      v28 = *(float *)(this + 80);
      v65 = v27;
      v51 = v64 - *(float *)&v61[13];
      v54 = v27 - *(float *)&v61[14];
      v59 = v51 * v28;
      v60 = v54 * v28;
      *(float *)&v48 = (v63 - *(float *)&v61[12]) * v28 + *(float *)&v61[12];
      v62[12] = v48;
      *(float *)&v52 = *(float *)&v61[13] + v59;
      v62[13] = v52;
      *(float *)&v55 = *(float *)&v61[14] + v60;
      v29 = *(float *)(this + 80) * 3.1415927;
      v62[14] = v55;
      v41 = v29;
      v30 = sine(v41);
      v42 = (float *)(*(_DWORD *)this + 104);
      *(float *)&v62[12] = *(float *)&v62[12] - v30 * 0.5;
      look_at_point((float *)v62, v42);
      qmemcpy(v61, (const void *)(*(_DWORD *)(*(_DWORD *)this + 256) + 512), sizeof(v61));
      v43 = *(float *)(this + 80) * 1.5707964;
      v44 = sine(v43);
      linear_interpolate_matrix((float *)(this + 16), (float *)v61, (float *)v62, v44);
      v31 = *(float *)(this + 80) + *(float *)(this + 84);
      *(float *)(this + 80) = v31;
      if ( v31 > 1.0 )
      {
        *(_DWORD *)(this + 12) = 7;
        *(_DWORD *)(this + 80) = 0;
        *(_DWORD *)(this + 84) = 1015580809;
      }
      return;
    case 7:
      *(_DWORD *)(this + 8) = -1;
      *(_BYTE *)(this + 88) = 1;
      set_matrix_identity((_DWORD *)(this + 16));
      v32 = (_DWORD *)(*(_DWORD *)this + 6280);
      v45 = (float *)(*(_DWORD *)this + 104);
      *(_DWORD *)(this + 64) = *v32;
      *(_DWORD *)(this + 68) = v32[1];
      *(_DWORD *)(this + 72) = v32[2];
      look_at_point((float *)(this + 16), v45);
      if ( !*(_DWORD *)(*(_DWORD *)this + 320) )
        dispatch_cutscene_animation(*(_DWORD *)this, 9, 0, -1);
      goto LABEL_29;
    case 8:
      *((_BYTE *)&loc_42FEC4 + (_DWORD)MEMORY[0x4DF904]) = 0;
      *(_DWORD *)(this + 8) = 1;
      set_matrix_identity(v61);
      v6 = *(float *)(this + 80) * 3.1415927;
      v7 = (int *)(*(_DWORD *)this + 6280);
      v61[12] = *v7;
      v34 = v6;
      v61[13] = v7[1];
      v61[14] = v7[2];
      v8 = sine(v34);
      v35 = (float *)(*(_DWORD *)this + 104);
      *(float *)&v61[12] = v8 + v8 + *(float *)&v61[12];
      look_at_point((float *)v61, v35);
      qmemcpy(v62, (const void *)(*(_DWORD *)(*(_DWORD *)this + 256) + 512), 0x40u);
      v36 = *(float *)(this + 80) * 1.5707964;
      v37 = sine(v36);
      linear_interpolate_matrix((float *)(this + 16), (float *)v61, (float *)v62, v37);
      v46 = *(float *)(this + 64) - *(float *)(*(_DWORD *)this + 104);
      v49 = *(float *)(this + 68) - *(float *)(*(_DWORD *)this + 108);
      v9 = *(float *)(this + 72) - *(float *)(*(_DWORD *)this + 112);
      v56 = v46;
      v57 = v49;
      v53 = v9;
      v58 = v53;
      v10 = normalize_vector(&v56);
      if ( v10 < 1.5 )
      {
        v11 = 1.5 - v10;
        v47 = v56 * v11;
        v50 = v57 * v11;
        v12 = v11 * v58;
        *(float *)(this + 64) = v47 + *(float *)(this + 64);
        *(float *)(this + 68) = v50 + *(float *)(this + 68);
        *(float *)(this + 72) = v12 + *(float *)(this + 72);
      }
      v13 = *(float *)(this + 80) + *(float *)(this + 84);
      *(float *)(this + 80) = v13;
      if ( v13 > 1.0 )
      {
        *(_DWORD *)(this + 12) = 9;
        *(_DWORD *)(this + 80) = 0;
        *(_DWORD *)(this + 84) = 1007192201;
      }
      return;
    case 9:
      qmemcpy((void *)(this + 16), (const void *)(*(_DWORD *)(*(_DWORD *)this + 256) + 512), 0x40u);
      *(_DWORD *)(this + 12) = 0;
      return;
    case 10:
      v14 = *(_DWORD *)this;
      *(_DWORD *)(this + 8) = -1;
      dispatch_cutscene_animation(v14, 7, 1, -1);
      *(_DWORD *)(this + 12) = 11;
      *(_DWORD *)(this + 80) = 0;
      *(_DWORD *)(this + 84) = 1007192201;
      *(_BYTE *)(this + 88) = 1;
      play_voice_manager((int)unk_751498, 3, 2u, -1);
      *(_BYTE *)(*(_DWORD *)(*(_DWORD *)this + 256) + 1100) = 1;
      release_snail_weapons(*(_DWORD *)this);
      goto LABEL_11;
    case 11:
LABEL_11:
      *(_DWORD *)(this + 8) = -1;
      set_matrix_identity(v62);
      v15 = *(float *)(this + 80) * 3.1415927;
      v16 = (int *)(*(_DWORD *)this + 6280);
      v62[12] = *v16;
      v62[13] = v16[1];
      v38 = v15;
      v62[14] = v16[2];
      v17 = sine(v38);
      *(float *)&v62[12] = v17 + v17 + *(float *)&v62[12];
      if ( *(float *)&v62[13] < 0.0 )
        v62[13] = 0;
      look_at_point((float *)v62, (float *)(*(_DWORD *)this + 104));
      v18 = *(float *)(this + 80);
      qmemcpy(v61, (const void *)(*(_DWORD *)(*(_DWORD *)this + 256) + 512), sizeof(v61));
      v39 = v18 * 1.5707964;
      v40 = sine(v39);
      linear_interpolate_matrix((float *)(this + 16), (float *)v61, (float *)v62, v40);
      v19 = *(float *)(this + 80) + *(float *)(this + 84);
      *(float *)(this + 80) = v19;
      if ( v19 > 1.0 )
      {
        *(_DWORD *)(this + 12) = 12;
        *(_DWORD *)(this + 80) = 0;
        *(_DWORD *)(this + 84) = 1015580809;
      }
      break;
    case 12:
      *(_DWORD *)(this + 8) = -1;
      *(_BYTE *)(this + 88) = 1;
      set_matrix_identity((_DWORD *)(this + 16));
      v20 = *(_DWORD *)this;
      *(_DWORD *)(this + 64) = *(_DWORD *)(*(_DWORD *)this + 6280);
      *(_DWORD *)(this + 68) = *(_DWORD *)(v20 + 6284);
      *(_DWORD *)(this + 72) = *(_DWORD *)(v20 + 6288);
      if ( *(float *)(this + 68) < 0.0 )
        *(_DWORD *)(this + 68) = 0;
      look_at_point((float *)(this + 16), (float *)(v20 + 104));
      v21 = *(_DWORD *)(this + 4);
      if ( *(_BYTE *)(v21 + 132) || (initialize_subgoldy_death((_DWORD *)v21), *(_BYTE *)(*(_DWORD *)(this + 4) + 1101)) )
      {
LABEL_29:
        *(float *)(this + 80) = *(float *)(this + 84) + *(float *)(this + 80);
      }
      else
      {
        play_voice_manager((int)unk_751498, 11, 2u, -1);
        *(_BYTE *)(*(_DWORD *)(this + 4) + 1101) = 1;
        *(_BYTE *)(*(_DWORD *)(this + 4) + 1100) = 1;
        *(float *)(this + 80) = *(float *)(this + 84) + *(float *)(this + 80);
      }
      break;
    default:
      return;
  }
}

