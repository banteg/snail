/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_p_path_template_pair @ 0x425a40 */
/* selector: initialize_p_path_template_pair */

// Builds the P attachment path-template pair; iOS Path.o names this `cRPath::BuildP(int, float, int, float, float, int, char*, char*)`.
void __thiscall initialize_p_path_template_pair(
        Path *self,
        int32_t variant,
        float scale_arg,
        int32_t width_cells_,
        float start_x,
        float end_x,
        int32_t curve_segments,
        char *texture_a,
        char *texture_b,
        char *cap_texture)
{
  signed int v11; // ebx
  double v12; // st7
  PathTemplateSample *primary_samples; // eax
  int v14; // edi
  double v15; // st7
  int32_t v16; // ebp
  int v17; // edi
  double v18; // st7
  Vec3 *p_basis_up; // edx
  PathTemplateSample *v20; // ecx
  float *p_x; // eax
  double v22; // st7
  Vec3 *v23; // eax
  PathTemplateSample *secondary_samples; // edx
  float *v25; // eax
  double v26; // st7
  signed int v27; // ebp
  int v28; // edi
  PathTemplateSample *v29; // eax
  double v30; // st7
  double v31; // st7
  PathTemplateSample *v32; // ecx
  float *v33; // eax
  double v34; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v36; // ecx
  Object *object; // eax
  signed int v38; // edx
  Vec3 *vertices; // ebp
  signed int width_cells; // ecx
  signed int v41; // edi
  double v42; // st7
  float *v43; // eax
  float *v44; // eax
  float v45; // ecx
  double v46; // st7
  int v47; // edi
  int32_t v48; // ecx
  ObjectFaceQuad *v49; // ebp
  float v50; // [esp+0h] [ebp-54h]
  float v51; // [esp+0h] [ebp-54h]
  signed int v52; // [esp+14h] [ebp-40h]
  float v53; // [esp+18h] [ebp-3Ch]
  float v54; // [esp+1Ch] [ebp-38h]
  float v55; // [esp+24h] [ebp-30h]
  float v56; // [esp+24h] [ebp-30h]
  float v57; // [esp+28h] [ebp-2Ch]
  float v58; // [esp+28h] [ebp-2Ch]
  float v59; // [esp+2Ch] [ebp-28h]
  float v60; // [esp+30h] [ebp-24h]
  float v61; // [esp+30h] [ebp-24h]
  float v62; // [esp+34h] [ebp-20h]
  float v63; // [esp+34h] [ebp-20h]
  float v64; // [esp+38h] [ebp-1Ch]
  float v65; // [esp+38h] [ebp-1Ch]
  float v66; // [esp+3Ch] [ebp-18h]
  float v67; // [esp+3Ch] [ebp-18h]
  float v68; // [esp+3Ch] [ebp-18h]
  float v69; // [esp+40h] [ebp-14h]
  float v70; // [esp+40h] [ebp-14h]
  float v71; // [esp+40h] [ebp-14h]
  float v72; // [esp+44h] [ebp-10h]
  float v73; // [esp+44h] [ebp-10h]
  float v74; // [esp+44h] [ebp-10h]
  float v75; // [esp+50h] [ebp-4h]
  int32_t arg2; // [esp+58h] [ebp+4h]
  float arg3; // [esp+5Ch] [ebp+8h]
  signed int arg3a; // [esp+5Ch] [ebp+8h]
  signed int arg3b; // [esp+5Ch] [ebp+8h]
  float arg3c; // [esp+5Ch] [ebp+8h]
  ObjectFaceQuad *arg4; // [esp+60h] [ebp+Ch]
  float arg5d; // [esp+64h] [ebp+10h]
  int arg5; // [esp+64h] [ebp+10h]
  float arg5a; // [esp+64h] [ebp+10h]
  float arg5e; // [esp+64h] [ebp+10h]
  Vec3 *arg5b; // [esp+64h] [ebp+10h]
  float arg5c; // [esp+64h] [ebp+10h]
  float arg6a; // [esp+68h] [ebp+14h]
  float arg6; // [esp+68h] [ebp+14h]
  char *texture_aa; // [esp+6Ch] [ebp+18h]
  float texture_ab; // [esp+6Ch] [ebp+18h]

  self->kind = variant + 33;
  v11 = 0;
  self->segment_count = curve_segments + 2;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = width_cells_;
  self->width_or_scale = 1.0;
  self->segment_count_f = (float)(curve_segments + 2);
  v12 = (end_x - start_x) * 0.5;
  if ( v12 < 0.0 )
    v12 = -v12;
  arg3 = v12;
  get_path_nodes(self);
  primary_samples = self->primary_samples;
  self->has_entry_mesh_transition = 0;
  primary_samples->center_x = start_x;
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
  v14 = curve_segments + 1;
  self->primary_samples[v14].center_x = end_x;
  self->primary_samples[v14].rotation_scalar_98 = 0.0;
  self->primary_samples[v14].rotation_scalar_94 = 0.0;
  self->primary_samples[v14].special_scalar = 0.0;
  self->primary_samples[v14].lateral_scale = 1.0;
  set_matrix_identity(&self->primary_samples[v14].transform);
  arg5d = (float)(curve_segments + 1);
  self->primary_samples[v14].transform.position.x = self->primary_samples[v14].center_x;
  self->primary_samples[v14].transform.position.y = 0.0;
  self->primary_samples[v14].transform.position.z = arg5d;
  set_matrix_identity(&self->secondary_samples[v14].transform);
  v15 = arg5d;
  v16 = 0;
  self->secondary_samples[v14].transform.position.x = self->primary_samples[v14].center_x;
  arg5 = 0;
  self->secondary_samples[v14].transform.position.y = 0.49000001;
  self->secondary_samples[v14].transform.position.z = v15;
  if ( curve_segments > 0 )
  {
    v17 = 1;
    while ( 1 )
    {
      arg6a = (float)curve_segments;
      arg5a = (double)arg5 * 3.1415927 / arg6a;
      if ( self->kind == 33 )
        break;
      if ( self->kind == 34 )
      {
        self->primary_samples[v17].center_x = 2.0 - cosine(arg5a) * arg3 - arg3 + 0.5;
      }
      else if ( self->kind == 35 )
      {
        v50 = arg5a + 1.5707964;
        v18 = (sine(v50) + 1.0) * arg3;
LABEL_11:
        self->primary_samples[v17].center_x = v18 + 0.5;
      }
      self->primary_samples[v17].rotation_scalar_98 = 0.0;
      self->primary_samples[v17].rotation_scalar_94 = 0.0;
      self->primary_samples[v17].special_scalar = 0.0;
      self->primary_samples[v17].lateral_scale = 1.0;
      set_matrix_identity(&self->primary_samples[v17].transform);
      ++v16;
      self->primary_samples[v17].transform.position.x = self->primary_samples[v17].center_x;
      arg5e = (float)v16;
      self->primary_samples[v17].transform.position.y = 0.0;
      self->primary_samples[v17].transform.position.z = arg5e;
      set_matrix_identity(&self->secondary_samples[v17].transform);
      self->secondary_samples[v17].transform.position.x = self->primary_samples[v17].center_x;
      self->secondary_samples[v17].transform.position.y = self->primary_samples[v17].transform.position.y + 0.49000001;
      self->secondary_samples[v17].transform.position.z = arg5e;
      if ( v17 <= 1 )
      {
        set_matrix_rotation_identity(&self->primary_samples[v17 - 1].transform);
        set_matrix_rotation_identity(&self->secondary_samples[v17 - 1].transform);
      }
      else
      {
        p_basis_up = &self->primary_samples[v17 - 1].transform.basis_up;
        p_basis_up->x = 0.0;
        p_basis_up->y = 1.0;
        p_basis_up->z = 0.0;
        v20 = self->primary_samples;
        p_x = &v20[v17 - 1].transform.basis_forward.x;
        v55 = v20[v17].transform.position.x - v20[v17 - 1].transform.position.x;
        v57 = p_x[47] - p_x[5];
        v22 = p_x[48] - p_x[6];
        *p_x = v55;
        p_x[1] = v57;
        v59 = v22;
        p_x[2] = v59;
        normalize_vector(&self->primary_samples[v17 - 1].transform.basis_forward);
        cross_vectors(
          &self->primary_samples[v17 - 1].transform.basis_right,
          &self->primary_samples[v17 - 1].transform.basis_up,
          &self->primary_samples[v17 - 1].transform.basis_forward);
        v23 = &self->secondary_samples[v17 - 1].transform.basis_up;
        v23->x = 0.0;
        v23->y = 1.0;
        v23->z = 0.0;
        secondary_samples = self->secondary_samples;
        v25 = &secondary_samples[v17 - 1].transform.basis_forward.x;
        v66 = secondary_samples[v17].transform.position.x - secondary_samples[v17 - 1].transform.position.x;
        v69 = v25[47] - v25[5];
        v26 = v25[48] - v25[6];
        *v25 = v66;
        v25[1] = v69;
        v72 = v26;
        v25[2] = v72;
        normalize_vector(&self->secondary_samples[v17 - 1].transform.basis_forward);
        cross_vectors(
          &self->secondary_samples[v17 - 1].transform.basis_right,
          &self->secondary_samples[v17 - 1].transform.basis_up,
          &self->secondary_samples[v17 - 1].transform.basis_forward);
      }
      ++v17;
      arg5 = v16;
      if ( v16 >= curve_segments )
        goto LABEL_16;
    }
    v51 = arg5a + 1.5707964;
    v18 = sine(v51) * arg3 - arg3;
    goto LABEL_11;
  }
LABEL_16:
  v27 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v28 = 0;
    do
    {
      v29 = &self->primary_samples[v28];
      v30 = v29[1].transform.position.x - v29->transform.position.x;
      v29 = (PathTemplateSample *)((char *)v29 + 128);
      v67 = v30;
      v70 = v29->inverse_matrix.basis_up_w - v29[-1].inverse_matrix.basis_up_w;
      v31 = v29->inverse_matrix.basis_forward.x - v29[-1].inverse_matrix.basis_forward.x;
      v29->transform.basis_right.x = v67;
      v29->transform.basis_right.y = v70;
      v73 = v31;
      v29->transform.basis_right.z = v73;
      self->primary_samples[v28].delta_length = normalize_vector(&self->primary_samples[v28].delta_dir_to_next);
      v32 = self->secondary_samples;
      v33 = &v32[v28].delta_dir_to_next.x;
      v60 = v32[v28 + 1].transform.position.x - v32[v28].transform.position.x;
      v62 = v32[v28 + 1].transform.position.y - v32[v28].transform.position.y;
      v34 = v32[v28 + 1].transform.position.z - v32[v28].transform.position.z;
      *v33 = v60;
      v33[1] = v62;
      v64 = v34;
      v33[2] = v64;
      ++v27;
      self->secondary_samples[v28].delta_length = normalize_vector(&self->secondary_samples[v28].delta_dir_to_next);
      ++v28;
    }
    while ( v27 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = 1.0;
  v36 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v36->x = 0.0;
  v36->y = 0.0;
  v36->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = 1.0;
  request_object_vertices(self->bod.object, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->bod.object, 2 * self->segment_count * self->width_cells);
  object = self->bod.object;
  v38 = 0;
  vertices = object->vertices;
  arg5b = vertices;
  arg4 = object->facequads;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    do
    {
      width_cells = self->width_cells;
      v41 = 0;
      arg3a = 0;
      for ( texture_aa = (char *)width_cells; v41 <= width_cells; arg3a = v41 )
      {
        v42 = (double)arg3a - (double)(int)texture_aa * 0.5;
        v43 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v11);
        if ( v38 == self->segment_count )
        {
          vertices = arg5b;
          v53 = v42 * *(v43 - 42);
          v54 = v42 * *(v43 - 41);
          v46 = v42 * *(v43 - 40);
          v75 = *(v43 - 28) + 1.0;
          v61 = *(v43 - 30) + v53;
          v63 = *(v43 - 29) + v54;
          v44 = &arg5b[v41 + v38 * (width_cells + 1)].x;
          *v44 = v61;
          v65 = v75 + v46;
          v44[1] = v63;
          v45 = v65;
        }
        else
        {
          v56 = v42 * *v43;
          v58 = v42 * v43[1];
          v68 = v56 + v43[12];
          v71 = v58 + v43[13];
          v74 = v42 * v43[2] + v43[14];
          v44 = &vertices[v41 + v38 * (width_cells + 1)].x;
          *v44 = v68;
          v44[1] = v71;
          v45 = v74;
        }
        v44[2] = v45;
        width_cells = self->width_cells;
        ++v41;
        texture_aa = (char *)width_cells;
      }
      ++v38;
      v11 += 168;
    }
    while ( v38 <= (signed int)self->segment_count );
    v11 = 0;
  }
  if ( (int)self->segment_count > 0 )
  {
    do
    {
      v47 = 0;
      arg3b = 0;
      if ( (int)self->width_cells > 0 )
      {
        texture_ab = (double)(v11 % 8) * 0.125;
        arg6 = (double)(v11 % 8 + 1) * 0.125;
        do
        {
          v48 = 0;
          v52 = v47 + 1;
          arg2 = 0;
          arg3c = (double)arg3b * 0.125;
          arg5c = (double)(v47 + 1) * 0.125;
          while ( 1 )
          {
            v49 = &arg4[2 * v47 + 2 * v11 * self->width_cells + v48];
            v49->header_word = 0;
            if ( v48 != 0 )
            {
              v49->vertex_0 = v11 * (LOWORD(self->width_cells) + 1) + v47 + 1;
              v49->vertex_1 = v47 + v11 * (LOWORD(self->width_cells) + 1);
              v49->vertex_2 = v47 + (v11 + 1) * (LOWORD(self->width_cells) + 1);
              v49->vertex_3 = (v11 + 1) * (LOWORD(self->width_cells) + 1) + v47 + 1;
              v49->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_b, nullptr, 0);
              v49->uv[0].u = arg5c;
              v49->uv[0].v = texture_ab;
              v49->uv[1].u = arg3c;
              v49->uv[1].v = texture_ab;
              v49->uv[2].u = arg3c;
              v49->uv[2].v = arg6;
              v49->uv[3].u = arg5c;
            }
            else
            {
              v49->vertex_0 = v47 + v11 * (LOWORD(self->width_cells) + 1);
              v49->vertex_1 = v11 * (LOWORD(self->width_cells) + 1) + v47 + 1;
              v49->vertex_2 = (v11 + 1) * (LOWORD(self->width_cells) + 1) + v47 + 1;
              v49->vertex_3 = v47 + (v11 + 1) * (LOWORD(self->width_cells) + 1);
              v49->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
              v49->uv[0].u = arg3c;
              v49->uv[0].v = texture_ab;
              v49->uv[1].u = arg5c;
              v49->uv[1].v = texture_ab;
              v49->uv[2].u = arg5c;
              v49->uv[2].v = arg6;
              v49->uv[3].u = arg3c;
            }
            v49->uv[3].v = arg6;
            if ( ++arg2 >= 2 )
              break;
            v48 = arg2;
          }
          ++v47;
          arg3b = v52;
        }
        while ( v52 < (signed int)self->width_cells );
      }
      ++v11;
    }
    while ( v11 < (signed int)self->segment_count );
  }
  calc_path_length_z(self);
}
