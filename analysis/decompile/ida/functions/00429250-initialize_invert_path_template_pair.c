/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_invert_path_template_pair @ 0x429250 */
/* selector: initialize_invert_path_template_pair */

int32_t __thiscall initialize_invert_path_template_pair(
        PathTemplate *self,
        int32_t arg2,
        char *texture_a,
        char *texture_b)
{
  double width_cells; // st7
  PathTemplateSample *primary_samples; // ecx
  int v7; // ebx
  char *v8; // edi
  double v9; // st7
  float v10; // esi
  Vec4 *p_basis_up; // edx
  PathTemplateSample *v12; // ecx
  float *p_x; // eax
  double v14; // st7
  PathTemplateSample *v15; // ecx
  double v16; // st7
  double v17; // st6
  Vec4 *p_position; // eax
  signed int v19; // edi
  int v20; // esi
  PathTemplateSample *v21; // ecx
  float *v22; // eax
  double v23; // st7
  PathTemplateSample *secondary_samples; // edx
  float *v25; // eax
  double v26; // st7
  Vec3 *p_delta_dir_to_next; // ecx
  Vec3 *v28; // eax
  PathTemplateStripMesh *strip_mesh; // eax
  Vec3 *vertices; // edi
  signed int v31; // edx
  int v32; // ebx
  signed int v33; // ecx
  char *v34; // esi
  double v35; // st7
  PathTemplateSample *v36; // eax
  float *v37; // eax
  float v38; // ecx
  double v39; // st7
  signed int j; // ebx
  int v41; // esi
  int v42; // ecx
  ObjectFaceQuad *v43; // edi
  float v45; // [esp+10h] [ebp-54h]
  float v46; // [esp+14h] [ebp-50h]
  int i; // [esp+18h] [ebp-4Ch]
  float v48; // [esp+18h] [ebp-4Ch]
  int v49; // [esp+1Ch] [ebp-48h]
  ObjectFaceQuad *facequads; // [esp+20h] [ebp-44h]
  Vec3 *v51; // [esp+24h] [ebp-40h]
  signed int v52; // [esp+24h] [ebp-40h]
  float v53; // [esp+28h] [ebp-3Ch]
  float v54; // [esp+28h] [ebp-3Ch]
  float v55; // [esp+28h] [ebp-3Ch]
  float v56; // [esp+2Ch] [ebp-38h]
  float v57; // [esp+2Ch] [ebp-38h]
  float v58; // [esp+30h] [ebp-34h]
  float v59; // [esp+30h] [ebp-34h]
  float v60; // [esp+34h] [ebp-30h]
  float v61; // [esp+34h] [ebp-30h]
  float v62; // [esp+34h] [ebp-30h]
  float v63; // [esp+38h] [ebp-2Ch]
  float v64; // [esp+38h] [ebp-2Ch]
  float v65; // [esp+38h] [ebp-2Ch]
  float v66; // [esp+3Ch] [ebp-28h]
  float v67; // [esp+3Ch] [ebp-28h]
  float v68; // [esp+3Ch] [ebp-28h]
  float v69; // [esp+40h] [ebp-24h]
  float v70; // [esp+44h] [ebp-20h]
  float v71; // [esp+44h] [ebp-20h]
  float v72; // [esp+48h] [ebp-1Ch]
  float v73; // [esp+4Ch] [ebp-18h]
  float v74; // [esp+50h] [ebp-14h]
  float v75; // [esp+60h] [ebp-4h]
  char *texture_aa; // [esp+6Ch] [ebp+8h]
  float texture_ae; // [esp+6Ch] [ebp+8h]
  float texture_af; // [esp+6Ch] [ebp+8h]
  char *texture_ab; // [esp+6Ch] [ebp+8h]
  char *texture_ac; // [esp+6Ch] [ebp+8h]
  float texture_ad; // [esp+6Ch] [ebp+8h]
  char *texture_path; // [esp+74h] [ebp+10h]
  char *v83; // [esp+78h] [ebp+14h]

  self->kind = PATH_TEMPLATE_KIND_INVERT;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = (uint32_t)texture_a;
  self->width_or_scale = 1.0;
  self->segment_count = 34;
  self->segment_count_f = 34.0;
  allocate_path_template_samples(self);
  width_cells = (double)(int)self->width_cells;
  primary_samples = self->primary_samples;
  self->special_runtime_flag_9c = 1;
  primary_samples->center_x = width_cells * 0.5 - 4.0;
  self->primary_samples->rotation_scalar_98 = 0.0;
  self->primary_samples->rotation_scalar_94 = 0.0;
  self->primary_samples->special_scalar = 0.0;
  self->primary_samples->lateral_scale = 1.0;
  set_matrix_identity(&self->primary_samples->transform);
  self->primary_samples->transform.position.x = self->primary_samples->center_x;
  self->primary_samples->transform.position.y = 0.0;
  self->primary_samples->transform.position.z = 0.0;
  self->primary_samples->delta_length = 1.0;
  set_matrix_identity(&self->secondary_samples->transform);
  self->secondary_samples->transform.position.x = self->primary_samples->center_x;
  self->secondary_samples->transform.position.y = 0.49000001;
  self->secondary_samples->transform.position.z = 0.0;
  self->secondary_samples->delta_length = 1.0;
  self->primary_samples[33].center_x = 4.0 - (double)(int)self->width_cells * 0.5;
  self->primary_samples[33].rotation_scalar_98 = 3.1415927;
  self->primary_samples[33].rotation_scalar_94 = 0.0;
  self->primary_samples[33].special_scalar = 0.0;
  self->primary_samples[33].lateral_scale = 1.0;
  set_matrix_identity(&self->primary_samples[33].transform);
  self->primary_samples[33].transform.position.x = self->primary_samples[33].center_x;
  self->primary_samples[33].transform.position.y = 0.0;
  self->primary_samples[33].transform.position.z = 33.0;
  self->primary_samples[33].delta_length = 1.0;
  set_matrix_identity(&self->secondary_samples[33].transform);
  self->secondary_samples[33].transform.position.x = self->primary_samples[33].center_x;
  self->secondary_samples[33].transform.position.y = 0.49000001;
  self->secondary_samples[33].transform.position.z = 33.0;
  v7 = 1;
  self->secondary_samples[33].delta_length = 1.0;
  v8 = nullptr;
  texture_aa = nullptr;
  do
  {
    v9 = (double)(int)texture_aa;
    texture_ae = v9 * 0.19634955;
    self->primary_samples[v7].center_x = (self->primary_samples[33].center_x - self->primary_samples->center_x)
                                       * v9
                                       * 0.03125
                                       + self->primary_samples->center_x;
    self->primary_samples[v7].rotation_scalar_98 = texture_ae * 0.5;
    self->primary_samples[v7].rotation_scalar_94 = 0.0;
    self->primary_samples[v7].special_scalar = 0.0;
    self->primary_samples[v7].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v7].transform);
    self->primary_samples[v7].transform.position.x = 0.0;
    self->primary_samples[v7].transform.position.z = (float)(int)(v8 + 1);
    self->primary_samples[v7].transform.position.y = 0.0;
    v10 = texture_ae;
    texture_af = cosine(texture_ae);
    v53 = sine(v10);
    p_basis_up = &self->primary_samples[v7].transform.basis_up;
    p_basis_up->x = v53;
    p_basis_up->y = texture_af;
    p_basis_up->z = 0.0;
    v12 = self->primary_samples;
    p_x = &v12[v7].transform.basis_forward.x;
    v60 = v12[v7].transform.position.x - v12[v7 - 1].transform.position.x;
    v63 = v12[v7].transform.position.y - v12[v7 - 1].transform.position.y;
    v14 = v12[v7].transform.position.z - v12[v7 - 1].transform.position.z;
    *p_x = v60;
    p_x[1] = v63;
    v66 = v14;
    p_x[2] = v66;
    normalize_vector((Vec3 *)&self->primary_samples[v7].transform.basis_forward);
    cross_vectors(
      (Vec3 *)&self->primary_samples[v7],
      (Vec3 *)&self->primary_samples[v7].transform.basis_up,
      (Vec3 *)&self->primary_samples[v7].transform.basis_forward);
    qmemcpy(&self->secondary_samples[v7], &self->primary_samples[v7], 0x40u);
    v15 = self->primary_samples;
    ++v8;
    v16 = v15[v7].transform.basis_up.x * 0.49000001;
    texture_aa = v8;
    v70 = v15[v7].transform.basis_up.y * 0.49000001;
    v17 = v15[v7].transform.basis_up.z * 0.49000001;
    p_position = &self->secondary_samples[v7++].transform.position;
    v72 = v17;
    p_position->x = v16 + p_position->x;
    p_position->y = v70 + p_position->y;
    p_position->z = v72 + p_position->z;
  }
  while ( v7 < 33 );
  v19 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v20 = 0;
    do
    {
      v21 = self->primary_samples;
      v22 = &v21[v20].delta_dir_to_next.x;
      v61 = v21[v20 + 1].transform.position.x - v21[v20].transform.position.x;
      v64 = v21[v20 + 1].transform.position.y - v21[v20].transform.position.y;
      v23 = v21[v20 + 1].transform.position.z - v21[v20].transform.position.z;
      *v22 = v61;
      v22[1] = v64;
      v67 = v23;
      v22[2] = v67;
      self->primary_samples[v20].delta_length = normalize_vector(&self->primary_samples[v20].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v25 = &secondary_samples[v20].delta_dir_to_next.x;
      v54 = secondary_samples[v20 + 1].transform.position.x - secondary_samples[v20].transform.position.x;
      v56 = secondary_samples[v20 + 1].transform.position.y - secondary_samples[v20].transform.position.y;
      v26 = secondary_samples[v20 + 1].transform.position.z - secondary_samples[v20].transform.position.z;
      *v25 = v54;
      v25[1] = v56;
      v58 = v26;
      v25[2] = v58;
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
  vertices = strip_mesh->vertices;
  facequads = strip_mesh->facequads;
  v31 = 0;
  v51 = vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v32 = 0;
    do
    {
      v33 = self->width_cells;
      v34 = nullptr;
      texture_ab = nullptr;
      for ( i = v33; (int)v34 <= v33; texture_ab = v34 )
      {
        v35 = (double)(int)texture_ab - (double)i * 0.5;
        v36 = &self->primary_samples[v32];
        if ( v31 == self->segment_count )
        {
          vertices = v51;
          v73 = v35 * v36[-1].transform.basis_right.x;
          v74 = v35 * v36[-1].transform.basis_right.y;
          v39 = v35 * v36[-1].transform.basis_right.z;
          v75 = v36[-1].transform.position.z + 1.0;
          v55 = v36[-1].transform.position.x + v73;
          v57 = v36[-1].transform.position.y + v74;
          v37 = &v51[(_DWORD)&v34[v31 * (v33 + 1)]].x;
          *v37 = v55;
          v59 = v75 + v39;
          v37[1] = v57;
          v38 = v59;
        }
        else
        {
          v69 = v35 * v36->transform.basis_right.x;
          v71 = v35 * v36->transform.basis_right.y;
          v62 = v69 + v36->transform.position.x;
          v65 = v71 + v36->transform.position.y;
          v68 = v35 * v36->transform.basis_right.z + v36->transform.position.z;
          v37 = &vertices[(_DWORD)&v34[v31 * (v33 + 1)]].x;
          *v37 = v62;
          v37[1] = v65;
          v38 = v68;
        }
        v37[2] = v38;
        v33 = self->width_cells;
        ++v34;
        i = v33;
      }
      ++v31;
      ++v32;
    }
    while ( v31 <= (signed int)self->segment_count );
  }
  for ( j = 0; j < (signed int)self->segment_count; ++j )
  {
    v41 = 0;
    texture_ac = nullptr;
    if ( (int)self->width_cells > 0 )
    {
      v45 = (double)(j % 8) * 0.125;
      v48 = (double)(j % 8 + 1) * 0.125;
      do
      {
        v42 = 0;
        v52 = v41 + 1;
        v49 = 0;
        texture_ad = (double)(int)texture_ac * 0.125;
        v46 = (double)(v41 + 1) * 0.125;
        while ( 1 )
        {
          v43 = &facequads[2 * v41 + 2 * j * self->width_cells + v42];
          v43->flags = 0;
          if ( v42 )
          {
            v43->vertex_index_a = j * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->vertex_index_b = v41 + j * (LOWORD(self->width_cells) + 1);
            v43->vertex_index_c = v41 + (j + 1) * (LOWORD(self->width_cells) + 1);
            v43->vertex_index_d = (j + 1) * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->texture_ref = get_or_create_texture_ref(&texture_list, v83, 0, 0);
            v43->u0 = v46;
            v43->v0 = v45;
            v43->u1 = texture_ad;
            v43->v1 = v45;
            v43->u2 = texture_ad;
            v43->v2 = v48;
            v43->u3 = v46;
          }
          else
          {
            v43->vertex_index_a = v41 + j * (LOWORD(self->width_cells) + 1);
            v43->vertex_index_b = j * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->vertex_index_c = (j + 1) * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->vertex_index_d = v41 + (j + 1) * (LOWORD(self->width_cells) + 1);
            v43->texture_ref = get_or_create_texture_ref(&texture_list, texture_path, 0, 0);
            v43->u0 = texture_ad;
            v43->v0 = v45;
            v43->u1 = v46;
            v43->v1 = v45;
            v43->u2 = v46;
            v43->v2 = v48;
            v43->u3 = texture_ad;
          }
          v43->v3 = v48;
          if ( ++v49 >= 2 )
            break;
          v42 = v49;
        }
        ++v41;
        texture_ac = (char *)v52;
      }
      while ( v52 < (signed int)self->width_cells );
    }
  }
  return finalize_path_template(self);
}

