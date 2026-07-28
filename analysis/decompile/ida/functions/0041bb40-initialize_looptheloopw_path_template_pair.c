/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_looptheloopw_path_template_pair @ 0x41bb40 */
/* selector: initialize_looptheloopw_path_template_pair */

// Builds the wide LoopTheLoop attachment path-template pair; iOS Path.o names this `cRPath::BuildLoopTheLoopW(float, int, bool, char*, char*)`.
void __thiscall initialize_looptheloopw_path_template_pair(
        cRPath *self,
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
  int v13; // ebx
  int v14; // edi
  double v15; // st7
  double v16; // st7
  float *p_center_x; // ebx
  PathTemplateSample *v18; // eax
  PathTemplateSample *v19; // edx
  signed int v20; // ebx
  int v21; // edi
  PathTemplateSample *v22; // eax
  double v23; // st7
  double v24; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *p_x; // eax
  double v27; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v29; // ecx
  Object *object; // eax
  signed int v31; // edi
  int v32; // edx
  signed int width_cells; // ecx
  signed int v34; // ebx
  double v35; // st7
  float *v36; // eax
  float *v37; // ecx
  float *v38; // edx
  double v39; // st6
  signed int i; // ebx
  int v41; // edi
  int v42; // ecx
  ObjectFaceQuad *v43; // ebp
  float v44; // [esp+0h] [ebp-74h]
  float v45; // [esp+0h] [ebp-74h]
  float v46; // [esp+14h] [ebp-60h]
  float v47; // [esp+14h] [ebp-60h]
  float v48; // [esp+18h] [ebp-5Ch]
  float v49; // [esp+18h] [ebp-5Ch]
  int v50; // [esp+1Ch] [ebp-58h]
  float v51; // [esp+1Ch] [ebp-58h]
  float v52; // [esp+20h] [ebp-54h]
  ObjectFaceQuad *facequads; // [esp+20h] [ebp-54h]
  int v54; // [esp+24h] [ebp-50h]
  float v55; // [esp+24h] [ebp-50h]
  int v56; // [esp+24h] [ebp-50h]
  float v57; // [esp+28h] [ebp-4Ch]
  int v58; // [esp+28h] [ebp-4Ch]
  float v59; // [esp+2Ch] [ebp-48h]
  Vec3 *vertices; // [esp+2Ch] [ebp-48h]
  signed int v61; // [esp+2Ch] [ebp-48h]
  int v62; // [esp+30h] [ebp-44h]
  float angle; // [esp+34h] [ebp-40h]
  float anglea; // [esp+34h] [ebp-40h]
  float v65; // [esp+38h] [ebp-3Ch]
  float v66; // [esp+38h] [ebp-3Ch]
  float v67; // [esp+3Ch] [ebp-38h]
  float v68; // [esp+3Ch] [ebp-38h]
  float v69; // [esp+40h] [ebp-34h]
  float v70; // [esp+40h] [ebp-34h]
  float v71; // [esp+44h] [ebp-30h]
  float v72; // [esp+44h] [ebp-30h]
  float v73; // [esp+48h] [ebp-2Ch]
  float v74; // [esp+48h] [ebp-2Ch]
  float v75; // [esp+4Ch] [ebp-28h]
  float v76; // [esp+4Ch] [ebp-28h]
  float v77; // [esp+50h] [ebp-24h]
  float v78; // [esp+54h] [ebp-20h]
  float v79; // [esp+5Ch] [ebp-18h]
  float v80; // [esp+60h] [ebp-14h]
  float v81; // [esp+70h] [ebp-4h]
  float arg2; // [esp+78h] [ebp+4h]
  int arg2a; // [esp+78h] [ebp+4h]
  int arg2b; // [esp+78h] [ebp+4h]
  float arg2c; // [esp+78h] [ebp+4h]
  int32_t arg3; // [esp+7Ch] [ebp+8h]
  int32_t arg3a; // [esp+7Ch] [ebp+8h]
  float arg3e; // [esp+7Ch] [ebp+8h]
  int32_t arg3b; // [esp+7Ch] [ebp+8h]
  int32_t arg3c; // [esp+7Ch] [ebp+8h]
  float arg3d; // [esp+7Ch] [ebp+8h]

  self->kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY;
  v48 = 0.0;
  if ( width_cells_ == 4 )
  {
    self->kind = PATH_TEMPLATE_KIND_LOOPTHELOOPW;
    v48 = 0.30000001;
  }
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = width_cells_;
  v50 = (__int64)(curve_source * 6.2831855);
  v54 = v50 + 14;
  self->width_or_scale = 1.0;
  self->segment_count = v50 + 14;
  self->segment_count_f = (float)(v50 + 14);
  v8 = (double)v50;
  v52 = v8;
  arg2 = v8 * 0.15915494;
  get_path_nodes(self);
  self->has_entry_mesh_transition = 1;
  arg3 = 0;
  v9 = 0;
  do
  {
    v46 = (float)arg3;
    self->primary_samples[v9].center_x = (double)(int)self->width_cells * 0.5 - 4.0 - v46 * 0.14285715 * v48;
    self->primary_samples[v9].rotation_scalar_98 = 0.0;
    self->primary_samples[v9].rotation_scalar_94 = 0.0;
    self->primary_samples[v9].special_scalar = 0.0;
    self->primary_samples[v9].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v9].transform);
    self->primary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    self->primary_samples[v9].transform.position.y = 0.0;
    self->primary_samples[v9].transform.position.z = v46;
    self->primary_samples[v9].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v9].transform);
    self->secondary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    self->secondary_samples[v9].transform.position.y = 0.49000001;
    self->secondary_samples[v9++].transform.position.z = v46;
    self->secondary_samples[v9 - 1].delta_length = 1.0;
    ++arg3;
  }
  while ( v9 < 7 );
  v10 = 0;
  arg3a = 0;
  v11 = v50 + 7;
  do
  {
    self->primary_samples[v11].center_x = (1.0 - (double)arg3a * 0.16666667) * v48
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
  if ( v50 > 0 )
  {
    v59 = arg2 - 0.49000001;
    v13 = 168 * v54;
    v62 = 168 * v54;
    v14 = 7;
    while ( 1 )
    {
      v15 = (double)arg3b;
      v47 = v15;
      v16 = v15 * 6.2831855 / v52;
      v55 = v16;
      v57 = v16 * 0.5;
      v44 = v55 * 8.0;
      angle = sine(v44);
      anglea = sine(v57) * angle * 0.39269909;
      self->primary_samples[v14].center_x = (*(float *)((char *)self->primary_samples + v13 - 24)
                                           - self->primary_samples->center_x)
                                          * v47
                                          / v52
                                          + self->primary_samples->center_x;
      p_center_x = &self->primary_samples[v14].center_x;
      v45 = v57 + 4.712389;
      *p_center_x = sine(v45) * v48 + *p_center_x;
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
      self->secondary_samples[v14].transform.position.z = sine(v55) * v59 + 7.0;
      self->secondary_samples[v14].transform.position.y = arg2 - cosine(v55) * v59;
      v18 = &self->primary_samples[v14];
      v18->transform.basis_right.x = 1.0;
      v18->transform.basis_right.y = 0.0;
      v18->transform.basis_right.z = 0.0;
      self->primary_samples[v14].transform.basis_up.x = 0.0;
      self->primary_samples[v14].transform.basis_up.y = arg2 - self->primary_samples[v14].transform.position.y;
      self->primary_samples[v14].transform.basis_up.z = 7.0 - self->primary_samples[v14].transform.position.z;
      normalize_vector(&self->primary_samples[v14].transform.basis_up);
      cross_vectors(
        &self->primary_samples[v14].transform.basis_forward,
        &self->primary_samples[v14].transform.basis_right,
        &self->primary_samples[v14].transform.basis_up);
      rotate_matrix_local_z(&self->primary_samples[v14].transform, anglea);
      v19 = &self->secondary_samples[v14];
      v19->transform.basis_right.x = 1.0;
      v19->transform.basis_right.y = 0.0;
      v19->transform.basis_right.z = 0.0;
      self->secondary_samples[v14].transform.basis_up.x = 0.0;
      self->secondary_samples[v14].transform.basis_up.y = arg2 - self->secondary_samples[v14].transform.position.y;
      self->secondary_samples[v14].transform.basis_up.z = 7.0 - self->secondary_samples[v14].transform.position.z;
      normalize_vector(&self->secondary_samples[v14].transform.basis_up);
      cross_vectors(
        &self->secondary_samples[v14].transform.basis_forward,
        &self->secondary_samples[v14].transform.basis_right,
        &self->secondary_samples[v14].transform.basis_up);
      rotate_matrix_local_z(&self->secondary_samples[v14++].transform, anglea);
      if ( ++arg3b >= v50 )
        break;
      v13 = v62;
    }
  }
  v20 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v21 = 0;
    do
    {
      v22 = &self->primary_samples[v21];
      v23 = v22[1].transform.position.x - v22->transform.position.x;
      v22 = (PathTemplateSample *)((char *)v22 + 128);
      v71 = v23;
      v73 = v22->inverse_matrix.basis_up_w - v22[-1].inverse_matrix.basis_up_w;
      v24 = v22->inverse_matrix.basis_forward.x - v22[-1].inverse_matrix.basis_forward.x;
      v22->transform.basis_right.x = v71;
      v22->transform.basis_right.y = v73;
      v75 = v24;
      v22->transform.basis_right.z = v75;
      self->primary_samples[v21].delta_length = normalize_vector(&self->primary_samples[v21].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      p_x = &secondary_samples[v21].delta_dir_to_next.x;
      v65 = secondary_samples[v21 + 1].transform.position.x - secondary_samples[v21].transform.position.x;
      v67 = secondary_samples[v21 + 1].transform.position.y - secondary_samples[v21].transform.position.y;
      v27 = secondary_samples[v21 + 1].transform.position.z - secondary_samples[v21].transform.position.z;
      *p_x = v65;
      p_x[1] = v67;
      v69 = v27;
      p_x[2] = v69;
      ++v20;
      self->secondary_samples[v21].delta_length = normalize_vector(&self->secondary_samples[v21].delta_dir_to_next);
      ++v21;
    }
    while ( v20 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = 1.0;
  v29 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v29->x = 0.0;
  v29->y = 0.0;
  v29->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = 1.0;
  request_object_vertices(self->bod.object, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->bod.object, 2 * self->segment_count * self->width_cells);
  object = self->bod.object;
  v31 = 0;
  vertices = object->vertices;
  facequads = object->facequads;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v32 = 0;
    v58 = 0;
    do
    {
      width_cells = self->width_cells;
      v34 = 0;
      arg2a = 0;
      for ( arg3c = width_cells; v34 <= width_cells; arg3c = width_cells )
      {
        v35 = (double)arg2a - (double)arg3c * 0.5;
        v36 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v32);
        if ( v31 == self->segment_count )
        {
          v79 = v35 * *(v36 - 42);
          v80 = v35 * *(v36 - 41);
          v81 = *(v36 - 28) + 1.0;
          v66 = *(v36 - 30) + v79;
          v68 = *(v36 - 29) + v80;
          v38 = &vertices[v34 + v31 * (width_cells + 1)].x;
          v39 = v81 + v35 * *(v36 - 40);
          *v38 = v66;
          v38[1] = v68;
          v70 = v39;
          v38[2] = v70;
          v32 = v58;
        }
        else
        {
          v77 = v35 * *v36;
          v78 = v35 * v36[1];
          v72 = v77 + v36[12];
          v74 = v78 + v36[13];
          v76 = v35 * v36[2] + v36[14];
          v37 = &vertices[v34 + v31 * (width_cells + 1)].x;
          *v37 = v72;
          v37[1] = v74;
          v37[2] = v76;
        }
        width_cells = self->width_cells;
        arg2a = ++v34;
      }
      ++v31;
      v32 += 168;
      v58 = v32;
    }
    while ( v31 <= (signed int)self->segment_count );
  }
  for ( i = 0; i < (signed int)self->segment_count; ++i )
  {
    v41 = 0;
    arg2b = 0;
    if ( (int)self->width_cells > 0 )
    {
      arg3d = (double)(i % 8) * 0.125;
      v49 = (double)(i % 8 + 1) * 0.125;
      do
      {
        v42 = 0;
        v61 = v41 + 1;
        v56 = 0;
        arg2c = (double)arg2b * 0.125;
        v51 = (double)(v41 + 1) * 0.125;
        while ( 1 )
        {
          v43 = &facequads[2 * v41 + 2 * i * self->width_cells + v42];
          v43->header_word = 0;
          if ( v42 != 0 )
          {
            v43->vertex_0 = i * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->vertex_1 = v41 + i * (LOWORD(self->width_cells) + 1);
            v43->vertex_2 = v41 + (i + 1) * (LOWORD(self->width_cells) + 1);
            v43->vertex_3 = (i + 1) * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_b, nullptr, 0);
            v43->uv[0].u = v51;
            v43->uv[0].v = arg3d;
            v43->uv[1].u = arg2c;
            v43->uv[1].v = arg3d;
            v43->uv[2].u = arg2c;
            v43->uv[2].v = v49;
            v43->uv[3].u = v51;
          }
          else
          {
            v43->vertex_0 = v41 + i * (LOWORD(self->width_cells) + 1);
            v43->vertex_1 = i * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->vertex_2 = (i + 1) * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->vertex_3 = v41 + (i + 1) * (LOWORD(self->width_cells) + 1);
            v43->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
            v43->uv[0].u = arg2c;
            v43->uv[0].v = arg3d;
            v43->uv[1].u = v51;
            v43->uv[1].v = arg3d;
            v43->uv[2].u = v51;
            v43->uv[2].v = v49;
            v43->uv[3].u = arg2c;
          }
          v43->uv[3].v = v49;
          if ( ++v56 >= 2 )
            break;
          v42 = v56;
        }
        ++v41;
        arg2b = v61;
      }
      while ( v61 < (signed int)self->width_cells );
    }
  }
  calc_path_length_z(self);
}
