/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_snake_path_template_pair @ 0x423580 */
/* selector: initialize_snake_path_template_pair */

int32_t __thiscall initialize_snake_path_template_pair(
        PathTemplate *self,
        int32_t arg2,
        char *texture_a,
        char *texture_b)
{
  signed int v5; // ebx
  int v6; // edi
  int v7; // ebp
  int v8; // edi
  int i; // edi
  PathTemplateSample *primary_samples; // ebp
  PathTemplateSample *v11; // edx
  PathTemplateSample *v12; // ecx
  float *p_x; // eax
  double v14; // st7
  PathTemplateSample *v15; // eax
  PathTemplateSample *secondary_samples; // edx
  float *v17; // eax
  double v18; // st7
  signed int v19; // ebp
  int v20; // edi
  float *v21; // eax
  double v22; // st7
  double v23; // st7
  PathTemplateSample *v24; // ecx
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
  float v43; // [esp+0h] [ebp-68h]
  float v44; // [esp+14h] [ebp-54h]
  float v45; // [esp+18h] [ebp-50h]
  int j; // [esp+1Ch] [ebp-4Ch]
  float v47; // [esp+1Ch] [ebp-4Ch]
  float v48; // [esp+20h] [ebp-48h]
  int v49; // [esp+20h] [ebp-48h]
  ObjectFaceQuad *facequads; // [esp+24h] [ebp-44h]
  float v51; // [esp+28h] [ebp-40h]
  float v52; // [esp+28h] [ebp-40h]
  Vec3 *v53; // [esp+28h] [ebp-40h]
  signed int v54; // [esp+28h] [ebp-40h]
  float v55; // [esp+2Ch] [ebp-3Ch]
  float v56; // [esp+30h] [ebp-38h]
  float v57; // [esp+38h] [ebp-30h]
  float v58; // [esp+38h] [ebp-30h]
  float v59; // [esp+3Ch] [ebp-2Ch]
  float v60; // [esp+3Ch] [ebp-2Ch]
  float v61; // [esp+40h] [ebp-28h]
  float v62; // [esp+44h] [ebp-24h]
  float v63; // [esp+44h] [ebp-24h]
  float v64; // [esp+48h] [ebp-20h]
  float v65; // [esp+48h] [ebp-20h]
  float v66; // [esp+4Ch] [ebp-1Ch]
  float v67; // [esp+4Ch] [ebp-1Ch]
  float v68; // [esp+50h] [ebp-18h]
  float v69; // [esp+50h] [ebp-18h]
  float v70; // [esp+50h] [ebp-18h]
  float v71; // [esp+54h] [ebp-14h]
  float v72; // [esp+54h] [ebp-14h]
  float v73; // [esp+54h] [ebp-14h]
  float v74; // [esp+58h] [ebp-10h]
  float v75; // [esp+58h] [ebp-10h]
  float v76; // [esp+58h] [ebp-10h]
  float v77; // [esp+64h] [ebp-4h]
  char *texture_aa; // [esp+70h] [ebp+8h]
  int texture_ab; // [esp+70h] [ebp+8h]
  float texture_ag; // [esp+70h] [ebp+8h]
  char *texture_ac; // [esp+70h] [ebp+8h]
  char *texture_ad; // [esp+70h] [ebp+8h]
  char *texture_ae; // [esp+70h] [ebp+8h]
  float texture_af; // [esp+70h] [ebp+8h]
  char *v85; // [esp+78h] [ebp+10h]
  char *v86; // [esp+7Ch] [ebp+14h]

  v5 = 0;
  self->kind = PATH_TEMPLATE_KIND_SNAKE;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = (uint32_t)texture_a;
  self->width_or_scale = 1.0;
  self->segment_count = 27;
  self->segment_count_f = 27.0;
  allocate_path_nodes(self);
  self->special_runtime_flag_9c = 0;
  texture_aa = nullptr;
  v6 = 0;
  do
  {
    self->primary_samples[v6].center_x = 0.0;
    self->primary_samples[v6].rotation_scalar_98 = 0.0;
    self->primary_samples[v6].rotation_scalar_94 = 0.0;
    self->primary_samples[v6].special_scalar = 0.0;
    self->primary_samples[v6].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v6].transform);
    self->primary_samples[v6].transform.position.x = 0.0;
    v51 = (float)(int)texture_aa;
    self->primary_samples[v6].transform.position.y = 0.0;
    self->primary_samples[v6].transform.position.z = v51;
    set_matrix_identity(&self->secondary_samples[v6++].transform);
    self->secondary_samples[v6 - 1].transform.position.x = 0.0;
    self->secondary_samples[v6 - 1].transform.position.y = 0.49000001;
    self->secondary_samples[v6 - 1].transform.position.z = v51;
    ++texture_aa;
  }
  while ( v6 < 6 );
  v7 = 24;
  v8 = 24;
  texture_ab = 24;
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
  while ( v7 - 24 < 3 );
  texture_ac = nullptr;
  for ( i = 6; i < 24; ++i )
  {
    primary_samples = self->primary_samples;
    v48 = (double)(int)texture_ac * 0.34906587;
    v43 = v48 * 0.5;
    primary_samples[i].center_x = (0.5 - cosine(v43) * 0.5) * primary_samples[24].center_x;
    self->primary_samples[i].rotation_scalar_98 = 0.0;
    self->primary_samples[i].rotation_scalar_94 = 0.0;
    self->primary_samples[i].special_scalar = 0.0;
    self->primary_samples[i].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[i].transform);
    self->primary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->primary_samples[i].transform.position.y = -(1.0 - cosine(v48));
    v52 = (float)(int)(texture_ac + 6);
    self->primary_samples[i].transform.position.z = v52;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->secondary_samples[i].transform.position.y = 0.49000001 - (1.0 - cosine(v48));
    self->secondary_samples[i].transform.position.z = v52;
    if ( i <= 6 )
    {
      set_matrix_rotation_identity(&self->primary_samples[i - 1].transform);
      set_matrix_rotation_identity(&self->secondary_samples[i - 1].transform);
    }
    else
    {
      v11 = &self->primary_samples[i - 1];
      v11->transform.basis_right.x = 1.0;
      v11->transform.basis_right.y = 0.0;
      v11->transform.basis_right.z = 0.0;
      v12 = self->primary_samples;
      p_x = &v12[i - 1].transform.basis_forward.x;
      v57 = v12[i].transform.position.x - v12[i - 1].transform.position.x;
      v59 = p_x[47] - p_x[5];
      v14 = p_x[48] - p_x[6];
      *p_x = v57;
      p_x[1] = v59;
      v61 = v14;
      p_x[2] = v61;
      normalize_vector((Vec3 *)&self->primary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&self->primary_samples[i - 1].transform.basis_up,
        (Vec3 *)&self->primary_samples[i - 1].transform.basis_forward,
        (Vec3 *)&self->primary_samples[i - 1]);
      v15 = &self->secondary_samples[i - 1];
      v15->transform.basis_right.x = 1.0;
      v15->transform.basis_right.y = 0.0;
      v15->transform.basis_right.z = 0.0;
      secondary_samples = self->secondary_samples;
      v17 = &secondary_samples[i - 1].transform.basis_forward.x;
      v68 = secondary_samples[i].transform.position.x - secondary_samples[i - 1].transform.position.x;
      v71 = v17[47] - v17[5];
      v18 = v17[48] - v17[6];
      *v17 = v68;
      v17[1] = v71;
      v74 = v18;
      v17[2] = v74;
      normalize_vector((Vec3 *)&self->secondary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&self->secondary_samples[i - 1].transform.basis_up,
        (Vec3 *)&self->secondary_samples[i - 1].transform.basis_forward,
        (Vec3 *)&self->secondary_samples[i - 1]);
    }
    ++texture_ac;
  }
  v19 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v20 = 0;
    do
    {
      v21 = &self->primary_samples[v20].transform.basis_right.x;
      v22 = v21[54] - v21[12];
      v21 += 32;
      v69 = v22;
      v72 = v21[23] - *(v21 - 19);
      v23 = v21[24] - *(v21 - 18);
      *v21 = v69;
      v21[1] = v72;
      v75 = v23;
      v21[2] = v75;
      self->primary_samples[v20].delta_length = normalize_vector(&self->primary_samples[v20].delta_dir_to_next);
      v24 = self->secondary_samples;
      v25 = &v24[v20].delta_dir_to_next.x;
      v62 = v24[v20 + 1].transform.position.x - v24[v20].transform.position.x;
      v64 = v24[v20 + 1].transform.position.y - v24[v20].transform.position.y;
      v26 = v24[v20 + 1].transform.position.z - v24[v20].transform.position.z;
      *v25 = v62;
      v25[1] = v64;
      v66 = v26;
      v25[2] = v66;
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
  v53 = vertices;
  facequads = strip_mesh->facequads;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    do
    {
      width_cells = self->width_cells;
      v33 = nullptr;
      texture_ad = nullptr;
      for ( j = width_cells; (int)v33 <= width_cells; texture_ad = v33 )
      {
        v34 = (double)(int)texture_ad - (double)j * 0.5;
        v35 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v5);
        if ( v30 == self->segment_count )
        {
          vertices = v53;
          v55 = v34 * *(v35 - 42);
          v56 = v34 * *(v35 - 41);
          v38 = v34 * *(v35 - 40);
          v77 = *(v35 - 28) + 1.0;
          v63 = *(v35 - 30) + v55;
          v65 = *(v35 - 29) + v56;
          v36 = &v53[(_DWORD)&v33[v30 * (width_cells + 1)]].x;
          *v36 = v63;
          v67 = v77 + v38;
          v36[1] = v65;
          v37 = v67;
        }
        else
        {
          v58 = v34 * *v35;
          v60 = v34 * v35[1];
          v70 = v58 + v35[12];
          v73 = v60 + v35[13];
          v76 = v34 * v35[2] + v35[14];
          v36 = &vertices[(_DWORD)&v33[v30 * (width_cells + 1)]].x;
          *v36 = v70;
          v36[1] = v73;
          v37 = v76;
        }
        v36[2] = v37;
        width_cells = self->width_cells;
        ++v33;
        j = width_cells;
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
        v44 = (double)(v5 % 8) * 0.125;
        v47 = (double)(v5 % 8 + 1) * 0.125;
        do
        {
          v40 = 0;
          v54 = v39 + 1;
          v49 = 0;
          texture_af = (double)(int)texture_ae * 0.125;
          v45 = (double)(v39 + 1) * 0.125;
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
              v41->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, v86, 0, 0);
              v41->u0 = v45;
              v41->v0 = v44;
              v41->u1 = texture_af;
              v41->v1 = v44;
              v41->u2 = texture_af;
              v41->v2 = v47;
              v41->u3 = v45;
            }
            else
            {
              v41->vertex_index_a = v39 + v5 * (LOWORD(self->width_cells) + 1);
              v41->vertex_index_b = v5 * (LOWORD(self->width_cells) + 1) + v39 + 1;
              v41->vertex_index_c = (v5 + 1) * (LOWORD(self->width_cells) + 1) + v39 + 1;
              v41->vertex_index_d = v39 + (v5 + 1) * (LOWORD(self->width_cells) + 1);
              v41->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, v85, 0, 0);
              v41->u0 = texture_af;
              v41->v0 = v44;
              v41->u1 = v45;
              v41->v1 = v44;
              v41->u2 = v45;
              v41->v2 = v47;
              v41->u3 = texture_af;
            }
            v41->v3 = v47;
            if ( ++v49 >= 2 )
              break;
            v40 = v49;
          }
          ++v39;
          texture_ae = (char *)v54;
        }
        while ( v54 < (signed int)self->width_cells );
      }
      ++v5;
    }
    while ( v5 < (signed int)self->segment_count );
  }
  return finalize_path_template_record(self);
}

