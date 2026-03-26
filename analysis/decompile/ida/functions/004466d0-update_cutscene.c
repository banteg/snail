/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_cutscene @ 0x4466d0 */
/* selector: update_cutscene */

// Advances the player-side cutscene controller, consuming the live snail hotspot bank as the intro/completion/death camera anchor source, including the authored `CameraSkidStop -> CameraIntroTalk` blend path, and handling the handoff into `initialize_completion_screen`. Cross-port Android and iOS symbols match this helper to `cRCutScene::AI()`.
int32_t __thiscall update_cutscene(CutsceneAI *cutscene_ai)
{
  int32_t active; // eax
  int32_t result; // eax
  PlayerPresentationController *shared_state; // ecx
  _DWORD *v5; // ecx
  double v6; // st7
  __int16 v7; // fps
  bool v8; // c0
  char v9; // c2
  bool v10; // c3
  double v11; // st7
  float *v12; // eax
  double v13; // st7
  double v14; // st7
  double v15; // st7
  double v16; // st7
  double v17; // st7
  __int16 v18; // fps
  bool v19; // c0
  char v20; // c2
  bool v21; // c3
  PlayerPresentationController *v22; // ecx
  double v23; // st7
  float *v24; // edx
  double v25; // st7
  double v26; // st7
  double v27; // st7
  __int16 v28; // fps
  bool v29; // c0
  char v30; // c2
  bool v31; // c3
  char *v32; // ecx
  _BYTE *intro_talk_anchor; // ecx
  PlayerPresentationController *v34; // ecx
  _DWORD *v35; // eax
  int v36; // eax
  float *v37; // ecx
  float *v38; // eax
  float v39; // edx
  float v40; // eax
  double v41; // st7
  double v42; // st7
  double v43; // st7
  __int16 v44; // fps
  bool v45; // c0
  char v46; // c2
  bool v47; // c3
  _DWORD *v48; // edx
  Vec3 *v49; // [esp+0h] [ebp-FCh]
  float v50; // [esp+0h] [ebp-FCh]
  Vec3 *v51; // [esp+0h] [ebp-FCh]
  float v52; // [esp+0h] [ebp-FCh]
  float v53; // [esp+0h] [ebp-FCh]
  float v54; // [esp+0h] [ebp-FCh]
  float v55; // [esp+0h] [ebp-FCh]
  float v56; // [esp+0h] [ebp-FCh]
  float v57; // [esp+0h] [ebp-FCh]
  Vec3 *v58; // [esp+0h] [ebp-FCh]
  float v59; // [esp+0h] [ebp-FCh]
  float v60; // [esp+0h] [ebp-FCh]
  Vec3 *v61; // [esp+0h] [ebp-FCh]
  float v62; // [esp+14h] [ebp-E8h]
  float v63; // [esp+14h] [ebp-E8h]
  float v64; // [esp+18h] [ebp-E4h]
  float v65; // [esp+18h] [ebp-E4h]
  float v66; // [esp+18h] [ebp-E4h]
  float v67; // [esp+1Ch] [ebp-E0h]
  float v68; // [esp+1Ch] [ebp-E0h]
  Vec3 v69; // [esp+24h] [ebp-D8h] BYREF
  float v70; // [esp+34h] [ebp-C8h]
  float v71; // [esp+38h] [ebp-C4h]
  TransformMatrix v72; // [esp+3Ch] [ebp-C0h] BYREF
  TransformMatrix v73; // [esp+7Ch] [ebp-80h] BYREF
  float v74; // [esp+ECh] [ebp-10h]
  float v75; // [esp+F0h] [ebp-Ch]
  float v76; // [esp+F4h] [ebp-8h]
  Vec3 v77; // 0:^1C.12

  active = cutscene_ai->active;
  cutscene_ai->_pad_10[72] = 0;
  result = active - 1;
  switch ( result )
  {
    case 0:
      shared_state = (PlayerPresentationController *)cutscene_ai->shared_state;
      cutscene_ai->active = 2;
      *(_DWORD *)&cutscene_ai->_pad_10[64] = 0;
      *(_DWORD *)&cutscene_ai->_pad_10[68] = 1007192201;
      cutscene_ai->_pad_10[72] = 1;
      dispatch_cutscene_animation(shared_state, 9, 1, -1);
      dispatch_cutscene_animation((PlayerPresentationController *)cutscene_ai->shared_state, 9, 0, -1);
      dispatch_cutscene_animation((PlayerPresentationController *)cutscene_ai->shared_state, 1, 0, -1);
      goto LABEL_3;
    case 1:
LABEL_3:
      *(_DWORD *)cutscene_ai->_pad_08 = 1;
      set_matrix_identity((TransformMatrix *)cutscene_ai->_pad_10);
      v5 = (char *)cutscene_ai->shared_state + 6280;
      v49 = (Vec3 *)((char *)cutscene_ai->shared_state + 104);
      *(_DWORD *)&cutscene_ai->_pad_10[48] = *v5;
      *(_DWORD *)&cutscene_ai->_pad_10[52] = v5[1];
      *(_DWORD *)&cutscene_ai->_pad_10[56] = v5[2];
      HIWORD(result) = (unsigned int)look_at_point((TransformMatrix *)cutscene_ai->_pad_10, v49) >> 16;
      v6 = *(float *)&cutscene_ai->_pad_10[64] + *(float *)&cutscene_ai->_pad_10[68];
      *(float *)&cutscene_ai->_pad_10[64] = v6;
      v8 = v6 < 1.0;
      v9 = 0;
      v10 = v6 == 1.0;
      LOWORD(result) = v7;
      if ( v6 > 1.0 )
      {
        *(_DWORD *)&cutscene_ai->_pad_10[68] = 1007192201;
        cutscene_ai->active = 8;
        *(_DWORD *)&cutscene_ai->_pad_10[64] = 0;
      }
      return result;
    case 4:
      v34 = (PlayerPresentationController *)cutscene_ai->shared_state;
      cutscene_ai->active = 7;
      *(_DWORD *)cutscene_ai->_pad_08 = -1;
      dispatch_cutscene_animation(v34, 8, 1, -1);
      dispatch_cutscene_animation((PlayerPresentationController *)cutscene_ai->shared_state, 9, 0, -1);
      dispatch_cutscene_animation((PlayerPresentationController *)cutscene_ai->shared_state, 9, 0, -1);
      v35 = cutscene_ai->shared_state;
      cutscene_ai->active = 6;
      *(_DWORD *)&cutscene_ai->_pad_10[64] = 0;
      *(_DWORD *)&cutscene_ai->_pad_10[68] = 1007192201;
      v35[1612] = 1015580809;
      *((_DWORD *)cutscene_ai->shared_state + 1611) = *((_DWORD *)cutscene_ai->shared_state + 1612);
      cutscene_ai->_pad_10[72] = 1;
      v36 = *((_DWORD *)MEMORY[0x4DF904] + 119190);
      if ( v36 )
      {
        if ( v36 == 1 )
          initialize_completion_screen(
            (int)MEMORY[0x4DF904] + 19820016,
            *((_DWORD *)cutscene_ai->intro_talk_anchor + 4302),
            1u);
      }
      else
      {
        initialize_completion_screen(
          (int)MEMORY[0x4DF904] + 19820016,
          *((_DWORD *)cutscene_ai->intro_talk_anchor + 4302),
          *((_DWORD *)cutscene_ai->intro_talk_anchor + 4302) == *((_DWORD *)MEMORY[0x4DF904] + 561662));
      }
      play_sound_effect(46);
      goto LABEL_25;
    case 5:
LABEL_25:
      *(_DWORD *)cutscene_ai->_pad_08 = -1;
      set_matrix_identity(&v73);
      v37 = (float *)((char *)cutscene_ai->shared_state + 6208);
      v38 = (float *)((char *)cutscene_ai->shared_state + 6280);
      v72.position.x = *v37;
      v72.position.y = v37[1];
      v72.position.z = v37[2];
      v74 = *v38;
      v39 = v38[2];
      v75 = v38[1];
      v40 = *(float *)&cutscene_ai->_pad_10[64];
      v76 = v39;
      v65 = v75 - v72.position.y;
      v67 = v39 - v72.position.z;
      v70 = v65 * v40;
      v71 = v67 * v40;
      v63 = (v74 - v72.position.x) * v40 + v72.position.x;
      v73.position.x = v63;
      v66 = v72.position.y + v70;
      v73.position.y = v66;
      v68 = v72.position.z + v71;
      v41 = *(float *)&cutscene_ai->_pad_10[64] * 3.1415927;
      v73.position.z = v68;
      v57 = v41;
      v42 = sine(v57);
      v58 = (Vec3 *)((char *)cutscene_ai->shared_state + 104);
      v73.position.x = v73.position.x - v42 * 0.5;
      look_at_point(&v73, v58);
      qmemcpy(&v72, (const void *)(*((_DWORD *)cutscene_ai->shared_state + 64) + 512), sizeof(v72));
      v59 = *(float *)&cutscene_ai->_pad_10[64] * 1.5707964;
      v60 = sine(v59);
      HIWORD(result) = (unsigned int)linear_interpolate_matrix((TransformMatrix *)cutscene_ai->_pad_10, &v72, &v73, v60) >> 16;
      v43 = *(float *)&cutscene_ai->_pad_10[64] + *(float *)&cutscene_ai->_pad_10[68];
      *(float *)&cutscene_ai->_pad_10[64] = v43;
      v45 = v43 < 1.0;
      v46 = 0;
      v47 = v43 == 1.0;
      LOWORD(result) = v44;
      if ( v43 > 1.0 )
      {
        cutscene_ai->active = 7;
        *(_DWORD *)&cutscene_ai->_pad_10[64] = 0;
        *(_DWORD *)&cutscene_ai->_pad_10[68] = 1015580809;
      }
      return result;
    case 6:
      *(_DWORD *)cutscene_ai->_pad_08 = -1;
      cutscene_ai->_pad_10[72] = 1;
      set_matrix_identity((TransformMatrix *)cutscene_ai->_pad_10);
      v48 = (char *)cutscene_ai->shared_state + 6280;
      v61 = (Vec3 *)((char *)cutscene_ai->shared_state + 104);
      *(_DWORD *)&cutscene_ai->_pad_10[48] = *v48;
      *(_DWORD *)&cutscene_ai->_pad_10[52] = v48[1];
      *(_DWORD *)&cutscene_ai->_pad_10[56] = v48[2];
      look_at_point((TransformMatrix *)cutscene_ai->_pad_10, v61);
      result = *((_DWORD *)cutscene_ai->shared_state + 80);
      if ( !result )
        result = dispatch_cutscene_animation((PlayerPresentationController *)cutscene_ai->shared_state, 9, 0, -1);
      goto LABEL_29;
    case 7:
      *((_BYTE *)&loc_42FEC4 + (_DWORD)MEMORY[0x4DF904]) = 0;
      *(_DWORD *)cutscene_ai->_pad_08 = 1;
      set_matrix_identity(&v72);
      v11 = *(float *)&cutscene_ai->_pad_10[64] * 3.1415927;
      v12 = (float *)((char *)cutscene_ai->shared_state + 6280);
      v72.position.x = *v12;
      v50 = v11;
      v72.position.y = v12[1];
      v72.position.z = v12[2];
      v13 = sine(v50);
      v51 = (Vec3 *)((char *)cutscene_ai->shared_state + 104);
      v72.position.x = v13 + v13 + v72.position.x;
      look_at_point(&v72, v51);
      qmemcpy(&v73, (const void *)(*((_DWORD *)cutscene_ai->shared_state + 64) + 512), sizeof(v73));
      v52 = *(float *)&cutscene_ai->_pad_10[64] * 1.5707964;
      v53 = sine(v52);
      linear_interpolate_matrix((TransformMatrix *)cutscene_ai->_pad_10, &v72, &v73, v53);
      v77.x = *(float *)&cutscene_ai->_pad_10[48] - *((float *)cutscene_ai->shared_state + 26);
      v77.y = *(float *)&cutscene_ai->_pad_10[52] - *((float *)cutscene_ai->shared_state + 27);
      v77.z = *(float *)&cutscene_ai->_pad_10[56] - *((float *)cutscene_ai->shared_state + 28);
      v69 = v77;
      v14 = normalize_vector(&v69);
      if ( v14 < 1.5 )
      {
        v15 = 1.5 - v14;
        v62 = v69.x * v15;
        v64 = v69.y * v15;
        v16 = v15 * v69.z;
        *(float *)&cutscene_ai->_pad_10[48] = v62 + *(float *)&cutscene_ai->_pad_10[48];
        *(float *)&cutscene_ai->_pad_10[52] = v64 + *(float *)&cutscene_ai->_pad_10[52];
        *(float *)&cutscene_ai->_pad_10[56] = v16 + *(float *)&cutscene_ai->_pad_10[56];
      }
      v17 = *(float *)&cutscene_ai->_pad_10[64] + *(float *)&cutscene_ai->_pad_10[68];
      *(float *)&cutscene_ai->_pad_10[64] = v17;
      v19 = v17 < 1.0;
      v20 = 0;
      v21 = v17 == 1.0;
      LOWORD(result) = v18;
      if ( v17 > 1.0 )
      {
        cutscene_ai->active = 9;
        *(_DWORD *)&cutscene_ai->_pad_10[64] = 0;
        *(_DWORD *)&cutscene_ai->_pad_10[68] = 1007192201;
      }
      return result;
    case 8:
      qmemcpy(cutscene_ai->_pad_10, (const void *)(*((_DWORD *)cutscene_ai->shared_state + 64) + 512), 0x40u);
      cutscene_ai->active = 0;
      return result;
    case 9:
      v22 = (PlayerPresentationController *)cutscene_ai->shared_state;
      *(_DWORD *)cutscene_ai->_pad_08 = -1;
      dispatch_cutscene_animation(v22, 7, 1, -1);
      cutscene_ai->active = 11;
      *(_DWORD *)&cutscene_ai->_pad_10[64] = 0;
      *(_DWORD *)&cutscene_ai->_pad_10[68] = 1007192201;
      cutscene_ai->_pad_10[72] = 1;
      play_voice_manager((int)unk_751498, 3, 2u, -1);
      *(_BYTE *)(*((_DWORD *)cutscene_ai->shared_state + 64) + 1100) = 1;
      release_snail_weapons((int)cutscene_ai->shared_state);
      goto LABEL_11;
    case 10:
LABEL_11:
      *(_DWORD *)cutscene_ai->_pad_08 = -1;
      set_matrix_identity(&v73);
      v23 = *(float *)&cutscene_ai->_pad_10[64] * 3.1415927;
      v24 = (float *)((char *)cutscene_ai->shared_state + 6280);
      v73.position.x = *v24;
      v73.position.y = v24[1];
      v54 = v23;
      v73.position.z = v24[2];
      v25 = sine(v54);
      v73.position.x = v25 + v25 + v73.position.x;
      if ( v73.position.y < 0.0 )
        v73.position.y = 0.0;
      look_at_point(&v73, (Vec3 *)((char *)cutscene_ai->shared_state + 104));
      v26 = *(float *)&cutscene_ai->_pad_10[64];
      qmemcpy(&v72, (const void *)(*((_DWORD *)cutscene_ai->shared_state + 64) + 512), sizeof(v72));
      v55 = v26 * 1.5707964;
      v56 = sine(v55);
      HIWORD(result) = (unsigned int)linear_interpolate_matrix((TransformMatrix *)cutscene_ai->_pad_10, &v72, &v73, v56) >> 16;
      v27 = *(float *)&cutscene_ai->_pad_10[64] + *(float *)&cutscene_ai->_pad_10[68];
      *(float *)&cutscene_ai->_pad_10[64] = v27;
      v29 = v27 < 1.0;
      v30 = 0;
      v31 = v27 == 1.0;
      LOWORD(result) = v28;
      if ( v27 > 1.0 )
      {
        cutscene_ai->active = 12;
        *(_DWORD *)&cutscene_ai->_pad_10[64] = 0;
        *(_DWORD *)&cutscene_ai->_pad_10[68] = 1015580809;
      }
      break;
    case 11:
      *(_DWORD *)cutscene_ai->_pad_08 = -1;
      cutscene_ai->_pad_10[72] = 1;
      set_matrix_identity((TransformMatrix *)cutscene_ai->_pad_10);
      v32 = (char *)cutscene_ai->shared_state;
      *(_DWORD *)&cutscene_ai->_pad_10[48] = *((_DWORD *)cutscene_ai->shared_state + 1570);
      *(_DWORD *)&cutscene_ai->_pad_10[52] = *((_DWORD *)v32 + 1571);
      *(_DWORD *)&cutscene_ai->_pad_10[56] = *((_DWORD *)v32 + 1572);
      if ( *(float *)&cutscene_ai->_pad_10[52] < 0.0 )
        *(_DWORD *)&cutscene_ai->_pad_10[52] = 0;
      result = (int32_t)look_at_point((TransformMatrix *)cutscene_ai->_pad_10, (Vec3 *)(v32 + 104));
      intro_talk_anchor = cutscene_ai->intro_talk_anchor;
      LOBYTE(result) = intro_talk_anchor[132];
      if ( (_BYTE)result
        || (initialize_subgoldy_death(intro_talk_anchor),
            result = (int32_t)cutscene_ai->intro_talk_anchor,
            *(_BYTE *)(result + 1101)) )
      {
LABEL_29:
        *(float *)&cutscene_ai->_pad_10[64] = *(float *)&cutscene_ai->_pad_10[68] + *(float *)&cutscene_ai->_pad_10[64];
      }
      else
      {
        LOBYTE(result) = play_voice_manager((int)unk_751498, 11, 2u, -1);
        *((_BYTE *)cutscene_ai->intro_talk_anchor + 1101) = 1;
        *((_BYTE *)cutscene_ai->intro_talk_anchor + 1100) = 1;
        *(float *)&cutscene_ai->_pad_10[64] = *(float *)&cutscene_ai->_pad_10[68] + *(float *)&cutscene_ai->_pad_10[64];
      }
      break;
    default:
      return result;
  }
  return result;
}

