/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_dip_path_template_pair @ 0x41e440 */
/* selector: initialize_dip_path_template_pair */

// Builds the Dip attachment path-template pair; iOS Path.o names this `cRPath::BuildDip(float, int, bool, char*, char*)`.
void __thiscall initialize_dip_path_template_pair(
        Path *self,
        float curve_source,
        int32_t width_cells_,
        bool side_exit,
        char *texture_a,
        char *texture_b,
        char *cap_texture)
{
  __int64 v8; // rax
  int v9; // edi
  double v10; // st7
  PathTemplateSample *primary_samples; // ecx
  int v12; // ebx
  int v13; // edi
  PathTemplateSample *v14; // eax
  PathTemplateSample *v15; // edx
  float *p_x; // eax
  double v17; // st7
  PathTemplateSample *v18; // ecx
  PathTemplateSample *v19; // eax
  double v20; // st7
  double v21; // st7
  signed int v22; // ebx
  int v23; // edi
  PathTemplateSample *v24; // eax
  double v25; // st7
  double v26; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *v28; // eax
  double v29; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v31; // ecx
  Object *object; // eax
  signed int v33; // edx
  int v34; // ebx
  signed int width_cells; // ecx
  signed int v36; // edi
  double v37; // st7
  PathTemplateSample *v38; // eax
  float *v39; // ecx
  float *v40; // ecx
  double v41; // st6
  signed int i; // ebx
  int v43; // edi
  int v44; // ecx
  ObjectFaceQuad *v45; // ebp
  float v46; // [esp+0h] [ebp-50h]
  int v47; // [esp+4h] [ebp-4Ch]
  float v48; // [esp+4h] [ebp-4Ch]
  float v49; // [esp+4h] [ebp-4Ch]
  float v50; // [esp+8h] [ebp-48h]
  Vec3 *vertices; // [esp+8h] [ebp-48h]
  int v52; // [esp+8h] [ebp-48h]
  ObjectFaceQuad *facequads; // [esp+Ch] [ebp-44h]
  int v54; // [esp+10h] [ebp-40h]
  float v55; // [esp+10h] [ebp-40h]
  float v56; // [esp+10h] [ebp-40h]
  signed int v57; // [esp+10h] [ebp-40h]
  float v58; // [esp+14h] [ebp-3Ch]
  float v59; // [esp+18h] [ebp-38h]
  float v60; // [esp+20h] [ebp-30h]
  float v61; // [esp+20h] [ebp-30h]
  float v62; // [esp+24h] [ebp-2Ch]
  float v63; // [esp+24h] [ebp-2Ch]
  float v64; // [esp+28h] [ebp-28h]
  float v65; // [esp+2Ch] [ebp-24h]
  float v66; // [esp+2Ch] [ebp-24h]
  float v67; // [esp+30h] [ebp-20h]
  float v68; // [esp+30h] [ebp-20h]
  float v69; // [esp+34h] [ebp-1Ch]
  float v70; // [esp+34h] [ebp-1Ch]
  float v71; // [esp+38h] [ebp-18h]
  float v72; // [esp+38h] [ebp-18h]
  float v73; // [esp+38h] [ebp-18h]
  float v74; // [esp+3Ch] [ebp-14h]
  float v75; // [esp+3Ch] [ebp-14h]
  float v76; // [esp+3Ch] [ebp-14h]
  float v77; // [esp+40h] [ebp-10h]
  float v78; // [esp+40h] [ebp-10h]
  float v79; // [esp+40h] [ebp-10h]
  float v80; // [esp+4Ch] [ebp-4h]
  float arg2; // [esp+54h] [ebp+4h]
  int32_t arg2a; // [esp+54h] [ebp+4h]
  int32_t arg2b; // [esp+54h] [ebp+4h]
  float arg2c; // [esp+54h] [ebp+4h]
  int32_t arg3; // [esp+58h] [ebp+8h]
  int32_t arg3a; // [esp+58h] [ebp+8h]
  float arg3b; // [esp+58h] [ebp+8h]

  self->kind = PATH_TEMPLATE_KIND_DIP;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = width_cells_;
  v8 = (__int64)(curve_source * 5.0);
  v9 = v8 + 1;
  arg3 = v8;
  self->width_or_scale = 1.0;
  self->segment_count = v8 + 2;
  self->segment_count_f = (float)(v8 + 2);
  v10 = (double)(int)v8;
  v50 = v10;
  arg2 = v10 * 0.047746483;
  get_path_nodes(self);
  primary_samples = self->primary_samples;
  self->has_entry_mesh_transition = 0;
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
  v54 = v9;
  self->secondary_samples->transform.position.x = self->primary_samples->center_x;
  self->secondary_samples->transform.position.y = 0.49000001;
  self->secondary_samples->transform.position.z = 0.0;
  v9 *= 168;
  *(float *)((char *)&self->primary_samples->center_x + v9) = 0.0;
  *(float *)((char *)&self->primary_samples->rotation_scalar_98 + v9) = 0.0;
  *(float *)((char *)&self->primary_samples->rotation_scalar_94 + v9) = 0.0;
  *(float *)((char *)&self->primary_samples->special_scalar + v9) = 0.0;
  *(float *)((char *)&self->primary_samples->lateral_scale + v9) = 1.0;
  set_matrix_identity((TransformMatrix *)((char *)&self->primary_samples->transform + v9));
  *(float *)((char *)&self->primary_samples->transform.position.x + v9) = *(float *)((char *)&self->primary_samples->center_x
                                                                                   + v9);
  v55 = (float)v54;
  *(float *)((char *)&self->primary_samples->transform.position.y + v9) = 0.0;
  *(float *)((char *)&self->primary_samples->transform.position.z + v9) = v55;
  set_matrix_identity((TransformMatrix *)((char *)&self->secondary_samples->transform + v9));
  v12 = 0;
  *(float *)((char *)&self->secondary_samples->transform.position.x + v9) = *(float *)((char *)&self->primary_samples->center_x
                                                                                     + v9);
  v47 = 0;
  *(float *)((char *)&self->secondary_samples->transform.position.y + v9) = 0.49000001;
  *(float *)((char *)&self->secondary_samples->transform.position.z + v9) = v55;
  if ( arg3 > 0 )
  {
    v13 = 1;
    do
    {
      self->primary_samples[v13].center_x = 0.0;
      self->primary_samples[v13].rotation_scalar_98 = 0.0;
      self->primary_samples[v13].rotation_scalar_94 = 0.0;
      self->primary_samples[v13].special_scalar = 0.0;
      self->primary_samples[v13].lateral_scale = 1.0;
      v48 = (double)v47 * 6.2831855 / v50;
      set_matrix_identity(&self->primary_samples[v13].transform);
      self->primary_samples[v13].transform.position.x = self->primary_samples[v13].center_x;
      ++v12;
      self->primary_samples[v13].transform.position.y = -((1.0 - cosine(v48)) * arg2);
      v56 = (float)v12;
      self->primary_samples[v13].transform.position.z = v56;
      set_matrix_identity(&self->secondary_samples[v13].transform);
      self->secondary_samples[v13].transform.position.x = self->primary_samples[v13].center_x;
      self->secondary_samples[v13].transform.position.y = 0.49000001 - (1.0 - cosine(v48)) * arg2;
      self->secondary_samples[v13].transform.position.z = v56;
      if ( v13 <= 1 )
      {
        set_matrix_rotation_identity(&self->primary_samples[v13 - 1].transform);
        set_matrix_rotation_identity(&self->secondary_samples[v13 - 1].transform);
      }
      else
      {
        v14 = &self->primary_samples[v13 - 1];
        v14->transform.basis_right.x = 1.0;
        v14->transform.basis_right.y = 0.0;
        v14->transform.basis_right.z = 0.0;
        v15 = self->primary_samples;
        p_x = &v15[v13 - 1].transform.basis_forward.x;
        v60 = v15[v13].transform.position.x - v15[v13 - 1].transform.position.x;
        v62 = p_x[47] - p_x[5];
        v17 = p_x[48] - p_x[6];
        *p_x = v60;
        p_x[1] = v62;
        v64 = v17;
        p_x[2] = v64;
        normalize_vector(&self->primary_samples[v13 - 1].transform.basis_forward);
        cross_vectors(
          &self->primary_samples[v13 - 1].transform.basis_up,
          &self->primary_samples[v13 - 1].transform.basis_forward,
          &self->primary_samples[v13 - 1].transform.basis_right);
        v18 = &self->secondary_samples[v13 - 1];
        v18->transform.basis_right.x = 1.0;
        v18->transform.basis_right.y = 0.0;
        v18->transform.basis_right.z = 0.0;
        v19 = &self->secondary_samples[v13];
        v20 = v19->transform.position.x - v19[-1].transform.position.x;
        v19 = (PathTemplateSample *)((char *)v19 - 136);
        v71 = v20;
        v74 = v19[1].transform.basis_up.y - v19->transform.basis_up.y;
        v21 = v19[1].transform.basis_up.z - v19->transform.basis_up.z;
        v19->transform.basis_right.x = v71;
        v19->transform.basis_right.y = v74;
        v77 = v21;
        v19->transform.basis_right.z = v77;
        normalize_vector(&self->secondary_samples[v13 - 1].transform.basis_forward);
        cross_vectors(
          &self->secondary_samples[v13 - 1].transform.basis_up,
          &self->secondary_samples[v13 - 1].transform.basis_forward,
          &self->secondary_samples[v13 - 1].transform.basis_right);
      }
      ++v13;
      v47 = v12;
    }
    while ( v12 < arg3 );
  }
  v22 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v23 = 0;
    do
    {
      v24 = &self->primary_samples[v23];
      v25 = v24[1].transform.position.x - v24->transform.position.x;
      v24 = (PathTemplateSample *)((char *)v24 + 128);
      v72 = v25;
      v75 = v24->inverse_matrix.basis_up_w - v24[-1].inverse_matrix.basis_up_w;
      v26 = v24->inverse_matrix.basis_forward.x - v24[-1].inverse_matrix.basis_forward.x;
      v24->transform.basis_right.x = v72;
      v24->transform.basis_right.y = v75;
      v78 = v26;
      v24->transform.basis_right.z = v78;
      self->primary_samples[v23].delta_length = normalize_vector(&self->primary_samples[v23].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v28 = &secondary_samples[v23].delta_dir_to_next.x;
      v65 = secondary_samples[v23 + 1].transform.position.x - secondary_samples[v23].transform.position.x;
      v67 = secondary_samples[v23 + 1].transform.position.y - secondary_samples[v23].transform.position.y;
      v29 = secondary_samples[v23 + 1].transform.position.z - secondary_samples[v23].transform.position.z;
      *v28 = v65;
      v28[1] = v67;
      v69 = v29;
      v28[2] = v69;
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
  facequads = object->facequads;
  v33 = 0;
  vertices = object->vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v34 = 0;
    do
    {
      width_cells = self->width_cells;
      v36 = 0;
      arg2a = 0;
      for ( arg3a = width_cells; v36 <= width_cells; arg3a = width_cells )
      {
        v37 = (double)arg2a - (double)arg3a * 0.5;
        v38 = &self->primary_samples[v34];
        if ( v33 == self->segment_count )
        {
          v58 = v37 * v38[-1].transform.basis_right.x;
          v59 = v37 * v38[-1].transform.basis_right.y;
          v80 = v38[-1].transform.position.z + 1.0;
          v66 = v38[-1].transform.position.x + v58;
          v68 = v38[-1].transform.position.y + v59;
          v40 = &vertices[v36 + v33 * (width_cells + 1)].x;
          v41 = v80 + v37 * v38[-1].transform.basis_right.z;
          *v40 = v66;
          v40[1] = v68;
          v70 = v41;
          v40[2] = v70;
        }
        else
        {
          v61 = v37 * v38->transform.basis_right.x;
          v63 = v37 * v38->transform.basis_right.y;
          v73 = v61 + v38->transform.position.x;
          v76 = v63 + v38->transform.position.y;
          v79 = v37 * v38->transform.basis_right.z + v38->transform.position.z;
          v39 = &vertices[v36 + v33 * (width_cells + 1)].x;
          *v39 = v73;
          v39[1] = v76;
          v39[2] = v79;
        }
        width_cells = self->width_cells;
        arg2a = ++v36;
      }
      ++v33;
      ++v34;
    }
    while ( v33 <= (signed int)self->segment_count );
  }
  for ( i = 0; i < (signed int)self->segment_count; ++i )
  {
    v43 = 0;
    arg2b = 0;
    if ( (int)self->width_cells > 0 )
    {
      arg3b = (double)(i % 8) * 0.125;
      v49 = (double)(i % 8 + 1) * 0.125;
      do
      {
        v44 = 0;
        v57 = v43 + 1;
        v52 = 0;
        arg2c = (double)arg2b * 0.125;
        v46 = (double)(v43 + 1) * 0.125;
        while ( 1 )
        {
          v45 = &facequads[2 * v43 + 2 * i * self->width_cells + v44];
          v45->header_word = 0;
          if ( v44 != 0 )
          {
            v45->vertex_0 = i * (LOWORD(self->width_cells) + 1) + v43 + 1;
            v45->vertex_1 = v43 + i * (LOWORD(self->width_cells) + 1);
            v45->vertex_2 = v43 + (i + 1) * (LOWORD(self->width_cells) + 1);
            v45->vertex_3 = (i + 1) * (LOWORD(self->width_cells) + 1) + v43 + 1;
            v45->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_b, nullptr, 0);
            v45->uv[0].u = v46;
            v45->uv[0].v = arg3b;
            v45->uv[1].u = arg2c;
            v45->uv[1].v = arg3b;
            v45->uv[2].u = arg2c;
            v45->uv[2].v = v49;
            v45->uv[3].u = v46;
          }
          else
          {
            v45->vertex_0 = v43 + i * (LOWORD(self->width_cells) + 1);
            v45->vertex_1 = i * (LOWORD(self->width_cells) + 1) + v43 + 1;
            v45->vertex_2 = (i + 1) * (LOWORD(self->width_cells) + 1) + v43 + 1;
            v45->vertex_3 = v43 + (i + 1) * (LOWORD(self->width_cells) + 1);
            v45->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
            v45->uv[0].u = arg2c;
            v45->uv[0].v = arg3b;
            v45->uv[1].u = v46;
            v45->uv[1].v = arg3b;
            v45->uv[2].u = v46;
            v45->uv[2].v = v49;
            v45->uv[3].u = arg2c;
          }
          v45->uv[3].v = v49;
          if ( ++v52 >= 2 )
            break;
          v44 = v52;
        }
        ++v43;
        arg2b = v57;
      }
      while ( v57 < (signed int)self->width_cells );
    }
  }
  calc_path_length_z(self);
}
