/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_worm_path_template_pair @ 0x420170 */
/* selector: initialize_worm_path_template_pair */

// Builds the Worm attachment path template; iOS Path.o names this `cRPath::BuildWorm(char*)`.
void __thiscall initialize_worm_path_template_pair(Path *self, char *texture_path)
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
  Vec3 *p_basis_up; // edx
  PathTemplateSample *primary_samples; // ecx
  float *p_x; // eax
  double v16; // st7
  Vec3 *v17; // ecx
  PathTemplateSample *v18; // eax
  double v19; // st7
  double v20; // st7
  signed int v21; // ebx
  int v22; // edi
  PathTemplateSample *v23; // eax
  double v24; // st7
  double v25; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *v27; // eax
  double v28; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v30; // eax
  Object *object; // eax
  ObjectFlag flags; // edx
  signed int v33; // edi
  Object *v34; // eax
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
  float v55; // [esp-Ch] [ebp-A0h]
  float v56; // [esp-8h] [ebp-9Ch]
  float v57; // [esp-4h] [ebp-98h]
  float v58; // [esp+0h] [ebp-94h]
  float v59; // [esp+0h] [ebp-94h]
  float v60; // [esp+0h] [ebp-94h]
  float v61; // [esp+0h] [ebp-94h]
  int v62; // [esp+14h] [ebp-80h]
  int v63; // [esp+14h] [ebp-80h]
  float v64; // [esp+14h] [ebp-80h]
  int v65; // [esp+14h] [ebp-80h]
  float v66; // [esp+14h] [ebp-80h]
  int v67; // [esp+18h] [ebp-7Ch]
  signed int v68; // [esp+18h] [ebp-7Ch]
  int v69; // [esp+1Ch] [ebp-78h]
  float v70; // [esp+1Ch] [ebp-78h]
  int v71; // [esp+1Ch] [ebp-78h]
  float v72; // [esp+1Ch] [ebp-78h]
  signed int segment_count; // [esp+20h] [ebp-74h]
  int v74; // [esp+20h] [ebp-74h]
  float v75; // [esp+20h] [ebp-74h]
  float v76; // [esp+24h] [ebp-70h]
  int v77; // [esp+24h] [ebp-70h]
  float v78; // [esp+24h] [ebp-70h]
  float v79; // [esp+24h] [ebp-70h]
  tColour *vertex_colours; // [esp+24h] [ebp-70h]
  int v81; // [esp+24h] [ebp-70h]
  float v82; // [esp+28h] [ebp-6Ch]
  float v83; // [esp+28h] [ebp-6Ch]
  float v84; // [esp+28h] [ebp-6Ch]
  ObjectFaceQuad *facequads; // [esp+2Ch] [ebp-68h]
  float v86; // [esp+30h] [ebp-64h]
  float v87; // [esp+34h] [ebp-60h]
  float v88; // [esp+40h] [ebp-54h]
  float v89; // [esp+40h] [ebp-54h]
  float v90; // [esp+44h] [ebp-50h]
  float v91; // [esp+44h] [ebp-50h]
  float v92; // [esp+48h] [ebp-4Ch]
  float v93; // [esp+48h] [ebp-4Ch]
  float v94; // [esp+4Ch] [ebp-48h]
  float v95; // [esp+4Ch] [ebp-48h]
  float v96; // [esp+50h] [ebp-44h]
  float v97; // [esp+50h] [ebp-44h]
  float v98; // [esp+54h] [ebp-40h]
  float v99; // [esp+54h] [ebp-40h]
  float v100; // [esp+58h] [ebp-3Ch]
  float v101; // [esp+58h] [ebp-3Ch]
  float v102; // [esp+58h] [ebp-3Ch]
  float v103; // [esp+5Ch] [ebp-38h]
  float v104; // [esp+5Ch] [ebp-38h]
  float v105; // [esp+5Ch] [ebp-38h]
  float v106; // [esp+60h] [ebp-34h]
  float v107; // [esp+60h] [ebp-34h]
  float v108; // [esp+60h] [ebp-34h]
  float v109; // [esp+64h] [ebp-30h]
  float v110; // [esp+68h] [ebp-2Ch]
  float v111; // [esp+74h] [ebp-20h]
  float v112; // [esp+78h] [ebp-1Ch]
  float v113; // [esp+8Ch] [ebp-8h]
  float v114; // [esp+90h] [ebp-4h]

  v3 = 0;
  self->kind = PATH_TEMPLATE_KIND_WORM;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = 16;
  self->width_or_scale = 4.0;
  self->segment_count = 24;
  self->segment_count_f = 96.0;
  get_path_nodes(self);
  self->has_entry_mesh_transition = 0;
  v62 = 0;
  v4 = 0;
  do
  {
    self->primary_samples[v4].center_x = 0.0;
    self->primary_samples[v4].rotation_scalar_98 = 0.0;
    self->primary_samples[v4].rotation_scalar_94 = 0.0;
    self->primary_samples[v4].special_scalar = 0.0;
    self->primary_samples[v4].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v4].transform);
    v5 = (double)v62;
    v76 = v5;
    self->primary_samples[v4].transform.position.x = self->primary_samples[v4].center_x;
    self->primary_samples[v4].transform.position.y = 0.49000001;
    self->primary_samples[v4].transform.position.z = v5 * self->width_or_scale;
    set_matrix_identity(&self->secondary_samples[v4].transform);
    self->secondary_samples[v4].transform.position.x = self->primary_samples[v4].center_x;
    self->secondary_samples[v4++].transform.position.y = 0.49000001;
    self->secondary_samples[v4 - 1].transform.position.z = v76 * self->width_or_scale;
    ++v62;
  }
  while ( v4 < 4 );
  v6 = 20;
  v7 = 20;
  v77 = 20;
  do
  {
    self->primary_samples[v7].center_x = 0.0;
    self->primary_samples[v7].rotation_scalar_98 = 0.0;
    self->primary_samples[v7].rotation_scalar_94 = 0.0;
    self->primary_samples[v7].special_scalar = 0.0;
    self->primary_samples[v7].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v7].transform);
    v8 = (double)v77;
    v78 = v8;
    self->primary_samples[v7].transform.position.x = self->primary_samples[v7].center_x;
    self->primary_samples[v7].transform.position.y = 0.49000001;
    self->primary_samples[v7].transform.position.z = v8 * self->width_or_scale;
    set_matrix_identity(&self->secondary_samples[v7].transform);
    self->secondary_samples[v7].transform.position.x = self->primary_samples[v7].center_x;
    self->secondary_samples[v7].transform.position.y = 0.49000001;
    v9 = v78 * self->width_or_scale;
    ++v7;
    v77 = ++v6;
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
    v79 = v12;
    self->primary_samples[i].transform.position.z = v12 * self->width_or_scale;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->secondary_samples[i].transform.position.y = 0.49000001;
    self->secondary_samples[i].transform.position.z = v79 * self->width_or_scale;
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
      v88 = primary_samples[i].transform.position.x - primary_samples[i - 1].transform.position.x;
      v90 = p_x[47] - p_x[5];
      v16 = p_x[48] - p_x[6];
      *p_x = v88;
      p_x[1] = v90;
      v92 = v16;
      p_x[2] = v92;
      normalize_vector(&self->primary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        &self->primary_samples[i - 1].transform.basis_right,
        &self->primary_samples[i - 1].transform.basis_up,
        &self->primary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        &self->primary_samples[i - 1].transform.basis_up,
        &self->primary_samples[i - 1].transform.basis_forward,
        &self->primary_samples[i - 1].transform.basis_right);
      v17 = &self->secondary_samples[i - 1].transform.basis_up;
      v17->x = 0.0;
      v17->y = 1.0;
      v17->z = 0.0;
      v18 = &self->secondary_samples[i];
      v19 = v18->transform.position.x - v18[-1].transform.position.x;
      v18 = (PathTemplateSample *)((char *)v18 - 136);
      v100 = v19;
      v103 = v18[1].transform.basis_up.y - v18->transform.basis_up.y;
      v20 = v18[1].transform.basis_up.z - v18->transform.basis_up.z;
      v18->transform.basis_right.x = v100;
      v18->transform.basis_right.y = v103;
      v106 = v20;
      v18->transform.basis_right.z = v106;
      normalize_vector(&self->secondary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        &self->secondary_samples[i - 1].transform.basis_right,
        &self->secondary_samples[i - 1].transform.basis_up,
        &self->secondary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        &self->secondary_samples[i - 1].transform.basis_up,
        &self->secondary_samples[i - 1].transform.basis_forward,
        &self->secondary_samples[i - 1].transform.basis_right);
    }
    ++v10;
  }
  v21 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v22 = 0;
    do
    {
      v23 = &self->primary_samples[v22];
      v24 = v23[1].transform.position.x - v23->transform.position.x;
      v23 = (PathTemplateSample *)((char *)v23 + 128);
      v101 = v24;
      v104 = v23->inverse_matrix.basis_up_w - v23[-1].inverse_matrix.basis_up_w;
      v25 = v23->inverse_matrix.basis_forward.x - v23[-1].inverse_matrix.basis_forward.x;
      v23->transform.basis_right.x = v101;
      v23->transform.basis_right.y = v104;
      v107 = v25;
      v23->transform.basis_right.z = v107;
      self->primary_samples[v22].delta_length = normalize_vector(&self->primary_samples[v22].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v27 = &secondary_samples[v22].delta_dir_to_next.x;
      v94 = secondary_samples[v22 + 1].transform.position.x - secondary_samples[v22].transform.position.x;
      v96 = secondary_samples[v22 + 1].transform.position.y - secondary_samples[v22].transform.position.y;
      v28 = secondary_samples[v22 + 1].transform.position.z - secondary_samples[v22].transform.position.z;
      *v27 = v94;
      v27[1] = v96;
      v98 = v28;
      v27[2] = v98;
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
  object = self->bod.object;
  flags = object->flags;
  LOBYTE(flags) = flags | 0x80;
  object->flags = flags;
  request_object_vertices(self->bod.object, self->width_cells * (self->segment_count + 1));
  request_object_facequads(self->bod.object, 2 * self->segment_count * self->width_cells);
  request_object_vertex_colours(self->bod.object);
  v33 = 0;
  v63 = 0;
  self->bod.object->flags |= 0x10000u;
  v34 = self->bod.object;
  vertices = v34->vertices;
  facequads = v34->facequads;
  vertex_colours = v34->vertex_colours;
  segment_count = self->segment_count;
  if ( segment_count >= 0 )
  {
    v67 = 0;
    while ( 1 )
    {
      width_cells = self->width_cells;
      v69 = 0;
      v37 = (double)v63 * 6.2831855 / (double)segment_count;
      v74 = width_cells;
      v82 = v37;
      if ( width_cells > 0 )
      {
        do
        {
          if ( v33 >= (signed int)self->segment_count )
          {
            v61 = 0.0;
            v57 = 0.0;
            v56 = 0.0;
            v55 = 0.0;
            v44 = (_DWORD *)&vertices[v3 + width_cells * (v33 - 1)].x;
            v45 = (_DWORD *)&vertices[v3 + v33 * width_cells].x;
            *v45 = *v44;
            v45[1] = v44[1];
            v45[2] = v44[2];
            vertices[v3 + v33 * self->width_cells].z = vertices[v3 + v33 * self->width_cells].z + self->width_or_scale;
          }
          else
          {
            v38 = &self->primary_samples[v67];
            v39 = v38->lateral_scale * 4.0;
            v64 = v39;
            v102 = v39 * v38->transform.basis_up.x;
            v105 = v64 * v38->transform.basis_up.y;
            v108 = v64 * v38->transform.basis_up.z;
            v70 = (float)v69;
            v58 = v70 / (double)v74 * 6.2831855;
            v40 = cosine(v58);
            v41 = self->primary_samples;
            v89 = v102 * v40;
            v91 = v105 * v40;
            v93 = v108 * v40;
            v95 = v64 * v41[v67].transform.basis_right.x;
            v97 = v64 * v41[v67].transform.basis_right.y;
            v99 = v64 * v41[v67].transform.basis_right.z;
            v59 = v70 / (double)(int)self->width_cells * 6.2831855;
            v42 = sine(v59);
            v109 = v95 * v42;
            v110 = v97 * v42;
            v111 = v110 + self->primary_samples[v67].transform.position.y;
            v112 = v42 * v99 + self->primary_samples[v67].transform.position.z;
            v113 = v111 + v91;
            v114 = v112 + v93;
            v87 = v109 + self->primary_samples[v67].transform.position.x + v89;
            v60 = v82 + v82;
            v43 = &vertices[v3 + v33 * self->width_cells].x;
            *v43 = v87;
            v43[1] = v113;
            v43[2] = v114;
            v61 = 0.5 - cosine(v60) * 0.5;
            v57 = 1.0;
            v56 = 1.0;
            v55 = 1.0;
          }
          store_color4f(&vertex_colours[v3 + v33 * self->width_cells], v55, v56, v57, v61);
          p_y = &vertices[v3 + v33 * self->width_cells].y;
          if ( *p_y < 0.0 )
            *p_y = *p_y * 0.30000001;
          width_cells = self->width_cells;
          v69 = ++v3;
          v74 = width_cells;
        }
        while ( v3 < width_cells );
      }
      v63 = ++v33;
      ++v67;
      segment_count = self->segment_count;
      if ( v33 > segment_count )
        break;
      v3 = 0;
    }
    v3 = 0;
  }
  v65 = 0;
  if ( (int)self->segment_count > 0 )
  {
    do
    {
      v47 = 0;
      v71 = 0;
      if ( (int)self->width_cells > 0 )
      {
        v66 = (double)v65 * 0.125;
        v75 = (double)(v3 + 1) * 0.125;
        do
        {
          v48 = v47 + 1;
          v49 = 0;
          v68 = v47 + 1;
          v81 = 0;
          v72 = (float)v71;
          while ( 1 )
          {
            v50 = &facequads[2 * v47 + 2 * v3 * self->width_cells + v49];
            v50->header_word = 0;
            if ( v49 != 0 )
            {
              v50->vertex_0 = LOWORD(self->width_cells) * v3 + v48 % (signed int)self->width_cells;
              v50->vertex_1 = v47 + LOWORD(self->width_cells) * v3;
              v50->vertex_2 = v47 + LOWORD(self->width_cells) * (v3 + 1);
              v50->vertex_3 = LOWORD(self->width_cells) * (v3 + 1) + v68 % (signed int)self->width_cells;
            }
            else
            {
              v50->vertex_0 = v47 + LOWORD(self->width_cells) * v3;
              v50->vertex_1 = LOWORD(self->width_cells) * v3 + v48 % (signed int)self->width_cells;
              v50->vertex_2 = LOWORD(self->width_cells) * (v3 + 1) + v68 % (signed int)self->width_cells;
              v50->vertex_3 = v47 + LOWORD(self->width_cells) * (v3 + 1);
            }
            v50->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0);
            v51 = v81;
            v83 = (float)(int)self->width_cells;
            v52 = v72 / v83;
            v86 = (float)(v47 + 1);
            v53 = v86 / v83;
            if ( v81 != 0 )
            {
              v50->uv[0].u = v53;
              v50->uv[0].v = v66;
              v50->uv[1].u = v52;
              v54 = (double)(v3 + 1) * 0.125;
              v50->uv[1].v = v66;
              v50->uv[2].u = v52;
              v50->uv[2].v = v75;
              v84 = v53;
              v50->uv[3].u = v84;
            }
            else
            {
              v50->uv[0].u = v52;
              v50->uv[0].v = v66;
              v54 = (double)(v3 + 1) * 0.125;
              v50->uv[1].u = v53;
              v50->uv[1].v = v66;
              v50->uv[2].u = v53;
              v50->uv[2].v = v75;
              v50->uv[3].u = v52;
            }
            v50->uv[3].v = v54;
            ++v81;
            if ( v51 + 1 >= 2 )
              break;
            v49 = v51 + 1;
            v48 = v47 + 1;
          }
          ++v47;
          v71 = v68;
        }
        while ( v68 < (signed int)self->width_cells );
      }
      v65 = ++v3;
    }
    while ( v3 < (signed int)self->segment_count );
  }
  calc_path_length_z(self);
}
