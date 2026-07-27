/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_cage2_path_template_pair @ 0x42e720 */
/* selector: initialize_cage2_path_template_pair */

// Builds the Cage2 attachment path-template pair; iOS Path.o names this `cRPath::BuildCage2(int, char*, char*)`.
void __thiscall initialize_cage2_path_template_pair(
        Path *self,
        int32_t width_cells_,
        char *texture_a,
        char *texture_b,
        char *vertical_texture)
{
  signed int v6; // ebx
  double width_cells; // st7
  PathTemplateSample *primary_samples; // ecx
  int i; // edi
  double v10; // st7
  PathTemplateSample *v11; // ebp
  Vec3 *p_basis_up; // eax
  PathTemplateSample *v13; // edx
  float *p_x; // eax
  double v15; // st7
  PathTemplateSample *v16; // ebp
  Vec3 *v17; // eax
  PathTemplateSample *secondary_samples; // edx
  float *v19; // eax
  double v20; // st7
  signed int v21; // ebp
  int v22; // edi
  PathTemplateSample *v23; // ecx
  float *v24; // eax
  double v25; // st7
  PathTemplateSample *v26; // edx
  float *v27; // eax
  double v28; // st7
  Vec3 *p_delta_dir_to_next; // ecx
  Vec3 *v30; // eax
  Object *object; // eax
  Vec3 *vertices; // ebp
  signed int v33; // edx
  signed int v34; // ecx
  int32_t v35; // edi
  double v36; // st7
  float *v37; // eax
  float *v38; // eax
  float v39; // ecx
  double v40; // st7
  int v41; // edi
  int v42; // ecx
  ObjectFaceQuad *v43; // ebp
  float angle; // [esp+0h] [ebp-68h]
  float anglea; // [esp+0h] [ebp-68h]
  float angleb; // [esp+0h] [ebp-68h]
  float v47; // [esp+14h] [ebp-54h]
  float v48; // [esp+18h] [ebp-50h]
  int j; // [esp+1Ch] [ebp-4Ch]
  float v50; // [esp+1Ch] [ebp-4Ch]
  float v51; // [esp+20h] [ebp-48h]
  int v52; // [esp+20h] [ebp-48h]
  ObjectFaceQuad *facequads; // [esp+24h] [ebp-44h]
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
  int32_t arg2; // [esp+6Ch] [ebp+4h]
  int32_t arg2a; // [esp+6Ch] [ebp+4h]
  int32_t arg2b; // [esp+6Ch] [ebp+4h]
  float arg2c; // [esp+6Ch] [ebp+4h]

  v6 = 0;
  self->kind = PATH_TEMPLATE_KIND_CAGE2;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = width_cells_;
  self->width_or_scale = 1.0;
  self->segment_count = 22;
  self->segment_count_f = 22.0;
  get_path_nodes(self);
  width_cells = (double)(int)self->width_cells;
  primary_samples = self->primary_samples;
  self->has_entry_mesh_transition = 0;
  primary_samples->center_x = width_cells * 0.5 - 4.0;
  self->primary_samples->rotation_scalar_98 = 0.0;
  self->primary_samples->rotation_scalar_94 = 0.0;
  self->primary_samples->special_scalar = 0.0;
  self->primary_samples->lateral_scale = 1.0;
  set_matrix_identity(&self->primary_samples->transform);
  self->primary_samples->transform.position.x = self->primary_samples->center_x;
  self->primary_samples->transform.position.y = 0.0;
  self->primary_samples->transform.position.z = 0.0;
  set_matrix_identity(&self->secondary_samples->transform);
  self->secondary_samples->transform.position.x = self->primary_samples->center_x;
  self->secondary_samples->transform.position.y = 0.49000001;
  self->secondary_samples->transform.position.z = 0.0;
  self->primary_samples[21].center_x = 4.0 - (double)(int)self->width_cells * 0.5;
  self->primary_samples[21].rotation_scalar_98 = 0.0;
  self->primary_samples[21].rotation_scalar_94 = 0.0;
  self->primary_samples[21].special_scalar = 0.0;
  self->primary_samples[21].lateral_scale = 1.0;
  set_matrix_identity(&self->primary_samples[21].transform);
  self->primary_samples[21].transform.position.x = self->primary_samples[21].center_x;
  self->primary_samples[21].transform.position.y = 0.0;
  self->primary_samples[21].transform.position.z = 21.0;
  set_matrix_identity(&self->secondary_samples[21].transform);
  self->secondary_samples[21].transform.position.x = self->primary_samples[21].center_x;
  arg2 = 0;
  self->secondary_samples[21].transform.position.y = 0.49000001;
  self->secondary_samples[21].transform.position.z = 21.0;
  for ( i = 1; i < 21; ++i )
  {
    v10 = (double)arg2;
    v11 = self->primary_samples;
    v51 = v10 * 0.31415927;
    angle = v10 * 0.47123891;
    v11[i].center_x = cosine(angle) * v11->center_x;
    self->primary_samples[i].rotation_scalar_98 = 0.0;
    self->primary_samples[i].rotation_scalar_94 = 0.0;
    self->primary_samples[i].special_scalar = 0.0;
    self->primary_samples[i].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[i].transform);
    self->primary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    ++arg2;
    self->primary_samples[i].transform.position.y = 0.0;
    v54 = (float)arg2;
    self->primary_samples[i].transform.position.z = v54;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->secondary_samples[i].transform.position.y = self->primary_samples[i].transform.position.y + 0.49000001;
    self->secondary_samples[i].transform.position.z = v54;
    if ( i <= 1 )
    {
      set_matrix_rotation_identity(&self->primary_samples[i - 1].transform);
      set_matrix_rotation_identity(&self->secondary_samples[i - 1].transform);
    }
    else
    {
      p_basis_up = &self->primary_samples[i - 1].transform.basis_up;
      p_basis_up->x = 0.0;
      p_basis_up->y = 1.0;
      p_basis_up->z = 0.0;
      v13 = self->primary_samples;
      p_x = &v13[i - 1].transform.basis_forward.x;
      v59 = v13[i].transform.position.x - v13[i - 1].transform.position.x;
      v61 = p_x[47] - p_x[5];
      v15 = p_x[48] - p_x[6];
      *p_x = v59;
      p_x[1] = v61;
      v63 = v15;
      p_x[2] = v63;
      normalize_vector(&self->primary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        &self->primary_samples[i - 1].transform.basis_right,
        &self->primary_samples[i - 1].transform.basis_up,
        &self->primary_samples[i - 1].transform.basis_forward);
      v16 = &self->primary_samples[i];
      anglea = (1.0 - cosine(v51)) * 0.5 * v16[-1].center_x * 0.39269909;
      rotate_matrix_local_z(&v16[-1].transform, anglea);
      v17 = &self->secondary_samples[i - 1].transform.basis_up;
      v17->x = 0.0;
      v17->y = 1.0;
      v17->z = 0.0;
      secondary_samples = self->secondary_samples;
      v19 = &secondary_samples[i - 1].transform.basis_forward.x;
      v70 = secondary_samples[i].transform.position.x - secondary_samples[i - 1].transform.position.x;
      v73 = v19[47] - v19[5];
      v20 = v19[48] - v19[6];
      *v19 = v70;
      v76 = v20;
      v19[1] = v73;
      v19[2] = v76;
      normalize_vector(&self->secondary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        &self->secondary_samples[i - 1].transform.basis_right,
        &self->secondary_samples[i - 1].transform.basis_up,
        &self->secondary_samples[i - 1].transform.basis_forward);
      angleb = (1.0 - cosine(v51)) * 0.5 * self->primary_samples[i - 1].center_x * 0.39269909;
      rotate_matrix_local_z(&self->secondary_samples[i - 1].transform, angleb);
    }
  }
  v21 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v22 = 0;
    do
    {
      v23 = self->primary_samples;
      v24 = &v23[v22].delta_dir_to_next.x;
      v71 = v23[v22 + 1].transform.position.x - v23[v22].transform.position.x;
      v74 = v23[v22 + 1].transform.position.y - v23[v22].transform.position.y;
      v25 = v23[v22 + 1].transform.position.z - v23[v22].transform.position.z;
      *v24 = v71;
      v24[1] = v74;
      v77 = v25;
      v24[2] = v77;
      self->primary_samples[v22].delta_length = normalize_vector(&self->primary_samples[v22].delta_dir_to_next);
      v26 = self->secondary_samples;
      v27 = &v26[v22].delta_dir_to_next.x;
      v64 = v26[v22 + 1].transform.position.x - v26[v22].transform.position.x;
      v66 = v26[v22 + 1].transform.position.y - v26[v22].transform.position.y;
      v28 = v26[v22 + 1].transform.position.z - v26[v22].transform.position.z;
      *v27 = v64;
      v27[1] = v66;
      v68 = v28;
      v27[2] = v68;
      ++v21;
      self->secondary_samples[v22].delta_length = normalize_vector(&self->secondary_samples[v22].delta_dir_to_next);
      ++v22;
    }
    while ( v21 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = 1.0;
  v30 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v30->x = 0.0;
  v30->y = 0.0;
  v30->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = 1.0;
  request_object_vertices(self->bod.object, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->bod.object, 2 * self->segment_count * self->width_cells);
  object = self->bod.object;
  vertices = object->vertices;
  facequads = object->facequads;
  v33 = 0;
  v55 = vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    do
    {
      v34 = self->width_cells;
      v35 = 0;
      arg2a = 0;
      for ( j = v34; v35 <= v34; arg2a = v35 )
      {
        v36 = (double)arg2a - (double)j * 0.5;
        v37 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v6);
        if ( v33 == self->segment_count )
        {
          vertices = v55;
          v57 = v36 * *(v37 - 42);
          v58 = v36 * *(v37 - 41);
          v40 = v36 * *(v37 - 40);
          v79 = *(v37 - 28) + 1.0;
          v65 = *(v37 - 30) + v57;
          v67 = *(v37 - 29) + v58;
          v38 = &v55[v35 + v33 * (v34 + 1)].x;
          *v38 = v65;
          v69 = v79 + v40;
          v38[1] = v67;
          v39 = v69;
        }
        else
        {
          v60 = v36 * *v37;
          v62 = v36 * v37[1];
          v72 = v60 + v37[12];
          v75 = v62 + v37[13];
          v78 = v36 * v37[2] + v37[14];
          v38 = &vertices[v35 + v33 * (v34 + 1)].x;
          *v38 = v72;
          v38[1] = v75;
          v39 = v78;
        }
        v38[2] = v39;
        v34 = self->width_cells;
        ++v35;
        j = v34;
      }
      ++v33;
      v6 += 168;
    }
    while ( v33 <= (signed int)self->segment_count );
    v6 = 0;
  }
  if ( (int)self->segment_count > 0 )
  {
    do
    {
      v41 = 0;
      arg2b = 0;
      if ( (int)self->width_cells > 0 )
      {
        v47 = (double)(v6 % 8) * 0.125;
        v50 = (double)(v6 % 8 + 1) * 0.125;
        do
        {
          v42 = 0;
          v56 = v41 + 1;
          v52 = 0;
          arg2c = (double)arg2b * 0.125;
          v48 = (double)(v41 + 1) * 0.125;
          while ( 1 )
          {
            v43 = &facequads[2 * v41 + 2 * v6 * self->width_cells + v42];
            v43->header_word = 0;
            if ( v42 != 0 )
            {
              v43->vertex_0 = v6 * (LOWORD(self->width_cells) + 1) + v41 + 1;
              v43->vertex_1 = v41 + v6 * (LOWORD(self->width_cells) + 1);
              v43->vertex_2 = v41 + (v6 + 1) * (LOWORD(self->width_cells) + 1);
              v43->vertex_3 = (v6 + 1) * (LOWORD(self->width_cells) + 1) + v41 + 1;
              v43->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_b, nullptr, 0);
              v43->uv[0].u = v48;
              v43->uv[0].v = v47;
              v43->uv[1].u = arg2c;
              v43->uv[1].v = v47;
              v43->uv[2].u = arg2c;
              v43->uv[2].v = v50;
              v43->uv[3].u = v48;
            }
            else
            {
              v43->vertex_0 = v41 + v6 * (LOWORD(self->width_cells) + 1);
              v43->vertex_1 = v6 * (LOWORD(self->width_cells) + 1) + v41 + 1;
              v43->vertex_2 = (v6 + 1) * (LOWORD(self->width_cells) + 1) + v41 + 1;
              v43->vertex_3 = v41 + (v6 + 1) * (LOWORD(self->width_cells) + 1);
              v43->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
              v43->uv[0].u = arg2c;
              v43->uv[0].v = v47;
              v43->uv[1].u = v48;
              v43->uv[1].v = v47;
              v43->uv[2].u = v48;
              v43->uv[2].v = v50;
              v43->uv[3].u = arg2c;
            }
            v43->uv[3].v = v50;
            if ( ++v52 >= 2 )
              break;
            v42 = v52;
          }
          ++v41;
          arg2b = v56;
        }
        while ( v56 < (signed int)self->width_cells );
      }
      ++v6;
    }
    while ( v6 < (signed int)self->segment_count );
  }
  calc_path_length_z(self);
}
