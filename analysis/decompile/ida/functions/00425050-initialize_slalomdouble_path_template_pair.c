/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_slalomdouble_path_template_pair @ 0x425050 */
/* selector: initialize_slalomdouble_path_template_pair */

// Builds the SlalomDouble attachment path-template pair; iOS Path.o names this `cRPath::BuildSlalomDouble(int, int, bool, char*, char*)`.
void __thiscall initialize_slalomdouble_path_template_pair(
        cRPath *self,
        int32_t curve_segments,
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
  double v15; // st7
  Vec3 *p_basis_up; // ecx
  PathTemplateSample *v17; // eax
  double v18; // st7
  double v19; // st7
  PathTemplateSample *v20; // eax
  Vec3 *v21; // edx
  PathTemplateSample *secondary_samples; // ecx
  float *p_x; // eax
  double v24; // st7
  signed int v25; // ebp
  int v26; // edi
  PathTemplateSample *primary_samples; // ecx
  float *v28; // eax
  double v29; // st7
  PathTemplateSample *v30; // edx
  float *v31; // eax
  double v32; // st7
  Vec3 *p_delta_dir_to_next; // ecx
  Vec3 *v34; // eax
  Object *object; // eax
  Vec3 *vertices; // ebp
  signed int v37; // edx
  signed int width_cells; // ecx
  char *v39; // edi
  double v40; // st7
  float *v41; // eax
  float *v42; // eax
  float v43; // ecx
  double v44; // st7
  int v45; // ebp
  int v46; // ecx
  ObjectFaceQuad *v47; // edi
  float angle; // [esp+0h] [ebp-68h]
  float anglea; // [esp+0h] [ebp-68h]
  float angleb; // [esp+0h] [ebp-68h]
  float v51; // [esp+14h] [ebp-54h]
  float v52; // [esp+18h] [ebp-50h]
  float v53; // [esp+1Ch] [ebp-4Ch]
  int j; // [esp+1Ch] [ebp-4Ch]
  float v55; // [esp+1Ch] [ebp-4Ch]
  float v56; // [esp+20h] [ebp-48h]
  int v57; // [esp+20h] [ebp-48h]
  float v58; // [esp+24h] [ebp-44h]
  Vec3 *v59; // [esp+24h] [ebp-44h]
  signed int v60; // [esp+24h] [ebp-44h]
  ObjectFaceQuad *facequads; // [esp+28h] [ebp-40h]
  float v62; // [esp+2Ch] [ebp-3Ch]
  float v63; // [esp+30h] [ebp-38h]
  float v64; // [esp+38h] [ebp-30h]
  float v65; // [esp+38h] [ebp-30h]
  float v66; // [esp+3Ch] [ebp-2Ch]
  float v67; // [esp+3Ch] [ebp-2Ch]
  float v68; // [esp+40h] [ebp-28h]
  float v69; // [esp+44h] [ebp-24h]
  float v70; // [esp+44h] [ebp-24h]
  float v71; // [esp+48h] [ebp-20h]
  float v72; // [esp+48h] [ebp-20h]
  float v73; // [esp+4Ch] [ebp-1Ch]
  float v74; // [esp+4Ch] [ebp-1Ch]
  float v75; // [esp+50h] [ebp-18h]
  float v76; // [esp+50h] [ebp-18h]
  float v77; // [esp+50h] [ebp-18h]
  float v78; // [esp+54h] [ebp-14h]
  float v79; // [esp+54h] [ebp-14h]
  float v80; // [esp+54h] [ebp-14h]
  float v81; // [esp+58h] [ebp-10h]
  float v82; // [esp+58h] [ebp-10h]
  float v83; // [esp+58h] [ebp-10h]
  float v84; // [esp+64h] [ebp-4h]
  char *texture_aa; // [esp+70h] [ebp+8h]
  int texture_ab; // [esp+70h] [ebp+8h]
  float texture_ag; // [esp+70h] [ebp+8h]
  char *texture_ac; // [esp+70h] [ebp+8h]
  float texture_ah; // [esp+70h] [ebp+8h]
  float texture_ai; // [esp+70h] [ebp+8h]
  char *texture_ad; // [esp+70h] [ebp+8h]
  char *texture_ae; // [esp+70h] [ebp+8h]
  float texture_af; // [esp+70h] [ebp+8h]

  v8 = 0;
  self->kind = PATH_TEMPLATE_KIND_SLALOMDOUBLE;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = width_cells_;
  self->width_or_scale = 1.0;
  self->segment_count = 70;
  self->segment_count_f = 70.0;
  get_path_nodes(self);
  self->has_entry_mesh_transition = 0;
  texture_aa = nullptr;
  for ( i = 0; i < 4; ++i )
  {
    self->primary_samples[i].center_x = 0.0;
    self->primary_samples[i].rotation_scalar_98 = 0.0;
    self->primary_samples[i].rotation_scalar_94 = 0.0;
    self->primary_samples[i].special_scalar = 0.0;
    self->primary_samples[i].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[i].transform);
    self->primary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    v58 = (float)(int)texture_aa;
    self->primary_samples[i].transform.position.y = 0.0;
    self->primary_samples[i].transform.position.z = v58;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->secondary_samples[i].transform.position.y = 0.49000001;
    self->secondary_samples[i].transform.position.z = v58;
    ++texture_aa;
  }
  v10 = 66;
  v11 = 66;
  texture_ab = 66;
  do
  {
    self->primary_samples[v11].center_x = 0.0;
    self->primary_samples[v11].rotation_scalar_98 = 0.0;
    self->primary_samples[v11].rotation_scalar_94 = 0.0;
    self->primary_samples[v11].special_scalar = 0.0;
    self->primary_samples[v11].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v11].transform);
    texture_ag = (float)texture_ab;
    self->primary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
    self->primary_samples[v11].transform.position.y = 0.0;
    self->primary_samples[v11].transform.position.z = texture_ag;
    set_matrix_identity(&self->secondary_samples[v11].transform);
    self->secondary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
    self->secondary_samples[v11].transform.position.y = 0.49000001;
    self->secondary_samples[v11++].transform.position.z = texture_ag;
    texture_ab = ++v10;
  }
  while ( v10 - 66 < 4 );
  v12 = 0;
  v13 = 4;
  texture_ac = nullptr;
  do
  {
    v14 = (double)(int)texture_ac * 0.016129032;
    v53 = v14 * 12.566371;
    v15 = v14 - 0.5;
    if ( v15 >= 0.0 )
      v56 = v15;
    else
      v56 = -v15;
    if ( v15 < 0.0 )
      v15 = -v15;
    texture_ah = v15;
    self->primary_samples[v13].center_x = sine(v53) * (1.0 - texture_ah) * (1.0 - v56) * 4.4444447;
    self->primary_samples[v13].rotation_scalar_98 = 0.0;
    self->primary_samples[v13].rotation_scalar_94 = 0.0;
    self->primary_samples[v13].special_scalar = 0.0;
    self->primary_samples[v13].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v13].transform);
    self->primary_samples[v13].transform.position.x = self->primary_samples[v13].center_x;
    angle = v53 * 0.5;
    self->primary_samples[v13].transform.position.y = 1.0 - cosine(angle);
    texture_ai = (float)(v12 + 4);
    self->primary_samples[v13].transform.position.z = texture_ai;
    set_matrix_identity(&self->secondary_samples[v13].transform);
    self->secondary_samples[v13].transform.position.x = self->primary_samples[v13].center_x;
    self->secondary_samples[v13].transform.position.y = self->primary_samples[v13].transform.position.y + 0.49000001;
    self->secondary_samples[v13].transform.position.z = texture_ai;
    if ( v13 <= 4 )
    {
      set_matrix_rotation_identity(&self->primary_samples[v13 - 1].transform);
      set_matrix_rotation_identity(&self->secondary_samples[v13 - 1].transform);
    }
    else
    {
      p_basis_up = &self->primary_samples[v13 - 1].transform.basis_up;
      p_basis_up->x = 0.0;
      p_basis_up->y = 1.0;
      p_basis_up->z = 0.0;
      v17 = &self->primary_samples[v13];
      v18 = v17->transform.position.x - v17[-1].transform.position.x;
      v17 = (PathTemplateSample *)((char *)v17 - 136);
      v64 = v18;
      v66 = v17[1].transform.basis_up.y - v17->transform.basis_up.y;
      v19 = v17[1].transform.basis_up.z - v17->transform.basis_up.z;
      v17->transform.basis_right.x = v64;
      v17->transform.basis_right.y = v66;
      v68 = v19;
      v17->transform.basis_right.z = v68;
      normalize_vector(&self->primary_samples[v13 - 1].transform.basis_forward);
      cross_vectors(
        &self->primary_samples[v13 - 1].transform.basis_right,
        &self->primary_samples[v13 - 1].transform.basis_up,
        &self->primary_samples[v13 - 1].transform.basis_forward);
      v20 = &self->primary_samples[v13];
      anglea = v20[-1].center_x * 0.2617994;
      rotate_matrix_local_z(&v20[-1].transform, anglea);
      v21 = &self->secondary_samples[v13 - 1].transform.basis_up;
      v21->x = 0.0;
      v21->y = 1.0;
      v21->z = 0.0;
      secondary_samples = self->secondary_samples;
      p_x = &secondary_samples[v13 - 1].transform.basis_forward.x;
      v75 = secondary_samples[v13].transform.position.x - secondary_samples[v13 - 1].transform.position.x;
      v78 = p_x[47] - p_x[5];
      v24 = p_x[48] - p_x[6];
      *p_x = v75;
      p_x[1] = v78;
      v81 = v24;
      p_x[2] = v81;
      normalize_vector(&self->secondary_samples[v13 - 1].transform.basis_forward);
      cross_vectors(
        &self->secondary_samples[v13 - 1].transform.basis_right,
        &self->secondary_samples[v13 - 1].transform.basis_up,
        &self->secondary_samples[v13 - 1].transform.basis_forward);
      angleb = self->primary_samples[v13 - 1].center_x * 0.2617994;
      rotate_matrix_local_z(&self->secondary_samples[v13 - 1].transform, angleb);
    }
    ++v13;
    texture_ac = (char *)++v12;
  }
  while ( v13 < 66 );
  v25 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v26 = 0;
    do
    {
      primary_samples = self->primary_samples;
      v28 = &primary_samples[v26].delta_dir_to_next.x;
      v76 = primary_samples[v26 + 1].transform.position.x - primary_samples[v26].transform.position.x;
      v79 = primary_samples[v26 + 1].transform.position.y - primary_samples[v26].transform.position.y;
      v29 = primary_samples[v26 + 1].transform.position.z - primary_samples[v26].transform.position.z;
      *v28 = v76;
      v28[1] = v79;
      v82 = v29;
      v28[2] = v82;
      self->primary_samples[v26].delta_length = normalize_vector(&self->primary_samples[v26].delta_dir_to_next);
      v30 = self->secondary_samples;
      v31 = &v30[v26].delta_dir_to_next.x;
      v69 = v30[v26 + 1].transform.position.x - v30[v26].transform.position.x;
      v71 = v30[v26 + 1].transform.position.y - v30[v26].transform.position.y;
      v32 = v30[v26 + 1].transform.position.z - v30[v26].transform.position.z;
      *v31 = v69;
      v31[1] = v71;
      v73 = v32;
      v31[2] = v73;
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
  vertices = object->vertices;
  facequads = object->facequads;
  v37 = 0;
  v59 = vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    do
    {
      width_cells = self->width_cells;
      v39 = nullptr;
      texture_ad = nullptr;
      for ( j = width_cells; (int)v39 <= width_cells; texture_ad = v39 )
      {
        v40 = (double)(int)texture_ad - (double)j * 0.5;
        v41 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v8);
        if ( v37 == self->segment_count )
        {
          vertices = v59;
          v62 = v40 * *(v41 - 42);
          v63 = v40 * *(v41 - 41);
          v44 = v40 * *(v41 - 40);
          v84 = *(v41 - 28) + 1.0;
          v70 = *(v41 - 30) + v62;
          v72 = *(v41 - 29) + v63;
          v42 = &v59[(_DWORD)&v39[v37 * (width_cells + 1)]].x;
          *v42 = v70;
          v74 = v84 + v44;
          v42[1] = v72;
          v43 = v74;
        }
        else
        {
          v65 = v40 * *v41;
          v67 = v40 * v41[1];
          v77 = v65 + v41[12];
          v80 = v67 + v41[13];
          v83 = v40 * v41[2] + v41[14];
          v42 = &vertices[(_DWORD)&v39[v37 * (width_cells + 1)]].x;
          *v42 = v77;
          v42[1] = v80;
          v43 = v83;
        }
        v42[2] = v43;
        width_cells = self->width_cells;
        ++v39;
        j = width_cells;
      }
      ++v37;
      v8 += 168;
    }
    while ( v37 <= (signed int)self->segment_count );
    v8 = 0;
  }
  if ( (int)self->segment_count > 0 )
  {
    do
    {
      v45 = 0;
      texture_ae = nullptr;
      if ( (int)self->width_cells > 0 )
      {
        v51 = (double)(v8 % 8) * 0.125;
        v55 = (double)(v8 % 8 + 1) * 0.125;
        do
        {
          v46 = 0;
          v60 = v45 + 1;
          v57 = 0;
          texture_af = (double)(int)texture_ae * 0.125;
          v52 = (double)(v45 + 1) * 0.125;
          while ( 1 )
          {
            v47 = &facequads[2 * v45 + 2 * v8 * self->width_cells + v46];
            v47->header_word = 0;
            if ( v46 != 0 )
            {
              v47->vertex_0 = v8 * (LOWORD(self->width_cells) + 1) + v45 + 1;
              v47->vertex_1 = v45 + v8 * (LOWORD(self->width_cells) + 1);
              v47->vertex_2 = v45 + (v8 + 1) * (LOWORD(self->width_cells) + 1);
              v47->vertex_3 = (v8 + 1) * (LOWORD(self->width_cells) + 1) + v45 + 1;
              v47->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_b, nullptr, 0);
              v47->uv[0].u = v52;
              v47->uv[0].v = v51;
              v47->uv[1].u = texture_af;
              v47->uv[1].v = v51;
              v47->uv[2].u = texture_af;
              v47->uv[2].v = v55;
              v47->uv[3].u = v52;
            }
            else
            {
              v47->vertex_0 = v45 + v8 * (LOWORD(self->width_cells) + 1);
              v47->vertex_1 = v8 * (LOWORD(self->width_cells) + 1) + v45 + 1;
              v47->vertex_2 = (v8 + 1) * (LOWORD(self->width_cells) + 1) + v45 + 1;
              v47->vertex_3 = v45 + (v8 + 1) * (LOWORD(self->width_cells) + 1);
              v47->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
              v47->uv[0].u = texture_af;
              v47->uv[0].v = v51;
              v47->uv[1].u = v52;
              v47->uv[1].v = v51;
              v47->uv[2].u = v52;
              v47->uv[2].v = v55;
              v47->uv[3].u = texture_af;
            }
            v47->uv[3].v = v55;
            if ( ++v57 >= 2 )
              break;
            v46 = v57;
          }
          ++v45;
          texture_ae = (char *)v60;
        }
        while ( v60 < (signed int)self->width_cells );
      }
      ++v8;
    }
    while ( v8 < (signed int)self->segment_count );
  }
  calc_path_length_z(self);
}
