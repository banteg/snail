/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_worm_path_template_pair @ 0x420170 */
/* selector: initialize_worm_path_template_pair */

int32_t __thiscall initialize_worm_path_template_pair(PathTemplate *self, char *texture_path)
{
  signed int v3; // ebp
  int v4; // edi
  PathTemplateSample *primary_samples; // eax
  PathTemplateSample *secondary_samples; // edx
  int v9; // ebx
  int v10; // edi
  PathTemplateSample *v11; // eax
  PathTemplateSample *v13; // edx
  int v15; // ebx
  PathTemplateSample *v17; // ecx
  PathTemplateSample *v19; // eax
  _DWORD *p_x; // edx
  _DWORD *v24; // ecx
  int v26; // ebx
  PathTemplateSample *v29; // eax
  PathTemplateSample *v33; // ecx
  _DWORD *v35; // edx
  _DWORD *v36; // eax
  PathTemplateStripMesh *strip_mesh; // eax
  PathTemplateStripMeshFlags flags; // edx
  int v39; // edi
  PathTemplateStripMesh *v40; // eax
  int width_cells; // ecx
  float *v46; // eax
  _DWORD *v47; // eax
  _DWORD *v48; // edx
  int v49; // eax
  float *p_z; // eax
  int v57; // ebx
  int v58; // eax
  int v59; // edx
  uint32_t v60; // edi
  int v61; // eax
  float v63; // ecx
  float v71; // [esp-Ch] [ebp-A0h]
  float v72; // [esp-8h] [ebp-9Ch]
  float v73; // [esp-4h] [ebp-98h]
  float v74; // [esp+0h] [ebp-94h]
  float v75; // [esp+0h] [ebp-94h]
  float v76; // [esp+0h] [ebp-94h]
  float v77; // [esp+0h] [ebp-94h]
  int v78; // [esp+14h] [ebp-80h]
  int v79; // [esp+14h] [ebp-80h]
  signed int v81; // [esp+14h] [ebp-80h]
  float v82; // [esp+14h] [ebp-80h]
  int v83; // [esp+18h] [ebp-7Ch]
  signed int v84; // [esp+18h] [ebp-7Ch]
  signed int v85; // [esp+1Ch] [ebp-78h]
  signed int v87; // [esp+1Ch] [ebp-78h]
  int segment_count; // [esp+20h] [ebp-74h]
  int v90; // [esp+20h] [ebp-74h]
  float v91; // [esp+20h] [ebp-74h]
  int v93; // [esp+24h] [ebp-70h]
  Color4f *vertex_colours; // [esp+24h] [ebp-70h]
  int v97; // [esp+24h] [ebp-70h]
  int v98; // [esp+28h] [ebp-6Ch]
  int v100; // [esp+28h] [ebp-6Ch]
  float v102; // [esp+28h] [ebp-6Ch]
  ObjectFaceQuad *facequads; // [esp+2Ch] [ebp-68h]
  float v105; // [esp+34h] [ebp-60h]
  float v106; // [esp+40h] [ebp-54h]
  float v108; // [esp+44h] [ebp-50h]
  float v110; // [esp+48h] [ebp-4Ch]
  float v112; // [esp+4Ch] [ebp-48h]
  float v114; // [esp+50h] [ebp-44h]
  float v116; // [esp+54h] [ebp-40h]
  float v118; // [esp+58h] [ebp-3Ch]
  float v119; // [esp+58h] [ebp-3Ch]
  float v121; // [esp+5Ch] [ebp-38h]
  float v122; // [esp+5Ch] [ebp-38h]
  float v124; // [esp+60h] [ebp-34h]
  float v125; // [esp+60h] [ebp-34h]
  float v129; // [esp+74h] [ebp-20h]
  float v130; // [esp+78h] [ebp-1Ch]
  float v131; // [esp+80h] [ebp-14h]
  float v132; // [esp+84h] [ebp-10h]
  float v133; // [esp+8Ch] [ebp-8h]
  float v134; // [esp+90h] [ebp-4h]

  _ESI = self;
  v3 = 0;
  self->kind = PATH_TEMPLATE_KIND_WORM;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = 16;
  self->width_or_scale = 4.0;
  self->segment_count = 24;
  self->segment_count_f = 96.0;
  allocate_path_nodes(self);
  _ESI->special_runtime_flag_9c = 0;
  v78 = 0;
  v4 = 0;
  do
  {
    _ESI->primary_samples[v4].center_x = 0.0;
    _ESI->primary_samples[v4].rotation_scalar_98 = 0.0;
    _ESI->primary_samples[v4].rotation_scalar_94 = 0.0;
    _ESI->primary_samples[v4].special_scalar = 0.0;
    _ESI->primary_samples[v4].lateral_scale = 1.0;
    set_matrix_identity(&_ESI->primary_samples[v4].transform);
    __asm { fild    [esp+90h+var_80] }
    __asm { fst     [esp+90h+var_70] }
    _ESI->primary_samples[v4].transform.position.x = _ESI->primary_samples[v4].center_x;
    _ESI->primary_samples[v4].transform.position.y = 0.49000001;
    primary_samples = _ESI->primary_samples;
    __asm
    {
      fmul    dword ptr [esi+50h]
      fstp    dword ptr [edi+eax+38h]
    }
    primary_samples[v4].transform.position.z = _ET1;
    set_matrix_identity(&_ESI->secondary_samples[v4].transform);
    __asm { fld     [esp+90h+var_70] }
    _ESI->secondary_samples[v4].transform.position.x = _ESI->primary_samples[v4].center_x;
    _ESI->secondary_samples[v4].transform.position.y = 0.49000001;
    secondary_samples = _ESI->secondary_samples;
    __asm { fmul    dword ptr [esi+50h] }
    ++v4;
    __asm { fstp    dword ptr [edx+edi-70h] }
    secondary_samples[v4 - 1].transform.position.z = _ET1;
    ++v78;
  }
  while ( v4 < 4 );
  v9 = 20;
  v10 = 20;
  v93 = 20;
  do
  {
    _ESI->primary_samples[v10].center_x = 0.0;
    _ESI->primary_samples[v10].rotation_scalar_98 = 0.0;
    _ESI->primary_samples[v10].rotation_scalar_94 = 0.0;
    _ESI->primary_samples[v10].special_scalar = 0.0;
    _ESI->primary_samples[v10].lateral_scale = 1.0;
    set_matrix_identity(&_ESI->primary_samples[v10].transform);
    __asm { fild    [esp+90h+var_70] }
    __asm { fst     [esp+90h+var_70] }
    _ESI->primary_samples[v10].transform.position.x = _ESI->primary_samples[v10].center_x;
    _ESI->primary_samples[v10].transform.position.y = 0.49000001;
    v11 = _ESI->primary_samples;
    __asm
    {
      fmul    dword ptr [esi+50h]
      fstp    dword ptr [edi+eax+38h]
    }
    v11[v10].transform.position.z = _ET1;
    set_matrix_identity(&_ESI->secondary_samples[v10].transform);
    __asm { fld     [esp+90h+var_70] }
    _ESI->secondary_samples[v10].transform.position.x = _ESI->primary_samples[v10].center_x;
    _ESI->secondary_samples[v10].transform.position.y = 0.49000001;
    v13 = _ESI->secondary_samples;
    __asm { fmul    dword ptr [esi+50h] }
    ++v10;
    v93 = ++v9;
    __asm { fstp    dword ptr [edx+edi-70h] }
    v13[v10 - 1].transform.position.z = _ET1;
  }
  while ( v9 - 20 < 4 );
  v15 = 0;
  for ( _EDI = 4; _EDI < 20; ++_EDI )
  {
    _ESI->primary_samples[_EDI].center_x = 0.0;
    _ESI->primary_samples[_EDI].rotation_scalar_98 = 0.0;
    _ESI->primary_samples[_EDI].rotation_scalar_94 = 0.0;
    _ESI->primary_samples[_EDI].special_scalar = 0.0;
    _ESI->primary_samples[_EDI].lateral_scale = 1.0;
    set_matrix_identity(&_ESI->primary_samples[_EDI].transform);
    _ESI->primary_samples[_EDI].transform.position.x = _ESI->primary_samples[_EDI].center_x;
    v98 = v15 + 4;
    _ESI->primary_samples[_EDI].transform.position.y = 0.49000001;
    __asm { fild    [esp+90h+var_6C] }
    v17 = _ESI->primary_samples;
    __asm
    {
      fst     [esp+90h+var_70]
      fmul    dword ptr [esi+50h]
      fstp    dword ptr [edi+ecx+38h]
    }
    v17[_EDI].transform.position.z = _ET1;
    set_matrix_identity(&_ESI->secondary_samples[_EDI].transform);
    __asm { fld     [esp+90h+var_70] }
    _ESI->secondary_samples[_EDI].transform.position.x = _ESI->primary_samples[_EDI].center_x;
    _ESI->secondary_samples[_EDI].transform.position.y = 0.49000001;
    v19 = _ESI->secondary_samples;
    __asm
    {
      fmul    dword ptr [esi+50h]
      fstp    dword ptr [eax+edi+38h]
    }
    v19[_EDI].transform.position.z = _ET1;
    if ( _EDI <= 4 )
    {
      set_matrix_rotation_identity(&_ESI->primary_samples[_EDI - 1].transform);
      set_matrix_rotation_identity(&_ESI->secondary_samples[_EDI - 1].transform);
    }
    else
    {
      p_x = (_DWORD *)&_ESI->primary_samples[_EDI - 1].transform.basis_up.x;
      *p_x = 0;
      p_x[1] = 1065353216;
      p_x[2] = 0;
      _ECX = _ESI->primary_samples;
      __asm
      {
        fld     dword ptr [edi+ecx+30h]
        fsub    dword ptr [edi+ecx-78h]
      }
      _EAX = &_ECX[_EDI - 1].transform.basis_forward.x;
      __asm
      {
        fstp    [esp+90h+var_54]
        fld     dword ptr [eax+0BCh]
        fsub    dword ptr [eax+14h]
      }
      __asm
      {
        fstp    [esp+90h+var_50]
        fld     dword ptr [eax+0C0h]
        fsub    dword ptr [eax+18h]
      }
      *_EAX = v106;
      _EAX[1] = v108;
      __asm { fstp    [esp+90h+var_4C] }
      _EAX[2] = v110;
      normalize_vector((Vec3 *)&_ESI->primary_samples[_EDI - 1].transform.basis_forward);
      __asm { fstp    st }
      cross_vectors(
        (Vec3 *)&_ESI->primary_samples[_EDI - 1],
        (Vec3 *)&_ESI->primary_samples[_EDI - 1].transform.basis_up,
        (Vec3 *)&_ESI->primary_samples[_EDI - 1].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&_ESI->primary_samples[_EDI - 1].transform.basis_up,
        (Vec3 *)&_ESI->primary_samples[_EDI - 1].transform.basis_forward,
        (Vec3 *)&_ESI->primary_samples[_EDI - 1]);
      v24 = (_DWORD *)&_ESI->secondary_samples[_EDI - 1].transform.basis_up.x;
      *v24 = 0;
      v24[1] = 1065353216;
      v24[2] = 0;
      _EAX = &_ESI->secondary_samples[_EDI].transform.basis_right.x;
      __asm
      {
        fld     dword ptr [eax+30h]
        fsub    dword ptr [eax-78h]
      }
      _EAX -= 34;
      __asm
      {
        fstp    [esp+90h+var_3C]
        fld     dword ptr [eax+0BCh]
        fsub    dword ptr [eax+14h]
      }
      __asm
      {
        fstp    [esp+90h+var_38]
        fld     dword ptr [eax+0C0h]
        fsub    dword ptr [eax+18h]
      }
      *_EAX = v118;
      _EAX[1] = v121;
      __asm { fstp    [esp+90h+var_34] }
      _EAX[2] = v124;
      normalize_vector((Vec3 *)&_ESI->secondary_samples[_EDI - 1].transform.basis_forward);
      __asm { fstp    st }
      cross_vectors(
        (Vec3 *)&_ESI->secondary_samples[_EDI - 1],
        (Vec3 *)&_ESI->secondary_samples[_EDI - 1].transform.basis_up,
        (Vec3 *)&_ESI->secondary_samples[_EDI - 1].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&_ESI->secondary_samples[_EDI - 1].transform.basis_up,
        (Vec3 *)&_ESI->secondary_samples[_EDI - 1].transform.basis_forward,
        (Vec3 *)&_ESI->secondary_samples[_EDI - 1]);
    }
    ++v15;
  }
  v26 = 0;
  if ( (signed int)(_ESI->segment_count - 1) > 0 )
  {
    _EDI = 0;
    do
    {
      _EAX = &_ESI->primary_samples[_EDI].transform.basis_right.x;
      __asm
      {
        fld     dword ptr [eax+0D8h]
        fsub    dword ptr [eax+30h]
      }
      _EAX += 32;
      __asm
      {
        fstp    [esp+90h+var_3C]
        fld     dword ptr [eax+5Ch]
        fsub    dword ptr [eax-4Ch]
      }
      __asm
      {
        fstp    [esp+90h+var_38]
        fld     dword ptr [eax+60h]
        fsub    dword ptr [eax-48h]
      }
      *_EAX = v119;
      _EAX[1] = v122;
      __asm { fstp    [esp+90h+var_34] }
      _EAX[2] = v125;
      normalize_vector(&_ESI->primary_samples[_EDI].delta_dir_to_next);
      v29 = _ESI->primary_samples;
      __asm { fstp    dword ptr [edi+eax+8Ch] }
      v29[_EDI].delta_length = _ET1;
      _ECX = _ESI->secondary_samples;
      __asm
      {
        fld     dword ptr [edi+ecx+0D8h]
        fsub    dword ptr [edi+ecx+30h]
      }
      _EAX = &_ECX[_EDI].delta_dir_to_next.x;
      __asm
      {
        fstp    [esp+90h+var_48]
        fld     dword ptr [eax+5Ch]
        fsub    dword ptr [eax-4Ch]
      }
      __asm
      {
        fstp    [esp+90h+var_44]
        fld     dword ptr [eax+60h]
        fsub    dword ptr [eax-48h]
      }
      *_EAX = v112;
      _EAX[1] = v114;
      __asm { fstp    [esp+90h+var_40] }
      _EAX[2] = v116;
      normalize_vector(&_ESI->secondary_samples[_EDI].delta_dir_to_next);
      v33 = _ESI->secondary_samples;
      ++v26;
      __asm { fstp    dword ptr [edi+ecx+8Ch] }
      v33[_EDI++].delta_length = _ET1;
    }
    while ( v26 < (signed int)(_ESI->segment_count - 1) );
  }
  v35 = (_DWORD *)&_ESI->primary_samples[_ESI->segment_count - 1].delta_dir_to_next.x;
  *v35 = 0;
  v35[1] = 0;
  v35[2] = 1065353216;
  _ESI->primary_samples[_ESI->segment_count - 1].delta_length = _ESI->width_or_scale;
  v36 = (_DWORD *)&_ESI->secondary_samples[_ESI->segment_count - 1].delta_dir_to_next.x;
  *v36 = 0;
  v36[1] = 0;
  v36[2] = 1065353216;
  _ESI->secondary_samples[_ESI->segment_count - 1].delta_length = _ESI->width_or_scale;
  strip_mesh = _ESI->strip_mesh;
  flags = strip_mesh->flags;
  LOBYTE(flags) = flags | 0x80;
  strip_mesh->flags = flags;
  request_object_vertices(_ESI->strip_mesh, _ESI->width_cells * (_ESI->segment_count + 1));
  request_object_facequads(_ESI->strip_mesh, 2 * _ESI->segment_count * _ESI->width_cells);
  request_object_vertex_colours(_ESI->strip_mesh);
  v39 = 0;
  v79 = 0;
  _ESI->strip_mesh->flags |= 0x10000u;
  v40 = _ESI->strip_mesh;
  _EBX = v40->vertices;
  facequads = v40->facequads;
  vertex_colours = v40->vertex_colours;
  segment_count = _ESI->segment_count;
  if ( segment_count >= 0 )
  {
    v83 = 0;
    while ( 1 )
    {
      __asm { fild    [esp+90h+var_80] }
      width_cells = _ESI->width_cells;
      v85 = 0;
      __asm
      {
        fmul    ds:flt_4972A0
        fidiv   [esp+90h+var_74]
      }
      v90 = width_cells;
      __asm { fstp    [esp+90h+var_6C] }
      if ( width_cells > 0 )
      {
        do
        {
          if ( v39 >= (signed int)_ESI->segment_count )
          {
            v77 = 0.0;
            v73 = 0.0;
            v72 = 0.0;
            v71 = 0.0;
            v47 = (_DWORD *)&_EBX[v3 + width_cells * (v39 - 1)].x;
            v48 = (_DWORD *)&_EBX[v3 + v39 * width_cells].x;
            *v48 = *v47;
            v48[1] = v47[1];
            v48[2] = v47[2];
            v49 = v39 * _ESI->width_cells;
            _ECX = 3 * (v3 + v49);
            __asm
            {
              fld     dword ptr [ebx+ecx*4+8]
              fadd    dword ptr [esi+50h]
            }
            p_z = &_EBX[v3 + v49].z;
            __asm { fstp    dword ptr [eax] }
            *p_z = _ET1;
          }
          else
          {
            _EAX = &_ESI->primary_samples[v83];
            __asm
            {
              fld     dword ptr [eax+9Ch]
              fmul    ds:flt_497210
              fst     [esp+94h+var_80]
              fmul    dword ptr [eax+10h]
              fstp    [esp+94h+var_3C]
              fld     [esp+94h+var_80]
              fmul    dword ptr [eax+14h]
              fstp    [esp+94h+var_38]
              fld     [esp+94h+var_80]
              fmul    dword ptr [eax+18h]
              fstp    [esp+94h+var_34]
              fild    [esp+94h+var_78]
              fstp    [esp+94h+var_78]
              fild    [esp+94h+var_74]
              fdivr   [esp+94h+var_78]
              fmul    ds:flt_4972A0
              fstp    [esp+94h+var_94]; float
            }
            cosine(v74);
            __asm
            {
              fld     [esp+94h+var_3C]
              fmul    st, st(1)
            }
            _EAX = &_ESI->primary_samples[v83];
            __asm
            {
              fstp    [esp+94h+var_54]
              fld     [esp+94h+var_38]
              fmul    st, st(1)
              fstp    [esp+94h+var_50]
              fld     [esp+94h+var_34]
              fmul    st, st(1)
              fstp    [esp+94h+var_4C]
              fstp    st
              fld     [esp+94h+var_80]
              fmul    dword ptr [eax]
              fstp    [esp+94h+var_48]
              fld     [esp+94h+var_80]
              fmul    dword ptr [eax+4]
              fstp    [esp+94h+var_44]
              fld     [esp+94h+var_80]
              fmul    dword ptr [eax+8]
              fstp    [esp+94h+var_40]
              fild    dword ptr [esi+54h]
              fdivr   [esp+94h+var_78]
              fmul    ds:flt_4972A0
              fstp    [esp+94h+var_94]; float
            }
            sine(v75);
            __asm
            {
              fld     [esp+94h+var_48]
              fmul    st, st(1)
            }
            _EAX = (int)&_ESI->primary_samples[v83].transform.position;
            __asm
            {
              fstp    [esp+94h+var_30]
              fld     [esp+94h+var_44]
              fmul    st, st(1)
              fstp    [esp+94h+var_2C]
              fmul    [esp+94h+var_40]
              fld     [esp+94h+var_30]
              fadd    dword ptr [eax]
              fld     [esp+94h+var_2C]
              fadd    dword ptr [eax+4]
              fstp    [esp+94h+var_20]
              fxch    st(1)
              fadd    dword ptr [eax+8]
            }
            v131 = v129;
            __asm { fstp    [esp+94h+var_1C] }
            __asm
            {
              fadd    [esp+94h+var_54]
              fld     [esp+94h+var_14]
              fadd    [esp+94h+var_50]
            }
            v132 = v130;
            __asm
            {
              fstp    [esp+94h+var_8]
              fld     [esp+94h+var_10]
              fadd    [esp+94h+var_4C]
              fstp    [esp+94h+var_4]
              fstp    [esp+94h+var_60]
            }
            __asm
            {
              fld     [esp+94h+var_6C]
              fadd    st, st
              fstp    [esp+94h+var_94]; float
            }
            v46 = &_EBX[v3 + v39 * _ESI->width_cells].x;
            *v46 = v105;
            v46[1] = v133;
            v46[2] = v134;
            cosine(v76);
            __asm
            {
              fmul    ds:flt_497228
              fsubr   ds:flt_497228
              fstp    [esp+94h+var_94]
            }
            v73 = 1.0;
            v72 = 1.0;
            v71 = 1.0;
          }
          store_color4f(&vertex_colours[v3 + v39 * _ESI->width_cells], v71, v72, v73, v77);
          _EAX = v3 + v39 * _ESI->width_cells;
          _EDX = 3 * _EAX;
          __asm
          {
            fld     dword ptr [ebx+edx*4+4]
            fcomp   ds:flt_497234
          }
          _ECX = &_EBX[_EAX].y;
          __asm { fnstsw  ax }
          if ( (_EAX & 0x100) != 0 )
          {
            __asm
            {
              fld     dword ptr [ecx]
              fmul    ds:flt_4973D8
              fstp    dword ptr [ecx]
            }
            *_ECX = _ET1;
          }
          width_cells = _ESI->width_cells;
          v85 = ++v3;
          v90 = width_cells;
        }
        while ( v3 < width_cells );
      }
      v79 = ++v39;
      ++v83;
      segment_count = _ESI->segment_count;
      if ( v39 > segment_count )
        break;
      v3 = 0;
    }
    v3 = 0;
  }
  v81 = 0;
  if ( (int)_ESI->segment_count > 0 )
  {
    do
    {
      v57 = 0;
      v87 = 0;
      if ( (int)_ESI->width_cells > 0 )
      {
        __asm { fild    [esp+90h+var_80] }
        v100 = v3 + 1;
        __asm
        {
          fmul    ds:flt_497428
          fstp    [esp+90h+var_80]
          fild    [esp+90h+var_6C]
          fmul    ds:flt_497428
          fstp    [esp+90h+var_74]
        }
        do
        {
          __asm { fild    [esp+90h+var_78] }
          v58 = v57 + 1;
          v59 = 0;
          v84 = v57 + 1;
          v97 = 0;
          __asm
          {
            fstp    [esp+90h+var_78]
            fild    [esp+90h+var_7C]
            fstp    [esp+90h+var_64]
          }
          while ( 1 )
          {
            v60 = (uint32_t)facequads + 96 * v57 + 96 * v3 * _ESI->width_cells + 48 * v59;
            *(_WORD *)v60 = 0;
            if ( v59 )
            {
              *(_WORD *)(v60 + 2) = LOWORD(_ESI->width_cells) * v3 + v58 % (signed int)_ESI->width_cells;
              *(_WORD *)(v60 + 4) = v57 + LOWORD(_ESI->width_cells) * v3;
              *(_WORD *)(v60 + 6) = v57 + LOWORD(_ESI->width_cells) * (v3 + 1);
              *(_WORD *)(v60 + 8) = LOWORD(_ESI->width_cells) * (v3 + 1) + v84 % (signed int)_ESI->width_cells;
            }
            else
            {
              *(_WORD *)(v60 + 2) = v57 + LOWORD(_ESI->width_cells) * v3;
              *(_WORD *)(v60 + 4) = LOWORD(_ESI->width_cells) * v3 + v58 % (signed int)_ESI->width_cells;
              *(_WORD *)(v60 + 6) = LOWORD(_ESI->width_cells) * (v3 + 1) + v84 % (signed int)_ESI->width_cells;
              *(_WORD *)(v60 + 8) = v57 + LOWORD(_ESI->width_cells) * (v3 + 1);
            }
            *(_DWORD *)(v60 + 12) = get_or_create_texture_ref((TextureRefList *)dword_4B7790, texture_path, 0, 0);
            v61 = v97;
            __asm { fild    dword ptr [esi+54h] }
            __asm
            {
              fstp    [esp+90h+var_6C]
              fld     [esp+90h+var_78]
              fdiv    [esp+90h+var_6C]
              fld     [esp+90h+var_64]
              fdiv    [esp+90h+var_6C]
              fst     [esp+90h+var_6C]
            }
            if ( v97 )
            {
              __asm { fstp    dword ptr [edi+10h] }
              *(float *)(v60 + 16) = _ET1;
              *(float *)(v60 + 20) = v82;
              __asm { fst     dword ptr [edi+18h] }
              *(float *)(v60 + 24) = _ET1;
              v63 = v91;
              *(float *)(v60 + 28) = v82;
              __asm { fstp    dword ptr [edi+20h] }
              *(float *)(v60 + 32) = _ET1;
              *(float *)(v60 + 36) = v91;
              *(float *)(v60 + 40) = v102;
            }
            else
            {
              __asm { fld     st(1) }
              __asm { fstp    dword ptr [edi+10h] }
              *(float *)(v60 + 16) = _ET1;
              *(float *)(v60 + 20) = v82;
              v63 = v91;
              __asm { fst     dword ptr [edi+18h] }
              *(float *)(v60 + 24) = _ET1;
              *(float *)(v60 + 28) = v82;
              __asm { fstp    dword ptr [edi+20h] }
              *(float *)(v60 + 32) = _ET1;
              *(float *)(v60 + 36) = v91;
              __asm { fstp    dword ptr [edi+28h] }
              *(float *)(v60 + 40) = _ET1;
            }
            *(float *)(v60 + 44) = v63;
            ++v97;
            if ( v61 + 1 >= 2 )
              break;
            v59 = v61 + 1;
            v58 = v57 + 1;
          }
          ++v57;
          v87 = v84;
        }
        while ( v84 < (signed int)_ESI->width_cells );
      }
      v81 = ++v3;
    }
    while ( v3 < (signed int)_ESI->segment_count );
  }
  return finalize_path_template_record(_ESI);
}

