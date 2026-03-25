/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_halfpipe_path_template_pair @ 0x41d030 */
/* selector: initialize_halfpipe_path_template_pair */

int32_t __thiscall initialize_halfpipe_path_template_pair(
        PathTemplate *self,
        float arg2,
        float arg3,
        int32_t arg4,
        char *texture_a,
        char *texture_b)
{
  signed int v7; // ebx
  __int64 v8; // rax
  int32_t v9; // ebp
  double v10; // st7
  int i; // edi
  int32_t v12; // edi
  int v13; // edi
  PathTemplateSample *primary_samples; // ebp
  PathTemplateSample *v15; // edx
  PathTemplateSample *v16; // ecx
  float *p_x; // eax
  double v18; // st7
  PathTemplateSample *v19; // eax
  PathTemplateSample *secondary_samples; // edx
  float *v21; // eax
  double v22; // st7
  signed int v23; // ebp
  int v24; // edi
  float *v25; // eax
  double v26; // st7
  double v27; // st7
  PathTemplateSample *v28; // ecx
  float *v29; // eax
  double v30; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v32; // ecx
  PathTemplateStripMesh *strip_mesh; // eax
  signed int v34; // edx
  Vec3 *vertices; // ebp
  signed int width_cells; // ecx
  signed int v37; // edi
  double v38; // st7
  float *v39; // eax
  float *v40; // eax
  float v41; // ecx
  double v42; // st7
  int v43; // edi
  int v44; // ecx
  uint32_t v45; // ebp
  float v47; // [esp+0h] [ebp-60h]
  int v48; // [esp+14h] [ebp-4Ch]
  float v49; // [esp+14h] [ebp-4Ch]
  float v50; // [esp+18h] [ebp-48h]
  int v51; // [esp+18h] [ebp-48h]
  float v52; // [esp+1Ch] [ebp-44h]
  ObjectFaceQuad *facequads; // [esp+1Ch] [ebp-44h]
  float v54; // [esp+20h] [ebp-40h]
  float v55; // [esp+20h] [ebp-40h]
  signed int v56; // [esp+20h] [ebp-40h]
  float v57; // [esp+24h] [ebp-3Ch]
  float v58; // [esp+28h] [ebp-38h]
  float v59; // [esp+30h] [ebp-30h]
  float v60; // [esp+30h] [ebp-30h]
  float v61; // [esp+34h] [ebp-2Ch]
  float v62; // [esp+34h] [ebp-2Ch]
  float v63; // [esp+38h] [ebp-28h]
  float v64; // [esp+3Ch] [ebp-24h]
  float v65; // [esp+3Ch] [ebp-24h]
  float v66; // [esp+40h] [ebp-20h]
  float v67; // [esp+40h] [ebp-20h]
  float v68; // [esp+44h] [ebp-1Ch]
  float v69; // [esp+44h] [ebp-1Ch]
  float v70; // [esp+48h] [ebp-18h]
  float v71; // [esp+48h] [ebp-18h]
  float v72; // [esp+48h] [ebp-18h]
  float v73; // [esp+4Ch] [ebp-14h]
  float v74; // [esp+4Ch] [ebp-14h]
  float v75; // [esp+4Ch] [ebp-14h]
  float v76; // [esp+50h] [ebp-10h]
  float v77; // [esp+50h] [ebp-10h]
  float v78; // [esp+50h] [ebp-10h]
  float v79; // [esp+5Ch] [ebp-4h]
  float arg2a; // [esp+64h] [ebp+4h]
  int arg2b; // [esp+64h] [ebp+4h]
  int arg2c; // [esp+64h] [ebp+4h]
  float arg2d; // [esp+64h] [ebp+4h]
  int arg3a; // [esp+68h] [ebp+8h]
  float arg3b; // [esp+68h] [ebp+8h]
  int32_t arg4a; // [esp+6Ch] [ebp+Ch]
  int32_t arg4b; // [esp+6Ch] [ebp+Ch]
  float arg4f; // [esp+6Ch] [ebp+Ch]
  int32_t arg4c; // [esp+6Ch] [ebp+Ch]
  int32_t arg4d; // [esp+6Ch] [ebp+Ch]
  float arg4e; // [esp+6Ch] [ebp+Ch]
  char *v92; // [esp+78h] [ebp+18h]

  v7 = 0;
  self->kind = PATH_TEMPLATE_KIND_HALFPIPE_FAMILY;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = arg4;
  v8 = (__int64)(arg2 * 4.0);
  v9 = v8 + 7;
  v48 = v8;
  self->width_or_scale = 1.0;
  self->segment_count = v8 + 14;
  self->segment_count_f = (float)(v8 + 14);
  v10 = (double)(int)v8;
  v50 = v10;
  arg2a = v10 * 0.095492966;
  allocate_path_template_samples(self);
  self->special_runtime_flag_9c = 0;
  arg4a = 0;
  for ( i = 0; i < 7; ++i )
  {
    self->primary_samples[i].center_x = (double)(int)self->width_cells * 0.5 - 4.0;
    self->primary_samples[i].rotation_scalar_98 = 0.0;
    self->primary_samples[i].rotation_scalar_94 = 0.0;
    self->primary_samples[i].special_scalar = 0.0;
    self->primary_samples[i].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[i].transform);
    self->primary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    v54 = (float)arg4a;
    self->primary_samples[i].transform.position.y = 0.0;
    self->primary_samples[i].transform.position.z = v54;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->secondary_samples[i].transform.position.y = 0.49000001;
    self->secondary_samples[i].transform.position.z = v54;
    ++arg4a;
  }
  arg4b = v9;
  v12 = v9;
  do
  {
    self->primary_samples[v12].center_x = 4.0 - (double)(int)self->width_cells * 0.5;
    self->primary_samples[v12].rotation_scalar_98 = 0.0;
    self->primary_samples[v12].rotation_scalar_94 = 0.0;
    self->primary_samples[v12].special_scalar = 0.0;
    self->primary_samples[v12].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v12].transform);
    arg4f = (float)arg4b;
    self->primary_samples[v12].transform.position.x = self->primary_samples[v12].center_x;
    self->primary_samples[v12].transform.position.y = 0.0;
    self->primary_samples[v12].transform.position.z = arg4f;
    set_matrix_identity(&self->secondary_samples[v12].transform);
    self->secondary_samples[v12].transform.position.x = self->primary_samples[v12].center_x;
    self->secondary_samples[v12].transform.position.y = 0.49000001;
    self->secondary_samples[v12++].transform.position.z = arg4f;
    arg4b = ++v9;
  }
  while ( v9 + -7 - v48 < 7 );
  arg4c = 0;
  if ( v48 > 0 )
  {
    v13 = 7;
    do
    {
      primary_samples = self->primary_samples;
      v52 = (double)arg4c * 6.2831855 / v50;
      v47 = v52 * 0.5;
      primary_samples[v13].center_x = cosine(v47) * primary_samples->center_x;
      self->primary_samples[v13].rotation_scalar_98 = 0.0;
      self->primary_samples[v13].rotation_scalar_94 = 0.0;
      self->primary_samples[v13].special_scalar = 0.0;
      self->primary_samples[v13].lateral_scale = 1.0;
      set_matrix_identity(&self->primary_samples[v13].transform);
      self->primary_samples[v13].transform.position.x = self->primary_samples[v13].center_x;
      self->primary_samples[v13].transform.position.y = (1.0 - cosine(v52)) * arg2a * arg3;
      v55 = (float)(arg4c + 7);
      self->primary_samples[v13].transform.position.z = v55;
      set_matrix_identity(&self->secondary_samples[v13].transform);
      self->secondary_samples[v13].transform.position.x = self->primary_samples[v13].center_x;
      self->secondary_samples[v13].transform.position.y = (1.0 - cosine(v52)) * arg2a * arg3 + 0.49000001;
      self->secondary_samples[v13].transform.position.z = v55;
      if ( v13 <= 7 )
      {
        set_matrix_rotation_identity(&self->primary_samples[v13 - 1].transform);
        set_matrix_rotation_identity(&self->secondary_samples[v13 - 1].transform);
      }
      else
      {
        v15 = &self->primary_samples[v13 - 1];
        v15->transform.basis_right.x = 1.0;
        v15->transform.basis_right.y = 0.0;
        v15->transform.basis_right.z = 0.0;
        v16 = self->primary_samples;
        p_x = &v16[v13 - 1].transform.basis_forward.x;
        v59 = v16[v13].transform.position.x - v16[v13 - 1].transform.position.x;
        v61 = p_x[47] - p_x[5];
        v18 = p_x[48] - p_x[6];
        *p_x = v59;
        p_x[1] = v61;
        v63 = v18;
        p_x[2] = v63;
        normalize_vector((Vec3 *)&self->primary_samples[v13 - 1].transform.basis_forward);
        cross_vectors(
          (Vec3 *)&self->primary_samples[v13 - 1].transform.basis_up,
          (Vec3 *)&self->primary_samples[v13 - 1].transform.basis_forward,
          (Vec3 *)&self->primary_samples[v13 - 1]);
        v19 = &self->secondary_samples[v13 - 1];
        v19->transform.basis_right.x = 1.0;
        v19->transform.basis_right.y = 0.0;
        v19->transform.basis_right.z = 0.0;
        secondary_samples = self->secondary_samples;
        v21 = &secondary_samples[v13 - 1].transform.basis_forward.x;
        v70 = secondary_samples[v13].transform.position.x - secondary_samples[v13 - 1].transform.position.x;
        v73 = v21[47] - v21[5];
        v22 = v21[48] - v21[6];
        *v21 = v70;
        v21[1] = v73;
        v76 = v22;
        v21[2] = v76;
        normalize_vector((Vec3 *)&self->secondary_samples[v13 - 1].transform.basis_forward);
        cross_vectors(
          (Vec3 *)&self->secondary_samples[v13 - 1].transform.basis_up,
          (Vec3 *)&self->secondary_samples[v13 - 1].transform.basis_forward,
          (Vec3 *)&self->secondary_samples[v13 - 1]);
      }
      ++v13;
      ++arg4c;
    }
    while ( arg4c < v48 );
  }
  v23 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v24 = 0;
    do
    {
      v25 = &self->primary_samples[v24].transform.basis_right.x;
      v26 = v25[54] - v25[12];
      v25 += 32;
      v71 = v26;
      v74 = v25[23] - *(v25 - 19);
      v27 = v25[24] - *(v25 - 18);
      *v25 = v71;
      v25[1] = v74;
      v77 = v27;
      v25[2] = v77;
      self->primary_samples[v24].delta_length = normalize_vector(&self->primary_samples[v24].delta_dir_to_next);
      v28 = self->secondary_samples;
      v29 = &v28[v24].delta_dir_to_next.x;
      v64 = v28[v24 + 1].transform.position.x - v28[v24].transform.position.x;
      v66 = v28[v24 + 1].transform.position.y - v28[v24].transform.position.y;
      v30 = v28[v24 + 1].transform.position.z - v28[v24].transform.position.z;
      *v29 = v64;
      v29[1] = v66;
      v68 = v30;
      v29[2] = v68;
      ++v23;
      self->secondary_samples[v24].delta_length = normalize_vector(&self->secondary_samples[v24].delta_dir_to_next);
      ++v24;
    }
    while ( v23 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = 1.0;
  v32 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v32->x = 0.0;
  v32->y = 0.0;
  v32->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = 1.0;
  request_object_vertices(self->strip_mesh, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->strip_mesh, 2 * self->segment_count * self->width_cells);
  strip_mesh = self->strip_mesh;
  v34 = 0;
  vertices = strip_mesh->vertices;
  arg4d = (int32_t)vertices;
  facequads = strip_mesh->facequads;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    do
    {
      width_cells = self->width_cells;
      v37 = 0;
      arg2b = 0;
      for ( arg3a = width_cells; v37 <= width_cells; arg2b = v37 )
      {
        v38 = (double)arg2b - (double)arg3a * 0.5;
        v39 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v7);
        if ( v34 == self->segment_count )
        {
          vertices = (Vec3 *)arg4d;
          v57 = v38 * *(v39 - 42);
          v58 = v38 * *(v39 - 41);
          v42 = v38 * *(v39 - 40);
          v79 = *(v39 - 28) + 1.0;
          v65 = *(v39 - 30) + v57;
          v67 = *(v39 - 29) + v58;
          v40 = (float *)(arg4d + 12 * (v37 + v34 * (width_cells + 1)));
          *v40 = v65;
          v69 = v79 + v42;
          v40[1] = v67;
          v41 = v69;
        }
        else
        {
          v60 = v38 * *v39;
          v62 = v38 * v39[1];
          v72 = v60 + v39[12];
          v75 = v62 + v39[13];
          v78 = v38 * v39[2] + v39[14];
          v40 = &vertices[v37 + v34 * (width_cells + 1)].x;
          *v40 = v72;
          v40[1] = v75;
          v41 = v78;
        }
        v40[2] = v41;
        width_cells = self->width_cells;
        ++v37;
        arg3a = width_cells;
      }
      ++v34;
      v7 += 168;
    }
    while ( v34 <= (signed int)self->segment_count );
    v7 = 0;
  }
  if ( (int)self->segment_count > 0 )
  {
    do
    {
      v43 = 0;
      arg2c = 0;
      if ( (int)self->width_cells > 0 )
      {
        arg3b = (double)(v7 % 8) * 0.125;
        v49 = (double)(v7 % 8 + 1) * 0.125;
        do
        {
          v44 = 0;
          v56 = v43 + 1;
          v51 = 0;
          arg2d = (double)arg2c * 0.125;
          arg4e = (double)(v43 + 1) * 0.125;
          while ( 1 )
          {
            v45 = (uint32_t)facequads + 96 * v43 + 96 * v7 * self->width_cells + 48 * v44;
            *(_WORD *)v45 = 0;
            if ( v44 )
            {
              *(_WORD *)(v45 + 2) = v7 * (LOWORD(self->width_cells) + 1) + v43 + 1;
              *(_WORD *)(v45 + 4) = v43 + v7 * (LOWORD(self->width_cells) + 1);
              *(_WORD *)(v45 + 6) = v43 + (v7 + 1) * (LOWORD(self->width_cells) + 1);
              *(_WORD *)(v45 + 8) = (v7 + 1) * (LOWORD(self->width_cells) + 1) + v43 + 1;
              *(_DWORD *)(v45 + 12) = get_or_create_texture_ref((TextureRefList *)dword_4B7790, v92, 0, 0);
              *(float *)(v45 + 16) = arg4e;
              *(float *)(v45 + 20) = arg3b;
              *(float *)(v45 + 24) = arg2d;
              *(float *)(v45 + 28) = arg3b;
              *(float *)(v45 + 32) = arg2d;
              *(float *)(v45 + 36) = v49;
              *(float *)(v45 + 40) = arg4e;
            }
            else
            {
              *(_WORD *)(v45 + 2) = v43 + v7 * (LOWORD(self->width_cells) + 1);
              *(_WORD *)(v45 + 4) = v7 * (LOWORD(self->width_cells) + 1) + v43 + 1;
              *(_WORD *)(v45 + 6) = (v7 + 1) * (LOWORD(self->width_cells) + 1) + v43 + 1;
              *(_WORD *)(v45 + 8) = v43 + (v7 + 1) * (LOWORD(self->width_cells) + 1);
              *(_DWORD *)(v45 + 12) = get_or_create_texture_ref((TextureRefList *)dword_4B7790, texture_b, 0, 0);
              *(float *)(v45 + 16) = arg2d;
              *(float *)(v45 + 20) = arg3b;
              *(float *)(v45 + 24) = arg4e;
              *(float *)(v45 + 28) = arg3b;
              *(float *)(v45 + 32) = arg4e;
              *(float *)(v45 + 36) = v49;
              *(float *)(v45 + 40) = arg2d;
            }
            *(float *)(v45 + 44) = v49;
            if ( ++v51 >= 2 )
              break;
            v44 = v51;
          }
          ++v43;
          arg2c = v56;
        }
        while ( v56 < (signed int)self->width_cells );
      }
      ++v7;
    }
    while ( v7 < (signed int)self->segment_count );
  }
  return finalize_path_template(self);
}

