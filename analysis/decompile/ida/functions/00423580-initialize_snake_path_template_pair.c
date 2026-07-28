/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_snake_path_template_pair @ 0x423580 */
/* selector: initialize_snake_path_template_pair */

// Builds the Snake attachment path-template pair; iOS Path.o names this `cRPath::BuildSnake(float, int, bool, char*, char*)`.
void __thiscall initialize_snake_path_template_pair(
        Path *self,
        float scale_arg,
        int32_t width_cells_,
        bool side_exit,
        char *texture_a,
        char *texture_b,
        char *cap_texture)
{
  signed int v8; // ebx
  int v9; // edi
  int v10; // ebp
  int v11; // edi
  int i; // edi
  PathTemplateSample *primary_samples; // ebp
  PathTemplateSample *v14; // edx
  PathTemplateSample *v15; // ecx
  float *p_x; // eax
  double v17; // st7
  PathTemplateSample *v18; // eax
  PathTemplateSample *secondary_samples; // edx
  float *v20; // eax
  double v21; // st7
  signed int v22; // ebp
  int v23; // edi
  PathTemplateSample *v24; // eax
  double v25; // st7
  double v26; // st7
  PathTemplateSample *v27; // ecx
  float *v28; // eax
  double v29; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v31; // ecx
  Object *object; // eax
  signed int v33; // edx
  Vec3 *vertices; // ebp
  signed int width_cells; // ecx
  char *v36; // edi
  double v37; // st7
  float *v38; // eax
  float *v39; // eax
  float v40; // ecx
  double v41; // st7
  int v42; // edi
  int v43; // ecx
  ObjectFaceQuad *v44; // ebp
  float v45; // [esp+0h] [ebp-68h]
  float v46; // [esp+14h] [ebp-54h]
  float v47; // [esp+18h] [ebp-50h]
  int j; // [esp+1Ch] [ebp-4Ch]
  float v49; // [esp+1Ch] [ebp-4Ch]
  float v50; // [esp+20h] [ebp-48h]
  int v51; // [esp+20h] [ebp-48h]
  ObjectFaceQuad *facequads; // [esp+24h] [ebp-44h]
  float v53; // [esp+28h] [ebp-40h]
  float v54; // [esp+28h] [ebp-40h]
  Vec3 *v55; // [esp+28h] [ebp-40h]
  signed int v56; // [esp+28h] [ebp-40h]
  float v57; // [esp+2Ch] [ebp-3Ch]
  float v58; // [esp+30h] [ebp-38h]
  float v59; // [esp+38h] [ebp-30h]
  float v60; // [esp+38h] [ebp-30h]
  float v61; // [esp+3Ch] [ebp-2Ch]
  float v62; // [esp+3Ch] [ebp-2Ch]
  float v63; // [esp+40h] [ebp-28h]
  float v64; // [esp+44h] [ebp-24h]
  float v65; // [esp+44h] [ebp-24h]
  float v66; // [esp+48h] [ebp-20h]
  float v67; // [esp+48h] [ebp-20h]
  float v68; // [esp+4Ch] [ebp-1Ch]
  float v69; // [esp+4Ch] [ebp-1Ch]
  float v70; // [esp+50h] [ebp-18h]
  float v71; // [esp+50h] [ebp-18h]
  float v72; // [esp+50h] [ebp-18h]
  float v73; // [esp+54h] [ebp-14h]
  float v74; // [esp+54h] [ebp-14h]
  float v75; // [esp+54h] [ebp-14h]
  float v76; // [esp+58h] [ebp-10h]
  float v77; // [esp+58h] [ebp-10h]
  float v78; // [esp+58h] [ebp-10h]
  float v79; // [esp+64h] [ebp-4h]
  char *texture_aa; // [esp+70h] [ebp+8h]
  int texture_ab; // [esp+70h] [ebp+8h]
  float texture_ag; // [esp+70h] [ebp+8h]
  char *texture_ac; // [esp+70h] [ebp+8h]
  char *texture_ad; // [esp+70h] [ebp+8h]
  char *texture_ae; // [esp+70h] [ebp+8h]
  float texture_af; // [esp+70h] [ebp+8h]

  v8 = 0;
  self->kind = PATH_TEMPLATE_KIND_SNAKE;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = width_cells_;
  self->width_or_scale = 1.0;
  self->segment_count = 27;
  self->segment_count_f = 27.0;
  get_path_nodes(self);
  self->has_entry_mesh_transition = 0;
  texture_aa = nullptr;
  v9 = 0;
  do
  {
    self->primary_samples[v9].center_x = 0.0;
    self->primary_samples[v9].rotation_scalar_98 = 0.0;
    self->primary_samples[v9].rotation_scalar_94 = 0.0;
    self->primary_samples[v9].special_scalar = 0.0;
    self->primary_samples[v9].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v9].transform);
    self->primary_samples[v9].transform.position.x = 0.0;
    v53 = (float)(int)texture_aa;
    self->primary_samples[v9].transform.position.y = 0.0;
    self->primary_samples[v9].transform.position.z = v53;
    set_matrix_identity(&self->secondary_samples[v9++].transform);
    self->secondary_samples[v9 - 1].transform.position.x = 0.0;
    self->secondary_samples[v9 - 1].transform.position.y = 0.49000001;
    self->secondary_samples[v9 - 1].transform.position.z = v53;
    ++texture_aa;
  }
  while ( v9 < 6 );
  v10 = 24;
  v11 = 24;
  texture_ab = 24;
  do
  {
    self->primary_samples[v11].center_x = 4.0 - (double)(int)self->width_cells * 0.5;
    self->primary_samples[v11].rotation_scalar_98 = 0.0;
    self->primary_samples[v11].rotation_scalar_94 = 0.0;
    self->primary_samples[v11].special_scalar = 0.0;
    self->primary_samples[v11].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v11].transform);
    texture_ag = (float)texture_ab;
    self->primary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
    self->primary_samples[v11].transform.position.y = 0.0;
    self->primary_samples[v11].transform.position.z = texture_ag;
    set_matrix_identity(&self->secondary_samples[v11].transform);
    self->secondary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
    self->secondary_samples[v11].transform.position.y = 0.49000001;
    self->secondary_samples[v11++].transform.position.z = texture_ag;
    texture_ab = ++v10;
  }
  while ( v10 - 24 < 3 );
  texture_ac = nullptr;
  for ( i = 6; i < 24; ++i )
  {
    primary_samples = self->primary_samples;
    v50 = (double)(int)texture_ac * 0.34906587;
    v45 = v50 * 0.5;
    primary_samples[i].center_x = (0.5 - cosine(v45) * 0.5) * primary_samples[24].center_x;
    self->primary_samples[i].rotation_scalar_98 = 0.0;
    self->primary_samples[i].rotation_scalar_94 = 0.0;
    self->primary_samples[i].special_scalar = 0.0;
    self->primary_samples[i].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[i].transform);
    self->primary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->primary_samples[i].transform.position.y = -(1.0 - cosine(v50));
    v54 = (float)(int)(texture_ac + 6);
    self->primary_samples[i].transform.position.z = v54;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->secondary_samples[i].transform.position.y = 0.49000001 - (1.0 - cosine(v50));
    self->secondary_samples[i].transform.position.z = v54;
    if ( i <= 6 )
    {
      set_matrix_rotation_identity(&self->primary_samples[i - 1].transform);
      set_matrix_rotation_identity(&self->secondary_samples[i - 1].transform);
    }
    else
    {
      v14 = &self->primary_samples[i - 1];
      v14->transform.basis_right.x = 1.0;
      v14->transform.basis_right.y = 0.0;
      v14->transform.basis_right.z = 0.0;
      v15 = self->primary_samples;
      p_x = &v15[i - 1].transform.basis_forward.x;
      v59 = v15[i].transform.position.x - v15[i - 1].transform.position.x;
      v61 = p_x[47] - p_x[5];
      v17 = p_x[48] - p_x[6];
      *p_x = v59;
      p_x[1] = v61;
      v63 = v17;
      p_x[2] = v63;
      normalize_vector(&self->primary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        &self->primary_samples[i - 1].transform.basis_up,
        &self->primary_samples[i - 1].transform.basis_forward,
        &self->primary_samples[i - 1].transform.basis_right);
      v18 = &self->secondary_samples[i - 1];
      v18->transform.basis_right.x = 1.0;
      v18->transform.basis_right.y = 0.0;
      v18->transform.basis_right.z = 0.0;
      secondary_samples = self->secondary_samples;
      v20 = &secondary_samples[i - 1].transform.basis_forward.x;
      v70 = secondary_samples[i].transform.position.x - secondary_samples[i - 1].transform.position.x;
      v73 = v20[47] - v20[5];
      v21 = v20[48] - v20[6];
      *v20 = v70;
      v20[1] = v73;
      v76 = v21;
      v20[2] = v76;
      normalize_vector(&self->secondary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        &self->secondary_samples[i - 1].transform.basis_up,
        &self->secondary_samples[i - 1].transform.basis_forward,
        &self->secondary_samples[i - 1].transform.basis_right);
    }
    ++texture_ac;
  }
  v22 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v23 = 0;
    do
    {
      v24 = &self->primary_samples[v23];
      v25 = v24[1].transform.position.x - v24->transform.position.x;
      v24 = (PathTemplateSample *)((char *)v24 + 128);
      v71 = v25;
      v74 = v24->inverse_matrix.basis_up_w - v24[-1].inverse_matrix.basis_up_w;
      v26 = v24->inverse_matrix.basis_forward.x - v24[-1].inverse_matrix.basis_forward.x;
      v24->transform.basis_right.x = v71;
      v24->transform.basis_right.y = v74;
      v77 = v26;
      v24->transform.basis_right.z = v77;
      self->primary_samples[v23].delta_length = normalize_vector(&self->primary_samples[v23].delta_dir_to_next);
      v27 = self->secondary_samples;
      v28 = &v27[v23].delta_dir_to_next.x;
      v64 = v27[v23 + 1].transform.position.x - v27[v23].transform.position.x;
      v66 = v27[v23 + 1].transform.position.y - v27[v23].transform.position.y;
      v29 = v27[v23 + 1].transform.position.z - v27[v23].transform.position.z;
      *v28 = v64;
      v28[1] = v66;
      v68 = v29;
      v28[2] = v68;
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
  request_object_vertices(self->bod.object, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->bod.object, 2 * self->segment_count * self->width_cells);
  object = self->bod.object;
  v33 = 0;
  vertices = object->vertices;
  v55 = vertices;
  facequads = object->facequads;
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
        v38 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v8);
        if ( v33 == self->segment_count )
        {
          vertices = v55;
          v57 = v37 * *(v38 - 42);
          v58 = v37 * *(v38 - 41);
          v41 = v37 * *(v38 - 40);
          v79 = *(v38 - 28) + 1.0;
          v65 = *(v38 - 30) + v57;
          v67 = *(v38 - 29) + v58;
          v39 = &v55[(_DWORD)&v36[v33 * (width_cells + 1)]].x;
          *v39 = v65;
          v69 = v79 + v41;
          v39[1] = v67;
          v40 = v69;
        }
        else
        {
          v60 = v37 * *v38;
          v62 = v37 * v38[1];
          v72 = v60 + v38[12];
          v75 = v62 + v38[13];
          v78 = v37 * v38[2] + v38[14];
          v39 = &vertices[(_DWORD)&v36[v33 * (width_cells + 1)]].x;
          *v39 = v72;
          v39[1] = v75;
          v40 = v78;
        }
        v39[2] = v40;
        width_cells = self->width_cells;
        ++v36;
        j = width_cells;
      }
      ++v33;
      v8 += 168;
    }
    while ( v33 <= (signed int)self->segment_count );
    v8 = 0;
  }
  if ( (int)self->segment_count > 0 )
  {
    do
    {
      v42 = 0;
      texture_ae = nullptr;
      if ( (int)self->width_cells > 0 )
      {
        v46 = (double)(v8 % 8) * 0.125;
        v49 = (double)(v8 % 8 + 1) * 0.125;
        do
        {
          v43 = 0;
          v56 = v42 + 1;
          v51 = 0;
          texture_af = (double)(int)texture_ae * 0.125;
          v47 = (double)(v42 + 1) * 0.125;
          while ( 1 )
          {
            v44 = &facequads[2 * v42 + 2 * v8 * self->width_cells + v43];
            v44->header_word = 0;
            if ( v43 != 0 )
            {
              v44->vertex_0 = v8 * (LOWORD(self->width_cells) + 1) + v42 + 1;
              v44->vertex_1 = v42 + v8 * (LOWORD(self->width_cells) + 1);
              v44->vertex_2 = v42 + (v8 + 1) * (LOWORD(self->width_cells) + 1);
              v44->vertex_3 = (v8 + 1) * (LOWORD(self->width_cells) + 1) + v42 + 1;
              v44->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_b, nullptr, 0);
              v44->uv[0].u = v47;
              v44->uv[0].v = v46;
              v44->uv[1].u = texture_af;
              v44->uv[1].v = v46;
              v44->uv[2].u = texture_af;
              v44->uv[2].v = v49;
              v44->uv[3].u = v47;
            }
            else
            {
              v44->vertex_0 = v42 + v8 * (LOWORD(self->width_cells) + 1);
              v44->vertex_1 = v8 * (LOWORD(self->width_cells) + 1) + v42 + 1;
              v44->vertex_2 = (v8 + 1) * (LOWORD(self->width_cells) + 1) + v42 + 1;
              v44->vertex_3 = v42 + (v8 + 1) * (LOWORD(self->width_cells) + 1);
              v44->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
              v44->uv[0].u = texture_af;
              v44->uv[0].v = v46;
              v44->uv[1].u = v47;
              v44->uv[1].v = v46;
              v44->uv[2].u = v47;
              v44->uv[2].v = v49;
              v44->uv[3].u = texture_af;
            }
            v44->uv[3].v = v49;
            if ( ++v51 >= 2 )
              break;
            v43 = v51;
          }
          ++v42;
          texture_ae = (char *)v56;
        }
        while ( v56 < (signed int)self->width_cells );
      }
      ++v8;
    }
    while ( v8 < (signed int)self->segment_count );
  }
  calc_path_length_z(self);
}
