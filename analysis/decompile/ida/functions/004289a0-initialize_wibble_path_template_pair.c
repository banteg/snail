/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_wibble_path_template_pair @ 0x4289a0 */
/* selector: initialize_wibble_path_template_pair */

// Builds the Wibble attachment path-template pair; iOS Path.o names this `cRPath::BuildWibble(float, int, bool, char*, char*)`.
void __thiscall initialize_wibble_path_template_pair(
        cRPath *self,
        float radius,
        int32_t width_cells_,
        bool side_exit,
        char *texture_a,
        char *texture_b,
        char *vertical_texture)
{
  double width_cells; // st7
  PathTemplateSample *primary_samples; // ecx
  int v10; // ebx
  int v11; // edi
  double v12; // st7
  float v13; // esi
  Vec3 *p_basis_up; // edx
  PathTemplateSample *v15; // ecx
  float *p_x; // eax
  double v17; // st7
  PathTemplateSample *v18; // ecx
  double v19; // st7
  double v20; // st6
  Vec3 *p_position; // eax
  signed int v22; // edi
  int v23; // esi
  PathTemplateSample *v24; // ecx
  float *v25; // eax
  double v26; // st7
  PathTemplateSample *secondary_samples; // edx
  float *v28; // eax
  double v29; // st7
  Vec3 *p_delta_dir_to_next; // ecx
  Vec3 *v31; // eax
  Object *object; // eax
  Vec3 *vertices; // edi
  signed int v34; // edx
  int v35; // ebx
  signed int v36; // ecx
  char *v37; // esi
  double v38; // st7
  PathTemplateSample *v39; // eax
  float *v40; // eax
  float v41; // ecx
  double v42; // st7
  signed int j; // ebx
  int v44; // esi
  int v45; // ecx
  ObjectFaceQuad *v46; // edi
  float v47; // [esp+0h] [ebp-68h]
  float v48; // [esp+0h] [ebp-68h]
  float v49; // [esp+14h] [ebp-54h]
  float v50; // [esp+18h] [ebp-50h]
  int i; // [esp+1Ch] [ebp-4Ch]
  float v52; // [esp+1Ch] [ebp-4Ch]
  int v53; // [esp+20h] [ebp-48h]
  ObjectFaceQuad *facequads; // [esp+24h] [ebp-44h]
  float v55; // [esp+28h] [ebp-40h]
  float v56; // [esp+28h] [ebp-40h]
  float v57; // [esp+28h] [ebp-40h]
  Vec3 *v58; // [esp+28h] [ebp-40h]
  signed int v59; // [esp+28h] [ebp-40h]
  float v60; // [esp+2Ch] [ebp-3Ch]
  float v61; // [esp+2Ch] [ebp-3Ch]
  float v62; // [esp+2Ch] [ebp-3Ch]
  float v63; // [esp+30h] [ebp-38h]
  float v64; // [esp+30h] [ebp-38h]
  float v65; // [esp+34h] [ebp-34h]
  float v66; // [esp+34h] [ebp-34h]
  float v67; // [esp+38h] [ebp-30h]
  float v68; // [esp+38h] [ebp-30h]
  float v69; // [esp+38h] [ebp-30h]
  float v70; // [esp+3Ch] [ebp-2Ch]
  float v71; // [esp+3Ch] [ebp-2Ch]
  float v72; // [esp+3Ch] [ebp-2Ch]
  float v73; // [esp+40h] [ebp-28h]
  float v74; // [esp+40h] [ebp-28h]
  float v75; // [esp+40h] [ebp-28h]
  float v76; // [esp+44h] [ebp-24h]
  float v77; // [esp+48h] [ebp-20h]
  float v78; // [esp+48h] [ebp-20h]
  float v79; // [esp+4Ch] [ebp-1Ch]
  float v80; // [esp+50h] [ebp-18h]
  float v81; // [esp+54h] [ebp-14h]
  float v82; // [esp+64h] [ebp-4h]
  char *texture_aa; // [esp+70h] [ebp+8h]
  char *texture_ab; // [esp+70h] [ebp+8h]
  char *texture_ac; // [esp+70h] [ebp+8h]
  float texture_ad; // [esp+70h] [ebp+8h]

  self->kind = PATH_TEMPLATE_KIND_WIBBLE;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = width_cells_;
  self->width_or_scale = 1.0;
  self->segment_count = 32;
  self->segment_count_f = 32.0;
  get_path_nodes(self);
  width_cells = (double)(int)self->width_cells;
  primary_samples = self->primary_samples;
  self->has_entry_mesh_transition = 0;
  primary_samples->center_x = width_cells * 0.5 - 4.0;
  self->primary_samples->rotation_scalar_98 = 0.0;
  self->primary_samples->rotation_scalar_94 = 0.0;
  self->primary_samples->special_scalar = 0.0;
  self->primary_samples->lateral_scale = 1.0;
  set_matrix_identity(&self->primary_samples->transform);
  self->primary_samples->transform.position.x = self->primary_samples->center_x;
  self->primary_samples->transform.position.y = 0.0;
  self->primary_samples->transform.position.z = 0.0;
  self->primary_samples->delta_length = 1.0;
  set_matrix_identity(&self->secondary_samples->transform);
  self->secondary_samples->transform.position.x = self->primary_samples->center_x;
  self->secondary_samples->transform.position.y = 0.49000001;
  self->secondary_samples->transform.position.z = 0.0;
  self->secondary_samples->delta_length = 1.0;
  self->primary_samples[31].center_x = 4.0 - (double)(int)self->width_cells * 0.5;
  self->primary_samples[31].rotation_scalar_98 = 0.0;
  self->primary_samples[31].rotation_scalar_94 = 0.0;
  self->primary_samples[31].special_scalar = 0.0;
  self->primary_samples[31].lateral_scale = 1.0;
  set_matrix_identity(&self->primary_samples[31].transform);
  self->primary_samples[31].transform.position.x = self->primary_samples[31].center_x;
  self->primary_samples[31].transform.position.y = 0.0;
  self->primary_samples[31].transform.position.z = 31.0;
  self->primary_samples[31].delta_length = 1.0;
  set_matrix_identity(&self->secondary_samples[31].transform);
  self->secondary_samples[31].transform.position.x = self->primary_samples[31].center_x;
  self->secondary_samples[31].transform.position.y = 0.49000001;
  self->secondary_samples[31].transform.position.z = 31.0;
  v10 = 1;
  self->secondary_samples[31].delta_length = 1.0;
  v11 = 0;
  texture_aa = nullptr;
  do
  {
    v12 = (double)(int)texture_aa;
    v55 = v12 * 0.20943952;
    self->primary_samples[v10].center_x = (self->primary_samples[31].center_x - self->primary_samples->center_x)
                                        * v12
                                        * 0.033333335
                                        + self->primary_samples->center_x;
    self->primary_samples[v10].rotation_scalar_98 = 0.0;
    self->primary_samples[v10].rotation_scalar_94 = 0.0;
    self->primary_samples[v10].special_scalar = 0.0;
    self->primary_samples[v10].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v10].transform);
    texture_aa = (char *)(v11 + 1);
    self->primary_samples[v10].transform.position.x = 0.0;
    self->primary_samples[v10].transform.position.z = (float)(v11 + 1);
    self->primary_samples[v10].transform.position.y = 0.0;
    v56 = v55 * 3.0;
    v13 = v56;
    v47 = sine(v56) * 0.30000001;
    v57 = cosine(v47);
    v48 = sine(v13) * 0.30000001;
    v60 = sine(v48);
    p_basis_up = &self->primary_samples[v10].transform.basis_up;
    p_basis_up->x = v60;
    p_basis_up->y = v57;
    p_basis_up->z = 0.0;
    v15 = self->primary_samples;
    p_x = &v15[v10].transform.basis_forward.x;
    v67 = v15[v10].transform.position.x - v15[v10 - 1].transform.position.x;
    v70 = v15[v10].transform.position.y - v15[v10 - 1].transform.position.y;
    v17 = v15[v10].transform.position.z - v15[v10 - 1].transform.position.z;
    *p_x = v67;
    p_x[1] = v70;
    v73 = v17;
    p_x[2] = v73;
    normalize_vector(&self->primary_samples[v10].transform.basis_forward);
    cross_vectors(
      &self->primary_samples[v10].transform.basis_right,
      &self->primary_samples[v10].transform.basis_up,
      &self->primary_samples[v10].transform.basis_forward);
    qmemcpy(&self->secondary_samples[v10], &self->primary_samples[v10], 0x40u);
    v18 = self->primary_samples;
    ++v11;
    v19 = v18[v10].transform.basis_up.x * 0.49000001;
    v77 = v18[v10].transform.basis_up.y * 0.49000001;
    v20 = v18[v10].transform.basis_up.z * 0.49000001;
    p_position = &self->secondary_samples[v10++].transform.position;
    v79 = v20;
    p_position->x = v19 + p_position->x;
    p_position->y = v77 + p_position->y;
    p_position->z = v79 + p_position->z;
  }
  while ( v10 < 31 );
  v22 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v23 = 0;
    do
    {
      v24 = self->primary_samples;
      v25 = &v24[v23].delta_dir_to_next.x;
      v68 = v24[v23 + 1].transform.position.x - v24[v23].transform.position.x;
      v71 = v24[v23 + 1].transform.position.y - v24[v23].transform.position.y;
      v26 = v24[v23 + 1].transform.position.z - v24[v23].transform.position.z;
      *v25 = v68;
      v25[1] = v71;
      v74 = v26;
      v25[2] = v74;
      self->primary_samples[v23].delta_length = normalize_vector(&self->primary_samples[v23].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v28 = &secondary_samples[v23].delta_dir_to_next.x;
      v61 = secondary_samples[v23 + 1].transform.position.x - secondary_samples[v23].transform.position.x;
      v63 = secondary_samples[v23 + 1].transform.position.y - secondary_samples[v23].transform.position.y;
      v29 = secondary_samples[v23 + 1].transform.position.z - secondary_samples[v23].transform.position.z;
      *v28 = v61;
      v28[1] = v63;
      v65 = v29;
      v28[2] = v65;
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
  vertices = object->vertices;
  facequads = object->facequads;
  v34 = 0;
  v58 = vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v35 = 0;
    do
    {
      v36 = self->width_cells;
      v37 = nullptr;
      texture_ab = nullptr;
      for ( i = v36; (int)v37 <= v36; texture_ab = v37 )
      {
        v38 = (double)(int)texture_ab - (double)i * 0.5;
        v39 = &self->primary_samples[v35];
        if ( v34 == self->segment_count )
        {
          vertices = v58;
          v80 = v38 * v39[-1].transform.basis_right.x;
          v81 = v38 * v39[-1].transform.basis_right.y;
          v42 = v38 * v39[-1].transform.basis_right.z;
          v82 = v39[-1].transform.position.z + 1.0;
          v62 = v39[-1].transform.position.x + v80;
          v64 = v39[-1].transform.position.y + v81;
          v40 = &v58[(_DWORD)&v37[v34 * (v36 + 1)]].x;
          *v40 = v62;
          v66 = v82 + v42;
          v40[1] = v64;
          v41 = v66;
        }
        else
        {
          v76 = v38 * v39->transform.basis_right.x;
          v78 = v38 * v39->transform.basis_right.y;
          v69 = v76 + v39->transform.position.x;
          v72 = v78 + v39->transform.position.y;
          v75 = v38 * v39->transform.basis_right.z + v39->transform.position.z;
          v40 = &vertices[(_DWORD)&v37[v34 * (v36 + 1)]].x;
          *v40 = v69;
          v40[1] = v72;
          v41 = v75;
        }
        v40[2] = v41;
        v36 = self->width_cells;
        ++v37;
        i = v36;
      }
      ++v34;
      ++v35;
    }
    while ( v34 <= (signed int)self->segment_count );
  }
  for ( j = 0; j < (signed int)self->segment_count; ++j )
  {
    v44 = 0;
    texture_ac = nullptr;
    if ( (int)self->width_cells > 0 )
    {
      v49 = (double)(j % 8) * 0.125;
      v52 = (double)(j % 8 + 1) * 0.125;
      do
      {
        v45 = 0;
        v59 = v44 + 1;
        v53 = 0;
        texture_ad = (double)(int)texture_ac * 0.125;
        v50 = (double)(v44 + 1) * 0.125;
        while ( 1 )
        {
          v46 = &facequads[2 * v44 + 2 * j * self->width_cells + v45];
          v46->header_word = 0;
          if ( v45 != 0 )
          {
            v46->vertex_0 = j * (LOWORD(self->width_cells) + 1) + v44 + 1;
            v46->vertex_1 = v44 + j * (LOWORD(self->width_cells) + 1);
            v46->vertex_2 = v44 + (j + 1) * (LOWORD(self->width_cells) + 1);
            v46->vertex_3 = (j + 1) * (LOWORD(self->width_cells) + 1) + v44 + 1;
            v46->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_b, nullptr, 0);
            v46->uv[0].u = v50;
            v46->uv[0].v = v49;
            v46->uv[1].u = texture_ad;
            v46->uv[1].v = v49;
            v46->uv[2].u = texture_ad;
            v46->uv[2].v = v52;
            v46->uv[3].u = v50;
          }
          else
          {
            v46->vertex_0 = v44 + j * (LOWORD(self->width_cells) + 1);
            v46->vertex_1 = j * (LOWORD(self->width_cells) + 1) + v44 + 1;
            v46->vertex_2 = (j + 1) * (LOWORD(self->width_cells) + 1) + v44 + 1;
            v46->vertex_3 = v44 + (j + 1) * (LOWORD(self->width_cells) + 1);
            v46->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
            v46->uv[0].u = texture_ad;
            v46->uv[0].v = v49;
            v46->uv[1].u = v50;
            v46->uv[1].v = v49;
            v46->uv[2].u = v50;
            v46->uv[2].v = v52;
            v46->uv[3].u = texture_ad;
          }
          v46->uv[3].v = v52;
          if ( ++v53 >= 2 )
            break;
          v45 = v53;
        }
        ++v44;
        texture_ac = (char *)v59;
      }
      while ( v59 < (signed int)self->width_cells );
    }
  }
  calc_path_length_z(self);
}
