/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_wibble_path_template_pair @ 0x4289a0 */
/* selector: initialize_wibble_path_template_pair */

int32_t __thiscall initialize_wibble_path_template_pair(
        PathTemplate *self,
        int32_t arg2,
        char *texture_a,
        char *texture_b)
{
  double width_cells; // st7
  PathTemplateSample *primary_samples; // ecx
  int v7; // ebx
  int v8; // edi
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
  float v45; // [esp+0h] [ebp-68h]
  float v46; // [esp+0h] [ebp-68h]
  float v47; // [esp+14h] [ebp-54h]
  float v48; // [esp+18h] [ebp-50h]
  int i; // [esp+1Ch] [ebp-4Ch]
  float v50; // [esp+1Ch] [ebp-4Ch]
  int v51; // [esp+20h] [ebp-48h]
  ObjectFaceQuad *facequads; // [esp+24h] [ebp-44h]
  float v53; // [esp+28h] [ebp-40h]
  float v54; // [esp+28h] [ebp-40h]
  float v55; // [esp+28h] [ebp-40h]
  Vec3 *v56; // [esp+28h] [ebp-40h]
  signed int v57; // [esp+28h] [ebp-40h]
  float v58; // [esp+2Ch] [ebp-3Ch]
  float v59; // [esp+2Ch] [ebp-3Ch]
  float v60; // [esp+2Ch] [ebp-3Ch]
  float v61; // [esp+30h] [ebp-38h]
  float v62; // [esp+30h] [ebp-38h]
  float v63; // [esp+34h] [ebp-34h]
  float v64; // [esp+34h] [ebp-34h]
  float v65; // [esp+38h] [ebp-30h]
  float v66; // [esp+38h] [ebp-30h]
  float v67; // [esp+38h] [ebp-30h]
  float v68; // [esp+3Ch] [ebp-2Ch]
  float v69; // [esp+3Ch] [ebp-2Ch]
  float v70; // [esp+3Ch] [ebp-2Ch]
  float v71; // [esp+40h] [ebp-28h]
  float v72; // [esp+40h] [ebp-28h]
  float v73; // [esp+40h] [ebp-28h]
  float v74; // [esp+44h] [ebp-24h]
  float v75; // [esp+48h] [ebp-20h]
  float v76; // [esp+48h] [ebp-20h]
  float v77; // [esp+4Ch] [ebp-1Ch]
  float v78; // [esp+50h] [ebp-18h]
  float v79; // [esp+54h] [ebp-14h]
  float v80; // [esp+64h] [ebp-4h]
  char *texture_aa; // [esp+70h] [ebp+8h]
  char *texture_ab; // [esp+70h] [ebp+8h]
  char *texture_ac; // [esp+70h] [ebp+8h]
  float texture_ad; // [esp+70h] [ebp+8h]
  char *v85; // [esp+78h] [ebp+10h]
  char *v86; // [esp+7Ch] [ebp+14h]

  self->kind = PATH_TEMPLATE_KIND_WIBBLE;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = (uint32_t)texture_a;
  self->width_or_scale = 1.0;
  self->segment_count = 32;
  self->segment_count_f = 32.0;
  allocate_path_nodes(self);
  width_cells = (double)(int)self->width_cells;
  primary_samples = self->primary_samples;
  self->special_runtime_flag_9c = 0;
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
  self->primary_samples[31].center_x = 4.0 - (double)(int)self->width_cells * 0.5;
  self->primary_samples[31].rotation_scalar_98 = 0.0;
  self->primary_samples[31].rotation_scalar_94 = 0.0;
  self->primary_samples[31].special_scalar = 0.0;
  self->primary_samples[31].lateral_scale = 1.0;
  set_matrix_identity(&self->primary_samples[31].transform);
  self->primary_samples[31].transform.position.x = self->primary_samples[31].center_x;
  self->primary_samples[31].transform.position.y = 0.0;
  self->primary_samples[31].transform.position.z = 31.0;
  self->primary_samples[31].delta_length = 1.0;
  set_matrix_identity(&self->secondary_samples[31].transform);
  self->secondary_samples[31].transform.position.x = self->primary_samples[31].center_x;
  self->secondary_samples[31].transform.position.y = 0.49000001;
  self->secondary_samples[31].transform.position.z = 31.0;
  v7 = 1;
  self->secondary_samples[31].delta_length = 1.0;
  v8 = 0;
  texture_aa = nullptr;
  do
  {
    v9 = (double)(int)texture_aa;
    v53 = v9 * 0.20943952;
    self->primary_samples[v7].center_x = (self->primary_samples[31].center_x - self->primary_samples->center_x)
                                       * v9
                                       * 0.033333335
                                       + self->primary_samples->center_x;
    self->primary_samples[v7].rotation_scalar_98 = 0.0;
    self->primary_samples[v7].rotation_scalar_94 = 0.0;
    self->primary_samples[v7].special_scalar = 0.0;
    self->primary_samples[v7].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v7].transform);
    texture_aa = (char *)(v8 + 1);
    self->primary_samples[v7].transform.position.x = 0.0;
    self->primary_samples[v7].transform.position.z = (float)(v8 + 1);
    self->primary_samples[v7].transform.position.y = 0.0;
    v54 = v53 * 3.0;
    v10 = v54;
    v45 = sine(v54) * 0.30000001;
    v55 = cosine(v45);
    v46 = sine(v10) * 0.30000001;
    v58 = sine(v46);
    p_basis_up = &self->primary_samples[v7].transform.basis_up;
    p_basis_up->x = v58;
    p_basis_up->y = v55;
    p_basis_up->z = 0.0;
    v12 = self->primary_samples;
    p_x = &v12[v7].transform.basis_forward.x;
    v65 = v12[v7].transform.position.x - v12[v7 - 1].transform.position.x;
    v68 = v12[v7].transform.position.y - v12[v7 - 1].transform.position.y;
    v14 = v12[v7].transform.position.z - v12[v7 - 1].transform.position.z;
    *p_x = v65;
    p_x[1] = v68;
    v71 = v14;
    p_x[2] = v71;
    normalize_vector((Vec3 *)&self->primary_samples[v7].transform.basis_forward);
    cross_vectors(
      (Vec3 *)&self->primary_samples[v7],
      (Vec3 *)&self->primary_samples[v7].transform.basis_up,
      (Vec3 *)&self->primary_samples[v7].transform.basis_forward);
    qmemcpy(&self->secondary_samples[v7], &self->primary_samples[v7], 0x40u);
    v15 = self->primary_samples;
    ++v8;
    v16 = v15[v7].transform.basis_up.x * 0.49000001;
    v75 = v15[v7].transform.basis_up.y * 0.49000001;
    v17 = v15[v7].transform.basis_up.z * 0.49000001;
    p_position = &self->secondary_samples[v7++].transform.position;
    v77 = v17;
    p_position->x = v16 + p_position->x;
    p_position->y = v75 + p_position->y;
    p_position->z = v77 + p_position->z;
  }
  while ( v7 < 31 );
  v19 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v20 = 0;
    do
    {
      v21 = self->primary_samples;
      v22 = &v21[v20].delta_dir_to_next.x;
      v66 = v21[v20 + 1].transform.position.x - v21[v20].transform.position.x;
      v69 = v21[v20 + 1].transform.position.y - v21[v20].transform.position.y;
      v23 = v21[v20 + 1].transform.position.z - v21[v20].transform.position.z;
      *v22 = v66;
      v22[1] = v69;
      v72 = v23;
      v22[2] = v72;
      self->primary_samples[v20].delta_length = normalize_vector(&self->primary_samples[v20].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v25 = &secondary_samples[v20].delta_dir_to_next.x;
      v59 = secondary_samples[v20 + 1].transform.position.x - secondary_samples[v20].transform.position.x;
      v61 = secondary_samples[v20 + 1].transform.position.y - secondary_samples[v20].transform.position.y;
      v26 = secondary_samples[v20 + 1].transform.position.z - secondary_samples[v20].transform.position.z;
      *v25 = v59;
      v25[1] = v61;
      v63 = v26;
      v25[2] = v63;
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
  v56 = vertices;
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
          vertices = v56;
          v78 = v35 * v36[-1].transform.basis_right.x;
          v79 = v35 * v36[-1].transform.basis_right.y;
          v39 = v35 * v36[-1].transform.basis_right.z;
          v80 = v36[-1].transform.position.z + 1.0;
          v60 = v36[-1].transform.position.x + v78;
          v62 = v36[-1].transform.position.y + v79;
          v37 = &v56[(_DWORD)&v34[v31 * (v33 + 1)]].x;
          *v37 = v60;
          v64 = v80 + v39;
          v37[1] = v62;
          v38 = v64;
        }
        else
        {
          v74 = v35 * v36->transform.basis_right.x;
          v76 = v35 * v36->transform.basis_right.y;
          v67 = v74 + v36->transform.position.x;
          v70 = v76 + v36->transform.position.y;
          v73 = v35 * v36->transform.basis_right.z + v36->transform.position.z;
          v37 = &vertices[(_DWORD)&v34[v31 * (v33 + 1)]].x;
          *v37 = v67;
          v37[1] = v70;
          v38 = v73;
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
      v47 = (double)(j % 8) * 0.125;
      v50 = (double)(j % 8 + 1) * 0.125;
      do
      {
        v42 = 0;
        v57 = v41 + 1;
        v51 = 0;
        texture_ad = (double)(int)texture_ac * 0.125;
        v48 = (double)(v41 + 1) * 0.125;
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
            v43->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, v86, 0, 0);
            v43->u0 = v48;
            v43->v0 = v47;
            v43->u1 = texture_ad;
            v43->v1 = v47;
            v43->u2 = texture_ad;
            v43->v2 = v50;
            v43->u3 = v48;
          }
          else
          {
            v43->vertex_index_a = v41 + j * (LOWORD(self->width_cells) + 1);
            v43->vertex_index_b = j * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->vertex_index_c = (j + 1) * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->vertex_index_d = v41 + (j + 1) * (LOWORD(self->width_cells) + 1);
            v43->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, v85, 0, 0);
            v43->u0 = texture_ad;
            v43->v0 = v47;
            v43->u1 = v48;
            v43->v1 = v47;
            v43->u2 = v48;
            v43->v2 = v50;
            v43->u3 = texture_ad;
          }
          v43->v3 = v50;
          if ( ++v51 >= 2 )
            break;
          v42 = v51;
        }
        ++v41;
        texture_ac = (char *)v57;
      }
      while ( v57 < (signed int)self->width_cells );
    }
  }
  return finalize_path_template_record(self);
}

