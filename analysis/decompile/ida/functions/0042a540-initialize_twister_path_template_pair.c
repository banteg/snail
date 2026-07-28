/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_twister_path_template_pair @ 0x42a540 */
/* selector: initialize_twister_path_template_pair */

// Builds the TwisterA attachment path-template pair; iOS Path.o names this `cRPath::BuildTwisterA(float, int, bool, char*, char*)`.
void __thiscall initialize_twister_path_template_pair(
        Path *self,
        float height,
        int32_t width_cells_,
        bool handedness,
        char *texture_a,
        char *texture_b,
        char *vertical_texture)
{
  signed int v8; // ebx
  double width_cells; // st7
  PathTemplateSample *primary_samples; // ecx
  int v11; // ebp
  int i; // edi
  double v13; // st7
  Vec3 *p_basis_up; // edx
  PathTemplateSample *v15; // ecx
  float *p_x; // eax
  double v17; // st7
  Vec3 *v18; // edx
  PathTemplateSample *secondary_samples; // ecx
  float *v20; // eax
  double v21; // st7
  signed int v22; // ebp
  int v23; // edi
  PathTemplateSample *v24; // ecx
  float *v25; // eax
  double v26; // st7
  PathTemplateSample *v27; // edx
  float *v28; // eax
  double v29; // st7
  Vec3 *p_delta_dir_to_next; // ecx
  Vec3 *v31; // eax
  Object *object; // eax
  Vec3 *vertices; // ebp
  signed int v34; // edx
  signed int v35; // ecx
  signed int v36; // edi
  double v37; // st7
  float *v38; // eax
  float *v39; // eax
  float v40; // ecx
  double v41; // st7
  int v42; // edi
  int v43; // ecx
  ObjectFaceQuad *v44; // ebp
  float v45; // [esp+10h] [ebp-4Ch]
  int v46; // [esp+14h] [ebp-48h]
  ObjectFaceQuad *facequads; // [esp+18h] [ebp-44h]
  float v48; // [esp+1Ch] [ebp-40h]
  signed int v49; // [esp+1Ch] [ebp-40h]
  float v50; // [esp+20h] [ebp-3Ch]
  float v51; // [esp+24h] [ebp-38h]
  float v52; // [esp+2Ch] [ebp-30h]
  float v53; // [esp+2Ch] [ebp-30h]
  float v54; // [esp+30h] [ebp-2Ch]
  float v55; // [esp+30h] [ebp-2Ch]
  float v56; // [esp+34h] [ebp-28h]
  float v57; // [esp+38h] [ebp-24h]
  float v58; // [esp+38h] [ebp-24h]
  float v59; // [esp+3Ch] [ebp-20h]
  float v60; // [esp+3Ch] [ebp-20h]
  float v61; // [esp+40h] [ebp-1Ch]
  float v62; // [esp+40h] [ebp-1Ch]
  float v63; // [esp+44h] [ebp-18h]
  float v64; // [esp+44h] [ebp-18h]
  float v65; // [esp+44h] [ebp-18h]
  float v66; // [esp+48h] [ebp-14h]
  float v67; // [esp+48h] [ebp-14h]
  float v68; // [esp+48h] [ebp-14h]
  float v69; // [esp+4Ch] [ebp-10h]
  float v70; // [esp+4Ch] [ebp-10h]
  float v71; // [esp+4Ch] [ebp-10h]
  float v72; // [esp+58h] [ebp-4h]
  Vec3 *arg2; // [esp+60h] [ebp+4h]
  float arg2a; // [esp+60h] [ebp+4h]
  int32_t arg3; // [esp+64h] [ebp+8h]
  float arg3a; // [esp+64h] [ebp+8h]
  float arg3d; // [esp+64h] [ebp+8h]
  float arg3e; // [esp+64h] [ebp+8h]
  int32_t arg3b; // [esp+64h] [ebp+8h]
  float arg3c; // [esp+64h] [ebp+8h]
  int arg4; // [esp+68h] [ebp+Ch]
  int arg4a; // [esp+68h] [ebp+Ch]
  float arg4b; // [esp+68h] [ebp+Ch]

  v8 = 0;
  self->kind = PATH_TEMPLATE_KIND_TWISTER;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = width_cells_;
  self->width_or_scale = 1.0;
  self->segment_count = 34;
  self->segment_count_f = 34.0;
  get_path_nodes(self);
  width_cells = (double)(int)self->width_cells;
  primary_samples = self->primary_samples;
  self->has_entry_mesh_transition = 0;
  primary_samples->center_x = width_cells * 0.5 - 4.0;
  if ( !handedness )
    self->primary_samples->center_x = self->primary_samples->center_x * -1.0;
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
  self->primary_samples[33].center_x = (double)(int)self->width_cells * 0.5 - 4.0;
  if ( !handedness )
    self->primary_samples[33].center_x = self->primary_samples[33].center_x * -1.0;
  self->primary_samples[33].rotation_scalar_98 = 0.0;
  self->primary_samples[33].rotation_scalar_94 = 0.0;
  self->primary_samples[33].special_scalar = 0.0;
  self->primary_samples[33].lateral_scale = 1.0;
  set_matrix_identity(&self->primary_samples[33].transform);
  self->primary_samples[33].transform.position.x = self->primary_samples[33].center_x;
  self->primary_samples[33].transform.position.y = 0.0;
  self->primary_samples[33].transform.position.z = 33.0;
  set_matrix_identity(&self->secondary_samples[33].transform);
  self->secondary_samples[33].transform.position.x = self->primary_samples[33].center_x;
  self->secondary_samples[33].transform.position.y = 0.49000001;
  v11 = 0;
  self->secondary_samples[33].transform.position.z = 33.0;
  arg3 = 0;
  for ( i = 1; i < 33; ++i )
  {
    v13 = (double)arg3 * 0.19634955;
    arg3a = v13;
    v48 = v13 * 0.5;
    if ( !handedness )
      arg3a = arg3a + 3.1415927;
    self->primary_samples[i].center_x = 2.5 - (cosine(arg3a) + 1.0) * 0.5 * 5.0;
    self->primary_samples[i].rotation_scalar_98 = 0.0;
    self->primary_samples[i].rotation_scalar_94 = 0.0;
    self->primary_samples[i].special_scalar = 0.0;
    self->primary_samples[i].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[i].transform);
    self->primary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    arg3d = sine(arg3a);
    ++v11;
    self->primary_samples[i].transform.position.y = sine(v48) * arg3d * height;
    arg3e = (float)v11;
    self->primary_samples[i].transform.position.z = arg3e;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->secondary_samples[i].transform.position.y = self->primary_samples[i].transform.position.y + 0.49000001;
    self->secondary_samples[i].transform.position.z = arg3e;
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
      v15 = self->primary_samples;
      p_x = &v15[i - 1].transform.basis_forward.x;
      v52 = v15[i].transform.position.x - v15[i - 1].transform.position.x;
      v54 = p_x[47] - p_x[5];
      v17 = p_x[48] - p_x[6];
      *p_x = v52;
      p_x[1] = v54;
      v56 = v17;
      p_x[2] = v56;
      normalize_vector(&self->primary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        &self->primary_samples[i - 1].transform.basis_right,
        &self->primary_samples[i - 1].transform.basis_up,
        &self->primary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        &self->primary_samples[i - 1].transform.basis_up,
        &self->primary_samples[i - 1].transform.basis_forward,
        &self->primary_samples[i - 1].transform.basis_right);
      orthogonalize_matrix(&self->primary_samples[i - 1].transform);
      v18 = &self->secondary_samples[i - 1].transform.basis_up;
      v18->x = 0.0;
      v18->y = 1.0;
      v18->z = 0.0;
      secondary_samples = self->secondary_samples;
      v20 = &secondary_samples[i - 1].transform.basis_forward.x;
      v63 = secondary_samples[i].transform.position.x - secondary_samples[i - 1].transform.position.x;
      v66 = v20[47] - v20[5];
      v21 = v20[48] - v20[6];
      *v20 = v63;
      v20[1] = v66;
      v69 = v21;
      v20[2] = v69;
      normalize_vector(&self->secondary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        &self->secondary_samples[i - 1].transform.basis_right,
        &self->secondary_samples[i - 1].transform.basis_up,
        &self->secondary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        &self->secondary_samples[i - 1].transform.basis_up,
        &self->secondary_samples[i - 1].transform.basis_forward,
        &self->secondary_samples[i - 1].transform.basis_right);
      orthogonalize_matrix(&self->secondary_samples[i - 1].transform);
    }
    arg3 = v11;
  }
  v22 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v23 = 0;
    do
    {
      v24 = self->primary_samples;
      v25 = &v24[v23].delta_dir_to_next.x;
      v64 = v24[v23 + 1].transform.position.x - v24[v23].transform.position.x;
      v67 = v24[v23 + 1].transform.position.y - v24[v23].transform.position.y;
      v26 = v24[v23 + 1].transform.position.z - v24[v23].transform.position.z;
      *v25 = v64;
      v25[1] = v67;
      v70 = v26;
      v25[2] = v70;
      self->primary_samples[v23].delta_length = normalize_vector(&self->primary_samples[v23].delta_dir_to_next);
      v27 = self->secondary_samples;
      v28 = &v27[v23].delta_dir_to_next.x;
      v57 = v27[v23 + 1].transform.position.x - v27[v23].transform.position.x;
      v59 = v27[v23 + 1].transform.position.y - v27[v23].transform.position.y;
      v29 = v27[v23 + 1].transform.position.z - v27[v23].transform.position.z;
      *v28 = v57;
      v28[1] = v59;
      v61 = v29;
      v28[2] = v61;
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
  vertices = object->vertices;
  facequads = object->facequads;
  v34 = 0;
  arg2 = vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    do
    {
      v35 = self->width_cells;
      v36 = 0;
      arg4 = 0;
      for ( arg3b = v35; v36 <= v35; arg4 = v36 )
      {
        v37 = (double)arg4 - (double)arg3b * 0.5;
        v38 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v8);
        if ( v34 == self->segment_count )
        {
          vertices = arg2;
          v50 = v37 * *(v38 - 42);
          v51 = v37 * *(v38 - 41);
          v41 = v37 * *(v38 - 40);
          v72 = *(v38 - 28) + 1.0;
          v58 = *(v38 - 30) + v50;
          v60 = *(v38 - 29) + v51;
          v39 = &arg2[v36 + v34 * (v35 + 1)].x;
          *v39 = v58;
          v62 = v72 + v41;
          v39[1] = v60;
          v40 = v62;
        }
        else
        {
          v53 = v37 * *v38;
          v55 = v37 * v38[1];
          v65 = v53 + v38[12];
          v68 = v55 + v38[13];
          v71 = v37 * v38[2] + v38[14];
          v39 = &vertices[v36 + v34 * (v35 + 1)].x;
          *v39 = v65;
          v39[1] = v68;
          v40 = v71;
        }
        v39[2] = v40;
        v35 = self->width_cells;
        ++v36;
        arg3b = v35;
      }
      ++v34;
      v8 += 168;
    }
    while ( v34 <= (signed int)self->segment_count );
    v8 = 0;
  }
  if ( (int)self->segment_count > 0 )
  {
    do
    {
      v42 = 0;
      arg4a = 0;
      if ( (int)self->width_cells > 0 )
      {
        arg3c = (double)(v8 % 8) * 0.125;
        v45 = (double)(v8 % 8 + 1) * 0.125;
        do
        {
          v43 = 0;
          v49 = v42 + 1;
          v46 = 0;
          arg4b = (double)arg4a * 0.125;
          arg2a = (double)(v42 + 1) * 0.125;
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
              v44->uv[0].u = arg2a;
              v44->uv[0].v = arg3c;
              v44->uv[1].u = arg4b;
              v44->uv[1].v = arg3c;
              v44->uv[2].u = arg4b;
              v44->uv[2].v = v45;
              v44->uv[3].u = arg2a;
            }
            else
            {
              v44->vertex_0 = v42 + v8 * (LOWORD(self->width_cells) + 1);
              v44->vertex_1 = v8 * (LOWORD(self->width_cells) + 1) + v42 + 1;
              v44->vertex_2 = (v8 + 1) * (LOWORD(self->width_cells) + 1) + v42 + 1;
              v44->vertex_3 = v42 + (v8 + 1) * (LOWORD(self->width_cells) + 1);
              v44->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
              v44->uv[0].u = arg4b;
              v44->uv[0].v = arg3c;
              v44->uv[1].u = arg2a;
              v44->uv[1].v = arg3c;
              v44->uv[2].u = arg2a;
              v44->uv[2].v = v45;
              v44->uv[3].u = arg4b;
            }
            v44->uv[3].v = v45;
            if ( ++v46 >= 2 )
              break;
            v43 = v46;
          }
          ++v42;
          arg4a = v49;
        }
        while ( v49 < (signed int)self->width_cells );
      }
      ++v8;
    }
    while ( v8 < (signed int)self->segment_count );
  }
  calc_path_length_z(self);
}
