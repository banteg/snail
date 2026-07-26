/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_toad_path_template_pair @ 0x42cbf0 */
/* selector: initialize_toad_path_template_pair */

// Builds the Toad attachment path-template pair; iOS Path.o names this `cRPath::BuildToad(bool, char*, char*)`.
void __thiscall initialize_toad_path_template_pair(
        Path *self,
        bool turn_left,
        char *texture_a,
        char *texture_b,
        char *vertical_texture)
{
  int v6; // esi
  int v7; // esi
  int v8; // esi
  int v9; // ebx
  double v10; // st7
  Vec3 *p_basis_up; // ecx
  PathTemplateSample *v12; // eax
  double v13; // st7
  double v14; // st7
  PathTemplateSample *primary_samples; // ecx
  double v16; // st7
  double v17; // st6
  Vec3 *p_position; // eax
  signed int v19; // edi
  int v20; // esi
  PathTemplateSample *v21; // ecx
  float *p_x; // eax
  double v23; // st7
  PathTemplateSample *secondary_samples; // edx
  float *v25; // eax
  double v26; // st7
  Vec3 *p_delta_dir_to_next; // ecx
  Vec3 *v28; // eax
  Object *object; // eax
  Vec3 *vertices; // edi
  signed int v31; // edx
  int v32; // ebx
  signed int width_cells; // ecx
  signed int v34; // esi
  double v35; // st7
  PathTemplateSample *v36; // eax
  float *v37; // eax
  float v38; // ecx
  double v39; // st7
  signed int j; // ebx
  int v41; // esi
  int v42; // ecx
  ObjectFaceQuad *v43; // edi
  float v44; // [esp+0h] [ebp-68h]
  int v45; // [esp+14h] [ebp-54h]
  float v46; // [esp+14h] [ebp-54h]
  float v47; // [esp+18h] [ebp-50h]
  float v48; // [esp+18h] [ebp-50h]
  int v49; // [esp+1Ch] [ebp-4Ch]
  int i; // [esp+1Ch] [ebp-4Ch]
  float v51; // [esp+1Ch] [ebp-4Ch]
  float v52; // [esp+20h] [ebp-48h]
  int v53; // [esp+20h] [ebp-48h]
  ObjectFaceQuad *facequads; // [esp+24h] [ebp-44h]
  float angleb; // [esp+28h] [ebp-40h]
  float anglec; // [esp+28h] [ebp-40h]
  float angled; // [esp+28h] [ebp-40h]
  Vec3 *angle; // [esp+28h] [ebp-40h]
  signed int anglea; // [esp+28h] [ebp-40h]
  float v60; // [esp+2Ch] [ebp-3Ch]
  float v61; // [esp+2Ch] [ebp-3Ch]
  float v62; // [esp+30h] [ebp-38h]
  float v63; // [esp+30h] [ebp-38h]
  float v64; // [esp+34h] [ebp-34h]
  float v65; // [esp+34h] [ebp-34h]
  float v66; // [esp+38h] [ebp-30h]
  float v67; // [esp+38h] [ebp-30h]
  float v68; // [esp+38h] [ebp-30h]
  float v69; // [esp+3Ch] [ebp-2Ch]
  float v70; // [esp+3Ch] [ebp-2Ch]
  float v71; // [esp+3Ch] [ebp-2Ch]
  float v72; // [esp+40h] [ebp-28h]
  float v73; // [esp+40h] [ebp-28h]
  float v74; // [esp+40h] [ebp-28h]
  float v75; // [esp+44h] [ebp-24h]
  float v76; // [esp+48h] [ebp-20h]
  float v77; // [esp+48h] [ebp-20h]
  float v78; // [esp+4Ch] [ebp-1Ch]
  float v79; // [esp+50h] [ebp-18h]
  float v80; // [esp+54h] [ebp-14h]
  float v81; // [esp+64h] [ebp-4h]
  signed int arg2f; // [esp+6Ch] [ebp+4h]
  signed int arg2; // [esp+6Ch] [ebp+4h]
  signed int arg2a; // [esp+6Ch] [ebp+4h]
  signed int arg2b; // [esp+6Ch] [ebp+4h]
  signed int arg2c; // [esp+6Ch] [ebp+4h]
  signed int arg2d; // [esp+6Ch] [ebp+4h]
  float arg2e; // [esp+6Ch] [ebp+4h]

  self->kind = PATH_TEMPLATE_KIND_TURNUNDER_TOAD_FAMILY;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = 4;
  if ( turn_left )
  {
    v6 = 1;
    v47 = -2.0;
    v52 = -1.0;
    v45 = 1;
    v49 = 3;
  }
  else
  {
    v45 = 2;
    v47 = 2.0;
    v6 = 2;
    v52 = 1.0;
    v49 = 1;
  }
  self->width_or_scale = 1.0;
  arg2f = v49 + v6 + 26;
  self->segment_count = arg2f;
  self->segment_count_f = (float)arg2f;
  get_path_nodes(self);
  self->has_entry_mesh_transition = 0;
  arg2 = 0;
  v7 = 0;
  do
  {
    self->primary_samples[v7].center_x = v47;
    self->primary_samples[v7].rotation_scalar_98 = 0.0;
    self->primary_samples[v7].rotation_scalar_94 = 0.0;
    self->primary_samples[v7].special_scalar = 0.0;
    self->primary_samples[v7].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v7].transform);
    self->primary_samples[v7].transform.position.x = self->primary_samples[v7].center_x;
    angleb = (float)arg2;
    self->primary_samples[v7].transform.position.y = 0.0;
    self->primary_samples[v7].transform.position.z = angleb;
    self->primary_samples[v7].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v7].transform);
    self->secondary_samples[v7].transform.position.x = self->primary_samples[v7].center_x;
    self->secondary_samples[v7].transform.position.y = 0.49000001;
    self->secondary_samples[v7].transform.position.z = angleb;
    self->secondary_samples[v7++].delta_length = 1.0;
    ++arg2;
  }
  while ( arg2 < v45 );
  arg2a = v45 + 26;
  v8 = v45 + 26;
  do
  {
    self->primary_samples[v8].center_x = v47;
    self->primary_samples[v8].rotation_scalar_98 = 0.0;
    self->primary_samples[v8].rotation_scalar_94 = 0.0;
    self->primary_samples[v8].special_scalar = 0.0;
    self->primary_samples[v8].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v8].transform);
    anglec = (float)arg2a;
    self->primary_samples[v8].transform.position.x = self->primary_samples[v8].center_x;
    self->primary_samples[v8].transform.position.y = 0.0;
    self->primary_samples[v8].transform.position.z = anglec;
    self->primary_samples[v8].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v8].transform);
    self->secondary_samples[v8].transform.position.x = self->primary_samples[v8].center_x;
    self->secondary_samples[v8].transform.position.y = 0.49000001;
    self->secondary_samples[v8].transform.position.z = anglec;
    self->secondary_samples[v8++].delta_length = 1.0;
    ++arg2a;
  }
  while ( arg2a + -26 - v45 < v49 );
  arg2b = 0;
  v9 = v45;
  do
  {
    v44 = (double)arg2b * 0.24166098;
    angled = (1.0 - cosine(v44)) * 0.5 * v52 * 1.5707964;
    self->primary_samples[v9].center_x = v47;
    self->primary_samples[v9].rotation_scalar_98 = 0.0;
    self->primary_samples[v9].rotation_scalar_94 = 0.0;
    self->primary_samples[v9].special_scalar = 0.0;
    self->primary_samples[v9].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v9].transform);
    v10 = sine(angled);
    self->primary_samples[v9].transform.position.x = v10 + v10 + v47;
    self->primary_samples[v9].transform.position.z = (float)(v45 + arg2b);
    self->primary_samples[v9].transform.position.y = 0.0;
    p_basis_up = &self->primary_samples[v9].transform.basis_up;
    p_basis_up->x = 0.0;
    p_basis_up->y = 1.0;
    p_basis_up->z = 0.0;
    v12 = &self->primary_samples[v9];
    v13 = v12->transform.position.x - v12[-1].transform.position.x;
    v12 = (PathTemplateSample *)((char *)v12 + 32);
    v66 = v13;
    v69 = v12->transform.basis_up.y - v12[-1].transform.basis_up.y;
    v14 = v12->transform.basis_up.z - v12[-1].transform.basis_up.z;
    v12->transform.basis_right.x = v66;
    v12->transform.basis_right.y = v69;
    v72 = v14;
    v12->transform.basis_right.z = v72;
    normalize_vector(&self->primary_samples[v9].transform.basis_forward);
    cross_vectors(
      &self->primary_samples[v9].transform.basis_right,
      &self->primary_samples[v9].transform.basis_up,
      &self->primary_samples[v9].transform.basis_forward);
    rotate_matrix_local_z(&self->primary_samples[v9].transform, angled);
    qmemcpy(&self->secondary_samples[v9], &self->primary_samples[v9], 0x40u);
    primary_samples = self->primary_samples;
    v16 = primary_samples[v9].transform.basis_up.x * 0.49000001;
    v76 = primary_samples[v9].transform.basis_up.y * 0.49000001;
    v17 = primary_samples[v9].transform.basis_up.z * 0.49000001;
    p_position = &self->secondary_samples[v9++].transform.position;
    v78 = v17;
    p_position->x = v16 + p_position->x;
    p_position->y = v76 + p_position->y;
    p_position->z = v78 + p_position->z;
    ++arg2b;
  }
  while ( arg2b < 26 );
  v19 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v20 = 0;
    do
    {
      v21 = self->primary_samples;
      p_x = &v21[v20].delta_dir_to_next.x;
      v67 = v21[v20 + 1].transform.position.x - v21[v20].transform.position.x;
      v70 = v21[v20 + 1].transform.position.y - v21[v20].transform.position.y;
      v23 = v21[v20 + 1].transform.position.z - v21[v20].transform.position.z;
      *p_x = v67;
      p_x[1] = v70;
      v73 = v23;
      p_x[2] = v73;
      self->primary_samples[v20].delta_length = normalize_vector(&self->primary_samples[v20].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v25 = &secondary_samples[v20].delta_dir_to_next.x;
      v60 = secondary_samples[v20 + 1].transform.position.x - secondary_samples[v20].transform.position.x;
      v62 = secondary_samples[v20 + 1].transform.position.y - secondary_samples[v20].transform.position.y;
      v26 = secondary_samples[v20 + 1].transform.position.z - secondary_samples[v20].transform.position.z;
      *v25 = v60;
      v25[1] = v62;
      v64 = v26;
      v25[2] = v64;
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
  vertices = object->vertices;
  facequads = object->facequads;
  v31 = 0;
  angle = vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v32 = 0;
    do
    {
      width_cells = self->width_cells;
      v34 = 0;
      arg2c = 0;
      for ( i = width_cells; v34 <= width_cells; arg2c = v34 )
      {
        v35 = (double)arg2c - (double)i * 0.5;
        v36 = &self->primary_samples[v32];
        if ( v31 == self->segment_count )
        {
          vertices = angle;
          v79 = v35 * v36[-1].transform.basis_right.x;
          v80 = v35 * v36[-1].transform.basis_right.y;
          v39 = v35 * v36[-1].transform.basis_right.z;
          v81 = v36[-1].transform.position.z + 1.0;
          v61 = v36[-1].transform.position.x + v79;
          v63 = v36[-1].transform.position.y + v80;
          v37 = &angle[v34 + v31 * (width_cells + 1)].x;
          *v37 = v61;
          v65 = v81 + v39;
          v37[1] = v63;
          v38 = v65;
        }
        else
        {
          v75 = v35 * v36->transform.basis_right.x;
          v77 = v35 * v36->transform.basis_right.y;
          v68 = v75 + v36->transform.position.x;
          v71 = v77 + v36->transform.position.y;
          v74 = v35 * v36->transform.basis_right.z + v36->transform.position.z;
          v37 = &vertices[v34 + v31 * (width_cells + 1)].x;
          *v37 = v68;
          v37[1] = v71;
          v38 = v74;
        }
        v37[2] = v38;
        width_cells = self->width_cells;
        ++v34;
        i = width_cells;
      }
      ++v31;
      ++v32;
    }
    while ( v31 <= (signed int)self->segment_count );
  }
  for ( j = 0; j < (signed int)self->segment_count; ++j )
  {
    v41 = 0;
    arg2d = 0;
    if ( (int)self->width_cells > 0 )
    {
      v51 = (double)(j % 8) * 0.125;
      v46 = (double)(j % 8 + 1) * 0.125;
      do
      {
        v42 = 0;
        anglea = v41 + 1;
        v53 = 0;
        arg2e = (double)arg2d * 0.125;
        v48 = (double)(v41 + 1) * 0.125;
        while ( 1 )
        {
          v43 = &facequads[2 * v41 + 2 * j * self->width_cells + v42];
          v43->header_word = 0;
          if ( v42 != 0 )
          {
            v43->vertex_0 = j * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->vertex_1 = v41 + j * (LOWORD(self->width_cells) + 1);
            v43->vertex_2 = v41 + (j + 1) * (LOWORD(self->width_cells) + 1);
            v43->vertex_3 = (j + 1) * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_b, nullptr, 0);
            v43->uv[0].u = v48;
            v43->uv[0].v = v51;
            v43->uv[1].u = arg2e;
            v43->uv[1].v = v51;
            v43->uv[2].u = arg2e;
            v43->uv[2].v = v46;
            v43->uv[3].u = v48;
          }
          else
          {
            v43->vertex_0 = v41 + j * (LOWORD(self->width_cells) + 1);
            v43->vertex_1 = j * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->vertex_2 = (j + 1) * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->vertex_3 = v41 + (j + 1) * (LOWORD(self->width_cells) + 1);
            v43->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
            v43->uv[0].u = arg2e;
            v43->uv[0].v = v51;
            v43->uv[1].u = v48;
            v43->uv[1].v = v51;
            v43->uv[2].u = v48;
            v43->uv[2].v = v46;
            v43->uv[3].u = arg2e;
          }
          v43->uv[3].v = v46;
          if ( ++v53 >= 2 )
            break;
          v42 = v53;
        }
        ++v41;
        arg2d = anglea;
      }
      while ( anglea < (signed int)self->width_cells );
    }
  }
  calc_path_length_z(self);
}
