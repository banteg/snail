/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_looptheloop_path_template_pair @ 0x41b0f0 */
/* selector: initialize_looptheloop_path_template_pair */

// Builds the LoopTheLoop attachment path-template pair; iOS Path.o names this `cRPath::BuildLoopTheLoop(float, int, bool, char*, char*)`.
void __thiscall initialize_looptheloop_path_template_pair(
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
  int v13; // ecx
  int v14; // edi
  double v15; // st7
  float *p_center_x; // ebx
  PathTemplateSample *v17; // eax
  PathTemplateSample *v18; // edx
  signed int v19; // ebx
  int v20; // edi
  PathTemplateSample *v21; // eax
  double v22; // st7
  double v23; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *p_x; // eax
  double v26; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v28; // ecx
  Object *object; // eax
  signed int v30; // edi
  int v31; // edx
  signed int width_cells; // ecx
  signed int v33; // ebx
  double v34; // st7
  float *v35; // eax
  float *v36; // ecx
  double v37; // st7
  float *v38; // edx
  signed int i; // ebx
  int v40; // edi
  int v41; // ecx
  ObjectFaceQuad *v42; // ebp
  float v43; // [esp+0h] [ebp-68h]
  float v44; // [esp+14h] [ebp-54h]
  float v45; // [esp+14h] [ebp-54h]
  int v46; // [esp+18h] [ebp-50h]
  float v47; // [esp+18h] [ebp-50h]
  float v48; // [esp+1Ch] [ebp-4Ch]
  float v49; // [esp+1Ch] [ebp-4Ch]
  ObjectFaceQuad *facequads; // [esp+1Ch] [ebp-4Ch]
  float v51; // [esp+20h] [ebp-48h]
  int v52; // [esp+20h] [ebp-48h]
  int v53; // [esp+20h] [ebp-48h]
  int v54; // [esp+24h] [ebp-44h]
  float v55; // [esp+24h] [ebp-44h]
  Vec3 *vertices; // [esp+24h] [ebp-44h]
  signed int v57; // [esp+24h] [ebp-44h]
  int v58; // [esp+28h] [ebp-40h]
  float v59; // [esp+2Ch] [ebp-3Ch]
  float v60; // [esp+2Ch] [ebp-3Ch]
  float v61; // [esp+30h] [ebp-38h]
  float v62; // [esp+30h] [ebp-38h]
  float v63; // [esp+34h] [ebp-34h]
  float v64; // [esp+34h] [ebp-34h]
  float v65; // [esp+38h] [ebp-30h]
  float v66; // [esp+38h] [ebp-30h]
  float v67; // [esp+3Ch] [ebp-2Ch]
  float v68; // [esp+3Ch] [ebp-2Ch]
  float v69; // [esp+40h] [ebp-28h]
  float v70; // [esp+40h] [ebp-28h]
  float v71; // [esp+44h] [ebp-24h]
  float v72; // [esp+48h] [ebp-20h]
  float v73; // [esp+50h] [ebp-18h]
  float v74; // [esp+54h] [ebp-14h]
  float v75; // [esp+64h] [ebp-4h]
  float arg2; // [esp+6Ch] [ebp+4h]
  int arg2a; // [esp+6Ch] [ebp+4h]
  int arg2b; // [esp+6Ch] [ebp+4h]
  float arg2c; // [esp+6Ch] [ebp+4h]
  int32_t arg3; // [esp+70h] [ebp+8h]
  int32_t arg3a; // [esp+70h] [ebp+8h]
  float arg3e; // [esp+70h] [ebp+8h]
  int32_t arg3b; // [esp+70h] [ebp+8h]
  int32_t arg3c; // [esp+70h] [ebp+8h]
  float arg3d; // [esp+70h] [ebp+8h]

  self->kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY;
  v44 = 0.0;
  if ( width_cells_ == 4 )
  {
    self->kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY;
    v44 = 0.30000001;
  }
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = width_cells_;
  v46 = (__int64)(curve_source * 6.2831855);
  v54 = v46 + 14;
  self->width_or_scale = 1.0;
  self->segment_count = v46 + 14;
  self->segment_count_f = (float)(v46 + 14);
  v8 = (double)v46;
  v51 = v8;
  arg2 = v8 * 0.15915494;
  get_path_nodes(self);
  self->has_entry_mesh_transition = 1;
  arg3 = 0;
  v9 = 0;
  do
  {
    v48 = (float)arg3;
    self->primary_samples[v9].center_x = (double)(int)self->width_cells * 0.5 - 4.0 - v48 * 0.14285715 * v44;
    self->primary_samples[v9].rotation_scalar_98 = 0.0;
    self->primary_samples[v9].rotation_scalar_94 = 0.0;
    self->primary_samples[v9].special_scalar = 0.0;
    self->primary_samples[v9].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v9].transform);
    self->primary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    self->primary_samples[v9].transform.position.y = 0.0;
    self->primary_samples[v9].transform.position.z = v48;
    self->primary_samples[v9].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v9].transform);
    self->secondary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    self->secondary_samples[v9].transform.position.y = 0.49000001;
    self->secondary_samples[v9++].transform.position.z = v48;
    self->secondary_samples[v9 - 1].delta_length = 1.0;
    ++arg3;
  }
  while ( v9 < 7 );
  v10 = 0;
  arg3a = 0;
  v11 = v46 + 7;
  do
  {
    self->primary_samples[v11].center_x = (1.0 - (double)arg3a * 0.16666667) * v44
                                        + 4.0
                                        - (double)(int)self->width_cells * 0.5;
    self->primary_samples[v11].rotation_scalar_98 = 0.0;
    self->primary_samples[v11].rotation_scalar_94 = 0.0;
    self->primary_samples[v11].special_scalar = 0.0;
    self->primary_samples[v11].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v11].transform);
    self->primary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
    self->primary_samples[v11].transform.position.y = 0.0;
    arg3e = (float)(v10 + 7);
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
  while ( v10 < 7 );
  arg3b = 0;
  if ( v46 > 0 )
  {
    v49 = arg2 - 0.49000001;
    v13 = 168 * v54;
    v58 = 168 * v54;
    v14 = 7;
    while ( 1 )
    {
      v15 = (double)arg3b;
      v55 = v15 * 6.2831855 / v51;
      self->primary_samples[v14].center_x = (*(float *)((char *)self->primary_samples + v13 - 24)
                                           - self->primary_samples->center_x)
                                          * v15
                                          / v51
                                          + self->primary_samples->center_x;
      p_center_x = &self->primary_samples[v14].center_x;
      v43 = v55 * 0.5 + 4.712389;
      *p_center_x = sine(v43) * v44 + *p_center_x;
      self->primary_samples[v14].rotation_scalar_98 = 0.0;
      self->primary_samples[v14].rotation_scalar_94 = 0.0;
      self->primary_samples[v14].special_scalar = 0.0;
      self->primary_samples[v14].lateral_scale = 1.0;
      set_matrix_identity(&self->primary_samples[v14].transform);
      self->primary_samples[v14].transform.position.x = self->primary_samples[v14].center_x;
      self->primary_samples[v14].transform.position.z = sine(v55) * arg2 + 7.0;
      self->primary_samples[v14].transform.position.y = arg2 - cosine(v55) * arg2;
      set_matrix_identity(&self->secondary_samples[v14].transform);
      self->secondary_samples[v14].transform.position.x = self->primary_samples[v14].center_x;
      self->secondary_samples[v14].transform.position.z = sine(v55) * v49 + 7.0;
      self->secondary_samples[v14].transform.position.y = arg2 - cosine(v55) * v49;
      v17 = &self->primary_samples[v14];
      v17->transform.basis_right.x = 1.0;
      v17->transform.basis_right.y = 0.0;
      v17->transform.basis_right.z = 0.0;
      self->primary_samples[v14].transform.basis_up.x = 0.0;
      self->primary_samples[v14].transform.basis_up.y = arg2 - self->primary_samples[v14].transform.position.y;
      self->primary_samples[v14].transform.basis_up.z = 7.0 - self->primary_samples[v14].transform.position.z;
      normalize_vector(&self->primary_samples[v14].transform.basis_up);
      cross_vectors(
        &self->primary_samples[v14].transform.basis_forward,
        &self->primary_samples[v14].transform.basis_right,
        &self->primary_samples[v14].transform.basis_up);
      v18 = &self->secondary_samples[v14];
      v18->transform.basis_right.x = 1.0;
      v18->transform.basis_right.y = 0.0;
      v18->transform.basis_right.z = 0.0;
      self->secondary_samples[v14].transform.basis_up.x = 0.0;
      self->secondary_samples[v14].transform.basis_up.y = arg2 - self->secondary_samples[v14].transform.position.y;
      self->secondary_samples[v14].transform.basis_up.z = 7.0 - self->secondary_samples[v14].transform.position.z;
      normalize_vector(&self->secondary_samples[v14].transform.basis_up);
      cross_vectors(
        &self->secondary_samples[v14].transform.basis_forward,
        &self->secondary_samples[v14].transform.basis_right,
        &self->secondary_samples[v14].transform.basis_up);
      ++v14;
      if ( ++arg3b >= v46 )
        break;
      v13 = v58;
    }
  }
  v19 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v20 = 0;
    do
    {
      v21 = &self->primary_samples[v20];
      v22 = v21[1].transform.position.x - v21->transform.position.x;
      v21 = (PathTemplateSample *)((char *)v21 + 128);
      v65 = v22;
      v67 = v21->inverse_matrix.basis_up_w - v21[-1].inverse_matrix.basis_up_w;
      v23 = v21->inverse_matrix.basis_forward.x - v21[-1].inverse_matrix.basis_forward.x;
      v21->transform.basis_right.x = v65;
      v21->transform.basis_right.y = v67;
      v69 = v23;
      v21->transform.basis_right.z = v69;
      self->primary_samples[v20].delta_length = normalize_vector(&self->primary_samples[v20].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      p_x = &secondary_samples[v20].delta_dir_to_next.x;
      v59 = secondary_samples[v20 + 1].transform.position.x - secondary_samples[v20].transform.position.x;
      v61 = secondary_samples[v20 + 1].transform.position.y - secondary_samples[v20].transform.position.y;
      v26 = secondary_samples[v20 + 1].transform.position.z - secondary_samples[v20].transform.position.z;
      *p_x = v59;
      p_x[1] = v61;
      v63 = v26;
      p_x[2] = v63;
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
  request_object_vertices(self->bod.object, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->bod.object, 2 * self->segment_count * self->width_cells);
  object = self->bod.object;
  v30 = 0;
  vertices = object->vertices;
  facequads = object->facequads;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v31 = 0;
    v52 = 0;
    do
    {
      width_cells = self->width_cells;
      v33 = 0;
      arg2a = 0;
      for ( arg3c = width_cells; v33 <= width_cells; arg3c = width_cells )
      {
        v34 = (double)arg2a - (double)arg3c * 0.5;
        v35 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v31);
        if ( v30 == self->segment_count )
        {
          v73 = v34 * *(v35 - 42);
          v74 = v34 * *(v35 - 41);
          v37 = v34 * *(v35 - 40);
          v75 = *(v35 - 28) + 1.0;
          v60 = *(v35 - 30) + v73;
          v62 = *(v35 - 29) + v74;
          v38 = &vertices[v33 + v30 * (width_cells + 1)].x;
          *v38 = v60;
          v38[1] = v62;
          v64 = v75 + v37;
          v38[2] = v64;
          v31 = v52;
        }
        else
        {
          v71 = v34 * *v35;
          v72 = v34 * v35[1];
          v66 = v71 + v35[12];
          v68 = v72 + v35[13];
          v70 = v34 * v35[2] + v35[14];
          v36 = &vertices[v33 + v30 * (width_cells + 1)].x;
          *v36 = v66;
          v36[1] = v68;
          v36[2] = v70;
        }
        width_cells = self->width_cells;
        arg2a = ++v33;
      }
      ++v30;
      v31 += 168;
      v52 = v31;
    }
    while ( v30 <= (signed int)self->segment_count );
  }
  for ( i = 0; i < (signed int)self->segment_count; ++i )
  {
    v40 = 0;
    arg2b = 0;
    if ( (int)self->width_cells > 0 )
    {
      arg3d = (double)(i % 8) * 0.125;
      v45 = (double)(i % 8 + 1) * 0.125;
      do
      {
        v41 = 0;
        v57 = v40 + 1;
        v53 = 0;
        arg2c = (double)arg2b * 0.125;
        v47 = (double)(v40 + 1) * 0.125;
        while ( 1 )
        {
          v42 = &facequads[2 * v40 + 2 * i * self->width_cells + v41];
          v42->header_word = 0;
          if ( v41 != 0 )
          {
            v42->vertex_0 = i * (LOWORD(self->width_cells) + 1) + v40 + 1;
            v42->vertex_1 = v40 + i * (LOWORD(self->width_cells) + 1);
            v42->vertex_2 = v40 + (i + 1) * (LOWORD(self->width_cells) + 1);
            v42->vertex_3 = (i + 1) * (LOWORD(self->width_cells) + 1) + v40 + 1;
            v42->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_b, nullptr, 0);
            v42->uv[0].u = v47;
            v42->uv[0].v = arg3d;
            v42->uv[1].u = arg2c;
            v42->uv[1].v = arg3d;
            v42->uv[2].u = arg2c;
            v42->uv[2].v = v45;
            v42->uv[3].u = v47;
          }
          else
          {
            v42->vertex_0 = v40 + i * (LOWORD(self->width_cells) + 1);
            v42->vertex_1 = i * (LOWORD(self->width_cells) + 1) + v40 + 1;
            v42->vertex_2 = (i + 1) * (LOWORD(self->width_cells) + 1) + v40 + 1;
            v42->vertex_3 = v40 + (i + 1) * (LOWORD(self->width_cells) + 1);
            v42->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
            v42->uv[0].u = arg2c;
            v42->uv[0].v = arg3d;
            v42->uv[1].u = v47;
            v42->uv[1].v = arg3d;
            v42->uv[2].u = v47;
            v42->uv[2].v = v45;
            v42->uv[3].u = arg2c;
          }
          v42->uv[3].v = v45;
          if ( ++v53 >= 2 )
            break;
          v41 = v53;
        }
        ++v40;
        arg2b = v57;
      }
      while ( v57 < (signed int)self->width_cells );
    }
  }
  calc_path_length_z(self);
}
