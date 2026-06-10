/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_sweep_path_template_pair @ 0x422c00 */
/* selector: initialize_sweep_path_template_pair */

int32_t __thiscall initialize_sweep_path_template_pair(
        PathTemplate *self,
        int32_t arg2,
        char *texture_a,
        char *texture_b)
{
  signed int v5; // ebx
  int i; // edi
  int v7; // ebp
  int v8; // edi
  int j; // edi
  PathTemplateSample *primary_samples; // ebp
  Vec4 *p_basis_up; // ecx
  PathTemplateSample *v12; // eax
  double v13; // st7
  double v14; // st7
  Vec4 *v15; // ecx
  PathTemplateSample *v16; // eax
  double v17; // st7
  double v18; // st7
  signed int v19; // ebp
  int v20; // edi
  float *p_x; // eax
  double v22; // st7
  double v23; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *v25; // eax
  double v26; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v28; // ecx
  PathTemplateStripMesh *strip_mesh; // eax
  signed int v30; // edx
  Vec3 *vertices; // ebp
  signed int width_cells; // ecx
  char *v33; // edi
  double v34; // st7
  float *v35; // eax
  float *v36; // eax
  float v37; // ecx
  double v38; // st7
  int v39; // edi
  int v40; // ecx
  ObjectFaceQuad *v41; // ebp
  float v43; // [esp+10h] [ebp-54h]
  float v44; // [esp+14h] [ebp-50h]
  int k; // [esp+18h] [ebp-4Ch]
  float v46; // [esp+18h] [ebp-4Ch]
  float v47; // [esp+1Ch] [ebp-48h]
  int v48; // [esp+1Ch] [ebp-48h]
  ObjectFaceQuad *facequads; // [esp+20h] [ebp-44h]
  float v50; // [esp+24h] [ebp-40h]
  float v51; // [esp+24h] [ebp-40h]
  Vec3 *v52; // [esp+24h] [ebp-40h]
  signed int v53; // [esp+24h] [ebp-40h]
  float v54; // [esp+28h] [ebp-3Ch]
  float v55; // [esp+2Ch] [ebp-38h]
  float v56; // [esp+34h] [ebp-30h]
  float v57; // [esp+34h] [ebp-30h]
  float v58; // [esp+38h] [ebp-2Ch]
  float v59; // [esp+38h] [ebp-2Ch]
  float v60; // [esp+3Ch] [ebp-28h]
  float v61; // [esp+40h] [ebp-24h]
  float v62; // [esp+40h] [ebp-24h]
  float v63; // [esp+44h] [ebp-20h]
  float v64; // [esp+44h] [ebp-20h]
  float v65; // [esp+48h] [ebp-1Ch]
  float v66; // [esp+48h] [ebp-1Ch]
  float v67; // [esp+4Ch] [ebp-18h]
  float v68; // [esp+4Ch] [ebp-18h]
  float v69; // [esp+4Ch] [ebp-18h]
  float v70; // [esp+50h] [ebp-14h]
  float v71; // [esp+50h] [ebp-14h]
  float v72; // [esp+50h] [ebp-14h]
  float v73; // [esp+54h] [ebp-10h]
  float v74; // [esp+54h] [ebp-10h]
  float v75; // [esp+54h] [ebp-10h]
  float v76; // [esp+60h] [ebp-4h]
  char *texture_aa; // [esp+6Ch] [ebp+8h]
  int texture_ab; // [esp+6Ch] [ebp+8h]
  float texture_ag; // [esp+6Ch] [ebp+8h]
  char *texture_ac; // [esp+6Ch] [ebp+8h]
  char *texture_ad; // [esp+6Ch] [ebp+8h]
  char *texture_ae; // [esp+6Ch] [ebp+8h]
  float texture_af; // [esp+6Ch] [ebp+8h]
  char *texture_path; // [esp+74h] [ebp+10h]
  char *v85; // [esp+78h] [ebp+14h]

  v5 = 0;
  self->kind = PATH_TEMPLATE_KIND_SWEEP;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = (uint32_t)texture_a;
  self->width_or_scale = 1.0;
  self->segment_count = 30;
  self->segment_count_f = 30.0;
  allocate_path_template_samples(self);
  self->special_runtime_flag_9c = 0;
  texture_aa = nullptr;
  for ( i = 0; i < 3; ++i )
  {
    self->primary_samples[i].center_x = (double)(int)self->width_cells * 0.5 - 4.0;
    self->primary_samples[i].rotation_scalar_98 = 0.0;
    self->primary_samples[i].rotation_scalar_94 = 0.0;
    self->primary_samples[i].special_scalar = 0.0;
    self->primary_samples[i].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[i].transform);
    self->primary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    v50 = (float)(int)texture_aa;
    self->primary_samples[i].transform.position.y = 0.0;
    self->primary_samples[i].transform.position.z = v50;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->secondary_samples[i].transform.position.y = 0.49000001;
    self->secondary_samples[i].transform.position.z = v50;
    ++texture_aa;
  }
  v7 = 27;
  v8 = 27;
  texture_ab = 27;
  do
  {
    self->primary_samples[v8].center_x = 4.0 - (double)(int)self->width_cells * 0.5;
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
  while ( v7 - 27 < 3 );
  texture_ac = nullptr;
  for ( j = 3; j < 27; ++j )
  {
    primary_samples = self->primary_samples;
    v47 = (double)(int)texture_ac * 0.1308997;
    primary_samples[j].center_x = cosine(v47) * primary_samples->center_x;
    self->primary_samples[j].rotation_scalar_98 = 0.0;
    self->primary_samples[j].rotation_scalar_94 = 0.0;
    self->primary_samples[j].special_scalar = 0.0;
    self->primary_samples[j].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[j].transform);
    self->primary_samples[j].transform.position.x = self->primary_samples[j].center_x;
    self->primary_samples[j].transform.position.y = sine(v47) * -0.30000001;
    v51 = (float)(int)(texture_ac + 3);
    self->primary_samples[j].transform.position.z = v51;
    set_matrix_identity(&self->secondary_samples[j].transform);
    self->secondary_samples[j].transform.position.x = self->primary_samples[j].center_x;
    self->secondary_samples[j].transform.position.y = self->primary_samples[j].transform.position.y + 0.49000001;
    self->secondary_samples[j].transform.position.z = v51;
    if ( j <= 3 )
    {
      set_matrix_rotation_identity(&self->primary_samples[j - 1].transform);
      set_matrix_rotation_identity(&self->secondary_samples[j - 1].transform);
    }
    else
    {
      p_basis_up = &self->primary_samples[j - 1].transform.basis_up;
      p_basis_up->x = 0.0;
      p_basis_up->y = 1.0;
      p_basis_up->z = 0.0;
      v12 = &self->primary_samples[j];
      v13 = v12->transform.position.x - v12[-1].transform.position.x;
      v12 = (PathTemplateSample *)((char *)v12 - 136);
      v56 = v13;
      v58 = v12[1].transform.basis_up.y - v12->transform.basis_up.y;
      v14 = v12[1].transform.basis_up.z - v12->transform.basis_up.z;
      v12->transform.basis_right.x = v56;
      v12->transform.basis_right.y = v58;
      v60 = v14;
      v12->transform.basis_right.z = v60;
      normalize_vector((Vec3 *)&self->primary_samples[j - 1].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&self->primary_samples[j - 1],
        (Vec3 *)&self->primary_samples[j - 1].transform.basis_up,
        (Vec3 *)&self->primary_samples[j - 1].transform.basis_forward);
      v15 = &self->secondary_samples[j - 1].transform.basis_up;
      v15->x = 0.0;
      v15->y = 1.0;
      v15->z = 0.0;
      v16 = &self->secondary_samples[j];
      v17 = v16->transform.position.x - v16[-1].transform.position.x;
      v16 = (PathTemplateSample *)((char *)v16 - 136);
      v67 = v17;
      v70 = v16[1].transform.basis_up.y - v16->transform.basis_up.y;
      v18 = v16[1].transform.basis_up.z - v16->transform.basis_up.z;
      v16->transform.basis_right.x = v67;
      v16->transform.basis_right.y = v70;
      v73 = v18;
      v16->transform.basis_right.z = v73;
      normalize_vector((Vec3 *)&self->secondary_samples[j - 1].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&self->secondary_samples[j - 1],
        (Vec3 *)&self->secondary_samples[j - 1].transform.basis_up,
        (Vec3 *)&self->secondary_samples[j - 1].transform.basis_forward);
    }
    ++texture_ac;
  }
  v19 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v20 = 0;
    do
    {
      p_x = &self->primary_samples[v20].transform.basis_right.x;
      v22 = p_x[54] - p_x[12];
      p_x += 32;
      v68 = v22;
      v71 = p_x[23] - *(p_x - 19);
      v23 = p_x[24] - *(p_x - 18);
      *p_x = v68;
      p_x[1] = v71;
      v74 = v23;
      p_x[2] = v74;
      self->primary_samples[v20].delta_length = normalize_vector(&self->primary_samples[v20].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v25 = &secondary_samples[v20].delta_dir_to_next.x;
      v61 = secondary_samples[v20 + 1].transform.position.x - secondary_samples[v20].transform.position.x;
      v63 = secondary_samples[v20 + 1].transform.position.y - secondary_samples[v20].transform.position.y;
      v26 = secondary_samples[v20 + 1].transform.position.z - secondary_samples[v20].transform.position.z;
      *v25 = v61;
      v25[1] = v63;
      v65 = v26;
      v25[2] = v65;
      ++v19;
      self->secondary_samples[v20].delta_length = normalize_vector(&self->secondary_samples[v20].delta_dir_to_next);
      ++v20;
    }
    while ( v19 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = 1.0;
  v28 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v28->x = 0.0;
  v28->y = 0.0;
  v28->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = 1.0;
  request_object_vertices(self->strip_mesh, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->strip_mesh, 2 * self->segment_count * self->width_cells);
  strip_mesh = self->strip_mesh;
  v30 = 0;
  vertices = strip_mesh->vertices;
  v52 = vertices;
  facequads = strip_mesh->facequads;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    do
    {
      width_cells = self->width_cells;
      v33 = nullptr;
      texture_ad = nullptr;
      for ( k = width_cells; (int)v33 <= width_cells; texture_ad = v33 )
      {
        v34 = (double)(int)texture_ad - (double)k * 0.5;
        v35 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v5);
        if ( v30 == self->segment_count )
        {
          vertices = v52;
          v54 = v34 * *(v35 - 42);
          v55 = v34 * *(v35 - 41);
          v38 = v34 * *(v35 - 40);
          v76 = *(v35 - 28) + 1.0;
          v62 = *(v35 - 30) + v54;
          v64 = *(v35 - 29) + v55;
          v36 = &v52[(_DWORD)&v33[v30 * (width_cells + 1)]].x;
          *v36 = v62;
          v66 = v76 + v38;
          v36[1] = v64;
          v37 = v66;
        }
        else
        {
          v57 = v34 * *v35;
          v59 = v34 * v35[1];
          v69 = v57 + v35[12];
          v72 = v59 + v35[13];
          v75 = v34 * v35[2] + v35[14];
          v36 = &vertices[(_DWORD)&v33[v30 * (width_cells + 1)]].x;
          *v36 = v69;
          v36[1] = v72;
          v37 = v75;
        }
        v36[2] = v37;
        width_cells = self->width_cells;
        ++v33;
        k = width_cells;
      }
      ++v30;
      v5 += 168;
    }
    while ( v30 <= (signed int)self->segment_count );
    v5 = 0;
  }
  if ( (int)self->segment_count > 0 )
  {
    do
    {
      v39 = 0;
      texture_ae = nullptr;
      if ( (int)self->width_cells > 0 )
      {
        v43 = (double)(v5 % 8) * 0.125;
        v46 = (double)(v5 % 8 + 1) * 0.125;
        do
        {
          v40 = 0;
          v53 = v39 + 1;
          v48 = 0;
          texture_af = (double)(int)texture_ae * 0.125;
          v44 = (double)(v39 + 1) * 0.125;
          while ( 1 )
          {
            v41 = &facequads[2 * v39 + 2 * v5 * self->width_cells + v40];
            v41->flags = 0;
            if ( v40 )
            {
              v41->vertex_index_a = v5 * (LOWORD(self->width_cells) + 1) + v39 + 1;
              v41->vertex_index_b = v39 + v5 * (LOWORD(self->width_cells) + 1);
              v41->vertex_index_c = v39 + (v5 + 1) * (LOWORD(self->width_cells) + 1);
              v41->vertex_index_d = (v5 + 1) * (LOWORD(self->width_cells) + 1) + v39 + 1;
              v41->texture_ref = get_or_create_texture_ref(&texture_list, v85, 0, 0);
              v41->u0 = v44;
              v41->v0 = v43;
              v41->u1 = texture_af;
              v41->v1 = v43;
              v41->u2 = texture_af;
              v41->v2 = v46;
              v41->u3 = v44;
            }
            else
            {
              v41->vertex_index_a = v39 + v5 * (LOWORD(self->width_cells) + 1);
              v41->vertex_index_b = v5 * (LOWORD(self->width_cells) + 1) + v39 + 1;
              v41->vertex_index_c = (v5 + 1) * (LOWORD(self->width_cells) + 1) + v39 + 1;
              v41->vertex_index_d = v39 + (v5 + 1) * (LOWORD(self->width_cells) + 1);
              v41->texture_ref = get_or_create_texture_ref(&texture_list, texture_path, 0, 0);
              v41->u0 = texture_af;
              v41->v0 = v43;
              v41->u1 = v44;
              v41->v1 = v43;
              v41->u2 = v44;
              v41->v2 = v46;
              v41->u3 = texture_af;
            }
            v41->v3 = v46;
            if ( ++v48 >= 2 )
              break;
            v40 = v48;
          }
          ++v39;
          texture_ae = (char *)v53;
        }
        while ( v53 < (signed int)self->width_cells );
      }
      ++v5;
    }
    while ( v5 < (signed int)self->segment_count );
  }
  return finalize_path_template(self);
}

