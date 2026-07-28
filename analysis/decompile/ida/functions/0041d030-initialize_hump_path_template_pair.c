/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_hump_path_template_pair @ 0x41d030 */
/* selector: initialize_hump_path_template_pair */

// Builds the Hump attachment path-template pair; iOS Path.o names this `cRPath::BuildHump(float, float, int, bool, char*, char*)`.
void __thiscall initialize_hump_path_template_pair(
        Path *self,
        float curve_source,
        float height_scale,
        int32_t width_cells_,
        bool side_exit,
        char *texture_a,
        char *texture_b,
        char *cap_texture)
{
  signed int v9; // ebx
  __int64 v10; // rax
  int32_t v11; // ebp
  double v12; // st7
  int i; // edi
  int32_t v14; // edi
  int v15; // edi
  PathTemplateSample *primary_samples; // ebp
  PathTemplateSample *v17; // edx
  PathTemplateSample *v18; // ecx
  float *p_x; // eax
  double v20; // st7
  PathTemplateSample *v21; // eax
  PathTemplateSample *secondary_samples; // edx
  float *v23; // eax
  double v24; // st7
  signed int v25; // ebp
  int v26; // edi
  PathTemplateSample *v27; // eax
  double v28; // st7
  double v29; // st7
  PathTemplateSample *v30; // ecx
  float *v31; // eax
  double v32; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v34; // ecx
  Object *object; // eax
  signed int v36; // edx
  Vec3 *vertices; // ebp
  signed int width_cells; // ecx
  signed int v39; // edi
  double v40; // st7
  float *v41; // eax
  float *v42; // eax
  float v43; // ecx
  double v44; // st7
  int v45; // edi
  int v46; // ecx
  ObjectFaceQuad *v47; // ebp
  float v48; // [esp+0h] [ebp-60h]
  int v49; // [esp+14h] [ebp-4Ch]
  float v50; // [esp+14h] [ebp-4Ch]
  float v51; // [esp+18h] [ebp-48h]
  int v52; // [esp+18h] [ebp-48h]
  float v53; // [esp+1Ch] [ebp-44h]
  ObjectFaceQuad *facequads; // [esp+1Ch] [ebp-44h]
  float v55; // [esp+20h] [ebp-40h]
  float v56; // [esp+20h] [ebp-40h]
  signed int v57; // [esp+20h] [ebp-40h]
  float v58; // [esp+24h] [ebp-3Ch]
  float v59; // [esp+28h] [ebp-38h]
  float v60; // [esp+30h] [ebp-30h]
  float v61; // [esp+30h] [ebp-30h]
  float v62; // [esp+34h] [ebp-2Ch]
  float v63; // [esp+34h] [ebp-2Ch]
  float v64; // [esp+38h] [ebp-28h]
  float v65; // [esp+3Ch] [ebp-24h]
  float v66; // [esp+3Ch] [ebp-24h]
  float v67; // [esp+40h] [ebp-20h]
  float v68; // [esp+40h] [ebp-20h]
  float v69; // [esp+44h] [ebp-1Ch]
  float v70; // [esp+44h] [ebp-1Ch]
  float v71; // [esp+48h] [ebp-18h]
  float v72; // [esp+48h] [ebp-18h]
  float v73; // [esp+48h] [ebp-18h]
  float v74; // [esp+4Ch] [ebp-14h]
  float v75; // [esp+4Ch] [ebp-14h]
  float v76; // [esp+4Ch] [ebp-14h]
  float v77; // [esp+50h] [ebp-10h]
  float v78; // [esp+50h] [ebp-10h]
  float v79; // [esp+50h] [ebp-10h]
  float v80; // [esp+5Ch] [ebp-4h]
  float arg2; // [esp+64h] [ebp+4h]
  int arg2a; // [esp+64h] [ebp+4h]
  int arg2b; // [esp+64h] [ebp+4h]
  float arg2c; // [esp+64h] [ebp+4h]
  int arg3; // [esp+68h] [ebp+8h]
  float arg3a; // [esp+68h] [ebp+8h]
  int32_t arg4; // [esp+6Ch] [ebp+Ch]
  int32_t arg4a; // [esp+6Ch] [ebp+Ch]
  float arg4e; // [esp+6Ch] [ebp+Ch]
  int32_t arg4b; // [esp+6Ch] [ebp+Ch]
  int32_t arg4c; // [esp+6Ch] [ebp+Ch]
  float arg4d; // [esp+6Ch] [ebp+Ch]

  v9 = 0;
  self->kind = PATH_TEMPLATE_KIND_FAMILY_10;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = width_cells_;
  v10 = (__int64)(curve_source * 4.0);
  v11 = v10 + 7;
  v49 = v10;
  self->width_or_scale = 1.0;
  self->segment_count = v10 + 14;
  self->segment_count_f = (float)(v10 + 14);
  v12 = (double)(int)v10;
  v51 = v12;
  arg2 = v12 * 0.095492966;
  get_path_nodes(self);
  self->has_entry_mesh_transition = 0;
  arg4 = 0;
  for ( i = 0; i < 7; ++i )
  {
    self->primary_samples[i].center_x = (double)(int)self->width_cells * 0.5 - 4.0;
    self->primary_samples[i].rotation_scalar_98 = 0.0;
    self->primary_samples[i].rotation_scalar_94 = 0.0;
    self->primary_samples[i].special_scalar = 0.0;
    self->primary_samples[i].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[i].transform);
    self->primary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    v55 = (float)arg4;
    self->primary_samples[i].transform.position.y = 0.0;
    self->primary_samples[i].transform.position.z = v55;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->secondary_samples[i].transform.position.y = 0.49000001;
    self->secondary_samples[i].transform.position.z = v55;
    ++arg4;
  }
  arg4a = v11;
  v14 = v11;
  do
  {
    self->primary_samples[v14].center_x = 4.0 - (double)(int)self->width_cells * 0.5;
    self->primary_samples[v14].rotation_scalar_98 = 0.0;
    self->primary_samples[v14].rotation_scalar_94 = 0.0;
    self->primary_samples[v14].special_scalar = 0.0;
    self->primary_samples[v14].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v14].transform);
    arg4e = (float)arg4a;
    self->primary_samples[v14].transform.position.x = self->primary_samples[v14].center_x;
    self->primary_samples[v14].transform.position.y = 0.0;
    self->primary_samples[v14].transform.position.z = arg4e;
    set_matrix_identity(&self->secondary_samples[v14].transform);
    self->secondary_samples[v14].transform.position.x = self->primary_samples[v14].center_x;
    self->secondary_samples[v14].transform.position.y = 0.49000001;
    self->secondary_samples[v14++].transform.position.z = arg4e;
    arg4a = ++v11;
  }
  while ( v11 + -7 - v49 < 7 );
  arg4b = 0;
  if ( v49 > 0 )
  {
    v15 = 7;
    do
    {
      primary_samples = self->primary_samples;
      v53 = (double)arg4b * 6.2831855 / v51;
      v48 = v53 * 0.5;
      primary_samples[v15].center_x = cosine(v48) * primary_samples->center_x;
      self->primary_samples[v15].rotation_scalar_98 = 0.0;
      self->primary_samples[v15].rotation_scalar_94 = 0.0;
      self->primary_samples[v15].special_scalar = 0.0;
      self->primary_samples[v15].lateral_scale = 1.0;
      set_matrix_identity(&self->primary_samples[v15].transform);
      self->primary_samples[v15].transform.position.x = self->primary_samples[v15].center_x;
      self->primary_samples[v15].transform.position.y = (1.0 - cosine(v53)) * arg2 * height_scale;
      v56 = (float)(arg4b + 7);
      self->primary_samples[v15].transform.position.z = v56;
      set_matrix_identity(&self->secondary_samples[v15].transform);
      self->secondary_samples[v15].transform.position.x = self->primary_samples[v15].center_x;
      self->secondary_samples[v15].transform.position.y = (1.0 - cosine(v53)) * arg2 * height_scale + 0.49000001;
      self->secondary_samples[v15].transform.position.z = v56;
      if ( v15 <= 7 )
      {
        set_matrix_rotation_identity(&self->primary_samples[v15 - 1].transform);
        set_matrix_rotation_identity(&self->secondary_samples[v15 - 1].transform);
      }
      else
      {
        v17 = &self->primary_samples[v15 - 1];
        v17->transform.basis_right.x = 1.0;
        v17->transform.basis_right.y = 0.0;
        v17->transform.basis_right.z = 0.0;
        v18 = self->primary_samples;
        p_x = &v18[v15 - 1].transform.basis_forward.x;
        v60 = v18[v15].transform.position.x - v18[v15 - 1].transform.position.x;
        v62 = p_x[47] - p_x[5];
        v20 = p_x[48] - p_x[6];
        *p_x = v60;
        p_x[1] = v62;
        v64 = v20;
        p_x[2] = v64;
        normalize_vector(&self->primary_samples[v15 - 1].transform.basis_forward);
        cross_vectors(
          &self->primary_samples[v15 - 1].transform.basis_up,
          &self->primary_samples[v15 - 1].transform.basis_forward,
          &self->primary_samples[v15 - 1].transform.basis_right);
        v21 = &self->secondary_samples[v15 - 1];
        v21->transform.basis_right.x = 1.0;
        v21->transform.basis_right.y = 0.0;
        v21->transform.basis_right.z = 0.0;
        secondary_samples = self->secondary_samples;
        v23 = &secondary_samples[v15 - 1].transform.basis_forward.x;
        v71 = secondary_samples[v15].transform.position.x - secondary_samples[v15 - 1].transform.position.x;
        v74 = v23[47] - v23[5];
        v24 = v23[48] - v23[6];
        *v23 = v71;
        v23[1] = v74;
        v77 = v24;
        v23[2] = v77;
        normalize_vector(&self->secondary_samples[v15 - 1].transform.basis_forward);
        cross_vectors(
          &self->secondary_samples[v15 - 1].transform.basis_up,
          &self->secondary_samples[v15 - 1].transform.basis_forward,
          &self->secondary_samples[v15 - 1].transform.basis_right);
      }
      ++v15;
      ++arg4b;
    }
    while ( arg4b < v49 );
  }
  v25 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v26 = 0;
    do
    {
      v27 = &self->primary_samples[v26];
      v28 = v27[1].transform.position.x - v27->transform.position.x;
      v27 = (PathTemplateSample *)((char *)v27 + 128);
      v72 = v28;
      v75 = v27->inverse_matrix.basis_up_w - v27[-1].inverse_matrix.basis_up_w;
      v29 = v27->inverse_matrix.basis_forward.x - v27[-1].inverse_matrix.basis_forward.x;
      v27->transform.basis_right.x = v72;
      v27->transform.basis_right.y = v75;
      v78 = v29;
      v27->transform.basis_right.z = v78;
      self->primary_samples[v26].delta_length = normalize_vector(&self->primary_samples[v26].delta_dir_to_next);
      v30 = self->secondary_samples;
      v31 = &v30[v26].delta_dir_to_next.x;
      v65 = v30[v26 + 1].transform.position.x - v30[v26].transform.position.x;
      v67 = v30[v26 + 1].transform.position.y - v30[v26].transform.position.y;
      v32 = v30[v26 + 1].transform.position.z - v30[v26].transform.position.z;
      *v31 = v65;
      v31[1] = v67;
      v69 = v32;
      v31[2] = v69;
      ++v25;
      self->secondary_samples[v26].delta_length = normalize_vector(&self->secondary_samples[v26].delta_dir_to_next);
      ++v26;
    }
    while ( v25 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = 1.0;
  v34 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v34->x = 0.0;
  v34->y = 0.0;
  v34->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = 1.0;
  request_object_vertices(self->bod.object, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->bod.object, 2 * self->segment_count * self->width_cells);
  object = self->bod.object;
  v36 = 0;
  vertices = object->vertices;
  arg4c = (int32_t)vertices;
  facequads = object->facequads;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    do
    {
      width_cells = self->width_cells;
      v39 = 0;
      arg2a = 0;
      for ( arg3 = width_cells; v39 <= width_cells; arg2a = v39 )
      {
        v40 = (double)arg2a - (double)arg3 * 0.5;
        v41 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v9);
        if ( v36 == self->segment_count )
        {
          vertices = (Vec3 *)arg4c;
          v58 = v40 * *(v41 - 42);
          v59 = v40 * *(v41 - 41);
          v44 = v40 * *(v41 - 40);
          v80 = *(v41 - 28) + 1.0;
          v66 = *(v41 - 30) + v58;
          v68 = *(v41 - 29) + v59;
          v42 = (float *)(arg4c + 12 * (v39 + v36 * (width_cells + 1)));
          *v42 = v66;
          v70 = v80 + v44;
          v42[1] = v68;
          v43 = v70;
        }
        else
        {
          v61 = v40 * *v41;
          v63 = v40 * v41[1];
          v73 = v61 + v41[12];
          v76 = v63 + v41[13];
          v79 = v40 * v41[2] + v41[14];
          v42 = &vertices[v39 + v36 * (width_cells + 1)].x;
          *v42 = v73;
          v42[1] = v76;
          v43 = v79;
        }
        v42[2] = v43;
        width_cells = self->width_cells;
        ++v39;
        arg3 = width_cells;
      }
      ++v36;
      v9 += 168;
    }
    while ( v36 <= (signed int)self->segment_count );
    v9 = 0;
  }
  if ( (int)self->segment_count > 0 )
  {
    do
    {
      v45 = 0;
      arg2b = 0;
      if ( (int)self->width_cells > 0 )
      {
        arg3a = (double)(v9 % 8) * 0.125;
        v50 = (double)(v9 % 8 + 1) * 0.125;
        do
        {
          v46 = 0;
          v57 = v45 + 1;
          v52 = 0;
          arg2c = (double)arg2b * 0.125;
          arg4d = (double)(v45 + 1) * 0.125;
          while ( 1 )
          {
            v47 = &facequads[2 * v45 + 2 * v9 * self->width_cells + v46];
            v47->header_word = 0;
            if ( v46 != 0 )
            {
              v47->vertex_0 = v9 * (LOWORD(self->width_cells) + 1) + v45 + 1;
              v47->vertex_1 = v45 + v9 * (LOWORD(self->width_cells) + 1);
              v47->vertex_2 = v45 + (v9 + 1) * (LOWORD(self->width_cells) + 1);
              v47->vertex_3 = (v9 + 1) * (LOWORD(self->width_cells) + 1) + v45 + 1;
              v47->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_b, nullptr, 0);
              v47->uv[0].u = arg4d;
              v47->uv[0].v = arg3a;
              v47->uv[1].u = arg2c;
              v47->uv[1].v = arg3a;
              v47->uv[2].u = arg2c;
              v47->uv[2].v = v50;
              v47->uv[3].u = arg4d;
            }
            else
            {
              v47->vertex_0 = v45 + v9 * (LOWORD(self->width_cells) + 1);
              v47->vertex_1 = v9 * (LOWORD(self->width_cells) + 1) + v45 + 1;
              v47->vertex_2 = (v9 + 1) * (LOWORD(self->width_cells) + 1) + v45 + 1;
              v47->vertex_3 = v45 + (v9 + 1) * (LOWORD(self->width_cells) + 1);
              v47->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
              v47->uv[0].u = arg2c;
              v47->uv[0].v = arg3a;
              v47->uv[1].u = arg4d;
              v47->uv[1].v = arg3a;
              v47->uv[2].u = arg4d;
              v47->uv[2].v = v50;
              v47->uv[3].u = arg2c;
            }
            v47->uv[3].v = v50;
            if ( ++v52 >= 2 )
              break;
            v46 = v52;
          }
          ++v45;
          arg2b = v57;
        }
        while ( v57 < (signed int)self->width_cells );
      }
      ++v9;
    }
    while ( v9 < (signed int)self->segment_count );
  }
  calc_path_length_z(self);
}
