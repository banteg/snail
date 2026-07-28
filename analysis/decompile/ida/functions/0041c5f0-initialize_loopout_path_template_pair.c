/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_loopout_path_template_pair @ 0x41c5f0 */
/* selector: initialize_loopout_path_template_pair */

// Builds the LoopOut attachment path-template pair; iOS Path.o names this `cRPath::BuildLoopOut(float, int, bool, char*, char*)`.
void __thiscall initialize_loopout_path_template_pair(
        Path *self,
        float curve_source,
        int32_t width_cells_,
        bool side_exit,
        char *texture_a,
        char *texture_b,
        char *cap_texture)
{
  double v8; // st7
  int v9; // edi
  int v10; // ebx
  int v11; // edi
  double v12; // st7
  int v13; // edi
  double v14; // st7
  float *p_center_x; // ebx
  PathTemplateSample *v16; // ecx
  PathTemplateSample *v17; // eax
  signed int v18; // ebx
  int v19; // edi
  PathTemplateSample *v20; // eax
  double v21; // st7
  double v22; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *p_x; // eax
  double v25; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v27; // ecx
  Object *object; // eax
  signed int v29; // edi
  int v30; // edx
  signed int width_cells; // ecx
  signed int v32; // ebx
  double v33; // st7
  float *v34; // eax
  float *v35; // ecx
  double v36; // st7
  float *v37; // edx
  signed int i; // ebx
  int v39; // edi
  int v40; // ecx
  ObjectFaceQuad *v41; // ebp
  float v42; // [esp+0h] [ebp-64h]
  int v43; // [esp+14h] [ebp-50h]
  float v44; // [esp+14h] [ebp-50h]
  float v45; // [esp+18h] [ebp-4Ch]
  float v46; // [esp+18h] [ebp-4Ch]
  float v47; // [esp+18h] [ebp-4Ch]
  float v48; // [esp+1Ch] [ebp-48h]
  int v49; // [esp+1Ch] [ebp-48h]
  int v50; // [esp+1Ch] [ebp-48h]
  float v51; // [esp+20h] [ebp-44h]
  Vec3 *vertices; // [esp+20h] [ebp-44h]
  signed int v53; // [esp+20h] [ebp-44h]
  ObjectFaceQuad *facequads; // [esp+24h] [ebp-40h]
  float v55; // [esp+28h] [ebp-3Ch]
  float v56; // [esp+28h] [ebp-3Ch]
  float v57; // [esp+2Ch] [ebp-38h]
  float v58; // [esp+2Ch] [ebp-38h]
  float v59; // [esp+30h] [ebp-34h]
  float v60; // [esp+30h] [ebp-34h]
  float v61; // [esp+34h] [ebp-30h]
  float v62; // [esp+34h] [ebp-30h]
  float v63; // [esp+38h] [ebp-2Ch]
  float v64; // [esp+38h] [ebp-2Ch]
  float v65; // [esp+3Ch] [ebp-28h]
  float v66; // [esp+3Ch] [ebp-28h]
  float v67; // [esp+40h] [ebp-24h]
  float v68; // [esp+44h] [ebp-20h]
  float v69; // [esp+44h] [ebp-20h]
  float v70; // [esp+4Ch] [ebp-18h]
  float v71; // [esp+50h] [ebp-14h]
  float v72; // [esp+60h] [ebp-4h]
  float arg2; // [esp+68h] [ebp+4h]
  int arg2a; // [esp+68h] [ebp+4h]
  int arg2b; // [esp+68h] [ebp+4h]
  float arg2c; // [esp+68h] [ebp+4h]
  int32_t arg3; // [esp+6Ch] [ebp+8h]
  int32_t arg3a; // [esp+6Ch] [ebp+8h]
  float arg3e; // [esp+6Ch] [ebp+8h]
  int32_t arg3b; // [esp+6Ch] [ebp+8h]
  int32_t arg3c; // [esp+6Ch] [ebp+8h]
  float arg3d; // [esp+6Ch] [ebp+8h]

  self->kind = PATH_TEMPLATE_KIND_LOOPOUT;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = width_cells_;
  v43 = (__int64)(curve_source * 6.2831855);
  self->width_or_scale = 1.0;
  self->segment_count = v43 + 14;
  self->segment_count_f = (float)(v43 + 14);
  v8 = (double)v43;
  v48 = v8;
  arg2 = v8 * 0.15915494;
  get_path_nodes(self);
  self->has_entry_mesh_transition = 1;
  arg3 = 0;
  v9 = 0;
  do
  {
    v45 = (float)arg3;
    self->primary_samples[v9].center_x = (double)(int)self->width_cells * 0.5 - 4.0 - v45 * 0.11111111 * 0.30000001;
    self->primary_samples[v9].rotation_scalar_98 = 0.0;
    self->primary_samples[v9].rotation_scalar_94 = 0.0;
    self->primary_samples[v9].special_scalar = 0.0;
    self->primary_samples[v9].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v9].transform);
    self->primary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    self->primary_samples[v9].transform.position.y = 0.0;
    self->primary_samples[v9].transform.position.z = v45;
    self->primary_samples[v9].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v9].transform);
    self->secondary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    self->secondary_samples[v9].transform.position.y = 0.49000001;
    self->secondary_samples[v9++].transform.position.z = v45;
    self->secondary_samples[v9 - 1].delta_length = 1.0;
    ++arg3;
  }
  while ( v9 < 10 );
  v10 = 0;
  arg3a = 0;
  v11 = v43 + 10;
  do
  {
    self->primary_samples[v11].center_x = (1.0 - (double)arg3a * 0.33333334) * 0.30000001
                                        + 4.0
                                        - (double)(int)self->width_cells * 0.5;
    self->primary_samples[v11].rotation_scalar_98 = 0.0;
    self->primary_samples[v11].rotation_scalar_94 = 0.0;
    self->primary_samples[v11].special_scalar = 0.0;
    self->primary_samples[v11].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v11].transform);
    self->primary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
    self->primary_samples[v11].transform.position.y = 0.0;
    arg3e = (float)(v10 + 10);
    self->primary_samples[v11].transform.position.z = arg3e;
    self->primary_samples[v11].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v11].transform);
    v12 = arg3e;
    ++v10;
    self->secondary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
    arg3a = v10;
    self->secondary_samples[v11].transform.position.y = 0.49000001;
    self->secondary_samples[v11++].transform.position.z = v12;
    self->secondary_samples[v11 - 1].delta_length = 1.0;
  }
  while ( v10 < 4 );
  arg3b = 0;
  v68 = -arg2;
  if ( v43 > 0 )
  {
    v51 = arg2 + 0.49000001;
    v13 = 10;
    do
    {
      v14 = (double)arg3b;
      v46 = v14 * 6.2831855 / v48;
      self->primary_samples[v13].center_x = (self->primary_samples[v43 + 10].center_x - self->primary_samples->center_x)
                                          * v14
                                          / v48
                                          + self->primary_samples->center_x;
      p_center_x = &self->primary_samples[v13].center_x;
      v42 = v46 * 0.5 + 4.712389;
      *p_center_x = sine(v42) * 0.30000001 + *p_center_x;
      self->primary_samples[v13].rotation_scalar_98 = 0.0;
      self->primary_samples[v13].rotation_scalar_94 = 0.0;
      self->primary_samples[v13].special_scalar = 0.0;
      self->primary_samples[v13].lateral_scale = 1.0;
      set_matrix_identity(&self->primary_samples[v13].transform);
      self->primary_samples[v13].transform.position.x = self->primary_samples[v13].center_x;
      self->primary_samples[v13].transform.position.z = sine(v46) * arg2 + 10.0;
      self->primary_samples[v13].transform.position.y = cosine(v46) * arg2 + v68;
      set_matrix_identity(&self->secondary_samples[v13].transform);
      self->secondary_samples[v13].transform.position.x = self->primary_samples[v13].center_x;
      self->secondary_samples[v13].transform.position.z = sine(v46) * v51 + 10.0;
      self->secondary_samples[v13].transform.position.y = cosine(v46) * v51 + v68;
      v16 = &self->primary_samples[v13];
      v16->transform.basis_right.x = 1.0;
      v16->transform.basis_right.y = 0.0;
      v16->transform.basis_right.z = 0.0;
      self->primary_samples[v13].transform.basis_up.x = 0.0;
      self->primary_samples[v13].transform.basis_up.y = -(v68 - self->primary_samples[v13].transform.position.y);
      self->primary_samples[v13].transform.basis_up.z = -(10.0 - self->primary_samples[v13].transform.position.z);
      normalize_vector(&self->primary_samples[v13].transform.basis_up);
      cross_vectors(
        &self->primary_samples[v13].transform.basis_forward,
        &self->primary_samples[v13].transform.basis_right,
        &self->primary_samples[v13].transform.basis_up);
      v17 = &self->secondary_samples[v13];
      v17->transform.basis_right.x = 1.0;
      v17->transform.basis_right.y = 0.0;
      v17->transform.basis_right.z = 0.0;
      self->secondary_samples[v13].transform.basis_up.x = 0.0;
      self->secondary_samples[v13].transform.basis_up.y = -(v68 - self->secondary_samples[v13].transform.position.y);
      self->secondary_samples[v13].transform.basis_up.z = -(10.0 - self->secondary_samples[v13].transform.position.z);
      normalize_vector(&self->secondary_samples[v13].transform.basis_up);
      cross_vectors(
        &self->secondary_samples[v13].transform.basis_forward,
        &self->secondary_samples[v13].transform.basis_right,
        &self->secondary_samples[v13].transform.basis_up);
      ++v13;
      ++arg3b;
    }
    while ( arg3b < v43 );
  }
  v18 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v19 = 0;
    do
    {
      v20 = &self->primary_samples[v19];
      v21 = v20[1].transform.position.x - v20->transform.position.x;
      v20 = (PathTemplateSample *)((char *)v20 + 128);
      v61 = v21;
      v63 = v20->inverse_matrix.basis_up_w - v20[-1].inverse_matrix.basis_up_w;
      v22 = v20->inverse_matrix.basis_forward.x - v20[-1].inverse_matrix.basis_forward.x;
      v20->transform.basis_right.x = v61;
      v20->transform.basis_right.y = v63;
      v65 = v22;
      v20->transform.basis_right.z = v65;
      self->primary_samples[v19].delta_length = normalize_vector(&self->primary_samples[v19].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      p_x = &secondary_samples[v19].delta_dir_to_next.x;
      v55 = secondary_samples[v19 + 1].transform.position.x - secondary_samples[v19].transform.position.x;
      v57 = secondary_samples[v19 + 1].transform.position.y - secondary_samples[v19].transform.position.y;
      v25 = secondary_samples[v19 + 1].transform.position.z - secondary_samples[v19].transform.position.z;
      *p_x = v55;
      p_x[1] = v57;
      v59 = v25;
      p_x[2] = v59;
      ++v18;
      self->secondary_samples[v19].delta_length = normalize_vector(&self->secondary_samples[v19].delta_dir_to_next);
      ++v19;
    }
    while ( v18 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = 1.0;
  v27 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v27->x = 0.0;
  v27->y = 0.0;
  v27->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = 1.0;
  request_object_vertices(self->bod.object, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->bod.object, 2 * self->segment_count * self->width_cells);
  object = self->bod.object;
  v29 = 0;
  vertices = object->vertices;
  facequads = object->facequads;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v30 = 0;
    v49 = 0;
    do
    {
      width_cells = self->width_cells;
      v32 = 0;
      arg2a = 0;
      for ( arg3c = width_cells; v32 <= width_cells; arg3c = width_cells )
      {
        v33 = (double)arg2a - (double)arg3c * 0.5;
        v34 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v30);
        if ( v29 == self->segment_count )
        {
          v70 = v33 * *(v34 - 42);
          v71 = v33 * *(v34 - 41);
          v36 = v33 * *(v34 - 40);
          v72 = *(v34 - 28) + 1.0;
          v56 = *(v34 - 30) + v70;
          v58 = *(v34 - 29) + v71;
          v37 = &vertices[v32 + v29 * (width_cells + 1)].x;
          *v37 = v56;
          v37[1] = v58;
          v60 = v72 + v36;
          v37[2] = v60;
          v30 = v49;
        }
        else
        {
          v67 = v33 * *v34;
          v69 = v33 * v34[1];
          v62 = v67 + v34[12];
          v64 = v69 + v34[13];
          v66 = v33 * v34[2] + v34[14];
          v35 = &vertices[v32 + v29 * (width_cells + 1)].x;
          *v35 = v62;
          v35[1] = v64;
          v35[2] = v66;
        }
        width_cells = self->width_cells;
        arg2a = ++v32;
      }
      ++v29;
      v30 += 168;
      v49 = v30;
    }
    while ( v29 <= (signed int)self->segment_count );
  }
  for ( i = 0; i < (signed int)self->segment_count; ++i )
  {
    v39 = 0;
    arg2b = 0;
    if ( (int)self->width_cells > 0 )
    {
      arg3d = (double)(i % 8) * 0.125;
      v47 = (double)(i % 8 + 1) * 0.125;
      do
      {
        v40 = 0;
        v53 = v39 + 1;
        v50 = 0;
        arg2c = (double)arg2b * 0.125;
        v44 = (double)(v39 + 1) * 0.125;
        while ( 1 )
        {
          v41 = &facequads[2 * v39 + 2 * i * self->width_cells + v40];
          v41->header_word = 0;
          if ( v40 != 0 )
          {
            v41->vertex_0 = i * (LOWORD(self->width_cells) + 1) + v39 + 1;
            v41->vertex_1 = v39 + i * (LOWORD(self->width_cells) + 1);
            v41->vertex_2 = v39 + (i + 1) * (LOWORD(self->width_cells) + 1);
            v41->vertex_3 = (i + 1) * (LOWORD(self->width_cells) + 1) + v39 + 1;
            v41->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_b, nullptr, 0);
            v41->uv[0].u = v44;
            v41->uv[0].v = arg3d;
            v41->uv[1].u = arg2c;
            v41->uv[1].v = arg3d;
            v41->uv[2].u = arg2c;
            v41->uv[2].v = v47;
            v41->uv[3].u = v44;
          }
          else
          {
            v41->vertex_0 = v39 + i * (LOWORD(self->width_cells) + 1);
            v41->vertex_1 = i * (LOWORD(self->width_cells) + 1) + v39 + 1;
            v41->vertex_2 = (i + 1) * (LOWORD(self->width_cells) + 1) + v39 + 1;
            v41->vertex_3 = v39 + (i + 1) * (LOWORD(self->width_cells) + 1);
            v41->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
            v41->uv[0].u = arg2c;
            v41->uv[0].v = arg3d;
            v41->uv[1].u = v44;
            v41->uv[1].v = arg3d;
            v41->uv[2].u = v44;
            v41->uv[2].v = v47;
            v41->uv[3].u = arg2c;
          }
          v41->uv[3].v = v47;
          if ( ++v50 >= 2 )
            break;
          v40 = v50;
        }
        ++v39;
        arg2b = v53;
      }
      while ( v53 < (signed int)self->width_cells );
    }
  }
  calc_path_length_z(self);
}
