/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_start_path_template_pair @ 0x426400 */
/* selector: initialize_start_path_template_pair */

// Builds the Start attachment path-template pair; iOS Path.o names this `cRPath::BuildStart(float, int, bool, char*, char*)`.
void __thiscall initialize_start_path_template_pair(
        cRPath *self,
        float length,
        int32_t width_cells_,
        bool side_exit,
        char *texture_a,
        char *texture_b,
        char *cap_texture)
{
  double v8; // st7
  uint32_t segment_count; // eax
  double v10; // st7
  int i; // edi
  int v12; // edi
  bool v13; // zf
  int v14; // edi
  PathTemplateSample *v15; // eax
  PathTemplateSample *primary_samples; // edx
  float *p_x; // eax
  double v18; // st7
  PathTemplateSample *v19; // ecx
  PathTemplateSample *v20; // eax
  double v21; // st7
  double v22; // st7
  signed int v23; // ebx
  int v24; // edi
  PathTemplateSample *v25; // edx
  float *v26; // eax
  double v27; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *v29; // eax
  double v30; // st7
  Object *object; // eax
  signed int v32; // edi
  int v33; // ebx
  signed int width_cells; // ecx
  signed int v35; // edx
  PathTemplateSample *v36; // eax
  double v37; // st7
  int v38; // eax
  float *v39; // ecx
  signed int j; // ebx
  int v41; // edi
  int v42; // ecx
  ObjectFaceQuad *v43; // ebp
  float v44; // [esp+0h] [ebp-58h]
  int v45; // [esp+14h] [ebp-44h]
  float v46; // [esp+14h] [ebp-44h]
  float v47; // [esp+18h] [ebp-40h]
  float v48; // [esp+18h] [ebp-40h]
  float v49; // [esp+1Ch] [ebp-3Ch]
  int v50; // [esp+1Ch] [ebp-3Ch]
  int v51; // [esp+1Ch] [ebp-3Ch]
  float v52; // [esp+20h] [ebp-38h]
  ObjectFaceQuad *facequads; // [esp+20h] [ebp-38h]
  float v54; // [esp+24h] [ebp-34h]
  float v55; // [esp+24h] [ebp-34h]
  Vec3 *vertices; // [esp+24h] [ebp-34h]
  signed int v57; // [esp+24h] [ebp-34h]
  float v58; // [esp+34h] [ebp-24h]
  float v59; // [esp+38h] [ebp-20h]
  float v60; // [esp+3Ch] [ebp-1Ch]
  float v61; // [esp+40h] [ebp-18h]
  float v62; // [esp+40h] [ebp-18h]
  float v63; // [esp+44h] [ebp-14h]
  float v64; // [esp+44h] [ebp-14h]
  float v65; // [esp+48h] [ebp-10h]
  float v66; // [esp+4Ch] [ebp-Ch]
  float v67; // [esp+4Ch] [ebp-Ch]
  float v68; // [esp+4Ch] [ebp-Ch]
  float v69; // [esp+50h] [ebp-8h]
  float v70; // [esp+50h] [ebp-8h]
  float v71; // [esp+50h] [ebp-8h]
  float v72; // [esp+54h] [ebp-4h]
  float v73; // [esp+54h] [ebp-4h]
  float v74; // [esp+54h] [ebp-4h]
  float arg2; // [esp+5Ch] [ebp+4h]
  int arg2a; // [esp+5Ch] [ebp+4h]
  int arg2b; // [esp+5Ch] [ebp+4h]
  float arg2c; // [esp+5Ch] [ebp+4h]
  int32_t arg3; // [esp+60h] [ebp+8h]
  int32_t arg3a; // [esp+60h] [ebp+8h]
  int32_t arg3b; // [esp+60h] [ebp+8h]
  int32_t arg3c; // [esp+60h] [ebp+8h]
  float arg3d; // [esp+60h] [ebp+8h]

  self->kind = PATH_TEMPLATE_KIND_START;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = width_cells_;
  v45 = (__int64)(length * 3.1415927);
  self->width_or_scale = 1.0;
  self->segment_count = v45 + 16;
  self->segment_count_f = (float)(v45 + 15);
  v8 = (double)v45;
  v47 = v8;
  arg2 = v8 * 0.31830987;
  get_path_nodes(self);
  segment_count = self->segment_count;
  self->has_entry_mesh_transition = 0;
  v10 = arg2 + arg2;
  arg3 = 0;
  self->segment_count = segment_count - 1;
  for ( i = 0; i < 5; self->secondary_samples[i - 1].delta_length = 1.0 )
  {
    self->primary_samples[i].center_x = 0.0;
    self->primary_samples[i].rotation_scalar_98 = 0.0;
    self->primary_samples[i].rotation_scalar_94 = 0.0;
    self->primary_samples[i].special_scalar = 0.0;
    self->primary_samples[i].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[i].transform);
    self->primary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    v49 = v10;
    self->primary_samples[i].transform.position.y = v49;
    v52 = (float)arg3;
    self->primary_samples[i].transform.position.z = v52;
    self->primary_samples[i].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    v54 = v10 + 0.49000001;
    self->secondary_samples[i].transform.position.y = v54;
    self->secondary_samples[i++].transform.position.z = v52;
    ++arg3;
  }
  v50 = 11;
  arg3a = v45 + 5;
  v12 = v45 + 5;
  do
  {
    self->primary_samples[v12].center_x = 0.0;
    self->primary_samples[v12].rotation_scalar_98 = 0.0;
    self->primary_samples[v12].rotation_scalar_94 = 0.0;
    self->primary_samples[v12].special_scalar = 0.0;
    self->primary_samples[v12].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v12].transform);
    self->primary_samples[v12].transform.position.x = self->primary_samples[v12].center_x;
    self->primary_samples[v12].transform.position.y = 0.0;
    self->primary_samples[v12].transform.position.z = (float)arg3a;
    self->primary_samples[v12].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v12].transform);
    self->secondary_samples[v12].transform.position.x = self->primary_samples[v12].center_x;
    self->secondary_samples[v12].transform.position.y = 0.49000001;
    self->secondary_samples[v12].transform.position.z = self->primary_samples[v12].transform.position.z;
    self->secondary_samples[v12++].delta_length = 1.0;
    v13 = v50 == 1;
    ++arg3a;
    --v50;
  }
  while ( !v13 );
  arg3b = 0;
  if ( v45 > 0 )
  {
    v14 = 5;
    do
    {
      self->primary_samples[v14].center_x = 0.0;
      self->primary_samples[v14].rotation_scalar_98 = 0.0;
      self->primary_samples[v14].rotation_scalar_94 = 0.0;
      self->primary_samples[v14].special_scalar = 0.0;
      self->primary_samples[v14].lateral_scale = 1.0;
      set_matrix_identity(&self->primary_samples[v14].transform);
      self->primary_samples[v14].transform.position.x = self->primary_samples[v14].center_x;
      v55 = (float)(arg3b + 5);
      self->primary_samples[v14].transform.position.z = v55;
      v44 = (double)arg3b * 3.1415927 / v47;
      self->primary_samples[v14].transform.position.y = (cosine(v44) + 1.0) * arg2;
      set_matrix_identity(&self->secondary_samples[v14].transform);
      self->secondary_samples[v14].transform.position.x = self->primary_samples[v14].center_x;
      self->secondary_samples[v14].transform.position.z = v55;
      self->secondary_samples[v14].transform.position.y = self->primary_samples[v14].transform.position.y + 0.49000001;
      if ( v14 <= 5 )
      {
        set_matrix_rotation_identity(&self->primary_samples[v14 - 1].transform);
        set_matrix_rotation_identity(&self->secondary_samples[v14 - 1].transform);
      }
      else
      {
        v15 = &self->primary_samples[v14 - 1];
        v15->transform.basis_right.x = 1.0;
        v15->transform.basis_right.y = 0.0;
        v15->transform.basis_right.z = 0.0;
        primary_samples = self->primary_samples;
        p_x = &primary_samples[v14 - 1].transform.basis_forward.x;
        v58 = primary_samples[v14].transform.position.x - primary_samples[v14 - 1].transform.position.x;
        v59 = p_x[47] - p_x[5];
        v18 = p_x[48] - p_x[6];
        *p_x = v58;
        p_x[1] = v59;
        v60 = v18;
        p_x[2] = v60;
        normalize_vector(&self->primary_samples[v14 - 1].transform.basis_forward);
        cross_vectors(
          &self->primary_samples[v14 - 1].transform.basis_up,
          &self->primary_samples[v14 - 1].transform.basis_forward,
          &self->primary_samples[v14 - 1].transform.basis_right);
        v19 = &self->secondary_samples[v14 - 1];
        v19->transform.basis_right.x = 1.0;
        v19->transform.basis_right.y = 0.0;
        v19->transform.basis_right.z = 0.0;
        v20 = &self->secondary_samples[v14];
        v21 = v20->transform.position.x - v20[-1].transform.position.x;
        v20 = (PathTemplateSample *)((char *)v20 - 136);
        v66 = v21;
        v69 = v20[1].transform.basis_up.y - v20->transform.basis_up.y;
        v22 = v20[1].transform.basis_up.z - v20->transform.basis_up.z;
        v20->transform.basis_right.x = v66;
        v20->transform.basis_right.y = v69;
        v72 = v22;
        v20->transform.basis_right.z = v72;
        normalize_vector(&self->secondary_samples[v14 - 1].transform.basis_forward);
        cross_vectors(
          &self->secondary_samples[v14 - 1].transform.basis_up,
          &self->secondary_samples[v14 - 1].transform.basis_forward,
          &self->secondary_samples[v14 - 1].transform.basis_right);
      }
      ++v14;
      ++arg3b;
    }
    while ( arg3b < v45 );
  }
  v23 = 0;
  if ( (int)self->segment_count > 0 )
  {
    v24 = 0;
    do
    {
      v25 = self->primary_samples;
      v26 = &v25[v24].delta_dir_to_next.x;
      v67 = v25[v24 + 1].transform.position.x - v25[v24].transform.position.x;
      v70 = v25[v24 + 1].transform.position.y - v25[v24].transform.position.y;
      v27 = v25[v24 + 1].transform.position.z - v25[v24].transform.position.z;
      *v26 = v67;
      v26[1] = v70;
      v73 = v27;
      v26[2] = v73;
      self->primary_samples[v24].delta_length = normalize_vector(&self->primary_samples[v24].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v29 = &secondary_samples[v24].delta_dir_to_next.x;
      v61 = secondary_samples[v24 + 1].transform.position.x - secondary_samples[v24].transform.position.x;
      v63 = secondary_samples[v24 + 1].transform.position.y - secondary_samples[v24].transform.position.y;
      v30 = secondary_samples[v24 + 1].transform.position.z - secondary_samples[v24].transform.position.z;
      *v29 = v61;
      v29[1] = v63;
      v65 = v30;
      v29[2] = v65;
      ++v23;
      self->secondary_samples[v24].delta_length = normalize_vector(&self->secondary_samples[v24].delta_dir_to_next);
      ++v24;
    }
    while ( v23 < (signed int)self->segment_count );
  }
  request_object_vertices(self->bod.object, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->bod.object, 2 * self->segment_count * self->width_cells);
  object = self->bod.object;
  v32 = 0;
  facequads = object->facequads;
  vertices = object->vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v33 = 0;
    do
    {
      width_cells = self->width_cells;
      v35 = 0;
      arg2a = 0;
      for ( arg3c = width_cells; v35 <= width_cells; arg3c = width_cells )
      {
        v36 = &self->primary_samples[v33];
        v37 = (double)arg2a - (double)arg3c * 0.5;
        v62 = v37 * v36->transform.basis_right.x;
        v64 = v37 * v36->transform.basis_right.y;
        v68 = v62 + v36->transform.position.x;
        v71 = v64 + v36->transform.position.y;
        v74 = v37 * v36->transform.basis_right.z + v36->transform.position.z;
        v38 = v35 + v32 * (width_cells + 1);
        arg2a = ++v35;
        v39 = &vertices[v38].x;
        *v39 = v68;
        v39[1] = v71;
        v39[2] = v74;
        width_cells = self->width_cells;
      }
      ++v32;
      ++v33;
    }
    while ( v32 <= (signed int)self->segment_count );
  }
  for ( j = 0; j < (signed int)self->segment_count; ++j )
  {
    v41 = 0;
    arg2b = 0;
    if ( (int)self->width_cells > 0 )
    {
      arg3d = (double)(j % 8) * 0.125;
      v48 = (double)(j % 8 + 1) * 0.125;
      do
      {
        v42 = 0;
        v57 = v41 + 1;
        v51 = 0;
        arg2c = (double)arg2b * 0.125;
        v46 = (double)(v41 + 1) * 0.125;
        while ( 1 )
        {
          v43 = &facequads[2 * v41 + 2 * j * self->width_cells + v42];
          if ( v42 != 0 )
          {
            v43->header_word = 4;
            v43->vertex_0 = j * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->vertex_1 = v41 + j * (LOWORD(self->width_cells) + 1);
            v43->vertex_2 = v41 + (j + 1) * (LOWORD(self->width_cells) + 1);
            v43->vertex_3 = (j + 1) * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
            v43->uv[0].u = v46;
            v43->uv[0].v = arg3d;
            v43->uv[1].u = arg2c;
            v43->uv[1].v = arg3d;
            v43->uv[2].u = arg2c;
            v43->uv[2].v = v48;
            v43->uv[3].u = v46;
          }
          else
          {
            v43->vertex_0 = v41 + j * (LOWORD(self->width_cells) + 1);
            v43->vertex_1 = j * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->vertex_2 = (j + 1) * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->vertex_3 = v41 + (j + 1) * (LOWORD(self->width_cells) + 1);
            v43->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
            v43->uv[0].u = arg2c;
            v43->uv[0].v = arg3d;
            v43->uv[1].u = v46;
            v43->uv[1].v = arg3d;
            v43->uv[2].u = v46;
            v43->uv[2].v = v48;
            v43->uv[3].u = arg2c;
          }
          v43->uv[3].v = v48;
          if ( ++v51 >= 2 )
            break;
          v42 = v51;
        }
        ++v41;
        arg2b = v57;
      }
      while ( v57 < (signed int)self->width_cells );
    }
  }
  calc_path_length_z(self);
}
