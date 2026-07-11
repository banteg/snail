/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: create_golb @ 0x415280 */
/* selector: create_golb */

// Initializes one Golb shot actor from the player's current movement_flags family and emitter slot, choosing the matching spawn anchor, velocity lane, render owner, and any path-follow state before the actor enters `update_golb_ai`.
int __thiscall create_golb(char *this, int a2, int32_t a3, int a4)
{
  char *v5; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // eax
  int v9; // eax
  float *v10; // edi
  double v11; // st7
  double v12; // st7
  int v13; // ecx
  int v14; // eax
  double v15; // st7
  float v16; // eax
  double v17; // st7
  float v18; // edx
  double v19; // st7
  float g; // eax
  float v21; // edx
  float v22; // ecx
  float *v23; // edx
  double v24; // st7
  float b; // ecx
  double v26; // st7
  float v27; // eax
  float v28; // edx
  float v29; // ecx
  int v30; // eax
  int v31; // eax
  int v32; // ecx
  char *v33; // ecx
  char *v34; // eax
  int v35; // edx
  int v36; // edx
  int v37; // eax
  ContactTargetRegistry *v38; // ecx
  ContactTargetEntry *v39; // eax
  ContactTargetObject *object; // ecx
  int32_t list_flags; // edx
  Vec3 *p_position; // eax
  float z; // eax
  int v44; // ecx
  char *v45; // ebp
  double v46; // st7
  char *v47; // eax
  int v48; // eax
  int v49; // ecx
  int v50; // edx
  _DWORD *sprite; // eax
  _DWORD *v52; // eax
  int v53; // ecx
  int v54; // eax
  float v55; // eax
  int v56; // ecx
  int v57; // eax
  Color4f color; // [esp+Ch] [ebp-10h] BYREF

  *(this + 444) = 0;
  *(this + 445) = 0;
  if ( (*((_DWORD *)this + 1) & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v5 = (char *)g_game_base + 1452;
    v6 = *((_DWORD *)g_game_base + 363);
    if ( v6 )
    {
      *(_DWORD *)(v6 + 8) = this;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v5 + 8) + 12) = *(_DWORD *)v5;
      v7 = *(_DWORD *)(*(_DWORD *)v5 + 8);
      *(_DWORD *)v5 = v7;
      *(_DWORD *)(v7 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v5 = this;
      *((_DWORD *)this + 2) = 0;
      *(_DWORD *)(*(_DWORD *)v5 + 12) = 0;
    }
    *((_DWORD *)this + 1) |= 0x200u;
  }
  *((_DWORD *)this + 158) = a2;
  v8 = *(_DWORD *)(a2 + 824);
  if ( (v8 & 7) != 0 )
  {
    *((_DWORD *)this + 112) = 0;
  }
  else if ( (v8 & 0x18) != 0 )
  {
    *((_DWORD *)this + 112) = 1;
  }
  else if ( (v8 & 0x60) != 0 )
  {
    *((_DWORD *)this + 112) = 2;
  }
  set_matrix_identity((TransformMatrix *)(this + 636));
  v9 = *((_DWORD *)this + 158);
  v10 = (float *)(this + 500);
  *((_DWORD *)this + 145) = 1;
  *((_DWORD *)this + 125) = *(_DWORD *)(v9 + 104);
  *((_DWORD *)this + 126) = *(_DWORD *)(v9 + 108);
  *((_DWORD *)this + 127) = *(_DWORD *)(v9 + 112);
  v11 = *(float *)(v9 + 88) * 0.5;
  color.g = *(float *)(v9 + 92) * 0.5;
  color.b = *(float *)(v9 + 96) * 0.5;
  *((float *)this + 125) = v11 + *((float *)this + 125);
  *((float *)this + 126) = color.g + *((float *)this + 126);
  v12 = color.b + *((float *)this + 127);
  *((float *)this + 127) = v12;
  v13 = *((_DWORD *)this + 158);
  v14 = *(_DWORD *)(v13 + 824);
  if ( (v14 & 5) != 0 )
  {
    switch ( a3 )
    {
      case 3:
        v23 = (float *)(v13 + 16692);
        break;
      case 2:
        v23 = (float *)(v13 + 16716);
        break;
      case 1:
        v23 = (float *)(v13 + 16740);
        break;
      default:
LABEL_43:
        if ( (*(_BYTE *)(v13 + 824) & 4) == 0 )
          goto LABEL_50;
        if ( a3 == 3 )
        {
          v24 = *(float *)(v13 + 1048) + 1.0;
          color.r = 0.1;
          color.g = 0.0;
          color.b = v24;
          v12 = *v10 + 0.5;
          *((_DWORD *)this + 147) = 1036831949;
          b = color.b;
          *((_DWORD *)this + 148) = 0;
          *v10 = v12;
          *((float *)this + 149) = b;
          goto LABEL_51;
        }
        if ( a3 != 2 )
        {
          v12 = *(float *)(v13 + 1048) + 1.0;
          color.r = 0.0;
          color.g = 0.0;
          *((_DWORD *)this + 147) = 0;
          color.b = v12;
          v28 = color.b;
          *((_DWORD *)this + 148) = 0;
          *((float *)this + 149) = v28;
          goto LABEL_51;
        }
        v26 = *(float *)(v13 + 1048) + 1.0;
        color.r = -0.1;
        color.g = 0.0;
        *((_DWORD *)this + 147) = -1110651699;
        color.b = v26;
        v27 = color.b;
        *((_DWORD *)this + 148) = 0;
        v19 = *v10;
        *((float *)this + 149) = v27;
LABEL_48:
        v12 = v19 - 0.5;
        *v10 = v12;
        goto LABEL_51;
    }
    *v10 = *v23;
    *((float *)this + 126) = v23[1];
    *((float *)this + 127) = v23[2];
    goto LABEL_43;
  }
  if ( (v14 & 2) != 0 )
  {
    if ( a3 == 2 )
    {
      *v10 = *(float *)(v13 + 16692);
      *((_DWORD *)this + 126) = *(_DWORD *)(v13 + 16696);
      *((_DWORD *)this + 127) = *(_DWORD *)(v13 + 16700);
      v15 = *v10 + 0.5;
LABEL_19:
      *v10 = v15;
      goto LABEL_50;
    }
    if ( a3 == 1 )
    {
      *v10 = *(float *)(v13 + 16716);
      *((_DWORD *)this + 126) = *(_DWORD *)(v13 + 16720);
      *((_DWORD *)this + 127) = *(_DWORD *)(v13 + 16724);
      v15 = *v10 - 0.5;
      goto LABEL_19;
    }
LABEL_50:
    v12 = *(float *)(v13 + 1048) + 1.0;
    color.r = 0.0;
    color.g = 0.0;
    *((_DWORD *)this + 147) = 0;
    color.b = v12;
    v29 = color.b;
    *((_DWORD *)this + 148) = 0;
    *((float *)this + 149) = v29;
    goto LABEL_51;
  }
  if ( (v14 & 0x18) != 0 )
  {
    if ( a3 == 2 )
    {
      *v10 = *(float *)(v13 + 16764);
      *((_DWORD *)this + 126) = *(_DWORD *)(v13 + 16768);
      *((_DWORD *)this + 127) = *(_DWORD *)(v13 + 16772);
      if ( *(float *)(v13 + 96) > 0.0 )
      {
        a3 = v13 + 16772;
LABEL_35:
        v12 = *(float *)(v13 + 1048) + 1.0;
        color.r = 0.0;
        color.g = 0.0;
        *(this + 444) = 1;
        *((_DWORD *)this + 147) = 0;
        color.b = v12;
        v22 = color.b;
        *((_DWORD *)this + 148) = 0;
        *((float *)this + 149) = v22;
        goto LABEL_51;
      }
    }
    else
    {
      *v10 = *(float *)(v13 + 16776);
      *((_DWORD *)this + 126) = *(_DWORD *)(v13 + 16780);
      *((_DWORD *)this + 127) = *(_DWORD *)(v13 + 16784);
      if ( *(float *)(v13 + 96) > 0.0 )
      {
        a3 = v13 + 16772;
        goto LABEL_35;
      }
    }
    a3 = 0;
    goto LABEL_35;
  }
  if ( (v14 & 0x60) != 0 )
  {
    color.r = 0.0;
    color.g = 0.0;
    *v10 = *(float *)(v13 + 16812);
    *((_DWORD *)this + 126) = *(_DWORD *)(v13 + 16816);
    *((_DWORD *)this + 127) = *(_DWORD *)(v13 + 16820);
    v12 = *(float *)(v13 + 1048) + 0.60000002;
    g = color.g;
    *((_DWORD *)this + 147) = LODWORD(color.r);
    color.b = v12;
    v21 = color.b;
    *((float *)this + 148) = g;
    *((float *)this + 149) = v21;
    goto LABEL_51;
  }
  if ( (v14 & 0x29) != 0 )
  {
    v12 = *(float *)(v13 + 1048) + 1.0;
    color.r = 0.0;
    color.g = 0.0;
    *((_DWORD *)this + 147) = 0;
    color.b = v12;
    v16 = color.b;
    *((_DWORD *)this + 148) = 0;
    *((float *)this + 149) = v16;
    goto LABEL_51;
  }
  if ( (v14 & 0x52) != 0 )
  {
    v17 = *(float *)(v13 + 1048) + 1.0;
    color.r = 0.0;
    color.g = 0.0;
    *((_DWORD *)this + 147) = 0;
    color.b = v17;
    v18 = color.b;
    *((_DWORD *)this + 148) = 0;
    v19 = *v10;
    *((float *)this + 149) = v18;
    if ( a3 == 2 )
    {
      v12 = v19 + 0.5;
      *v10 = v12;
      goto LABEL_51;
    }
    goto LABEL_48;
  }
LABEL_51:
  if ( *((_DWORD *)this + 112) == 1 )
  {
    *((float *)this + 147) = *((float *)this + 147) + *((float *)this + 147);
    *((float *)this + 148) = *((float *)this + 148) + *((float *)this + 148);
    v12 = *((float *)this + 149) + *((float *)this + 149);
    *((float *)this + 149) = v12;
  }
  if ( *((_DWORD *)this + 112) == 2 )
  {
    *((float *)this + 147) = *((float *)this + 147) * 0.80000001;
    *((float *)this + 148) = *((float *)this + 148) * 0.80000001;
    v12 = *((float *)this + 149) * 0.80000001;
    *((float *)this + 149) = v12;
  }
  *((_DWORD *)this + 150) = *((_DWORD *)this + 147);
  *((_DWORD *)this + 151) = *((_DWORD *)this + 148);
  *((_DWORD *)this + 152) = *((_DWORD *)this + 149);
  v30 = *((_DWORD *)this + 112);
  if ( v30 )
  {
    v31 = v30 - 1;
    if ( v31 )
    {
      if ( v31 == 1 )
      {
        v32 = *((_DWORD *)this + 156);
        *((_DWORD *)this + 154) = 0;
        v12 = *(float *)(v32 + 56) * 0.027777776;
        v33 = this + 280;
        *((_DWORD *)this + 106) = this;
        *((_DWORD *)this + 109) = 0;
        *((_DWORD *)this + 110) = 1045854032;
        *((_DWORD *)this + 102) = 0;
        *((float *)this + 155) = v12;
        if ( (*((_DWORD *)this + 71) & 0x200) != 0 )
        {
          report_errorf(aListAdd);
        }
        else
        {
          v34 = (char *)g_game_base + 1452;
          v35 = *((_DWORD *)g_game_base + 363);
          if ( v35 )
          {
            *(_DWORD *)(v35 + 8) = v33;
            *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v34 + 8) + 12) = *(_DWORD *)v34;
            v36 = *(_DWORD *)(*(_DWORD *)v34 + 8);
            *(_DWORD *)v34 = v36;
            *(_DWORD *)(v36 + 8) = 0;
          }
          else
          {
            *(_DWORD *)v34 = v33;
            *((_DWORD *)this + 72) = 0;
            *(_DWORD *)(*(_DWORD *)v34 + 12) = 0;
          }
          v37 = *((_DWORD *)this + 71);
          BYTE1(v37) |= 2u;
          *((_DWORD *)this + 71) = v37;
        }
        v38 = (ContactTargetRegistry *)(*((_DWORD *)this + 156) + 19337172);
        *((_DWORD *)this + 157) = a4;
        v39 = search_path_for_golb(v38, (const Vec3 *)(this + 500));
        if ( v39 )
        {
          object = v39->object;
          *((_DWORD *)this + 102) = object;
          if ( !v39->kind )
          {
            list_flags = object->list_flags;
            BYTE1(list_flags) |= 0x10u;
            object->list_flags = list_flags;
          }
          p_position = &v39->position;
          *((_DWORD *)this + 103) = LODWORD(p_position->x);
          *((_DWORD *)this + 104) = LODWORD(p_position->y);
          z = p_position->z;
          *((_DWORD *)this + 107) = 0;
          *((float *)this + 105) = z;
          *((_DWORD *)this + 108) = 1023969417;
        }
      }
    }
    else
    {
      v44 = *((_DWORD *)this + 156);
      *((_DWORD *)this + 154) = 0;
      v45 = this + 128;
      v46 = *(float *)(v44 + 56) * 0.041666668;
      *((_DWORD *)this + 69) = this;
      *((float *)this + 155) = v46;
      v47 = (char *)g_game_base + 3973948;
      if ( (*((_DWORD *)this + 33) & 0x200) != 0 )
      {
        report_errorf(aListAddafter);
      }
      else
      {
        *((_DWORD *)this + 34) = v47;
        *((_DWORD *)this + 35) = *((_DWORD *)v47 + 3);
        *((_DWORD *)v47 + 3) = v45;
        v48 = *((_DWORD *)this + 35);
        if ( v48 )
          *(_DWORD *)(v48 + 8) = v45;
        *((_DWORD *)this + 33) |= 0x200u;
      }
      reset_vapour((VapourTrail *)(this + 128), a3);
      v12 = store_color4f((Color4f *)(this + 168), 1.0, 1.0, 1.0, 0.99000001);
      *((_DWORD *)this + 157) = a4;
      add_vapour_point((VapourTrail *)(this + 128), (const TransformMatrix *)(this + 452));
      (**(void (__usercall ***)(char *@<ecx>, double@<st0>))v45)(this + 128, v12);
    }
  }
  else
  {
    v49 = *((_DWORD *)this + 156);
    v50 = *((_DWORD *)this + 158);
    *((_DWORD *)this + 154) = 0;
    *((float *)this + 155) = *(float *)(v49 + 56) * 0.041666668;
    sprite = allocate_sprite(g_sprite_manager, *(_DWORD *)(v50 + 896), 130, -1, -1);
    *((_DWORD *)this + 146) = sprite;
    sprite[1] |= 0x800u;
    *(_DWORD *)(*((_DWORD *)this + 146) + 104) = 0;
    *(_DWORD *)(*((_DWORD *)this + 146) + 108) = 0;
    *(_DWORD *)(*((_DWORD *)this + 146) + 120) = 0;
    *(Color4f *)(*((_DWORD *)this + 146) + 44) = *set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
    *(_DWORD *)(*((_DWORD *)this + 146) + 96) = 1056629064;
    *(_DWORD *)(*((_DWORD *)this + 146) + 100) = 1056629064;
    v52 = (_DWORD *)(*((_DWORD *)this + 146) + 72);
    *v52 = *(_DWORD *)v10;
    v52[1] = *((_DWORD *)this + 126);
    v52[2] = *((_DWORD *)this + 127);
    *(float *)(*((_DWORD *)this + 146) + 124) = ((double)next_math_random_value() - 16384.0) * 0.0001917476;
    v12 = *(float *)(*((_DWORD *)this + 156) + 56) * 0.58177644;
    *(float *)(*((_DWORD *)this + 146) + 128) = v12;
    *((_DWORD *)this + 157) = a4;
  }
  v53 = *((_DWORD *)this + 158);
  if ( *(_BYTE *)(v53 + 900) == 1 && (v12 = *(float *)(v53 + 920), v12 < 0.5) )
  {
    *(this + 700) = 1;
    *((_DWORD *)this + 176) = *(_DWORD *)(v53 + 904);
    *((_DWORD *)this + 177) = *(_DWORD *)(v53 + 908);
    *((_DWORD *)this + 178) = *(_DWORD *)(v53 + 912);
    *((_DWORD *)this + 179) = *(_DWORD *)(v53 + 916);
    *((_DWORD *)this + 180) = 0;
    *((_DWORD *)this + 181) = *(_DWORD *)(v53 + 944);
    *((_DWORD *)this + 182) = *(_DWORD *)(v53 + 948);
    v54 = *(_DWORD *)(v53 + 952);
    *((_DWORD *)this + 184) = this;
    *((_DWORD *)this + 183) = v54;
    *((_DWORD *)this + 185) = *(_DWORD *)(v53 + 952);
  }
  else
  {
    *(this + 700) = 0;
    *((_DWORD *)this + 185) = -1082130432;
  }
  vector_magnitude((float *)this + 147);
  v55 = *v10;
  v56 = *((_DWORD *)this + 126);
  *((float *)this + 153) = v12;
  *((float *)this + 141) = v55;
  v57 = *((_DWORD *)this + 127);
  *((_DWORD *)this + 142) = v56;
  *((_DWORD *)this + 143) = v57;
  return (**(int (__thiscall ***)(char *))this)(this);
}

