/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_turnoverdouble_path_template_pair @ 0x427640 */
/* selector: initialize_turnoverdouble_path_template_pair */

// Builds the TurnoverDouble attachment path-template pair; iOS Path.o names this `cRPath::BuildTurnoverDouble(float, int, bool, char*, char*)`.
void __thiscall initialize_turnoverdouble_path_template_pair(
        cRPath *self,
        float length,
        int32_t width_cells_,
        bool side_exit,
        char *texture_a,
        char *texture_b,
        char *cap_texture)
{
  signed int v8; // ebx
  double v9; // st7
  int v10; // edi
  int v11; // edi
  int v12; // ecx
  int v13; // ebx
  double v14; // st7
  double v15; // st7
  PathTemplateSample *primary_samples; // edi
  PathTemplateSample *v17; // edi
  double v18; // st7
  Vec3 *p_basis_up; // ecx
  PathTemplateSample *v20; // eax
  PathTemplateSample *v21; // ecx
  double v22; // st7
  double v23; // st6
  Vec3 *p_position; // eax
  int v25; // edi
  PathTemplateSample *v26; // ecx
  float *p_x; // eax
  double v28; // st7
  PathTemplateSample *secondary_samples; // edx
  float *v30; // eax
  double v31; // st7
  Vec3 *p_delta_dir_to_next; // ecx
  Vec3 *v33; // ecx
  Object *object; // eax
  Vec3 *vertices; // ebx
  signed int v36; // edx
  int v37; // esi
  signed int width_cells; // ecx
  signed int v39; // edi
  double v40; // st7
  PathTemplateSample *v41; // eax
  float *v42; // eax
  float v43; // ecx
  double v44; // st7
  signed int i; // edi
  int v46; // esi
  int v47; // ecx
  ObjectFaceQuad *v48; // ebx
  float v49; // [esp+0h] [ebp-64h]
  float v50; // [esp+0h] [ebp-64h]
  float v51; // [esp+14h] [ebp-50h]
  float v52; // [esp+14h] [ebp-50h]
  int v53; // [esp+18h] [ebp-4Ch]
  float v54; // [esp+18h] [ebp-4Ch]
  float v55; // [esp+1Ch] [ebp-48h]
  int v56; // [esp+1Ch] [ebp-48h]
  ObjectFaceQuad *facequads; // [esp+20h] [ebp-44h]
  float v58; // [esp+24h] [ebp-40h]
  float v59; // [esp+24h] [ebp-40h]
  float v60; // [esp+24h] [ebp-40h]
  float v61; // [esp+24h] [ebp-40h]
  float v62; // [esp+24h] [ebp-40h]
  Vec3 *v63; // [esp+24h] [ebp-40h]
  signed int v64; // [esp+24h] [ebp-40h]
  float v65; // [esp+28h] [ebp-3Ch]
  float v66; // [esp+28h] [ebp-3Ch]
  float v67; // [esp+28h] [ebp-3Ch]
  float v68; // [esp+2Ch] [ebp-38h]
  float v69; // [esp+2Ch] [ebp-38h]
  float v70; // [esp+30h] [ebp-34h]
  float v71; // [esp+30h] [ebp-34h]
  float v72; // [esp+34h] [ebp-30h]
  float v73; // [esp+34h] [ebp-30h]
  float v74; // [esp+34h] [ebp-30h]
  float v75; // [esp+38h] [ebp-2Ch]
  float v76; // [esp+38h] [ebp-2Ch]
  float v77; // [esp+38h] [ebp-2Ch]
  float v78; // [esp+3Ch] [ebp-28h]
  float v79; // [esp+3Ch] [ebp-28h]
  float v80; // [esp+3Ch] [ebp-28h]
  float v81; // [esp+40h] [ebp-24h]
  float v82; // [esp+44h] [ebp-20h]
  float v83; // [esp+44h] [ebp-20h]
  float v84; // [esp+48h] [ebp-1Ch]
  float v85; // [esp+4Ch] [ebp-18h]
  float v86; // [esp+50h] [ebp-14h]
  float v87; // [esp+60h] [ebp-4h]
  float arg2; // [esp+68h] [ebp+4h]
  int arg2a; // [esp+68h] [ebp+4h]
  int arg2b; // [esp+68h] [ebp+4h]
  float arg2c; // [esp+68h] [ebp+4h]
  int32_t arg3; // [esp+6Ch] [ebp+8h]
  int32_t arg3a; // [esp+6Ch] [ebp+8h]
  int32_t arg3b; // [esp+6Ch] [ebp+8h]
  int32_t arg3c; // [esp+6Ch] [ebp+8h]
  float arg3d; // [esp+6Ch] [ebp+8h]

  v8 = 0;
  self->kind = PATH_TEMPLATE_KIND_TURNOVERDOUBLE;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = width_cells_;
  v53 = (__int64)(length * 9.424778);
  self->width_or_scale = 1.0;
  self->segment_count = v53 + 8;
  self->segment_count_f = (float)(v53 + 8);
  v9 = (double)v53;
  v55 = v9;
  arg2 = v9 * 0.079577468;
  get_path_nodes(self);
  self->has_entry_mesh_transition = 0;
  arg3 = 0;
  v10 = 0;
  do
  {
    self->primary_samples[v10].center_x = (double)(int)self->width_cells * 0.5 - 4.0;
    self->primary_samples[v10].rotation_scalar_98 = 0.0;
    self->primary_samples[v10].rotation_scalar_94 = 0.0;
    self->primary_samples[v10].special_scalar = 0.0;
    self->primary_samples[v10].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v10].transform);
    self->primary_samples[v10].transform.position.x = self->primary_samples[v10].center_x;
    v58 = (float)arg3;
    self->primary_samples[v10].transform.position.y = 0.0;
    self->primary_samples[v10].transform.position.z = v58;
    self->primary_samples[v10].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v10].transform);
    self->secondary_samples[v10].transform.position.x = self->primary_samples[v10].center_x;
    self->secondary_samples[v10].transform.position.y = 0.49000001;
    self->secondary_samples[v10++].transform.position.z = v58;
    self->secondary_samples[v10 - 1].delta_length = 1.0;
    ++arg3;
  }
  while ( v10 < 6 );
  arg3a = v53 + 6;
  v11 = v53 + 6;
  do
  {
    self->primary_samples[v11].center_x = (double)(int)self->width_cells * 0.5 - 4.0;
    self->primary_samples[v11].rotation_scalar_98 = 0.0;
    self->primary_samples[v11].rotation_scalar_94 = 0.0;
    self->primary_samples[v11].special_scalar = 0.0;
    self->primary_samples[v11].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v11].transform);
    v59 = (float)arg3a;
    self->primary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
    self->primary_samples[v11].transform.position.y = 0.0;
    self->primary_samples[v11].transform.position.z = v59;
    self->primary_samples[v11].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v11].transform);
    self->secondary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
    self->secondary_samples[v11].transform.position.y = 0.49000001;
    self->secondary_samples[v11].transform.position.z = v59;
    self->secondary_samples[v11++].delta_length = 1.0;
    v12 = ++arg3a + -6 - v53;
  }
  while ( v12 < 2 );
  arg3b = 0;
  if ( v53 > 0 )
  {
    v13 = 6;
    do
    {
      v14 = (double)arg3b;
      v60 = v14 * 6.2831855 / v55;
      v15 = v14 * 12.566371 / v55;
      v51 = v15;
      if ( v15 > 6.2831855 )
        v51 = 12.566371 - v51;
      primary_samples = self->primary_samples;
      v49 = v60 + 1.5707964;
      primary_samples[v13].center_x = sine(v49) * primary_samples->center_x;
      self->primary_samples[v13].rotation_scalar_98 = -v51;
      self->primary_samples[v13].rotation_scalar_94 = 0.0;
      self->primary_samples[v13].special_scalar = 0.0;
      self->primary_samples[v13].lateral_scale = 1.0;
      set_matrix_identity(&self->primary_samples[v13].transform);
      v17 = self->primary_samples;
      v50 = v51 * 0.5;
      v61 = sine(v50);
      v18 = sine(v51);
      self->primary_samples[v13].transform.position.x = v17[v13].center_x - (v18 * v61 + v18 * v61);
      self->primary_samples[v13].transform.position.z = (float)(arg3b + 6);
      self->primary_samples[v13].transform.position.y = (arg2 - cosine(v51) * arg2) * 0.40000001;
      v62 = cosine(v51);
      v65 = sine(v51);
      p_basis_up = &self->primary_samples[v13].transform.basis_up;
      p_basis_up->x = v65;
      p_basis_up->y = v62;
      p_basis_up->z = 0.0;
      v20 = &self->primary_samples[v13];
      v72 = v20->transform.position.x - v20[-1].transform.position.x;
      v75 = v20->transform.position.y - v20[-1].transform.position.y;
      v78 = v20->transform.position.z - v20[-1].transform.position.z;
      v20 = (PathTemplateSample *)((char *)v20 + 32);
      v20->transform.basis_right.x = v72;
      v20->transform.basis_right.y = v75;
      v20->transform.basis_right.z = v78;
      normalize_vector(&self->primary_samples[v13].transform.basis_forward);
      cross_vectors(
        &self->primary_samples[v13].transform.basis_right,
        &self->primary_samples[v13].transform.basis_up,
        &self->primary_samples[v13].transform.basis_forward);
      qmemcpy(&self->secondary_samples[v13], &self->primary_samples[v13], 0x40u);
      v21 = self->primary_samples;
      v22 = v21[v13].transform.basis_up.x * 0.49000001;
      v82 = v21[v13].transform.basis_up.y * 0.49000001;
      v23 = v21[v13].transform.basis_up.z * 0.49000001;
      p_position = &self->secondary_samples[v13++].transform.position;
      v84 = v23;
      p_position->x = v22 + p_position->x;
      p_position->y = v82 + p_position->y;
      p_position->z = v84 + p_position->z;
      ++arg3b;
    }
    while ( arg3b < v53 );
    v8 = 0;
  }
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v25 = 0;
    do
    {
      v26 = self->primary_samples;
      p_x = &v26[v25].delta_dir_to_next.x;
      v73 = v26[v25 + 1].transform.position.x - v26[v25].transform.position.x;
      v76 = v26[v25 + 1].transform.position.y - v26[v25].transform.position.y;
      v28 = v26[v25 + 1].transform.position.z - v26[v25].transform.position.z;
      *p_x = v73;
      p_x[1] = v76;
      v79 = v28;
      p_x[2] = v79;
      self->primary_samples[v25].delta_length = normalize_vector(&self->primary_samples[v25].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v30 = &secondary_samples[v25].delta_dir_to_next.x;
      v66 = secondary_samples[v25 + 1].transform.position.x - secondary_samples[v25].transform.position.x;
      v68 = secondary_samples[v25 + 1].transform.position.y - secondary_samples[v25].transform.position.y;
      v31 = secondary_samples[v25 + 1].transform.position.z - secondary_samples[v25].transform.position.z;
      *v30 = v66;
      v30[1] = v68;
      v70 = v31;
      v30[2] = v70;
      ++v8;
      self->secondary_samples[v25].delta_length = normalize_vector(&self->secondary_samples[v25].delta_dir_to_next);
      ++v25;
    }
    while ( v8 < (signed int)(self->segment_count - 1) );
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
  v36 = 0;
  v63 = vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v37 = 0;
    do
    {
      width_cells = self->width_cells;
      v39 = 0;
      arg2a = 0;
      for ( arg3c = width_cells; v39 <= width_cells; arg2a = v39 )
      {
        v40 = (double)arg2a - (double)arg3c * 0.5;
        v41 = &self->primary_samples[v37];
        if ( v36 == self->segment_count )
        {
          vertices = v63;
          v85 = v40 * v41[-1].transform.basis_right.x;
          v86 = v40 * v41[-1].transform.basis_right.y;
          v44 = v40 * v41[-1].transform.basis_right.z;
          v87 = v41[-1].transform.position.z + 1.0;
          v67 = v41[-1].transform.position.x + v85;
          v69 = v41[-1].transform.position.y + v86;
          v42 = &v63[v39 + v36 * (width_cells + 1)].x;
          *v42 = v67;
          v71 = v87 + v44;
          v42[1] = v69;
          v43 = v71;
        }
        else
        {
          v81 = v40 * v41->transform.basis_right.x;
          v83 = v40 * v41->transform.basis_right.y;
          v74 = v81 + v41->transform.position.x;
          v77 = v83 + v41->transform.position.y;
          v80 = v40 * v41->transform.basis_right.z + v41->transform.position.z;
          v42 = &vertices[v39 + v36 * (width_cells + 1)].x;
          *v42 = v74;
          v42[1] = v77;
          v43 = v80;
        }
        v42[2] = v43;
        width_cells = self->width_cells;
        ++v39;
        arg3c = width_cells;
      }
      ++v36;
      ++v37;
    }
    while ( v36 <= (signed int)self->segment_count );
  }
  for ( i = 0; i < (signed int)self->segment_count; ++i )
  {
    v46 = 0;
    arg2b = 0;
    if ( (int)self->width_cells > 0 )
    {
      arg3d = (double)(i % 8) * 0.125;
      v52 = (double)(i % 8 + 1) * 0.125;
      do
      {
        v47 = 0;
        v64 = v46 + 1;
        v56 = 0;
        arg2c = (double)arg2b * 0.125;
        v54 = (double)(v46 + 1) * 0.125;
        while ( 1 )
        {
          v48 = &facequads[2 * v46 + 2 * i * self->width_cells + v47];
          v48->header_word = 0;
          if ( v47 != 0 )
          {
            v48->vertex_0 = i * (LOWORD(self->width_cells) + 1) + v46 + 1;
            v48->vertex_1 = v46 + i * (LOWORD(self->width_cells) + 1);
            v48->vertex_2 = v46 + (i + 1) * (LOWORD(self->width_cells) + 1);
            v48->vertex_3 = (i + 1) * (LOWORD(self->width_cells) + 1) + v46 + 1;
            v48->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_b, nullptr, 0);
            v48->uv[0].u = v54;
            v48->uv[0].v = arg3d;
            v48->uv[1].u = arg2c;
            v48->uv[1].v = arg3d;
            v48->uv[2].u = arg2c;
            v48->uv[2].v = v52;
            v48->uv[3].u = v54;
          }
          else
          {
            v48->vertex_0 = v46 + i * (LOWORD(self->width_cells) + 1);
            v48->vertex_1 = i * (LOWORD(self->width_cells) + 1) + v46 + 1;
            v48->vertex_2 = (i + 1) * (LOWORD(self->width_cells) + 1) + v46 + 1;
            v48->vertex_3 = v46 + (i + 1) * (LOWORD(self->width_cells) + 1);
            v48->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
            v48->uv[0].u = arg2c;
            v48->uv[0].v = arg3d;
            v48->uv[1].u = v54;
            v48->uv[1].v = arg3d;
            v48->uv[2].u = v54;
            v48->uv[2].v = v52;
            v48->uv[3].u = arg2c;
          }
          v48->uv[3].v = v52;
          if ( ++v56 >= 2 )
            break;
          v47 = v56;
        }
        ++v46;
        arg2b = v64;
      }
      while ( v64 < (signed int)self->width_cells );
    }
  }
  calc_path_length_z(self);
}
