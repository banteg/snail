/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_dip_path_template_pair @ 0x425050 */
/* selector: initialize_dip_path_template_pair */

int32_t __thiscall initialize_dip_path_template_pair(
        PathTemplate *self,
        int32_t arg2,
        char *texture_a,
        char *texture_b)
{
  signed int v5; // ebx
  int i; // edi
  int v7; // ebp
  int v8; // edi
  int v9; // ebp
  int v10; // edi
  double v11; // st7
  double v12; // st7
  Vec4 *p_basis_up; // ecx
  PathTemplateSample *v14; // eax
  double v15; // st7
  double v16; // st7
  PathTemplateSample *v17; // eax
  Vec4 *v18; // edx
  PathTemplateSample *secondary_samples; // ecx
  float *p_x; // eax
  double v21; // st7
  signed int v22; // ebp
  int v23; // edi
  PathTemplateSample *primary_samples; // ecx
  float *v25; // eax
  double v26; // st7
  PathTemplateSample *v27; // edx
  float *v28; // eax
  double v29; // st7
  Vec3 *p_delta_dir_to_next; // ecx
  Vec3 *v31; // eax
  PathTemplateStripMesh *strip_mesh; // eax
  Vec3 *vertices; // ebp
  signed int v34; // edx
  signed int width_cells; // ecx
  char *v36; // edi
  double v37; // st7
  float *v38; // eax
  float *v39; // eax
  float v40; // ecx
  double v41; // st7
  int v42; // ebp
  int v43; // ecx
  uint32_t v44; // edi
  float v46; // [esp+0h] [ebp-68h]
  float v47; // [esp+0h] [ebp-68h]
  float v48; // [esp+0h] [ebp-68h]
  float v49; // [esp+14h] [ebp-54h]
  float v50; // [esp+18h] [ebp-50h]
  float v51; // [esp+1Ch] [ebp-4Ch]
  int j; // [esp+1Ch] [ebp-4Ch]
  float v53; // [esp+1Ch] [ebp-4Ch]
  float v54; // [esp+20h] [ebp-48h]
  int v55; // [esp+20h] [ebp-48h]
  float v56; // [esp+24h] [ebp-44h]
  Vec3 *v57; // [esp+24h] [ebp-44h]
  signed int v58; // [esp+24h] [ebp-44h]
  ObjectFaceQuad *facequads; // [esp+28h] [ebp-40h]
  float v60; // [esp+2Ch] [ebp-3Ch]
  float v61; // [esp+30h] [ebp-38h]
  float v62; // [esp+38h] [ebp-30h]
  float v63; // [esp+38h] [ebp-30h]
  float v64; // [esp+3Ch] [ebp-2Ch]
  float v65; // [esp+3Ch] [ebp-2Ch]
  float v66; // [esp+40h] [ebp-28h]
  float v67; // [esp+44h] [ebp-24h]
  float v68; // [esp+44h] [ebp-24h]
  float v69; // [esp+48h] [ebp-20h]
  float v70; // [esp+48h] [ebp-20h]
  float v71; // [esp+4Ch] [ebp-1Ch]
  float v72; // [esp+4Ch] [ebp-1Ch]
  float v73; // [esp+50h] [ebp-18h]
  float v74; // [esp+50h] [ebp-18h]
  float v75; // [esp+50h] [ebp-18h]
  float v76; // [esp+54h] [ebp-14h]
  float v77; // [esp+54h] [ebp-14h]
  float v78; // [esp+54h] [ebp-14h]
  float v79; // [esp+58h] [ebp-10h]
  float v80; // [esp+58h] [ebp-10h]
  float v81; // [esp+58h] [ebp-10h]
  float v82; // [esp+64h] [ebp-4h]
  char *texture_aa; // [esp+70h] [ebp+8h]
  int texture_ab; // [esp+70h] [ebp+8h]
  float texture_ag; // [esp+70h] [ebp+8h]
  char *texture_ac; // [esp+70h] [ebp+8h]
  float texture_ah; // [esp+70h] [ebp+8h]
  float texture_ai; // [esp+70h] [ebp+8h]
  char *texture_ad; // [esp+70h] [ebp+8h]
  char *texture_ae; // [esp+70h] [ebp+8h]
  float texture_af; // [esp+70h] [ebp+8h]
  char *v92; // [esp+78h] [ebp+10h]
  char *v93; // [esp+7Ch] [ebp+14h]

  v5 = 0;
  self->kind = PATH_TEMPLATE_KIND_DIP;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = (uint32_t)texture_a;
  self->width_or_scale = 1.0;
  self->segment_count = 70;
  self->segment_count_f = 70.0;
  allocate_path_template_samples(self);
  self->special_runtime_flag_9c = 0;
  texture_aa = nullptr;
  for ( i = 0; i < 4; ++i )
  {
    self->primary_samples[i].center_x = 0.0;
    self->primary_samples[i].rotation_scalar_98 = 0.0;
    self->primary_samples[i].rotation_scalar_94 = 0.0;
    self->primary_samples[i].special_scalar = 0.0;
    self->primary_samples[i].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[i].transform);
    self->primary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    v56 = (float)(int)texture_aa;
    self->primary_samples[i].transform.position.y = 0.0;
    self->primary_samples[i].transform.position.z = v56;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->secondary_samples[i].transform.position.y = 0.49000001;
    self->secondary_samples[i].transform.position.z = v56;
    ++texture_aa;
  }
  v7 = 66;
  v8 = 66;
  texture_ab = 66;
  do
  {
    self->primary_samples[v8].center_x = 0.0;
    self->primary_samples[v8].rotation_scalar_98 = 0.0;
    self->primary_samples[v8].rotation_scalar_94 = 0.0;
    self->primary_samples[v8].special_scalar = 0.0;
    self->primary_samples[v8].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v8].transform);
    texture_ag = (float)texture_ab;
    self->primary_samples[v8].transform.position.x = self->primary_samples[v8].center_x;
    self->primary_samples[v8].transform.position.y = 0.0;
    self->primary_samples[v8].transform.position.z = texture_ag;
    set_matrix_identity(&self->secondary_samples[v8].transform);
    self->secondary_samples[v8].transform.position.x = self->primary_samples[v8].center_x;
    self->secondary_samples[v8].transform.position.y = 0.49000001;
    self->secondary_samples[v8++].transform.position.z = texture_ag;
    texture_ab = ++v7;
  }
  while ( v7 - 66 < 4 );
  v9 = 0;
  v10 = 4;
  texture_ac = nullptr;
  do
  {
    v11 = (double)(int)texture_ac * 0.016129032;
    v51 = v11 * 12.566371;
    v12 = v11 - 0.5;
    if ( v12 >= 0.0 )
      v54 = v12;
    else
      v54 = -v12;
    if ( v12 < 0.0 )
      v12 = -v12;
    texture_ah = v12;
    self->primary_samples[v10].center_x = sine(v51) * (1.0 - texture_ah) * (1.0 - v54) * 4.4444447;
    self->primary_samples[v10].rotation_scalar_98 = 0.0;
    self->primary_samples[v10].rotation_scalar_94 = 0.0;
    self->primary_samples[v10].special_scalar = 0.0;
    self->primary_samples[v10].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v10].transform);
    self->primary_samples[v10].transform.position.x = self->primary_samples[v10].center_x;
    v46 = v51 * 0.5;
    self->primary_samples[v10].transform.position.y = 1.0 - cosine(v46);
    texture_ai = (float)(v9 + 4);
    self->primary_samples[v10].transform.position.z = texture_ai;
    set_matrix_identity(&self->secondary_samples[v10].transform);
    self->secondary_samples[v10].transform.position.x = self->primary_samples[v10].center_x;
    self->secondary_samples[v10].transform.position.y = self->primary_samples[v10].transform.position.y + 0.49000001;
    self->secondary_samples[v10].transform.position.z = texture_ai;
    if ( v10 <= 4 )
    {
      set_matrix_rotation_identity(&self->primary_samples[v10 - 1].transform);
      set_matrix_rotation_identity(&self->secondary_samples[v10 - 1].transform);
    }
    else
    {
      p_basis_up = &self->primary_samples[v10 - 1].transform.basis_up;
      p_basis_up->x = 0.0;
      p_basis_up->y = 1.0;
      p_basis_up->z = 0.0;
      v14 = &self->primary_samples[v10];
      v15 = v14->transform.position.x - v14[-1].transform.position.x;
      v14 = (PathTemplateSample *)((char *)v14 - 136);
      v62 = v15;
      v64 = v14[1].transform.basis_up.y - v14->transform.basis_up.y;
      v16 = v14[1].transform.basis_up.z - v14->transform.basis_up.z;
      v14->transform.basis_right.x = v62;
      v14->transform.basis_right.y = v64;
      v66 = v16;
      v14->transform.basis_right.z = v66;
      normalize_vector((Vec3 *)&self->primary_samples[v10 - 1].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&self->primary_samples[v10 - 1],
        (Vec3 *)&self->primary_samples[v10 - 1].transform.basis_up,
        (Vec3 *)&self->primary_samples[v10 - 1].transform.basis_forward);
      v17 = &self->primary_samples[v10];
      v47 = v17[-1].center_x * 0.2617994;
      rotate_matrix_world_z(&v17[-1].transform, v47);
      v18 = &self->secondary_samples[v10 - 1].transform.basis_up;
      v18->x = 0.0;
      v18->y = 1.0;
      v18->z = 0.0;
      secondary_samples = self->secondary_samples;
      p_x = &secondary_samples[v10 - 1].transform.basis_forward.x;
      v73 = secondary_samples[v10].transform.position.x - secondary_samples[v10 - 1].transform.position.x;
      v76 = p_x[47] - p_x[5];
      v21 = p_x[48] - p_x[6];
      *p_x = v73;
      p_x[1] = v76;
      v79 = v21;
      p_x[2] = v79;
      normalize_vector((Vec3 *)&self->secondary_samples[v10 - 1].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&self->secondary_samples[v10 - 1],
        (Vec3 *)&self->secondary_samples[v10 - 1].transform.basis_up,
        (Vec3 *)&self->secondary_samples[v10 - 1].transform.basis_forward);
      v48 = self->primary_samples[v10 - 1].center_x * 0.2617994;
      rotate_matrix_world_z(&self->secondary_samples[v10 - 1].transform, v48);
    }
    ++v10;
    texture_ac = (char *)++v9;
  }
  while ( v10 < 66 );
  v22 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v23 = 0;
    do
    {
      primary_samples = self->primary_samples;
      v25 = &primary_samples[v23].delta_dir_to_next.x;
      v74 = primary_samples[v23 + 1].transform.position.x - primary_samples[v23].transform.position.x;
      v77 = primary_samples[v23 + 1].transform.position.y - primary_samples[v23].transform.position.y;
      v26 = primary_samples[v23 + 1].transform.position.z - primary_samples[v23].transform.position.z;
      *v25 = v74;
      v25[1] = v77;
      v80 = v26;
      v25[2] = v80;
      self->primary_samples[v23].delta_length = normalize_vector(&self->primary_samples[v23].delta_dir_to_next);
      v27 = self->secondary_samples;
      v28 = &v27[v23].delta_dir_to_next.x;
      v67 = v27[v23 + 1].transform.position.x - v27[v23].transform.position.x;
      v69 = v27[v23 + 1].transform.position.y - v27[v23].transform.position.y;
      v29 = v27[v23 + 1].transform.position.z - v27[v23].transform.position.z;
      *v28 = v67;
      v28[1] = v69;
      v71 = v29;
      v28[2] = v71;
      ++v22;
      self->secondary_samples[v23].delta_length = normalize_vector(&self->secondary_samples[v23].delta_dir_to_next);
      ++v23;
    }
    while ( v22 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = 1.0;
  v31 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v31->x = 0.0;
  v31->y = 0.0;
  v31->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = 1.0;
  request_object_vertices(self->strip_mesh, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->strip_mesh, 2 * self->segment_count * self->width_cells);
  strip_mesh = self->strip_mesh;
  vertices = strip_mesh->vertices;
  facequads = strip_mesh->facequads;
  v34 = 0;
  v57 = vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    do
    {
      width_cells = self->width_cells;
      v36 = nullptr;
      texture_ad = nullptr;
      for ( j = width_cells; (int)v36 <= width_cells; texture_ad = v36 )
      {
        v37 = (double)(int)texture_ad - (double)j * 0.5;
        v38 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v5);
        if ( v34 == self->segment_count )
        {
          vertices = v57;
          v60 = v37 * *(v38 - 42);
          v61 = v37 * *(v38 - 41);
          v41 = v37 * *(v38 - 40);
          v82 = *(v38 - 28) + 1.0;
          v68 = *(v38 - 30) + v60;
          v70 = *(v38 - 29) + v61;
          v39 = &v57[(_DWORD)&v36[v34 * (width_cells + 1)]].x;
          *v39 = v68;
          v72 = v82 + v41;
          v39[1] = v70;
          v40 = v72;
        }
        else
        {
          v63 = v37 * *v38;
          v65 = v37 * v38[1];
          v75 = v63 + v38[12];
          v78 = v65 + v38[13];
          v81 = v37 * v38[2] + v38[14];
          v39 = &vertices[(_DWORD)&v36[v34 * (width_cells + 1)]].x;
          *v39 = v75;
          v39[1] = v78;
          v40 = v81;
        }
        v39[2] = v40;
        width_cells = self->width_cells;
        ++v36;
        j = width_cells;
      }
      ++v34;
      v5 += 168;
    }
    while ( v34 <= (signed int)self->segment_count );
    v5 = 0;
  }
  if ( (int)self->segment_count > 0 )
  {
    do
    {
      v42 = 0;
      texture_ae = nullptr;
      if ( (int)self->width_cells > 0 )
      {
        v49 = (double)(v5 % 8) * 0.125;
        v53 = (double)(v5 % 8 + 1) * 0.125;
        do
        {
          v43 = 0;
          v58 = v42 + 1;
          v55 = 0;
          texture_af = (double)(int)texture_ae * 0.125;
          v50 = (double)(v42 + 1) * 0.125;
          while ( 1 )
          {
            v44 = (uint32_t)facequads + 96 * v42 + 96 * v5 * self->width_cells + 48 * v43;
            *(_WORD *)v44 = 0;
            if ( v43 )
            {
              *(_WORD *)(v44 + 2) = v5 * (LOWORD(self->width_cells) + 1) + v42 + 1;
              *(_WORD *)(v44 + 4) = v42 + v5 * (LOWORD(self->width_cells) + 1);
              *(_WORD *)(v44 + 6) = v42 + (v5 + 1) * (LOWORD(self->width_cells) + 1);
              *(_WORD *)(v44 + 8) = (v5 + 1) * (LOWORD(self->width_cells) + 1) + v42 + 1;
              *(_DWORD *)(v44 + 12) = get_or_create_texture_ref((TextureRefList *)dword_4B7790, v93, 0, 0);
              *(float *)(v44 + 16) = v50;
              *(float *)(v44 + 20) = v49;
              *(float *)(v44 + 24) = texture_af;
              *(float *)(v44 + 28) = v49;
              *(float *)(v44 + 32) = texture_af;
              *(float *)(v44 + 36) = v53;
              *(float *)(v44 + 40) = v50;
            }
            else
            {
              *(_WORD *)(v44 + 2) = v42 + v5 * (LOWORD(self->width_cells) + 1);
              *(_WORD *)(v44 + 4) = v5 * (LOWORD(self->width_cells) + 1) + v42 + 1;
              *(_WORD *)(v44 + 6) = (v5 + 1) * (LOWORD(self->width_cells) + 1) + v42 + 1;
              *(_WORD *)(v44 + 8) = v42 + (v5 + 1) * (LOWORD(self->width_cells) + 1);
              *(_DWORD *)(v44 + 12) = get_or_create_texture_ref((TextureRefList *)dword_4B7790, v92, 0, 0);
              *(float *)(v44 + 16) = texture_af;
              *(float *)(v44 + 20) = v49;
              *(float *)(v44 + 24) = v50;
              *(float *)(v44 + 28) = v49;
              *(float *)(v44 + 32) = v50;
              *(float *)(v44 + 36) = v53;
              *(float *)(v44 + 40) = texture_af;
            }
            *(float *)(v44 + 44) = v53;
            if ( ++v55 >= 2 )
              break;
            v43 = v55;
          }
          ++v42;
          texture_ae = (char *)v58;
        }
        while ( v58 < (signed int)self->width_cells );
      }
      ++v5;
    }
    while ( v5 < (signed int)self->segment_count );
  }
  return finalize_path_template(self);
}

