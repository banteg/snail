/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_screw_path_template_pair @ 0x41eda0 */
/* selector: initialize_screw_path_template_pair */

// Builds the Screw attachment path-template pair; iOS Path.o names this `cRPath::BuildScrew(int, int, bool, char*, char*)`.
void __thiscall initialize_screw_path_template_pair(
        cRPath *self,
        int32_t curve_source,
        int32_t width_cells_,
        bool side_exit,
        char *texture_a,
        char *texture_b,
        char *cap_texture)
{
  signed int v8; // ebx
  int i; // edi
  int v10; // ebp
  int v11; // edi
  int v12; // ebp
  int v13; // edi
  double v14; // st7
  PathTemplateSample *primary_samples; // ebp
  Vec3 *p_basis_up; // ecx
  PathTemplateSample *v17; // eax
  double v18; // st7
  double v19; // st7
  Vec3 *v20; // edx
  PathTemplateSample *v21; // eax
  signed int v22; // ebp
  int v23; // edi
  PathTemplateSample *v24; // edx
  float *p_x; // eax
  double v26; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *v28; // eax
  double v29; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v31; // ecx
  Object *object; // eax
  signed int v33; // edx
  Vec3 *vertices; // ebp
  signed int width_cells; // ecx
  int32_t v36; // edi
  double v37; // st7
  float *v38; // eax
  float *v39; // eax
  float v40; // ecx
  double v41; // st7
  int v42; // ebp
  int v43; // ecx
  ObjectFaceQuad *v44; // edi
  float v45; // [esp+0h] [ebp-64h]
  float v46; // [esp+14h] [ebp-50h]
  float v47; // [esp+18h] [ebp-4Ch]
  float v48; // [esp+18h] [ebp-4Ch]
  float v49; // [esp+1Ch] [ebp-48h]
  float v50; // [esp+1Ch] [ebp-48h]
  float v51; // [esp+1Ch] [ebp-48h]
  int v52; // [esp+1Ch] [ebp-48h]
  float v53; // [esp+20h] [ebp-44h]
  float v54; // [esp+20h] [ebp-44h]
  Vec3 *v55; // [esp+20h] [ebp-44h]
  signed int v56; // [esp+20h] [ebp-44h]
  ObjectFaceQuad *facequads; // [esp+24h] [ebp-40h]
  float v58; // [esp+28h] [ebp-3Ch]
  float v59; // [esp+28h] [ebp-3Ch]
  float v60; // [esp+2Ch] [ebp-38h]
  float v61; // [esp+34h] [ebp-30h]
  float v62; // [esp+34h] [ebp-30h]
  float v63; // [esp+38h] [ebp-2Ch]
  float v64; // [esp+38h] [ebp-2Ch]
  float v65; // [esp+3Ch] [ebp-28h]
  float v66; // [esp+40h] [ebp-24h]
  float v67; // [esp+40h] [ebp-24h]
  float v68; // [esp+40h] [ebp-24h]
  float v69; // [esp+44h] [ebp-20h]
  float v70; // [esp+44h] [ebp-20h]
  float v71; // [esp+48h] [ebp-1Ch]
  float v72; // [esp+48h] [ebp-1Ch]
  float v73; // [esp+4Ch] [ebp-18h]
  float v74; // [esp+4Ch] [ebp-18h]
  float v75; // [esp+4Ch] [ebp-18h]
  float v76; // [esp+50h] [ebp-14h]
  float v77; // [esp+50h] [ebp-14h]
  float v78; // [esp+50h] [ebp-14h]
  float v79; // [esp+54h] [ebp-10h]
  float v80; // [esp+54h] [ebp-10h]
  float v81; // [esp+54h] [ebp-10h]
  float v82; // [esp+60h] [ebp-4h]
  int32_t arg2; // [esp+68h] [ebp+4h]
  int32_t arg2a; // [esp+68h] [ebp+4h]
  float arg2b; // [esp+68h] [ebp+4h]
  int32_t arg3; // [esp+6Ch] [ebp+8h]
  int32_t arg3a; // [esp+6Ch] [ebp+8h]
  float arg3e; // [esp+6Ch] [ebp+8h]
  int arg3b; // [esp+6Ch] [ebp+8h]
  int32_t arg3c; // [esp+6Ch] [ebp+8h]
  float arg3d; // [esp+6Ch] [ebp+8h]

  v8 = 0;
  self->width_cells = width_cells_;
  self->kind = PATH_TEMPLATE_KIND_SCREW;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_or_scale = 1.0;
  self->segment_count = curve_source + 8;
  self->segment_count_f = (float)(curve_source + 8);
  get_path_nodes(self);
  self->has_entry_mesh_transition = 0;
  arg3 = 0;
  for ( i = 0; i < 3; ++i )
  {
    self->primary_samples[i].center_x = 0.5;
    self->primary_samples[i].rotation_scalar_98 = 0.0;
    self->primary_samples[i].rotation_scalar_94 = 0.0;
    self->primary_samples[i].special_scalar = 0.0;
    self->primary_samples[i].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[i].transform);
    v53 = (float)arg3;
    self->primary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->primary_samples[i].transform.position.y = 0.0;
    self->primary_samples[i].transform.position.z = v53;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->secondary_samples[i].transform.position.y = 0.49000001;
    self->secondary_samples[i].transform.position.z = v53;
    ++arg3;
  }
  v10 = curve_source + 3;
  arg3a = curve_source + 3;
  v11 = curve_source + 3;
  do
  {
    self->primary_samples[v11].center_x = -0.5;
    self->primary_samples[v11].rotation_scalar_98 = 0.0;
    self->primary_samples[v11].rotation_scalar_94 = 0.0;
    self->primary_samples[v11].special_scalar = 0.0;
    self->primary_samples[v11].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v11].transform);
    arg3e = (float)arg3a;
    self->primary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
    self->primary_samples[v11].transform.position.y = 0.0;
    self->primary_samples[v11].transform.position.z = arg3e;
    set_matrix_identity(&self->secondary_samples[v11].transform);
    self->secondary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
    self->secondary_samples[v11].transform.position.y = 0.49000001;
    self->secondary_samples[v11++].transform.position.z = arg3e;
    arg3a = ++v10;
  }
  while ( v10 + -3 - curve_source < 5 );
  v12 = 0;
  arg3b = 0;
  if ( curve_source > 0 )
  {
    v13 = 3;
    do
    {
      v54 = (float)curve_source;
      v14 = (double)arg3b * 6.2831855 / v54;
      v47 = v14;
      v45 = v14 * 0.5;
      self->primary_samples[v13].center_x = cosine(v45) * 0.5;
      self->primary_samples[v13].rotation_scalar_98 = 0.0;
      self->primary_samples[v13].rotation_scalar_94 = v47;
      self->primary_samples[v13].special_scalar = 0.0;
      self->primary_samples[v13].lateral_scale = 1.0;
      set_matrix_identity(&self->primary_samples[v13].transform);
      self->primary_samples[v13].transform.position.x = self->primary_samples[v13].center_x;
      v49 = (float)(v12 + 3);
      self->primary_samples[v13].transform.position.y = 0.0;
      self->primary_samples[v13].transform.position.z = v49;
      set_matrix_identity(&self->secondary_samples[v13].transform);
      primary_samples = self->primary_samples;
      self->secondary_samples[v13].transform.position.x = primary_samples[v13].center_x - sine(v47) * 0.49000001;
      self->secondary_samples[v13].transform.position.y = cosine(v47) * 0.49000001;
      self->secondary_samples[v13].transform.position.z = v49;
      if ( v13 <= 3 )
      {
        set_matrix_rotation_identity(&self->primary_samples[v13 - 1].transform);
        set_matrix_rotation_identity(&self->secondary_samples[v13 - 1].transform);
      }
      else
      {
        v50 = cosine(v47);
        v58 = -sine(v47);
        p_basis_up = &self->primary_samples[v13 - 1].transform.basis_up;
        p_basis_up->x = v58;
        p_basis_up->y = v50;
        p_basis_up->z = 0.0;
        v17 = &self->primary_samples[v13];
        v18 = v17->transform.position.x - v17[-1].transform.position.x;
        v17 = (PathTemplateSample *)((char *)v17 - 136);
        v61 = v18;
        v63 = v17[1].transform.basis_up.y - v17->transform.basis_up.y;
        v19 = v17[1].transform.basis_up.z - v17->transform.basis_up.z;
        v17->transform.basis_right.x = v61;
        v17->transform.basis_right.y = v63;
        v65 = v19;
        v17->transform.basis_right.z = v65;
        normalize_vector(&self->primary_samples[v13 - 1].transform.basis_forward);
        cross_vectors(
          &self->primary_samples[v13 - 1].transform.basis_right,
          &self->primary_samples[v13 - 1].transform.basis_up,
          &self->primary_samples[v13 - 1].transform.basis_forward);
        v51 = cosine(v47);
        v66 = -sine(v47);
        v20 = &self->secondary_samples[v13 - 1].transform.basis_up;
        v20->x = v66;
        v20->y = v51;
        v20->z = 0.0;
        v21 = &self->secondary_samples[v13];
        v73 = v21->transform.position.x - v21[-1].transform.position.x;
        v76 = v21->transform.position.y - v21[-1].transform.position.y;
        v79 = v21->transform.position.z - v21[-1].transform.position.z;
        v21 = (PathTemplateSample *)((char *)v21 - 136);
        v21->transform.basis_right.x = v73;
        v21->transform.basis_right.y = v76;
        v21->transform.basis_right.z = v79;
        normalize_vector(&self->secondary_samples[v13 - 1].transform.basis_forward);
        cross_vectors(
          &self->secondary_samples[v13 - 1].transform.basis_right,
          &self->secondary_samples[v13 - 1].transform.basis_up,
          &self->secondary_samples[v13 - 1].transform.basis_forward);
      }
      v12 = arg3b + 1;
      ++v13;
      ++arg3b;
    }
    while ( arg3b < curve_source );
    v8 = 0;
  }
  v22 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v23 = 0;
    do
    {
      v24 = self->primary_samples;
      p_x = &v24[v23].delta_dir_to_next.x;
      v74 = v24[v23 + 1].transform.position.x - v24[v23].transform.position.x;
      v77 = v24[v23 + 1].transform.position.y - v24[v23].transform.position.y;
      v26 = v24[v23 + 1].transform.position.z - v24[v23].transform.position.z;
      *p_x = v74;
      p_x[1] = v77;
      v80 = v26;
      p_x[2] = v80;
      self->primary_samples[v23].delta_length = normalize_vector(&self->primary_samples[v23].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v28 = &secondary_samples[v23].delta_dir_to_next.x;
      v67 = secondary_samples[v23 + 1].transform.position.x - secondary_samples[v23].transform.position.x;
      v69 = secondary_samples[v23 + 1].transform.position.y - secondary_samples[v23].transform.position.y;
      v29 = secondary_samples[v23 + 1].transform.position.z - secondary_samples[v23].transform.position.z;
      *v28 = v67;
      v28[1] = v69;
      v71 = v29;
      v28[2] = v71;
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
      v36 = 0;
      arg2 = 0;
      for ( arg3c = width_cells; v36 <= width_cells; arg2 = v36 )
      {
        v37 = (double)arg2 - (double)arg3c * 0.5;
        v38 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v8);
        if ( v33 == self->segment_count )
        {
          vertices = v55;
          v59 = v37 * *(v38 - 42);
          v60 = v37 * *(v38 - 41);
          v41 = v37 * *(v38 - 40);
          v82 = *(v38 - 28) + 1.0;
          v68 = *(v38 - 30) + v59;
          v70 = *(v38 - 29) + v60;
          v39 = &v55[v36 + v33 * (width_cells + 1)].x;
          *v39 = v68;
          v72 = v82 + v41;
          v39[1] = v70;
          v40 = v72;
        }
        else
        {
          v62 = v37 * *v38;
          v64 = v37 * v38[1];
          v75 = v62 + v38[12];
          v78 = v64 + v38[13];
          v81 = v37 * v38[2] + v38[14];
          v39 = &vertices[v36 + v33 * (width_cells + 1)].x;
          *v39 = v75;
          v39[1] = v78;
          v40 = v81;
        }
        v39[2] = v40;
        width_cells = self->width_cells;
        ++v36;
        arg3c = width_cells;
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
      arg2a = 0;
      if ( (int)self->width_cells > 0 )
      {
        arg3d = (double)(v8 % 8) * 0.125;
        v48 = (double)(v8 % 8 + 1) * 0.125;
        do
        {
          v43 = 0;
          v56 = v42 + 1;
          v52 = 0;
          arg2b = (double)arg2a * 0.125;
          v46 = (double)(v42 + 1) * 0.125;
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
              v44->uv[0].u = v46;
              v44->uv[0].v = arg3d;
              v44->uv[1].u = arg2b;
              v44->uv[1].v = arg3d;
              v44->uv[2].u = arg2b;
              v44->uv[2].v = v48;
              v44->uv[3].u = v46;
            }
            else
            {
              v44->vertex_0 = v42 + v8 * (LOWORD(self->width_cells) + 1);
              v44->vertex_1 = v8 * (LOWORD(self->width_cells) + 1) + v42 + 1;
              v44->vertex_2 = (v8 + 1) * (LOWORD(self->width_cells) + 1) + v42 + 1;
              v44->vertex_3 = v42 + (v8 + 1) * (LOWORD(self->width_cells) + 1);
              v44->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
              v44->uv[0].u = arg2b;
              v44->uv[0].v = arg3d;
              v44->uv[1].u = v46;
              v44->uv[1].v = arg3d;
              v44->uv[2].u = v46;
              v44->uv[2].v = v48;
              v44->uv[3].u = arg2b;
            }
            v44->uv[3].v = v48;
            if ( ++v52 >= 2 )
              break;
            v43 = v52;
          }
          ++v42;
          arg2a = v56;
        }
        while ( v56 < (signed int)self->width_cells );
      }
      ++v8;
    }
    while ( v8 < (signed int)self->segment_count );
  }
  calc_path_length_z(self);
}
