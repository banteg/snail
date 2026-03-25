/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_cage2_path_template_pair @ 0x41e440 */
/* selector: initialize_cage2_path_template_pair */

int32_t __thiscall initialize_cage2_path_template_pair(
        PathTemplate *self,
        float arg2,
        int32_t arg3,
        char *texture_a,
        char *texture_b)
{
  __int64 v6; // rax
  int v7; // edi
  double v8; // st7
  PathTemplateSample *primary_samples; // ecx
  int v10; // ebx
  int v11; // edi
  PathTemplateSample *v12; // eax
  PathTemplateSample *v13; // edx
  float *p_x; // eax
  double v15; // st7
  PathTemplateSample *v16; // ecx
  PathTemplateSample *v17; // eax
  double v18; // st7
  double v19; // st7
  signed int v20; // ebx
  int v21; // edi
  float *v22; // eax
  double v23; // st7
  double v24; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *v26; // eax
  double v27; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v29; // ecx
  PathTemplateStripMesh *strip_mesh; // eax
  signed int v31; // edx
  int v32; // ebx
  signed int width_cells; // ecx
  signed int v34; // edi
  double v35; // st7
  PathTemplateSample *v36; // eax
  float *v37; // ecx
  float *v38; // ecx
  double v39; // st6
  signed int i; // ebx
  int v41; // edi
  int v42; // ecx
  ObjectFaceQuad *v43; // ebp
  float v45; // [esp+0h] [ebp-50h]
  int v46; // [esp+4h] [ebp-4Ch]
  float v47; // [esp+4h] [ebp-4Ch]
  float v48; // [esp+4h] [ebp-4Ch]
  float v49; // [esp+8h] [ebp-48h]
  Vec3 *vertices; // [esp+8h] [ebp-48h]
  int v51; // [esp+8h] [ebp-48h]
  ObjectFaceQuad *facequads; // [esp+Ch] [ebp-44h]
  int v53; // [esp+10h] [ebp-40h]
  float v54; // [esp+10h] [ebp-40h]
  float v55; // [esp+10h] [ebp-40h]
  signed int v56; // [esp+10h] [ebp-40h]
  float v57; // [esp+14h] [ebp-3Ch]
  float v58; // [esp+18h] [ebp-38h]
  float v59; // [esp+20h] [ebp-30h]
  float v60; // [esp+20h] [ebp-30h]
  float v61; // [esp+24h] [ebp-2Ch]
  float v62; // [esp+24h] [ebp-2Ch]
  float v63; // [esp+28h] [ebp-28h]
  float v64; // [esp+2Ch] [ebp-24h]
  float v65; // [esp+2Ch] [ebp-24h]
  float v66; // [esp+30h] [ebp-20h]
  float v67; // [esp+30h] [ebp-20h]
  float v68; // [esp+34h] [ebp-1Ch]
  float v69; // [esp+34h] [ebp-1Ch]
  float v70; // [esp+38h] [ebp-18h]
  float v71; // [esp+38h] [ebp-18h]
  float v72; // [esp+38h] [ebp-18h]
  float v73; // [esp+3Ch] [ebp-14h]
  float v74; // [esp+3Ch] [ebp-14h]
  float v75; // [esp+3Ch] [ebp-14h]
  float v76; // [esp+40h] [ebp-10h]
  float v77; // [esp+40h] [ebp-10h]
  float v78; // [esp+40h] [ebp-10h]
  float v79; // [esp+4Ch] [ebp-4h]
  float arg2a; // [esp+54h] [ebp+4h]
  int arg2b; // [esp+54h] [ebp+4h]
  int arg2c; // [esp+54h] [ebp+4h]
  float arg2d; // [esp+54h] [ebp+4h]
  int32_t arg3a; // [esp+58h] [ebp+8h]
  int32_t arg3b; // [esp+58h] [ebp+8h]
  float arg3c; // [esp+58h] [ebp+8h]
  char *v87; // [esp+64h] [ebp+14h]

  self->kind = 20;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = arg3;
  v6 = (__int64)(arg2 * 5.0);
  v7 = v6 + 1;
  arg3a = v6;
  self->width_or_scale = 1.0;
  self->segment_count = v6 + 2;
  self->segment_count_f = (float)(v6 + 2);
  v8 = (double)(int)v6;
  v49 = v8;
  arg2a = v8 * 0.047746483;
  allocate_path_nodes(self);
  primary_samples = self->primary_samples;
  self->special_runtime_flag_9c = 0;
  primary_samples->center_x = 0.0;
  self->primary_samples->rotation_scalar_98 = 0.0;
  self->primary_samples->rotation_scalar_94 = 0.0;
  self->primary_samples->special_scalar = 0.0;
  self->primary_samples->lateral_scale = 1.0;
  set_matrix_identity(&self->primary_samples->transform);
  self->primary_samples->transform.position.x = self->primary_samples->center_x;
  self->primary_samples->transform.position.y = 0.0;
  self->primary_samples->transform.position.z = 0.0;
  set_matrix_identity(&self->secondary_samples->transform);
  v53 = v7;
  self->secondary_samples->transform.position.x = self->primary_samples->center_x;
  self->secondary_samples->transform.position.y = 0.49000001;
  self->secondary_samples->transform.position.z = 0.0;
  v7 *= 168;
  *(float *)((char *)&self->primary_samples->center_x + v7) = 0.0;
  *(float *)((char *)&self->primary_samples->rotation_scalar_98 + v7) = 0.0;
  *(float *)((char *)&self->primary_samples->rotation_scalar_94 + v7) = 0.0;
  *(float *)((char *)&self->primary_samples->special_scalar + v7) = 0.0;
  *(float *)((char *)&self->primary_samples->lateral_scale + v7) = 1.0;
  set_matrix_identity((PathTemplateTransform *)((char *)&self->primary_samples->transform + v7));
  *(float *)((char *)&self->primary_samples->transform.position.x + v7) = *(float *)((char *)&self->primary_samples->center_x
                                                                                   + v7);
  v54 = (float)v53;
  *(float *)((char *)&self->primary_samples->transform.position.y + v7) = 0.0;
  *(float *)((char *)&self->primary_samples->transform.position.z + v7) = v54;
  set_matrix_identity((PathTemplateTransform *)((char *)&self->secondary_samples->transform + v7));
  v10 = 0;
  *(float *)((char *)&self->secondary_samples->transform.position.x + v7) = *(float *)((char *)&self->primary_samples->center_x
                                                                                     + v7);
  v46 = 0;
  *(float *)((char *)&self->secondary_samples->transform.position.y + v7) = 0.49000001;
  *(float *)((char *)&self->secondary_samples->transform.position.z + v7) = v54;
  if ( arg3a > 0 )
  {
    v11 = 1;
    do
    {
      self->primary_samples[v11].center_x = 0.0;
      self->primary_samples[v11].rotation_scalar_98 = 0.0;
      self->primary_samples[v11].rotation_scalar_94 = 0.0;
      self->primary_samples[v11].special_scalar = 0.0;
      self->primary_samples[v11].lateral_scale = 1.0;
      v47 = (double)v46 * 6.2831855 / v49;
      set_matrix_identity(&self->primary_samples[v11].transform);
      self->primary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
      ++v10;
      self->primary_samples[v11].transform.position.y = -((1.0 - cosine(v47)) * arg2a);
      v55 = (float)v10;
      self->primary_samples[v11].transform.position.z = v55;
      set_matrix_identity(&self->secondary_samples[v11].transform);
      self->secondary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
      self->secondary_samples[v11].transform.position.y = 0.49000001 - (1.0 - cosine(v47)) * arg2a;
      self->secondary_samples[v11].transform.position.z = v55;
      if ( v11 <= 1 )
      {
        set_matrix_rotation_identity(&self->primary_samples[v11 - 1].transform);
        set_matrix_rotation_identity(&self->secondary_samples[v11 - 1].transform);
      }
      else
      {
        v12 = &self->primary_samples[v11 - 1];
        v12->transform.basis_right.x = 1.0;
        v12->transform.basis_right.y = 0.0;
        v12->transform.basis_right.z = 0.0;
        v13 = self->primary_samples;
        p_x = &v13[v11 - 1].transform.basis_forward.x;
        v59 = v13[v11].transform.position.x - v13[v11 - 1].transform.position.x;
        v61 = p_x[47] - p_x[5];
        v15 = p_x[48] - p_x[6];
        *p_x = v59;
        p_x[1] = v61;
        v63 = v15;
        p_x[2] = v63;
        normalize_vector((Vec3 *)&self->primary_samples[v11 - 1].transform.basis_forward);
        cross_vectors(
          (Vec3 *)&self->primary_samples[v11 - 1].transform.basis_up,
          (Vec3 *)&self->primary_samples[v11 - 1].transform.basis_forward,
          (Vec3 *)&self->primary_samples[v11 - 1]);
        v16 = &self->secondary_samples[v11 - 1];
        v16->transform.basis_right.x = 1.0;
        v16->transform.basis_right.y = 0.0;
        v16->transform.basis_right.z = 0.0;
        v17 = &self->secondary_samples[v11];
        v18 = v17->transform.position.x - v17[-1].transform.position.x;
        v17 = (PathTemplateSample *)((char *)v17 - 136);
        v70 = v18;
        v73 = v17[1].transform.basis_up.y - v17->transform.basis_up.y;
        v19 = v17[1].transform.basis_up.z - v17->transform.basis_up.z;
        v17->transform.basis_right.x = v70;
        v17->transform.basis_right.y = v73;
        v76 = v19;
        v17->transform.basis_right.z = v76;
        normalize_vector((Vec3 *)&self->secondary_samples[v11 - 1].transform.basis_forward);
        cross_vectors(
          (Vec3 *)&self->secondary_samples[v11 - 1].transform.basis_up,
          (Vec3 *)&self->secondary_samples[v11 - 1].transform.basis_forward,
          (Vec3 *)&self->secondary_samples[v11 - 1]);
      }
      ++v11;
      v46 = v10;
    }
    while ( v10 < arg3a );
  }
  v20 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v21 = 0;
    do
    {
      v22 = &self->primary_samples[v21].transform.basis_right.x;
      v23 = v22[54] - v22[12];
      v22 += 32;
      v71 = v23;
      v74 = v22[23] - *(v22 - 19);
      v24 = v22[24] - *(v22 - 18);
      *v22 = v71;
      v22[1] = v74;
      v77 = v24;
      v22[2] = v77;
      self->primary_samples[v21].delta_length = normalize_vector(&self->primary_samples[v21].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v26 = &secondary_samples[v21].delta_dir_to_next.x;
      v64 = secondary_samples[v21 + 1].transform.position.x - secondary_samples[v21].transform.position.x;
      v66 = secondary_samples[v21 + 1].transform.position.y - secondary_samples[v21].transform.position.y;
      v27 = secondary_samples[v21 + 1].transform.position.z - secondary_samples[v21].transform.position.z;
      *v26 = v64;
      v26[1] = v66;
      v68 = v27;
      v26[2] = v68;
      ++v20;
      self->secondary_samples[v21].delta_length = normalize_vector(&self->secondary_samples[v21].delta_dir_to_next);
      ++v21;
    }
    while ( v20 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = 1.0;
  v29 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v29->x = 0.0;
  v29->y = 0.0;
  v29->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = 1.0;
  request_object_vertices(self->strip_mesh, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->strip_mesh, 2 * self->segment_count * self->width_cells);
  strip_mesh = self->strip_mesh;
  facequads = strip_mesh->facequads;
  v31 = 0;
  vertices = strip_mesh->vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v32 = 0;
    do
    {
      width_cells = self->width_cells;
      v34 = 0;
      arg2b = 0;
      for ( arg3b = width_cells; v34 <= width_cells; arg3b = width_cells )
      {
        v35 = (double)arg2b - (double)arg3b * 0.5;
        v36 = &self->primary_samples[v32];
        if ( v31 == self->segment_count )
        {
          v57 = v35 * v36[-1].transform.basis_right.x;
          v58 = v35 * v36[-1].transform.basis_right.y;
          v79 = v36[-1].transform.position.z + 1.0;
          v65 = v36[-1].transform.position.x + v57;
          v67 = v36[-1].transform.position.y + v58;
          v38 = &vertices[v34 + v31 * (width_cells + 1)].x;
          v39 = v79 + v35 * v36[-1].transform.basis_right.z;
          *v38 = v65;
          v38[1] = v67;
          v69 = v39;
          v38[2] = v69;
        }
        else
        {
          v60 = v35 * v36->transform.basis_right.x;
          v62 = v35 * v36->transform.basis_right.y;
          v72 = v60 + v36->transform.position.x;
          v75 = v62 + v36->transform.position.y;
          v78 = v35 * v36->transform.basis_right.z + v36->transform.position.z;
          v37 = &vertices[v34 + v31 * (width_cells + 1)].x;
          *v37 = v72;
          v37[1] = v75;
          v37[2] = v78;
        }
        width_cells = self->width_cells;
        arg2b = ++v34;
      }
      ++v31;
      ++v32;
    }
    while ( v31 <= (signed int)self->segment_count );
  }
  for ( i = 0; i < (signed int)self->segment_count; ++i )
  {
    v41 = 0;
    arg2c = 0;
    if ( (int)self->width_cells > 0 )
    {
      arg3c = (double)(i % 8) * 0.125;
      v48 = (double)(i % 8 + 1) * 0.125;
      do
      {
        v42 = 0;
        v56 = v41 + 1;
        v51 = 0;
        arg2d = (double)arg2c * 0.125;
        v45 = (double)(v41 + 1) * 0.125;
        while ( 1 )
        {
          v43 = &facequads[2 * v41 + 2 * i * self->width_cells + v42];
          v43->flags = 0;
          if ( v42 )
          {
            v43->vertex_index_a = i * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->vertex_index_b = v41 + i * (LOWORD(self->width_cells) + 1);
            v43->vertex_index_c = v41 + (i + 1) * (LOWORD(self->width_cells) + 1);
            v43->vertex_index_d = (i + 1) * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->texture_ref = get_or_create_texture_ref(dword_4B7790, v87, 0, 0);
            v43->u0 = v45;
            v43->v0 = arg3c;
            v43->u1 = arg2d;
            v43->v1 = arg3c;
            v43->u2 = arg2d;
            v43->v2 = v48;
            v43->u3 = v45;
          }
          else
          {
            v43->vertex_index_a = v41 + i * (LOWORD(self->width_cells) + 1);
            v43->vertex_index_b = i * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->vertex_index_c = (i + 1) * (LOWORD(self->width_cells) + 1) + v41 + 1;
            v43->vertex_index_d = v41 + (i + 1) * (LOWORD(self->width_cells) + 1);
            v43->texture_ref = get_or_create_texture_ref(dword_4B7790, texture_b, 0, 0);
            v43->u0 = arg2d;
            v43->v0 = arg3c;
            v43->u1 = v45;
            v43->v1 = arg3c;
            v43->u2 = v45;
            v43->v2 = v48;
            v43->u3 = arg2d;
          }
          v43->v3 = v48;
          if ( ++v51 >= 2 )
            break;
          v42 = v51;
        }
        ++v41;
        arg2c = v56;
      }
      while ( v56 < (signed int)self->width_cells );
    }
  }
  return finalize_path_template_record(self);
}

