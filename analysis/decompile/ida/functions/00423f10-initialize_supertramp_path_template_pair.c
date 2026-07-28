/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_supertramp_path_template_pair @ 0x423f10 */
/* selector: initialize_supertramp_path_template_pair */

// Builds the SuperTramp attachment path-template pair; iOS Path.o names this `cRPath::BuildSuperTramp(float, float, int, bool, char*, char*, char*)`.
void __thiscall initialize_supertramp_path_template_pair(
        Path *self,
        float length,
        int32_t width_cells_,
        bool side_exit,
        char *texture_a,
        char *texture_b,
        char *unused_texture,
        char *cap_texture)
{
  double v9; // st7
  uint32_t segment_count; // eax
  int v11; // edi
  int v12; // edi
  PathTemplateSample *v13; // ecx
  PathTemplateSample *v14; // eax
  signed int v15; // ebx
  int v16; // edi
  PathTemplateSample *primary_samples; // edx
  float *p_x; // eax
  double v19; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *v21; // eax
  double v22; // st7
  Object *object; // eax
  signed int v24; // ebx
  ObjectFaceQuad *facequads; // edx
  signed int width_cells; // ecx
  signed int v27; // edi
  PathTemplateSample *v28; // eax
  double v29; // st7
  int v30; // eax
  float *v31; // ecx
  signed int j; // ebx
  int v33; // edi
  int v34; // ecx
  uint32_t v35; // eax
  ObjectFaceQuad *v36; // ebp
  char *v37; // ecx
  TextureRef *texture_ref; // eax
  ObjectFaceQuad *v39; // ebp
  float v40; // [esp+0h] [ebp-2Ch]
  int v41; // [esp+4h] [ebp-28h]
  int v42; // [esp+4h] [ebp-28h]
  float v43; // [esp+4h] [ebp-28h]
  float v44; // [esp+8h] [ebp-24h]
  int i; // [esp+8h] [ebp-24h]
  int v46; // [esp+8h] [ebp-24h]
  float v47; // [esp+Ch] [ebp-20h]
  ObjectFaceQuad *v48; // [esp+Ch] [ebp-20h]
  float v49; // [esp+10h] [ebp-1Ch]
  float v50; // [esp+10h] [ebp-1Ch]
  Vec3 *vertices; // [esp+10h] [ebp-1Ch]
  signed int v52; // [esp+10h] [ebp-1Ch]
  float v53; // [esp+14h] [ebp-18h]
  float v54; // [esp+14h] [ebp-18h]
  float v55; // [esp+18h] [ebp-14h]
  float v56; // [esp+18h] [ebp-14h]
  float v57; // [esp+1Ch] [ebp-10h]
  float v58; // [esp+20h] [ebp-Ch]
  float v59; // [esp+20h] [ebp-Ch]
  float v60; // [esp+24h] [ebp-8h]
  float v61; // [esp+24h] [ebp-8h]
  float v62; // [esp+28h] [ebp-4h]
  float v63; // [esp+28h] [ebp-4h]
  float arg2; // [esp+30h] [ebp+4h]
  int arg2a; // [esp+30h] [ebp+4h]
  int arg2b; // [esp+30h] [ebp+4h]
  float arg2c; // [esp+30h] [ebp+4h]
  int32_t arg3; // [esp+34h] [ebp+8h]
  int32_t arg3a; // [esp+34h] [ebp+8h]
  int32_t arg3b; // [esp+34h] [ebp+8h]
  float arg3c; // [esp+34h] [ebp+8h]

  self->kind = PATH_TEMPLATE_KIND_SUPERTRAMP;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = width_cells_;
  v41 = (__int64)(length * 1.0461504);
  self->width_or_scale = 1.0;
  self->segment_count = v41 + 8;
  self->segment_count_f = (float)(v41 + 7);
  v9 = (double)v41;
  v47 = v9;
  arg2 = v9 * 0.95588547;
  get_path_nodes(self);
  segment_count = self->segment_count;
  self->has_entry_mesh_transition = 0;
  arg3 = 0;
  self->segment_count = segment_count - 1;
  v11 = 0;
  do
  {
    self->primary_samples[v11].center_x = 0.0;
    self->primary_samples[v11].rotation_scalar_98 = 0.0;
    self->primary_samples[v11].rotation_scalar_94 = 0.0;
    self->primary_samples[v11].special_scalar = 0.0;
    self->primary_samples[v11].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v11].transform);
    self->primary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
    v49 = (float)arg3;
    self->primary_samples[v11].transform.position.y = 0.0;
    self->primary_samples[v11].transform.position.z = v49;
    self->primary_samples[v11].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v11].transform);
    self->secondary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
    self->secondary_samples[v11].transform.position.y = 0.49000001;
    self->secondary_samples[v11++].transform.position.z = v49;
    self->secondary_samples[v11 - 1].delta_length = 1.0;
    ++arg3;
  }
  while ( v11 < 7 );
  arg3a = 0;
  if ( v41 >= 0 )
  {
    v44 = arg2 - 0.49000001;
    v12 = 7;
    do
    {
      self->primary_samples[v12].center_x = 0.0;
      self->primary_samples[v12].rotation_scalar_98 = 0.0;
      self->primary_samples[v12].rotation_scalar_94 = 0.0;
      self->primary_samples[v12].special_scalar = 0.0;
      self->primary_samples[v12].lateral_scale = 1.0;
      v50 = (double)arg3a * 1.0461504 / v47;
      set_matrix_identity(&self->primary_samples[v12].transform);
      self->primary_samples[v12].transform.position.x = self->primary_samples[v12].center_x;
      self->primary_samples[v12].transform.position.z = sine(v50) * arg2 + 7.0;
      self->primary_samples[v12].transform.position.y = arg2 - cosine(v50) * arg2;
      set_matrix_identity(&self->secondary_samples[v12].transform);
      self->secondary_samples[v12].transform.position.x = self->primary_samples[v12].center_x;
      self->secondary_samples[v12].transform.position.z = sine(v50) * v44 + 7.0;
      self->secondary_samples[v12].transform.position.y = arg2 - cosine(v50) * v44;
      v13 = &self->primary_samples[v12];
      v13->transform.basis_right.x = 1.0;
      v13->transform.basis_right.y = 0.0;
      v13->transform.basis_right.z = 0.0;
      self->primary_samples[v12].transform.basis_up.x = 0.0;
      self->primary_samples[v12].transform.basis_up.y = arg2 - self->primary_samples[v12].transform.position.y;
      self->primary_samples[v12].transform.basis_up.z = 7.0 - self->primary_samples[v12].transform.position.z;
      normalize_vector(&self->primary_samples[v12].transform.basis_up);
      cross_vectors(
        &self->primary_samples[v12].transform.basis_forward,
        &self->primary_samples[v12].transform.basis_right,
        &self->primary_samples[v12].transform.basis_up);
      v14 = &self->secondary_samples[v12];
      v14->transform.basis_right.x = 1.0;
      v14->transform.basis_right.y = 0.0;
      v14->transform.basis_right.z = 0.0;
      self->secondary_samples[v12].transform.basis_up.x = 0.0;
      self->secondary_samples[v12].transform.basis_up.y = arg2 - self->secondary_samples[v12].transform.position.y;
      self->secondary_samples[v12].transform.basis_up.z = 7.0 - self->secondary_samples[v12].transform.position.z;
      normalize_vector(&self->secondary_samples[v12].transform.basis_up);
      cross_vectors(
        &self->secondary_samples[v12].transform.basis_forward,
        &self->secondary_samples[v12].transform.basis_right,
        &self->secondary_samples[v12].transform.basis_up);
      ++v12;
      ++arg3a;
    }
    while ( arg3a <= v41 );
  }
  v15 = 0;
  if ( (int)self->segment_count > 0 )
  {
    v16 = 0;
    do
    {
      primary_samples = self->primary_samples;
      p_x = &primary_samples[v16].delta_dir_to_next.x;
      v58 = primary_samples[v16 + 1].transform.position.x - primary_samples[v16].transform.position.x;
      v60 = primary_samples[v16 + 1].transform.position.y - primary_samples[v16].transform.position.y;
      v19 = primary_samples[v16 + 1].transform.position.z - primary_samples[v16].transform.position.z;
      *p_x = v58;
      p_x[1] = v60;
      v62 = v19;
      p_x[2] = v62;
      self->primary_samples[v16].delta_length = normalize_vector(&self->primary_samples[v16].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v21 = &secondary_samples[v16].delta_dir_to_next.x;
      v53 = secondary_samples[v16 + 1].transform.position.x - secondary_samples[v16].transform.position.x;
      v55 = secondary_samples[v16 + 1].transform.position.y - secondary_samples[v16].transform.position.y;
      v22 = secondary_samples[v16 + 1].transform.position.z - secondary_samples[v16].transform.position.z;
      *v21 = v53;
      v21[1] = v55;
      v57 = v22;
      v21[2] = v57;
      ++v15;
      self->secondary_samples[v16].delta_length = normalize_vector(&self->secondary_samples[v16].delta_dir_to_next);
      ++v16;
    }
    while ( v15 < (signed int)self->segment_count );
  }
  request_object_vertices(self->bod.object, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->bod.object, 2 * self->segment_count * self->width_cells);
  object = self->bod.object;
  v24 = 0;
  arg3b = 0;
  vertices = object->vertices;
  facequads = object->facequads;
  v48 = facequads;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v42 = 0;
    do
    {
      width_cells = self->width_cells;
      v27 = 0;
      arg2a = 0;
      for ( i = width_cells; v27 <= width_cells; i = width_cells )
      {
        v28 = &self->primary_samples[v42];
        v24 = arg3b;
        v29 = (double)arg2a - (double)i * 0.5;
        v54 = v29 * v28->transform.basis_right.x;
        v56 = v29 * v28->transform.basis_right.y;
        v59 = v54 + v28->transform.position.x;
        v61 = v56 + v28->transform.position.y;
        v63 = v29 * v28->transform.basis_right.z + v28->transform.position.z;
        v30 = v27 + arg3b * (width_cells + 1);
        arg2a = ++v27;
        v31 = &vertices[v30].x;
        *v31 = v59;
        v31[1] = v61;
        v31[2] = v63;
        width_cells = self->width_cells;
      }
      arg3b = ++v24;
      ++v42;
    }
    while ( v24 <= (signed int)self->segment_count );
  }
  for ( j = 0; j < (signed int)self->segment_count; ++j )
  {
    v33 = 0;
    arg2b = 0;
    if ( (int)self->width_cells <= 0 )
      continue;
    arg3c = (double)(j % 8) * 0.125;
    v43 = (double)(j % 8 + 1) * 0.125;
    do
    {
      v34 = 0;
      v52 = v33 + 1;
      v46 = 0;
      arg2c = (double)arg2b * 0.125;
      v40 = (double)(v33 + 1) * 0.125;
      while ( 1 )
      {
        v35 = v34 + 2 * (v33 + j * self->width_cells);
        if ( v34 == 0 )
        {
          v36 = &facequads[v35];
          v36->header_word = 0;
          v36->vertex_0 = v33 + j * (LOWORD(self->width_cells) + 1);
          v36->vertex_1 = j * (LOWORD(self->width_cells) + 1) + v33 + 1;
          v36->vertex_2 = (j + 1) * (LOWORD(self->width_cells) + 1) + v33 + 1;
          v36->vertex_3 = v33 + (j + 1) * (LOWORD(self->width_cells) + 1);
          if ( j == self->segment_count - 1 )
          {
            v37 = cap_texture;
            goto LABEL_22;
          }
          if ( (((unsigned __int8)j ^ (unsigned __int8)v33) & 1) != 0 )
          {
            v37 = texture_a;
LABEL_22:
            texture_ref = get_or_create_texture_ref(&g_texture_refs, v37, nullptr, 0);
          }
          else
          {
            texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
          }
          v36->texture_ref = texture_ref;
          v36->uv[0].u = arg2c;
          v36->uv[0].v = arg3c;
          v36->uv[1].u = v40;
          v36->uv[1].v = arg3c;
          v36->uv[2].u = v40;
          v36->uv[2].v = v43;
          v36->uv[3].u = arg2c;
          v36->uv[3].v = v43;
          goto LABEL_28;
        }
        v39 = &facequads[v35];
        v39->header_word = 0;
        v39->vertex_0 = j * (LOWORD(self->width_cells) + 1) + v33 + 1;
        v39->vertex_1 = v33 + j * (LOWORD(self->width_cells) + 1);
        v39->vertex_2 = v33 + (j + 1) * (LOWORD(self->width_cells) + 1);
        v39->vertex_3 = (j + 1) * (LOWORD(self->width_cells) + 1) + v33 + 1;
        v39->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_b, nullptr, 0);
        v39->uv[0].u = v40;
        v39->uv[0].v = arg3c;
        v39->uv[1].u = arg2c;
        v39->uv[1].v = arg3c;
        v39->uv[2].u = arg2c;
        v39->uv[2].v = v43;
        v39->uv[3].u = v40;
        v39->uv[3].v = v43;
LABEL_28:
        if ( ++v46 >= 2 )
          break;
        v34 = v46;
        facequads = v48;
      }
      ++v33;
      facequads = v48;
      arg2b = v52;
    }
    while ( v52 < (signed int)self->width_cells );
  }
  calc_path_length_z(self);
}
