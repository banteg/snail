/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_worm_path_template_pair @ 0x420170 */
/* selector: initialize_worm_path_template_pair */

int32_t __thiscall initialize_worm_path_template_pair(PathTemplate *self, char *texture_path)
{
  signed int v3; // ebp
  int v4; // edi
  double v5; // st7
  int v6; // ebx
  int v7; // edi
  double v8; // st7
  double v9; // st7
  int v10; // ebx
  int i; // edi
  double v12; // st7
  Vec4 *p_basis_up; // edx
  PathTemplateSample *primary_samples; // ecx
  float *p_x; // eax
  double v16; // st7
  Vec4 *v17; // ecx
  PathTemplateSample *v18; // eax
  double v19; // st7
  double v20; // st7
  signed int v21; // ebx
  int v22; // edi
  float *v23; // eax
  double v24; // st7
  double v25; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *v27; // eax
  double v28; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v30; // eax
  PathTemplateStripMesh *strip_mesh; // eax
  PathTemplateStripMeshFlags flags; // edx
  signed int v33; // edi
  PathTemplateStripMesh *v34; // eax
  Vec3 *vertices; // ebx
  signed int width_cells; // ecx
  double v37; // st7
  PathTemplateSample *v38; // eax
  double v39; // st7
  double v40; // st7
  PathTemplateSample *v41; // ecx
  double v42; // st7
  float *v43; // eax
  _DWORD *v44; // eax
  _DWORD *v45; // edx
  float *p_y; // ecx
  int v47; // ebx
  int v48; // eax
  int v49; // edx
  ObjectFaceQuad *v50; // edi
  int v51; // eax
  double v52; // st7
  double v53; // st6
  float v54; // ecx
  int v56; // [esp-Ch] [ebp-A0h]
  int v57; // [esp-8h] [ebp-9Ch]
  int v58; // [esp-4h] [ebp-98h]
  float v59; // [esp+0h] [ebp-94h]
  float v60; // [esp+0h] [ebp-94h]
  float v61; // [esp+0h] [ebp-94h]
  float v62; // [esp+0h] [ebp-94h]
  int v63; // [esp+14h] [ebp-80h]
  int v64; // [esp+14h] [ebp-80h]
  float v65; // [esp+14h] [ebp-80h]
  int v66; // [esp+14h] [ebp-80h]
  float v67; // [esp+14h] [ebp-80h]
  int v68; // [esp+18h] [ebp-7Ch]
  signed int v69; // [esp+18h] [ebp-7Ch]
  int v70; // [esp+1Ch] [ebp-78h]
  float v71; // [esp+1Ch] [ebp-78h]
  int v72; // [esp+1Ch] [ebp-78h]
  float v73; // [esp+1Ch] [ebp-78h]
  signed int segment_count; // [esp+20h] [ebp-74h]
  int v75; // [esp+20h] [ebp-74h]
  float v76; // [esp+20h] [ebp-74h]
  float v77; // [esp+24h] [ebp-70h]
  int v78; // [esp+24h] [ebp-70h]
  float v79; // [esp+24h] [ebp-70h]
  float v80; // [esp+24h] [ebp-70h]
  Color4f *vertex_colours; // [esp+24h] [ebp-70h]
  int v82; // [esp+24h] [ebp-70h]
  float v83; // [esp+28h] [ebp-6Ch]
  float v84; // [esp+28h] [ebp-6Ch]
  float v85; // [esp+28h] [ebp-6Ch]
  ObjectFaceQuad *facequads; // [esp+2Ch] [ebp-68h]
  float v87; // [esp+30h] [ebp-64h]
  float v88; // [esp+34h] [ebp-60h]
  float v89; // [esp+40h] [ebp-54h]
  float v90; // [esp+40h] [ebp-54h]
  float v91; // [esp+44h] [ebp-50h]
  float v92; // [esp+44h] [ebp-50h]
  float v93; // [esp+48h] [ebp-4Ch]
  float v94; // [esp+48h] [ebp-4Ch]
  float v95; // [esp+4Ch] [ebp-48h]
  float v96; // [esp+4Ch] [ebp-48h]
  float v97; // [esp+50h] [ebp-44h]
  float v98; // [esp+50h] [ebp-44h]
  float v99; // [esp+54h] [ebp-40h]
  float v100; // [esp+54h] [ebp-40h]
  float v101; // [esp+58h] [ebp-3Ch]
  float v102; // [esp+58h] [ebp-3Ch]
  float v103; // [esp+58h] [ebp-3Ch]
  float v104; // [esp+5Ch] [ebp-38h]
  float v105; // [esp+5Ch] [ebp-38h]
  float v106; // [esp+5Ch] [ebp-38h]
  float v107; // [esp+60h] [ebp-34h]
  float v108; // [esp+60h] [ebp-34h]
  float v109; // [esp+60h] [ebp-34h]
  float v110; // [esp+64h] [ebp-30h]
  float v111; // [esp+68h] [ebp-2Ch]
  float v112; // [esp+74h] [ebp-20h]
  float v113; // [esp+78h] [ebp-1Ch]
  float v114; // [esp+8Ch] [ebp-8h]
  float v115; // [esp+90h] [ebp-4h]

  v3 = 0;
  self->kind = 24;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = 16;
  self->width_or_scale = 4.0;
  self->segment_count = 24;
  self->segment_count_f = 96.0;
  allocate_path_nodes(self);
  self->special_runtime_flag_9c = 0;
  v63 = 0;
  v4 = 0;
  do
  {
    self->primary_samples[v4].center_x = 0.0;
    self->primary_samples[v4].rotation_scalar_98 = 0.0;
    self->primary_samples[v4].rotation_scalar_94 = 0.0;
    self->primary_samples[v4].special_scalar = 0.0;
    self->primary_samples[v4].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v4].transform);
    v5 = (double)v63;
    v77 = v5;
    self->primary_samples[v4].transform.position.x = self->primary_samples[v4].center_x;
    self->primary_samples[v4].transform.position.y = 0.49000001;
    self->primary_samples[v4].transform.position.z = v5 * self->width_or_scale;
    set_matrix_identity(&self->secondary_samples[v4].transform);
    self->secondary_samples[v4].transform.position.x = self->primary_samples[v4].center_x;
    self->secondary_samples[v4++].transform.position.y = 0.49000001;
    self->secondary_samples[v4 - 1].transform.position.z = v77 * self->width_or_scale;
    ++v63;
  }
  while ( v4 < 4 );
  v6 = 20;
  v7 = 20;
  v78 = 20;
  do
  {
    self->primary_samples[v7].center_x = 0.0;
    self->primary_samples[v7].rotation_scalar_98 = 0.0;
    self->primary_samples[v7].rotation_scalar_94 = 0.0;
    self->primary_samples[v7].special_scalar = 0.0;
    self->primary_samples[v7].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v7].transform);
    v8 = (double)v78;
    v79 = v8;
    self->primary_samples[v7].transform.position.x = self->primary_samples[v7].center_x;
    self->primary_samples[v7].transform.position.y = 0.49000001;
    self->primary_samples[v7].transform.position.z = v8 * self->width_or_scale;
    set_matrix_identity(&self->secondary_samples[v7].transform);
    self->secondary_samples[v7].transform.position.x = self->primary_samples[v7].center_x;
    self->secondary_samples[v7].transform.position.y = 0.49000001;
    v9 = v79 * self->width_or_scale;
    ++v7;
    v78 = ++v6;
    self->secondary_samples[v7 - 1].transform.position.z = v9;
  }
  while ( v6 - 20 < 4 );
  v10 = 0;
  for ( i = 4; i < 20; ++i )
  {
    self->primary_samples[i].center_x = 0.0;
    self->primary_samples[i].rotation_scalar_98 = 0.0;
    self->primary_samples[i].rotation_scalar_94 = 0.0;
    self->primary_samples[i].special_scalar = 0.0;
    self->primary_samples[i].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[i].transform);
    self->primary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->primary_samples[i].transform.position.y = 0.49000001;
    v12 = (double)(v10 + 4);
    v80 = v12;
    self->primary_samples[i].transform.position.z = v12 * self->width_or_scale;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->secondary_samples[i].transform.position.y = 0.49000001;
    self->secondary_samples[i].transform.position.z = v80 * self->width_or_scale;
    if ( i <= 4 )
    {
      set_matrix_rotation_identity(&self->primary_samples[i - 1].transform);
      set_matrix_rotation_identity(&self->secondary_samples[i - 1].transform);
    }
    else
    {
      p_basis_up = &self->primary_samples[i - 1].transform.basis_up;
      p_basis_up->x = 0.0;
      p_basis_up->y = 1.0;
      p_basis_up->z = 0.0;
      primary_samples = self->primary_samples;
      p_x = &primary_samples[i - 1].transform.basis_forward.x;
      v89 = primary_samples[i].transform.position.x - primary_samples[i - 1].transform.position.x;
      v91 = p_x[47] - p_x[5];
      v16 = p_x[48] - p_x[6];
      *p_x = v89;
      p_x[1] = v91;
      v93 = v16;
      p_x[2] = v93;
      normalize_vector((Vec3 *)&self->primary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&self->primary_samples[i - 1],
        (Vec3 *)&self->primary_samples[i - 1].transform.basis_up,
        (Vec3 *)&self->primary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&self->primary_samples[i - 1].transform.basis_up,
        (Vec3 *)&self->primary_samples[i - 1].transform.basis_forward,
        (Vec3 *)&self->primary_samples[i - 1]);
      v17 = &self->secondary_samples[i - 1].transform.basis_up;
      v17->x = 0.0;
      v17->y = 1.0;
      v17->z = 0.0;
      v18 = &self->secondary_samples[i];
      v19 = v18->transform.position.x - v18[-1].transform.position.x;
      v18 = (PathTemplateSample *)((char *)v18 - 136);
      v101 = v19;
      v104 = v18[1].transform.basis_up.y - v18->transform.basis_up.y;
      v20 = v18[1].transform.basis_up.z - v18->transform.basis_up.z;
      v18->transform.basis_right.x = v101;
      v18->transform.basis_right.y = v104;
      v107 = v20;
      v18->transform.basis_right.z = v107;
      normalize_vector((Vec3 *)&self->secondary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&self->secondary_samples[i - 1],
        (Vec3 *)&self->secondary_samples[i - 1].transform.basis_up,
        (Vec3 *)&self->secondary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&self->secondary_samples[i - 1].transform.basis_up,
        (Vec3 *)&self->secondary_samples[i - 1].transform.basis_forward,
        (Vec3 *)&self->secondary_samples[i - 1]);
    }
    ++v10;
  }
  v21 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v22 = 0;
    do
    {
      v23 = &self->primary_samples[v22].transform.basis_right.x;
      v24 = v23[54] - v23[12];
      v23 += 32;
      v102 = v24;
      v105 = v23[23] - *(v23 - 19);
      v25 = v23[24] - *(v23 - 18);
      *v23 = v102;
      v23[1] = v105;
      v108 = v25;
      v23[2] = v108;
      self->primary_samples[v22].delta_length = normalize_vector(&self->primary_samples[v22].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v27 = &secondary_samples[v22].delta_dir_to_next.x;
      v95 = secondary_samples[v22 + 1].transform.position.x - secondary_samples[v22].transform.position.x;
      v97 = secondary_samples[v22 + 1].transform.position.y - secondary_samples[v22].transform.position.y;
      v28 = secondary_samples[v22 + 1].transform.position.z - secondary_samples[v22].transform.position.z;
      *v27 = v95;
      v27[1] = v97;
      v99 = v28;
      v27[2] = v99;
      ++v21;
      self->secondary_samples[v22].delta_length = normalize_vector(&self->secondary_samples[v22].delta_dir_to_next);
      ++v22;
    }
    while ( v21 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = self->width_or_scale;
  v30 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v30->x = 0.0;
  v30->y = 0.0;
  v30->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = self->width_or_scale;
  strip_mesh = self->strip_mesh;
  flags = strip_mesh->flags;
  LOBYTE(flags) = flags | 0x80;
  strip_mesh->flags = flags;
  request_object_vertices(self->strip_mesh, self->width_cells * (self->segment_count + 1));
  request_object_facequads(self->strip_mesh, 2 * self->segment_count * self->width_cells);
  request_object_vertex_colours(self->strip_mesh);
  v33 = 0;
  v64 = 0;
  self->strip_mesh->flags |= 0x10000u;
  v34 = self->strip_mesh;
  vertices = v34->vertices;
  facequads = v34->facequads;
  vertex_colours = v34->vertex_colours;
  segment_count = self->segment_count;
  if ( segment_count >= 0 )
  {
    v68 = 0;
    while ( 1 )
    {
      width_cells = self->width_cells;
      v70 = 0;
      v37 = (double)v64 * 6.2831855 / (double)segment_count;
      v75 = width_cells;
      v83 = v37;
      if ( width_cells > 0 )
      {
        do
        {
          if ( v33 >= (signed int)self->segment_count )
          {
            v62 = 0.0;
            v58 = 0;
            v57 = 0;
            v56 = 0;
            v44 = (_DWORD *)&vertices[v3 + width_cells * (v33 - 1)].x;
            v45 = (_DWORD *)&vertices[v3 + v33 * width_cells].x;
            *v45 = *v44;
            v45[1] = v44[1];
            v45[2] = v44[2];
            vertices[v3 + v33 * self->width_cells].z = vertices[v3 + v33 * self->width_cells].z + self->width_or_scale;
          }
          else
          {
            v38 = &self->primary_samples[v68];
            v39 = v38->lateral_scale * 4.0;
            v65 = v39;
            v103 = v39 * v38->transform.basis_up.x;
            v106 = v65 * v38->transform.basis_up.y;
            v109 = v65 * v38->transform.basis_up.z;
            v71 = (float)v70;
            v59 = v71 / (double)v75 * 6.2831855;
            v40 = cosine(v59);
            v41 = self->primary_samples;
            v90 = v103 * v40;
            v92 = v106 * v40;
            v94 = v109 * v40;
            v96 = v65 * v41[v68].transform.basis_right.x;
            v98 = v65 * v41[v68].transform.basis_right.y;
            v100 = v65 * v41[v68].transform.basis_right.z;
            v60 = v71 / (double)(int)self->width_cells * 6.2831855;
            v42 = sine(v60);
            v110 = v96 * v42;
            v111 = v98 * v42;
            v112 = v111 + self->primary_samples[v68].transform.position.y;
            v113 = v42 * v100 + self->primary_samples[v68].transform.position.z;
            v114 = v112 + v92;
            v115 = v113 + v94;
            v88 = v110 + self->primary_samples[v68].transform.position.x + v90;
            v61 = v83 + v83;
            v43 = &vertices[v3 + v33 * self->width_cells].x;
            *v43 = v88;
            v43[1] = v114;
            v43[2] = v115;
            v62 = 0.5 - cosine(v61) * 0.5;
            v58 = 1065353216;
            v57 = 1065353216;
            v56 = 1065353216;
          }
          sub_44DBB0(&vertex_colours[v3 + v33 * self->width_cells].r, v56, v57, v58, SLODWORD(v62));
          p_y = &vertices[v3 + v33 * self->width_cells].y;
          if ( *p_y < 0.0 )
            *p_y = *p_y * 0.30000001;
          width_cells = self->width_cells;
          v70 = ++v3;
          v75 = width_cells;
        }
        while ( v3 < width_cells );
      }
      v64 = ++v33;
      ++v68;
      segment_count = self->segment_count;
      if ( v33 > segment_count )
        break;
      v3 = 0;
    }
    v3 = 0;
  }
  v66 = 0;
  if ( (int)self->segment_count > 0 )
  {
    do
    {
      v47 = 0;
      v72 = 0;
      if ( (int)self->width_cells > 0 )
      {
        v67 = (double)v66 * 0.125;
        v76 = (double)(v3 + 1) * 0.125;
        do
        {
          v48 = v47 + 1;
          v49 = 0;
          v69 = v47 + 1;
          v82 = 0;
          v73 = (float)v72;
          while ( 1 )
          {
            v50 = &facequads[2 * v47 + 2 * v3 * self->width_cells + v49];
            v50->flags = 0;
            if ( v49 )
            {
              v50->vertex_index_a = LOWORD(self->width_cells) * v3 + v48 % (signed int)self->width_cells;
              v50->vertex_index_b = v47 + LOWORD(self->width_cells) * v3;
              v50->vertex_index_c = v47 + LOWORD(self->width_cells) * (v3 + 1);
              v50->vertex_index_d = LOWORD(self->width_cells) * (v3 + 1) + v69 % (signed int)self->width_cells;
            }
            else
            {
              v50->vertex_index_a = v47 + LOWORD(self->width_cells) * v3;
              v50->vertex_index_b = LOWORD(self->width_cells) * v3 + v48 % (signed int)self->width_cells;
              v50->vertex_index_c = LOWORD(self->width_cells) * (v3 + 1) + v69 % (signed int)self->width_cells;
              v50->vertex_index_d = v47 + LOWORD(self->width_cells) * (v3 + 1);
            }
            v50->texture_ref = get_or_create_texture_ref(dword_4B7790, texture_path, 0, 0);
            v51 = v82;
            v84 = (float)(int)self->width_cells;
            v52 = v73 / v84;
            v87 = (float)(v47 + 1);
            v53 = v87 / v84;
            if ( v82 )
            {
              v50->u0 = v53;
              v50->v0 = v67;
              v50->u1 = v52;
              v54 = (double)(v3 + 1) * 0.125;
              v50->v1 = v67;
              v50->u2 = v52;
              v50->v2 = v76;
              v85 = v53;
              v50->u3 = v85;
            }
            else
            {
              v50->u0 = v52;
              v50->v0 = v67;
              v54 = (double)(v3 + 1) * 0.125;
              v50->u1 = v53;
              v50->v1 = v67;
              v50->u2 = v53;
              v50->v2 = v76;
              v50->u3 = v52;
            }
            v50->v3 = v54;
            ++v82;
            if ( v51 + 1 >= 2 )
              break;
            v49 = v51 + 1;
            v48 = v47 + 1;
          }
          ++v47;
          v72 = v69;
        }
        while ( v69 < (signed int)self->width_cells );
      }
      v66 = ++v3;
    }
    while ( v3 < (signed int)self->segment_count );
  }
  return finalize_path_template_record(self);
}

