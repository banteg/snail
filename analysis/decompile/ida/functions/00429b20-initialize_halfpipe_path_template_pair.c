/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_halfpipe_path_template_pair @ 0x429b20 */
/* selector: initialize_halfpipe_path_template_pair */

// Builds the Windows public HALFPIPE path-template pair at authored slot 42. The direct initialize_game_assets_and_world call targets pair base game+0x106a64c, seeds runtime kind 42 with 66 samples, and emits the generated strip mesh through the shared kind-42 transform helper; Android cRPath::BuildHalfPipe independently matches the shape.
void __thiscall initialize_halfpipe_path_template_pair(
        Path *self,
        float scale,
        int32_t width_cells_,
        bool side_exit,
        char *texture_a,
        char *texture_b,
        char *vertical_texture)
{
  int v8; // esi
  double v9; // st7
  double v10; // st7
  int i; // esi
  double v12; // st7
  int v13; // ebx
  double v14; // st7
  PathTemplateSample *primary_samples; // eax
  Vec3 *p_basis_up; // ecx
  PathTemplateSample *v17; // eax
  double v18; // st7
  double v19; // st7
  PathTemplateSample *v20; // ecx
  double v21; // st7
  double v22; // st6
  Vec3 *p_position; // eax
  signed int v24; // edi
  int v25; // esi
  PathTemplateSample *v26; // ecx
  float *p_x; // eax
  double v28; // st7
  PathTemplateSample *secondary_samples; // edx
  float *v30; // eax
  double v31; // st7
  Vec3 *p_delta_dir_to_next; // ecx
  Vec3 *v33; // eax
  Object *object; // eax
  Vec3 *vertices; // edi
  signed int v36; // esi
  int v37; // eax
  signed int width_cells; // ecx
  signed int v39; // ebx
  double v40; // st7
  float *v41; // eax
  float *v42; // ecx
  float v43; // edx
  double v44; // st6
  double v45; // st7
  double v46; // st6
  double v47; // st6
  signed int v48; // ecx
  signed int k; // ebx
  int v50; // esi
  int v51; // ecx
  ObjectFaceQuad *v52; // edi
  float v53; // [esp+0h] [ebp-B0h]
  float v54; // [esp+0h] [ebp-B0h]
  int v55; // [esp+14h] [ebp-9Ch]
  int v56; // [esp+14h] [ebp-9Ch]
  int v57; // [esp+14h] [ebp-9Ch]
  int v58; // [esp+14h] [ebp-9Ch]
  int v59; // [esp+14h] [ebp-9Ch]
  float v60; // [esp+14h] [ebp-9Ch]
  float v61; // [esp+18h] [ebp-98h]
  signed int v62; // [esp+18h] [ebp-98h]
  float v63; // [esp+1Ch] [ebp-94h]
  int j; // [esp+1Ch] [ebp-94h]
  float v65; // [esp+1Ch] [ebp-94h]
  float v66; // [esp+20h] [ebp-90h]
  float v67; // [esp+20h] [ebp-90h]
  float v68; // [esp+20h] [ebp-90h]
  float v69; // [esp+24h] [ebp-8Ch]
  float v70; // [esp+24h] [ebp-8Ch]
  float v71; // [esp+24h] [ebp-8Ch]
  float v72; // [esp+28h] [ebp-88h]
  float v73; // [esp+28h] [ebp-88h]
  float v74; // [esp+28h] [ebp-88h]
  int v75; // [esp+2Ch] [ebp-84h]
  float v76; // [esp+2Ch] [ebp-84h]
  float v77; // [esp+30h] [ebp-80h]
  float v78; // [esp+30h] [ebp-80h]
  float v79; // [esp+34h] [ebp-7Ch]
  float v80; // [esp+34h] [ebp-7Ch]
  float v81; // [esp+38h] [ebp-78h]
  float v82; // [esp+38h] [ebp-78h]
  float v83; // [esp+3Ch] [ebp-74h]
  int v84; // [esp+40h] [ebp-70h]
  ObjectFaceQuad *facequads; // [esp+44h] [ebp-6Ch]
  float v86; // [esp+48h] [ebp-68h]
  float v87; // [esp+4Ch] [ebp-64h]
  float v88; // [esp+4Ch] [ebp-64h]
  float v89; // [esp+50h] [ebp-60h]
  float out_angle[2]; // [esp+54h] [ebp-5Ch] BYREF
  float v91; // [esp+5Ch] [ebp-54h]
  float v92; // [esp+60h] [ebp-50h]
  float v93; // [esp+64h] [ebp-4Ch]
  float v94; // [esp+68h] [ebp-48h]
  TransformMatrix transform; // [esp+70h] [ebp-40h] BYREF

  self->kind = PATH_TEMPLATE_KIND_NONLINEAR_42;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = width_cells_;
  self->width_or_scale = 1.0;
  self->segment_count = 66;
  self->segment_count_f = 66.0;
  get_path_nodes(self);
  self->has_entry_mesh_transition = 0;
  v55 = 0;
  v8 = 0;
  do
  {
    v9 = (double)v55;
    v63 = v9;
    v53 = v9 * 0.0625 * 3.1415927 + 1.5707964;
    v10 = ((0.5 - sine(v53) * 0.5) * 0.94999999 + 0.050000001) * 4.0;
    self->primary_samples[v8].center_x = (double)(int)self->width_cells * 0.5 - 4.0;
    self->primary_samples[v8].rotation_scalar_98 = 0.0;
    self->primary_samples[v8].rotation_scalar_94 = 0.0;
    self->primary_samples[v8].special_scalar = (v10 * v10 + 16.0) / (v10 + v10);
    self->primary_samples[v8].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v8].transform);
    self->primary_samples[v8].transform.position.x = self->primary_samples[v8].center_x;
    self->primary_samples[v8].transform.position.y = 0.0;
    self->primary_samples[v8].transform.position.z = v63;
    self->primary_samples[v8].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v8].transform);
    self->secondary_samples[v8].transform.position.x = self->primary_samples[v8].center_x;
    self->secondary_samples[v8].transform.position.y = 0.49000001;
    self->secondary_samples[v8++].transform.position.z = v63;
    self->secondary_samples[v8 - 1].delta_length = 1.0;
    ++v55;
  }
  while ( v8 < 16 );
  v56 = 0;
  for ( i = 50; i < 66; ++i )
  {
    v54 = (1.0 - (double)v56 * 0.0625) * 3.1415927 + 1.5707964;
    v12 = ((0.5 - sine(v54) * 0.5) * 0.94999999 + 0.050000001) * 4.0;
    self->primary_samples[i].center_x = 4.0 - (double)(int)self->width_cells * 0.5;
    self->primary_samples[i].rotation_scalar_98 = 0.0;
    self->primary_samples[i].rotation_scalar_94 = 0.0;
    self->primary_samples[i].special_scalar = (v12 * v12 + 16.0) / (v12 + v12);
    self->primary_samples[i].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[i].transform);
    self->primary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->primary_samples[i].transform.position.y = 0.0;
    v61 = (float)(v56 + 50);
    self->primary_samples[i].transform.position.z = v61;
    self->primary_samples[i].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->secondary_samples[i].transform.position.y = 0.49000001;
    self->secondary_samples[i].transform.position.z = v61;
    self->secondary_samples[i].delta_length = 1.0;
    ++v56;
  }
  v57 = 0;
  v13 = 16;
  do
  {
    v14 = (double)v57;
    primary_samples = self->primary_samples;
    out_angle[0] = v14 * 0.18479957;
    primary_samples[v13].center_x = (primary_samples[50].center_x - primary_samples->center_x) * v14 * 0.029411765
                                  + primary_samples->center_x;
    self->primary_samples[v13].rotation_scalar_98 = 0.0;
    self->primary_samples[v13].rotation_scalar_94 = 0.0;
    self->primary_samples[v13].special_scalar = 4.0;
    self->primary_samples[v13].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v13].transform);
    self->primary_samples[v13].transform.position.x = 0.0;
    self->primary_samples[v13].transform.position.z = (float)(v57 + 16);
    self->primary_samples[v13].transform.position.y = 0.0;
    p_basis_up = &self->primary_samples[v13].transform.basis_up;
    p_basis_up->x = 0.0;
    p_basis_up->y = 1.0;
    p_basis_up->z = 0.0;
    v17 = &self->primary_samples[v13];
    v18 = v17->transform.position.x - v17[-1].transform.position.x;
    v17 = (PathTemplateSample *)((char *)v17 + 32);
    v66 = v18;
    v69 = v17->transform.basis_up.y - v17[-1].transform.basis_up.y;
    v19 = v17->transform.basis_up.z - v17[-1].transform.basis_up.z;
    v17->transform.basis_right.x = v66;
    v17->transform.basis_right.y = v69;
    v72 = v19;
    v17->transform.basis_right.z = v72;
    normalize_vector(&self->primary_samples[v13].transform.basis_forward);
    cross_vectors(
      &self->primary_samples[v13].transform.basis_right,
      &self->primary_samples[v13].transform.basis_up,
      &self->primary_samples[v13].transform.basis_forward);
    qmemcpy(&self->secondary_samples[v13], &self->primary_samples[v13], 0x40u);
    v20 = self->primary_samples;
    v21 = v20[v13].transform.basis_up.x * 0.49000001;
    v87 = v20[v13].transform.basis_up.y * 0.49000001;
    v22 = v20[v13].transform.basis_up.z * 0.49000001;
    p_position = &self->secondary_samples[v13++].transform.position;
    ++v57;
    v89 = v22;
    p_position->x = v21 + p_position->x;
    p_position->y = v87 + p_position->y;
    p_position->z = v89 + p_position->z;
  }
  while ( v13 < 50 );
  v24 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v25 = 0;
    do
    {
      v26 = self->primary_samples;
      p_x = &v26[v25].delta_dir_to_next.x;
      v67 = v26[v25 + 1].transform.position.x - v26[v25].transform.position.x;
      v70 = v26[v25 + 1].transform.position.y - v26[v25].transform.position.y;
      v28 = v26[v25 + 1].transform.position.z - v26[v25].transform.position.z;
      *p_x = v67;
      p_x[1] = v70;
      v73 = v28;
      p_x[2] = v73;
      self->primary_samples[v25].delta_length = normalize_vector(&self->primary_samples[v25].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v30 = &secondary_samples[v25].delta_dir_to_next.x;
      v77 = secondary_samples[v25 + 1].transform.position.x - secondary_samples[v25].transform.position.x;
      v79 = secondary_samples[v25 + 1].transform.position.y - secondary_samples[v25].transform.position.y;
      v31 = secondary_samples[v25 + 1].transform.position.z - secondary_samples[v25].transform.position.z;
      *v30 = v77;
      v30[1] = v79;
      v81 = v31;
      v30[2] = v81;
      ++v24;
      self->secondary_samples[v25].delta_length = normalize_vector(&self->secondary_samples[v25].delta_dir_to_next);
      ++v25;
    }
    while ( v24 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = 1.0;
  v33 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v33->x = 0.0;
  v33->y = 0.0;
  v33->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = 1.0;
  request_object_vertices(self->bod.object, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->bod.object, 2 * self->segment_count * self->width_cells);
  object = self->bod.object;
  vertices = object->vertices;
  facequads = object->facequads;
  set_matrix_identity(&transform);
  v36 = 0;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v37 = 0;
    v75 = 0;
    do
    {
      width_cells = self->width_cells;
      v39 = 0;
      v58 = 0;
      for ( j = width_cells; v39 <= width_cells; v58 = v39 )
      {
        v40 = (double)v58 - (double)j * 0.5;
        v41 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v37);
        if ( v36 == self->segment_count )
        {
          v44 = v40 * *(v41 - 42);
          v91 = *(v41 - 29);
          v93 = v44;
          v94 = v40 * *(v41 - 41);
          v45 = v40 * *(v41 - 40);
          v46 = *(v41 - 30);
          v92 = *(v41 - 28) + 1.0;
          v78 = v46 + v93;
          v80 = v91 + v94;
          v47 = v92 + v45;
          v42 = &vertices[v39 + v36 * (width_cells + 1)].x;
          *v42 = v78;
          v82 = v47;
          v43 = v82;
          v42[1] = v80;
        }
        else
        {
          v86 = v40 * *v41;
          v88 = v40 * v41[1];
          v68 = v86 + v41[12];
          v71 = v88 + v41[13];
          v74 = v40 * v41[2] + v41[14];
          v42 = &vertices[v39 + v36 * (width_cells + 1)].x;
          *v42 = v68;
          v43 = v74;
          v42[1] = v71;
        }
        v42[2] = v43;
        v48 = v36 - 1;
        if ( v36 != self->segment_count )
          v48 = v36;
        compute_kind42_attachment_transform(
          self,
          self->primary_samples[v48].special_scalar,
          vertices[v39 + v36 * (self->width_cells + 1)].x,
          0.0,
          &transform,
          out_angle);
        if ( v75 > 168 && v36 != self->segment_count )
        {
          vertices[v39 + v36 * (self->width_cells + 1)].x = transform.position.x;
          vertices[v39 + v36 * (self->width_cells + 1)].y = transform.position.y;
        }
        width_cells = self->width_cells;
        v37 = v75;
        ++v39;
        j = width_cells;
      }
      ++v36;
      v37 += 168;
      v75 = v37;
    }
    while ( v36 <= (signed int)self->segment_count );
  }
  for ( k = 0; k < (signed int)self->segment_count; ++k )
  {
    v50 = 0;
    v59 = 0;
    if ( (int)self->width_cells > 0 )
    {
      v76 = (double)(k % 8) * 0.125;
      v65 = (double)(k % 8 + 1) * 0.125;
      do
      {
        v51 = 0;
        v62 = v50 + 1;
        v84 = 0;
        v60 = (double)v59 * 0.125;
        v83 = (double)(v50 + 1) * 0.125;
        while ( 1 )
        {
          v52 = &facequads[2 * v50 + 2 * k * self->width_cells + v51];
          v52->header_word = 0;
          if ( v51 != 0 )
          {
            v52->vertex_0 = k * (LOWORD(self->width_cells) + 1) + v50 + 1;
            v52->vertex_1 = v50 + k * (LOWORD(self->width_cells) + 1);
            v52->vertex_2 = v50 + (k + 1) * (LOWORD(self->width_cells) + 1);
            v52->vertex_3 = (k + 1) * (LOWORD(self->width_cells) + 1) + v50 + 1;
            v52->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_b, nullptr, 0);
            v52->uv[0].u = v83;
            v52->uv[0].v = v76;
            v52->uv[1].u = v60;
            v52->uv[1].v = v76;
            v52->uv[2].u = v60;
            v52->uv[2].v = v65;
            v52->uv[3].u = v83;
          }
          else
          {
            v52->vertex_0 = v50 + k * (LOWORD(self->width_cells) + 1);
            v52->vertex_1 = k * (LOWORD(self->width_cells) + 1) + v50 + 1;
            v52->vertex_2 = (k + 1) * (LOWORD(self->width_cells) + 1) + v50 + 1;
            v52->vertex_3 = v50 + (k + 1) * (LOWORD(self->width_cells) + 1);
            v52->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
            v52->uv[0].u = v60;
            v52->uv[0].v = v76;
            v52->uv[1].u = v83;
            v52->uv[1].v = v76;
            v52->uv[2].u = v83;
            v52->uv[2].v = v65;
            v52->uv[3].u = v60;
          }
          v52->uv[3].v = v65;
          if ( ++v84 >= 2 )
            break;
          v51 = v84;
        }
        ++v50;
        v59 = v62;
      }
      while ( v62 < (signed int)self->width_cells );
    }
  }
  calc_path_length_z(self);
}
