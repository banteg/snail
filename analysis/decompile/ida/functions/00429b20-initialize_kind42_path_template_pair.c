/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_kind42_path_template_pair @ 0x429b20 */
/* selector: initialize_kind42_path_template_pair */

// Builds one nonlinear kind-42 attachment template branch. The constructor seeds sample_count=66, writes the special per-sample scalar at +0xa0, and emits a generated strip mesh through the shared kind-42 transform helper. Android's cRPath::BuildHalfPipe is a strong structural match, but the exact Windows public-path mapping remains open.
int32_t __thiscall initialize_kind42_path_template_pair(PathTemplate *self, int32_t arg2, char *arg3, char *arg4)
{
  int v5; // esi
  double v6; // st7
  double v7; // st7
  int i; // esi
  double v9; // st7
  int v10; // ebx
  double v11; // st7
  PathTemplateSample *primary_samples; // eax
  Vec4 *p_basis_up; // ecx
  PathTemplateSample *v14; // eax
  double v15; // st7
  double v16; // st7
  PathTemplateSample *v17; // ecx
  double v18; // st7
  double v19; // st6
  Vec4 *p_position; // eax
  signed int v21; // edi
  int v22; // esi
  PathTemplateSample *v23; // ecx
  float *p_x; // eax
  double v25; // st7
  PathTemplateSample *secondary_samples; // edx
  float *v27; // eax
  double v28; // st7
  Vec3 *p_delta_dir_to_next; // ecx
  Vec3 *v30; // eax
  PathTemplateStripMesh *strip_mesh; // eax
  Vec3 *vertices; // edi
  signed int v33; // esi
  int v34; // eax
  signed int width_cells; // ecx
  signed int v36; // ebx
  double v37; // st7
  float *v38; // eax
  float *v39; // ecx
  float v40; // edx
  double v41; // st6
  double v42; // st7
  double v43; // st6
  double v44; // st6
  signed int v45; // ecx
  signed int k; // ebx
  int v47; // esi
  int v48; // ecx
  ObjectFaceQuad *v49; // edi
  float v51; // [esp+0h] [ebp-B0h]
  float v52; // [esp+0h] [ebp-B0h]
  int v53; // [esp+14h] [ebp-9Ch]
  int v54; // [esp+14h] [ebp-9Ch]
  int v55; // [esp+14h] [ebp-9Ch]
  int v56; // [esp+14h] [ebp-9Ch]
  int v57; // [esp+14h] [ebp-9Ch]
  float v58; // [esp+14h] [ebp-9Ch]
  float v59; // [esp+18h] [ebp-98h]
  signed int v60; // [esp+18h] [ebp-98h]
  float v61; // [esp+1Ch] [ebp-94h]
  int j; // [esp+1Ch] [ebp-94h]
  float v63; // [esp+1Ch] [ebp-94h]
  float v64; // [esp+20h] [ebp-90h]
  float v65; // [esp+20h] [ebp-90h]
  float v66; // [esp+20h] [ebp-90h]
  float v67; // [esp+24h] [ebp-8Ch]
  float v68; // [esp+24h] [ebp-8Ch]
  float v69; // [esp+24h] [ebp-8Ch]
  float v70; // [esp+28h] [ebp-88h]
  float v71; // [esp+28h] [ebp-88h]
  float v72; // [esp+28h] [ebp-88h]
  int v73; // [esp+2Ch] [ebp-84h]
  float v74; // [esp+2Ch] [ebp-84h]
  float v75; // [esp+30h] [ebp-80h]
  float v76; // [esp+30h] [ebp-80h]
  float v77; // [esp+34h] [ebp-7Ch]
  float v78; // [esp+34h] [ebp-7Ch]
  float v79; // [esp+38h] [ebp-78h]
  float v80; // [esp+38h] [ebp-78h]
  float v81; // [esp+3Ch] [ebp-74h]
  int v82; // [esp+40h] [ebp-70h]
  ObjectFaceQuad *facequads; // [esp+44h] [ebp-6Ch]
  float v84; // [esp+48h] [ebp-68h]
  float v85; // [esp+4Ch] [ebp-64h]
  float v86; // [esp+4Ch] [ebp-64h]
  float v87; // [esp+50h] [ebp-60h]
  float v88[2]; // [esp+54h] [ebp-5Ch] BYREF
  float v89; // [esp+5Ch] [ebp-54h]
  float v90; // [esp+60h] [ebp-50h]
  float v91; // [esp+64h] [ebp-4Ch]
  float v92; // [esp+68h] [ebp-48h]
  PathTemplateTransform v93; // [esp+70h] [ebp-40h] BYREF
  char *v94; // [esp+C0h] [ebp+10h]
  char *v95; // [esp+C4h] [ebp+14h]

  self->kind = 42;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = (uint32_t)arg3;
  self->width_or_scale = 1.0;
  self->segment_count = 66;
  self->segment_count_f = 66.0;
  allocate_path_nodes(self);
  self->special_runtime_flag_9c = 0;
  v53 = 0;
  v5 = 0;
  do
  {
    v6 = (double)v53;
    v61 = v6;
    v51 = v6 * 0.0625 * 3.1415927 + 1.5707964;
    v7 = ((0.5 - sine(v51) * 0.5) * 0.94999999 + 0.050000001) * 4.0;
    self->primary_samples[v5].center_x = (double)(int)self->width_cells * 0.5 - 4.0;
    self->primary_samples[v5].rotation_scalar_98 = 0.0;
    self->primary_samples[v5].rotation_scalar_94 = 0.0;
    self->primary_samples[v5].special_scalar = (v7 * v7 + 16.0) / (v7 + v7);
    self->primary_samples[v5].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v5].transform);
    self->primary_samples[v5].transform.position.x = self->primary_samples[v5].center_x;
    self->primary_samples[v5].transform.position.y = 0.0;
    self->primary_samples[v5].transform.position.z = v61;
    self->primary_samples[v5].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v5].transform);
    self->secondary_samples[v5].transform.position.x = self->primary_samples[v5].center_x;
    self->secondary_samples[v5].transform.position.y = 0.49000001;
    self->secondary_samples[v5++].transform.position.z = v61;
    self->secondary_samples[v5 - 1].delta_length = 1.0;
    ++v53;
  }
  while ( v5 < 16 );
  v54 = 0;
  for ( i = 50; i < 66; ++i )
  {
    v52 = (1.0 - (double)v54 * 0.0625) * 3.1415927 + 1.5707964;
    v9 = ((0.5 - sine(v52) * 0.5) * 0.94999999 + 0.050000001) * 4.0;
    self->primary_samples[i].center_x = 4.0 - (double)(int)self->width_cells * 0.5;
    self->primary_samples[i].rotation_scalar_98 = 0.0;
    self->primary_samples[i].rotation_scalar_94 = 0.0;
    self->primary_samples[i].special_scalar = (v9 * v9 + 16.0) / (v9 + v9);
    self->primary_samples[i].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[i].transform);
    self->primary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->primary_samples[i].transform.position.y = 0.0;
    v59 = (float)(v54 + 50);
    self->primary_samples[i].transform.position.z = v59;
    self->primary_samples[i].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->secondary_samples[i].transform.position.y = 0.49000001;
    self->secondary_samples[i].transform.position.z = v59;
    self->secondary_samples[i].delta_length = 1.0;
    ++v54;
  }
  v55 = 0;
  v10 = 16;
  do
  {
    v11 = (double)v55;
    primary_samples = self->primary_samples;
    v88[0] = v11 * 0.18479957;
    primary_samples[v10].center_x = (primary_samples[50].center_x - primary_samples->center_x) * v11 * 0.029411765
                                  + primary_samples->center_x;
    self->primary_samples[v10].rotation_scalar_98 = 0.0;
    self->primary_samples[v10].rotation_scalar_94 = 0.0;
    self->primary_samples[v10].special_scalar = 4.0;
    self->primary_samples[v10].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v10].transform);
    self->primary_samples[v10].transform.position.x = 0.0;
    self->primary_samples[v10].transform.position.z = (float)(v55 + 16);
    self->primary_samples[v10].transform.position.y = 0.0;
    p_basis_up = &self->primary_samples[v10].transform.basis_up;
    p_basis_up->x = 0.0;
    p_basis_up->y = 1.0;
    p_basis_up->z = 0.0;
    v14 = &self->primary_samples[v10];
    v15 = v14->transform.position.x - v14[-1].transform.position.x;
    v14 = (PathTemplateSample *)((char *)v14 + 32);
    v64 = v15;
    v67 = v14->transform.basis_up.y - v14[-1].transform.basis_up.y;
    v16 = v14->transform.basis_up.z - v14[-1].transform.basis_up.z;
    v14->transform.basis_right.x = v64;
    v14->transform.basis_right.y = v67;
    v70 = v16;
    v14->transform.basis_right.z = v70;
    normalize_vector((Vec3 *)&self->primary_samples[v10].transform.basis_forward);
    cross_vectors(
      (Vec3 *)&self->primary_samples[v10],
      (Vec3 *)&self->primary_samples[v10].transform.basis_up,
      (Vec3 *)&self->primary_samples[v10].transform.basis_forward);
    qmemcpy(&self->secondary_samples[v10], &self->primary_samples[v10], 0x40u);
    v17 = self->primary_samples;
    v18 = v17[v10].transform.basis_up.x * 0.49000001;
    v85 = v17[v10].transform.basis_up.y * 0.49000001;
    v19 = v17[v10].transform.basis_up.z * 0.49000001;
    p_position = &self->secondary_samples[v10++].transform.position;
    ++v55;
    v87 = v19;
    p_position->x = v18 + p_position->x;
    p_position->y = v85 + p_position->y;
    p_position->z = v87 + p_position->z;
  }
  while ( v10 < 50 );
  v21 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v22 = 0;
    do
    {
      v23 = self->primary_samples;
      p_x = &v23[v22].delta_dir_to_next.x;
      v65 = v23[v22 + 1].transform.position.x - v23[v22].transform.position.x;
      v68 = v23[v22 + 1].transform.position.y - v23[v22].transform.position.y;
      v25 = v23[v22 + 1].transform.position.z - v23[v22].transform.position.z;
      *p_x = v65;
      p_x[1] = v68;
      v71 = v25;
      p_x[2] = v71;
      self->primary_samples[v22].delta_length = normalize_vector(&self->primary_samples[v22].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v27 = &secondary_samples[v22].delta_dir_to_next.x;
      v75 = secondary_samples[v22 + 1].transform.position.x - secondary_samples[v22].transform.position.x;
      v77 = secondary_samples[v22 + 1].transform.position.y - secondary_samples[v22].transform.position.y;
      v28 = secondary_samples[v22 + 1].transform.position.z - secondary_samples[v22].transform.position.z;
      *v27 = v75;
      v27[1] = v77;
      v79 = v28;
      v27[2] = v79;
      ++v21;
      self->secondary_samples[v22].delta_length = normalize_vector(&self->secondary_samples[v22].delta_dir_to_next);
      ++v22;
    }
    while ( v21 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = 1.0;
  v30 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v30->x = 0.0;
  v30->y = 0.0;
  v30->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = 1.0;
  request_object_vertices(self->strip_mesh, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->strip_mesh, 2 * self->segment_count * self->width_cells);
  strip_mesh = self->strip_mesh;
  vertices = strip_mesh->vertices;
  facequads = strip_mesh->facequads;
  set_matrix_identity(&v93);
  v33 = 0;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v34 = 0;
    v73 = 0;
    do
    {
      width_cells = self->width_cells;
      v36 = 0;
      v56 = 0;
      for ( j = width_cells; v36 <= width_cells; v56 = v36 )
      {
        v37 = (double)v56 - (double)j * 0.5;
        v38 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v34);
        if ( v33 == self->segment_count )
        {
          v41 = v37 * *(v38 - 42);
          v89 = *(v38 - 29);
          v91 = v41;
          v92 = v37 * *(v38 - 41);
          v42 = v37 * *(v38 - 40);
          v43 = *(v38 - 30);
          v90 = *(v38 - 28) + 1.0;
          v76 = v43 + v91;
          v78 = v89 + v92;
          v44 = v90 + v42;
          v39 = &vertices[v36 + v33 * (width_cells + 1)].x;
          *v39 = v76;
          v80 = v44;
          v40 = v80;
          v39[1] = v78;
        }
        else
        {
          v84 = v37 * *v38;
          v86 = v37 * v38[1];
          v66 = v84 + v38[12];
          v69 = v86 + v38[13];
          v72 = v37 * v38[2] + v38[14];
          v39 = &vertices[v36 + v33 * (width_cells + 1)].x;
          *v39 = v66;
          v40 = v72;
          v39[1] = v69;
        }
        v39[2] = v40;
        v45 = v33 - 1;
        if ( v33 != self->segment_count )
          v45 = v33;
        compute_kind42_attachment_transform(
          self->primary_samples[v45].special_scalar,
          vertices[v36 + v33 * (self->width_cells + 1)].x,
          0.0,
          (int)&v93,
          v88);
        if ( v73 > 168 && v33 != self->segment_count )
        {
          vertices[v36 + v33 * (self->width_cells + 1)].x = v93.position.x;
          vertices[v36 + v33 * (self->width_cells + 1)].y = v93.position.y;
        }
        width_cells = self->width_cells;
        v34 = v73;
        ++v36;
        j = width_cells;
      }
      ++v33;
      v34 += 168;
      v73 = v34;
    }
    while ( v33 <= (signed int)self->segment_count );
  }
  for ( k = 0; k < (signed int)self->segment_count; ++k )
  {
    v47 = 0;
    v57 = 0;
    if ( (int)self->width_cells > 0 )
    {
      v74 = (double)(k % 8) * 0.125;
      v63 = (double)(k % 8 + 1) * 0.125;
      do
      {
        v48 = 0;
        v60 = v47 + 1;
        v82 = 0;
        v58 = (double)v57 * 0.125;
        v81 = (double)(v47 + 1) * 0.125;
        while ( 1 )
        {
          v49 = &facequads[2 * v47 + 2 * k * self->width_cells + v48];
          v49->flags = 0;
          if ( v48 )
          {
            v49->vertex_index_a = k * (LOWORD(self->width_cells) + 1) + v47 + 1;
            v49->vertex_index_b = v47 + k * (LOWORD(self->width_cells) + 1);
            v49->vertex_index_c = v47 + (k + 1) * (LOWORD(self->width_cells) + 1);
            v49->vertex_index_d = (k + 1) * (LOWORD(self->width_cells) + 1) + v47 + 1;
            v49->texture_ref = get_or_create_texture_ref(dword_4B7790, v95, 0, 0);
            v49->u0 = v81;
            v49->v0 = v74;
            v49->u1 = v58;
            v49->v1 = v74;
            v49->u2 = v58;
            v49->v2 = v63;
            v49->u3 = v81;
          }
          else
          {
            v49->vertex_index_a = v47 + k * (LOWORD(self->width_cells) + 1);
            v49->vertex_index_b = k * (LOWORD(self->width_cells) + 1) + v47 + 1;
            v49->vertex_index_c = (k + 1) * (LOWORD(self->width_cells) + 1) + v47 + 1;
            v49->vertex_index_d = v47 + (k + 1) * (LOWORD(self->width_cells) + 1);
            v49->texture_ref = get_or_create_texture_ref(dword_4B7790, v94, 0, 0);
            v49->u0 = v58;
            v49->v0 = v74;
            v49->u1 = v81;
            v49->v1 = v74;
            v49->u2 = v81;
            v49->v2 = v63;
            v49->u3 = v58;
          }
          v49->v3 = v63;
          if ( ++v82 >= 2 )
            break;
          v48 = v82;
        }
        ++v47;
        v57 = v60;
      }
      while ( v60 < (signed int)self->width_cells );
    }
  }
  return finalize_path_template_record(self);
}

