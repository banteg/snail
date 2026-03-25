/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_p_path_template_pair @ 0x425a40 */
/* selector: initialize_p_path_template_pair */

int32_t __thiscall initialize_p_path_template_pair(
        PathTemplate *self,
        int32_t arg2,
        uint32_t arg3,
        float arg4,
        float arg5,
        int32_t arg6,
        char *texture_a,
        char *texture_b)
{
  signed int v9; // ebx
  double v10; // st7
  PathTemplateSample *primary_samples; // eax
  int v12; // edi
  double v13; // st7
  int v14; // ebp
  int v15; // edi
  double v16; // st7
  Vec4 *p_basis_up; // edx
  PathTemplateSample *v18; // ecx
  float *p_x; // eax
  double v20; // st7
  Vec4 *v21; // eax
  PathTemplateSample *secondary_samples; // edx
  float *v23; // eax
  double v24; // st7
  signed int v25; // ebp
  int v26; // edi
  float *v27; // eax
  double v28; // st7
  double v29; // st7
  PathTemplateSample *v30; // ecx
  float *v31; // eax
  double v32; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v34; // ecx
  PathTemplateStripMesh *strip_mesh; // eax
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
  int32_t v46; // ecx
  uint32_t v47; // ebp
  float v49; // [esp+0h] [ebp-54h]
  float v50; // [esp+0h] [ebp-54h]
  signed int v51; // [esp+14h] [ebp-40h]
  float v52; // [esp+18h] [ebp-3Ch]
  float v53; // [esp+1Ch] [ebp-38h]
  float v54; // [esp+24h] [ebp-30h]
  float v55; // [esp+24h] [ebp-30h]
  float v56; // [esp+28h] [ebp-2Ch]
  float v57; // [esp+28h] [ebp-2Ch]
  float v58; // [esp+2Ch] [ebp-28h]
  float v59; // [esp+30h] [ebp-24h]
  float v60; // [esp+30h] [ebp-24h]
  float v61; // [esp+34h] [ebp-20h]
  float v62; // [esp+34h] [ebp-20h]
  float v63; // [esp+38h] [ebp-1Ch]
  float v64; // [esp+38h] [ebp-1Ch]
  float v65; // [esp+3Ch] [ebp-18h]
  float v66; // [esp+3Ch] [ebp-18h]
  float v67; // [esp+3Ch] [ebp-18h]
  float v68; // [esp+40h] [ebp-14h]
  float v69; // [esp+40h] [ebp-14h]
  float v70; // [esp+40h] [ebp-14h]
  float v71; // [esp+44h] [ebp-10h]
  float v72; // [esp+44h] [ebp-10h]
  float v73; // [esp+44h] [ebp-10h]
  float v74; // [esp+50h] [ebp-4h]
  int32_t arg2a; // [esp+58h] [ebp+4h]
  float arg3a; // [esp+5Ch] [ebp+8h]
  signed int arg3b; // [esp+5Ch] [ebp+8h]
  signed int arg3c; // [esp+5Ch] [ebp+8h]
  float arg3d; // [esp+5Ch] [ebp+8h]
  ObjectFaceQuad *arg4a; // [esp+60h] [ebp+Ch]
  float arg5e; // [esp+64h] [ebp+10h]
  int arg5a; // [esp+64h] [ebp+10h]
  float arg5b; // [esp+64h] [ebp+10h]
  float arg5f; // [esp+64h] [ebp+10h]
  Vec3 *arg5c; // [esp+64h] [ebp+10h]
  float arg5d; // [esp+64h] [ebp+10h]
  float arg6b; // [esp+68h] [ebp+14h]
  float arg6a; // [esp+68h] [ebp+14h]
  char *texture_aa; // [esp+6Ch] [ebp+18h]
  float texture_ab; // [esp+6Ch] [ebp+18h]
  char *v91; // [esp+74h] [ebp+20h]

  self->kind = arg2 + 33;
  v9 = 0;
  self->segment_count = (uint32_t)(texture_a + 2);
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  *(float *)&self->width_cells = arg4;
  self->width_or_scale = 1.0;
  self->segment_count_f = (float)(int)(texture_a + 2);
  v10 = (*(float *)&arg6 - arg5) * 0.5;
  if ( v10 < 0.0 )
    v10 = -v10;
  arg3a = v10;
  allocate_path_nodes(self);
  primary_samples = self->primary_samples;
  self->special_runtime_flag_9c = 0;
  primary_samples->center_x = arg5;
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
  v12 = (int)(texture_a + 1);
  self->primary_samples[v12].center_x = *(float *)&arg6;
  self->primary_samples[v12].rotation_scalar_98 = 0.0;
  self->primary_samples[v12].rotation_scalar_94 = 0.0;
  self->primary_samples[v12].special_scalar = 0.0;
  self->primary_samples[v12].lateral_scale = 1.0;
  set_matrix_identity(&self->primary_samples[v12].transform);
  arg5e = (float)(int)(texture_a + 1);
  self->primary_samples[v12].transform.position.x = self->primary_samples[v12].center_x;
  self->primary_samples[v12].transform.position.y = 0.0;
  self->primary_samples[v12].transform.position.z = arg5e;
  set_matrix_identity(&self->secondary_samples[v12].transform);
  v13 = arg5e;
  v14 = 0;
  self->secondary_samples[v12].transform.position.x = self->primary_samples[v12].center_x;
  arg5a = 0;
  self->secondary_samples[v12].transform.position.y = 0.49000001;
  self->secondary_samples[v12].transform.position.z = v13;
  if ( (int)texture_a > 0 )
  {
    v15 = 1;
    while ( 1 )
    {
      arg6b = (float)(int)texture_a;
      arg5b = (double)arg5a * 3.1415927 / arg6b;
      if ( self->kind == 33 )
        break;
      if ( self->kind == 34 )
      {
        self->primary_samples[v15].center_x = 2.0 - cosine(arg5b) * arg3a - arg3a + 0.5;
      }
      else if ( self->kind == 35 )
      {
        v49 = arg5b + 1.5707964;
        v16 = (sine(v49) + 1.0) * arg3a;
LABEL_11:
        self->primary_samples[v15].center_x = v16 + 0.5;
      }
      self->primary_samples[v15].rotation_scalar_98 = 0.0;
      self->primary_samples[v15].rotation_scalar_94 = 0.0;
      self->primary_samples[v15].special_scalar = 0.0;
      self->primary_samples[v15].lateral_scale = 1.0;
      set_matrix_identity(&self->primary_samples[v15].transform);
      ++v14;
      self->primary_samples[v15].transform.position.x = self->primary_samples[v15].center_x;
      arg5f = (float)v14;
      self->primary_samples[v15].transform.position.y = 0.0;
      self->primary_samples[v15].transform.position.z = arg5f;
      set_matrix_identity(&self->secondary_samples[v15].transform);
      self->secondary_samples[v15].transform.position.x = self->primary_samples[v15].center_x;
      self->secondary_samples[v15].transform.position.y = self->primary_samples[v15].transform.position.y + 0.49000001;
      self->secondary_samples[v15].transform.position.z = arg5f;
      if ( v15 <= 1 )
      {
        set_matrix_rotation_identity(&self->primary_samples[v15 - 1].transform);
        set_matrix_rotation_identity(&self->secondary_samples[v15 - 1].transform);
      }
      else
      {
        p_basis_up = &self->primary_samples[v15 - 1].transform.basis_up;
        p_basis_up->x = 0.0;
        p_basis_up->y = 1.0;
        p_basis_up->z = 0.0;
        v18 = self->primary_samples;
        p_x = &v18[v15 - 1].transform.basis_forward.x;
        v54 = v18[v15].transform.position.x - v18[v15 - 1].transform.position.x;
        v56 = p_x[47] - p_x[5];
        v20 = p_x[48] - p_x[6];
        *p_x = v54;
        p_x[1] = v56;
        v58 = v20;
        p_x[2] = v58;
        normalize_vector((Vec3 *)&self->primary_samples[v15 - 1].transform.basis_forward);
        cross_vectors(
          (Vec3 *)&self->primary_samples[v15 - 1],
          (Vec3 *)&self->primary_samples[v15 - 1].transform.basis_up,
          (Vec3 *)&self->primary_samples[v15 - 1].transform.basis_forward);
        v21 = &self->secondary_samples[v15 - 1].transform.basis_up;
        v21->x = 0.0;
        v21->y = 1.0;
        v21->z = 0.0;
        secondary_samples = self->secondary_samples;
        v23 = &secondary_samples[v15 - 1].transform.basis_forward.x;
        v65 = secondary_samples[v15].transform.position.x - secondary_samples[v15 - 1].transform.position.x;
        v68 = v23[47] - v23[5];
        v24 = v23[48] - v23[6];
        *v23 = v65;
        v23[1] = v68;
        v71 = v24;
        v23[2] = v71;
        normalize_vector((Vec3 *)&self->secondary_samples[v15 - 1].transform.basis_forward);
        cross_vectors(
          (Vec3 *)&self->secondary_samples[v15 - 1],
          (Vec3 *)&self->secondary_samples[v15 - 1].transform.basis_up,
          (Vec3 *)&self->secondary_samples[v15 - 1].transform.basis_forward);
      }
      ++v15;
      arg5a = v14;
      if ( v14 >= (int)texture_a )
        goto LABEL_16;
    }
    v50 = arg5b + 1.5707964;
    v16 = sine(v50) * arg3a - arg3a;
    goto LABEL_11;
  }
LABEL_16:
  v25 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v26 = 0;
    do
    {
      v27 = &self->primary_samples[v26].transform.basis_right.x;
      v28 = v27[54] - v27[12];
      v27 += 32;
      v66 = v28;
      v69 = v27[23] - *(v27 - 19);
      v29 = v27[24] - *(v27 - 18);
      *v27 = v66;
      v27[1] = v69;
      v72 = v29;
      v27[2] = v72;
      self->primary_samples[v26].delta_length = normalize_vector(&self->primary_samples[v26].delta_dir_to_next);
      v30 = self->secondary_samples;
      v31 = &v30[v26].delta_dir_to_next.x;
      v59 = v30[v26 + 1].transform.position.x - v30[v26].transform.position.x;
      v61 = v30[v26 + 1].transform.position.y - v30[v26].transform.position.y;
      v32 = v30[v26 + 1].transform.position.z - v30[v26].transform.position.z;
      *v31 = v59;
      v31[1] = v61;
      v63 = v32;
      v31[2] = v63;
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
  request_object_vertices(self->strip_mesh, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->strip_mesh, 2 * self->segment_count * self->width_cells);
  strip_mesh = self->strip_mesh;
  v36 = 0;
  vertices = strip_mesh->vertices;
  arg5c = vertices;
  arg4a = strip_mesh->facequads;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    do
    {
      width_cells = self->width_cells;
      v39 = 0;
      arg3b = 0;
      for ( texture_aa = (char *)width_cells; v39 <= width_cells; arg3b = v39 )
      {
        v40 = (double)arg3b - (double)(int)texture_aa * 0.5;
        v41 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v9);
        if ( v36 == self->segment_count )
        {
          vertices = arg5c;
          v52 = v40 * *(v41 - 42);
          v53 = v40 * *(v41 - 41);
          v44 = v40 * *(v41 - 40);
          v74 = *(v41 - 28) + 1.0;
          v60 = *(v41 - 30) + v52;
          v62 = *(v41 - 29) + v53;
          v42 = &arg5c[v39 + v36 * (width_cells + 1)].x;
          *v42 = v60;
          v64 = v74 + v44;
          v42[1] = v62;
          v43 = v64;
        }
        else
        {
          v55 = v40 * *v41;
          v57 = v40 * v41[1];
          v67 = v55 + v41[12];
          v70 = v57 + v41[13];
          v73 = v40 * v41[2] + v41[14];
          v42 = &vertices[v39 + v36 * (width_cells + 1)].x;
          *v42 = v67;
          v42[1] = v70;
          v43 = v73;
        }
        v42[2] = v43;
        width_cells = self->width_cells;
        ++v39;
        texture_aa = (char *)width_cells;
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
      arg3c = 0;
      if ( (int)self->width_cells > 0 )
      {
        texture_ab = (double)(v9 % 8) * 0.125;
        arg6a = (double)(v9 % 8 + 1) * 0.125;
        do
        {
          v46 = 0;
          v51 = v45 + 1;
          arg2a = 0;
          arg3d = (double)arg3c * 0.125;
          arg5d = (double)(v45 + 1) * 0.125;
          while ( 1 )
          {
            v47 = (uint32_t)arg4a + 96 * v45 + 96 * v9 * self->width_cells + 48 * v46;
            *(_WORD *)v47 = 0;
            if ( v46 )
            {
              *(_WORD *)(v47 + 2) = v9 * (LOWORD(self->width_cells) + 1) + v45 + 1;
              *(_WORD *)(v47 + 4) = v45 + v9 * (LOWORD(self->width_cells) + 1);
              *(_WORD *)(v47 + 6) = v45 + (v9 + 1) * (LOWORD(self->width_cells) + 1);
              *(_WORD *)(v47 + 8) = (v9 + 1) * (LOWORD(self->width_cells) + 1) + v45 + 1;
              *(_DWORD *)(v47 + 12) = get_or_create_texture_ref((TextureRefList *)dword_4B7790, v91, 0, 0);
              *(float *)(v47 + 16) = arg5d;
              *(float *)(v47 + 20) = texture_ab;
              *(float *)(v47 + 24) = arg3d;
              *(float *)(v47 + 28) = texture_ab;
              *(float *)(v47 + 32) = arg3d;
              *(float *)(v47 + 36) = arg6a;
              *(float *)(v47 + 40) = arg5d;
            }
            else
            {
              *(_WORD *)(v47 + 2) = v45 + v9 * (LOWORD(self->width_cells) + 1);
              *(_WORD *)(v47 + 4) = v9 * (LOWORD(self->width_cells) + 1) + v45 + 1;
              *(_WORD *)(v47 + 6) = (v9 + 1) * (LOWORD(self->width_cells) + 1) + v45 + 1;
              *(_WORD *)(v47 + 8) = v45 + (v9 + 1) * (LOWORD(self->width_cells) + 1);
              *(_DWORD *)(v47 + 12) = get_or_create_texture_ref((TextureRefList *)dword_4B7790, texture_b, 0, 0);
              *(float *)(v47 + 16) = arg3d;
              *(float *)(v47 + 20) = texture_ab;
              *(float *)(v47 + 24) = arg5d;
              *(float *)(v47 + 28) = texture_ab;
              *(float *)(v47 + 32) = arg5d;
              *(float *)(v47 + 36) = arg6a;
              *(float *)(v47 + 40) = arg3d;
            }
            *(float *)(v47 + 44) = arg6a;
            if ( ++arg2a >= 2 )
              break;
            v46 = arg2a;
          }
          ++v45;
          arg3c = v51;
        }
        while ( v51 < (signed int)self->width_cells );
      }
      ++v9;
    }
    while ( v9 < (signed int)self->segment_count );
  }
  return finalize_path_template_record(self);
}

