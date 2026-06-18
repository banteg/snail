/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_garbage_hazard @ 0x43f200 */
/* selector: update_garbage_hazard */

// Advances one live garbage hazard through its hover, impact-burst, bounce, smoke, and teardown states. Cross-port Android and iOS symbols match this helper to `cRSubGarbage::AI()`.
// slot->game +0x09 is subgame_pause_gate; slot->game +0x38 is subgame_rate.
int *__thiscall sub_43F200(int this)
{
  int *result; // eax
  float *v3; // edi
  _DWORD *v4; // ecx
  int v5; // ecx
  double v6; // st7
  double v7; // st7
  int v8; // edx
  float *v9; // ecx
  double v10; // st6
  int v11; // eax
  double v13; // st7
  char v14; // c0
  double v16; // st7
  char v17; // c0
  double v18; // st7
  double v19; // st7
  _DWORD *v20; // eax
  int v21; // edi
  double v22; // st7
  int v23; // [esp+Ch] [ebp-1Ch]
  float v24; // [esp+10h] [ebp-18h]
  float v25; // [esp+14h] [ebp-14h]
  float v26; // [esp+18h] [ebp-10h]
  float v27; // [esp+1Ch] [ebp-Ch]
  float v28; // [esp+20h] [ebp-8h]

  result = *(int **)(this + 140);
  if ( !*((_BYTE *)result + 9) )
  {
    result = *(int **)(this + 132);
    switch ( (unsigned int)result )
    {
      case 0u:
        return result;
      case 1u:
        v3 = (float *)(this + 104);
        v4 = (_DWORD *)(*(_DWORD *)(this + 180) + 72);
        *v4 = *(_DWORD *)(this + 104);
        v4[1] = *(_DWORD *)(this + 108);
        v4[2] = *(_DWORD *)(this + 112);
        v5 = *(_DWORD *)(this + 192);
        if ( *(float *)(this + 112) < (double)*(float *)(v5 + 10624) )
          goto LABEL_4;
        if ( *(float *)(v5 + 884) > 0.0 )
        {
          v6 = *v3;
          *(_DWORD *)(this + 132) = 2;
          if ( v6 <= 0.0 )
            *(_DWORD *)(this + 136) = 2;
          else
            *(_DWORD *)(this + 136) = 1;
          add_subgoldy_score((int *)v5, SUBGOLDY_SCORE_GARBAGE, 0);
        }
        sub_415EF0(
          (float *)(*(_DWORD *)(this + 140) + 19337172),
          (float *)(this + 104),
          *(float *)(this + 156),
          0,
          this);
        goto LABEL_27;
      case 2u:
        *(_DWORD *)(this + 132) = 3;
        v27 = random_signed_float_below(0.1);
        v28 = random_float_below(0.2) + 0.1;
        v7 = random_float_below(0.30000001);
        v8 = *(_DWORD *)(this + 140);
        v9 = (float *)(this + 144);
        v10 = *(float *)(v8 + 56);
        v24 = v10 * v27;
        *(float *)(this + 144) = v24;
        v25 = v28 * v10;
        *(float *)(this + 148) = v25;
        v26 = v7 * v10;
        *(float *)(this + 152) = v26;
        v11 = *(_DWORD *)(this + 136);
        if ( v11 == 1 )
        {
          v13 = *v9;
          if ( v14 )
            v13 = -v13;
        }
        else
        {
          if ( v11 != 2 )
            goto LABEL_19;
          v16 = *v9;
          if ( v17 )
            v16 = -v16;
          v13 = -v16;
        }
        *v9 = v13;
LABEL_19:
        if ( *v9 >= 0.0 )
          v23 = *v9 != 0.0;
        else
          v23 = -1;
        v18 = (double)v23 * 0.2 * *(float *)(v8 + 56);
        *(_DWORD *)(this + 164) = 0;
        *v9 = v18 + *v9;
        v19 = *(float *)(v8 + 56) * 0.0083333338;
        *(_DWORD *)(this + 172) = 0;
        *(float *)(this + 168) = v19;
        *(float *)(this + 176) = *(float *)(v8 + 56) * 0.27777779;
LABEL_23:
        *(float *)(this + 104) = *(float *)(this + 144) + *(float *)(this + 104);
        *(float *)(this + 108) = *(float *)(this + 148) + *(float *)(this + 108);
        *(float *)(this + 112) = *(float *)(this + 152) + *(float *)(this + 112);
        v20 = (_DWORD *)(*(_DWORD *)(this + 180) + 72);
        *v20 = *(_DWORD *)(this + 104);
        v20[1] = *(_DWORD *)(this + 108);
        v20[2] = *(_DWORD *)(this + 112);
        *(float *)(this + 148) = *(float *)(*(_DWORD *)(this + 140) + 56)
                               * *(float *)(*(_DWORD *)(this + 140) + 56)
                               * -0.0099999998
                               + *(float *)(this + 148);
        if ( *(float *)(this + 108) < -10.0
          || (v21 = *(_DWORD *)(this + 192), *(float *)(this + 112) < (double)*(float *)(v21 + 10624)) )
        {
LABEL_4:
          result = destroy_garbage_hazard((int *)this);
        }
        else
        {
          v22 = *(float *)(this + 176) + *(float *)(this + 172);
          *(float *)(this + 172) = v22;
          if ( v22 > 1.0 )
          {
            *(_DWORD *)(this + 172) = 0;
            spawn_garbage_smoke_particle((_DWORD *)this, (float *)(this + 104), (float *)(this + 144), v21);
          }
LABEL_27:
          *(float *)(*(_DWORD *)(this + 180) + 124) = *(float *)(*(_DWORD *)(this + 192) + 880) + *(float *)(this + 160);
          result = *(int **)(this + 192);
          if ( *((_BYTE *)result + 900) == 1 )
            *(float *)(*(_DWORD *)(this + 180) + 124) = *((float *)result + 232)
                                                      + *(float *)(*(_DWORD *)(this + 180) + 124);
        }
        break;
      case 3u:
        goto LABEL_23;
      default:
        goto LABEL_27;
    }
  }
  return result;
}
