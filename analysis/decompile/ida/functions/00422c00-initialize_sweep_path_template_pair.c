/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_sweep_path_template_pair @ 0x422c00 */
/* selector: initialize_sweep_path_template_pair */

// Builds the Sweep attachment path-template pair; iOS Path.o names this `cRPath::BuildSweep(float, int, bool, char*, char*)`.
void __thiscall initialize_sweep_path_template_pair(
        cRPath *self,
        float scale_arg,
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
  int j; // edi
  PathTemplateSample *primary_samples; // ebp
  Vec3 *p_basis_up; // ecx
  PathTemplateSample *v15; // eax
  double v16; // st7
  double v17; // st7
  Vec3 *v18; // ecx
  PathTemplateSample *v19; // eax
  double v20; // st7
  double v21; // st7
  signed int v22; // ebp
  int v23; // edi
  PathTemplateSample *v24; // eax
  double v25; // st7
  double v26; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *p_x; // eax
  double v29; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v31; // ecx
  Object *object; // eax
  signed int v33; // edx
  Vec3 *vertices; // ebp
  signed int width_cells; // ecx
  char *v36; // edi
  double v37; // st7
  float *v38; // eax
  float *v39; // eax
  float v40; // ecx
  double v41; // st7
  int v42; // edi
  int v43; // ecx
  ObjectFaceQuad *v44; // ebp
  float v45; // [esp+10h] [ebp-54h]
  float v46; // [esp+14h] [ebp-50h]
  int k; // [esp+18h] [ebp-4Ch]
  float v48; // [esp+18h] [ebp-4Ch]
  float v49; // [esp+1Ch] [ebp-48h]
  int v50; // [esp+1Ch] [ebp-48h]
  ObjectFaceQuad *facequads; // [esp+20h] [ebp-44h]
  float v52; // [esp+24h] [ebp-40h]
  float v53; // [esp+24h] [ebp-40h]
  Vec3 *v54; // [esp+24h] [ebp-40h]
  signed int v55; // [esp+24h] [ebp-40h]
  float v56; // [esp+28h] [ebp-3Ch]
  float v57; // [esp+2Ch] [ebp-38h]
  float v58; // [esp+34h] [ebp-30h]
  float v59; // [esp+34h] [ebp-30h]
  float v60; // [esp+38h] [ebp-2Ch]
  float v61; // [esp+38h] [ebp-2Ch]
  float v62; // [esp+3Ch] [ebp-28h]
  float v63; // [esp+40h] [ebp-24h]
  float v64; // [esp+40h] [ebp-24h]
  float v65; // [esp+44h] [ebp-20h]
  float v66; // [esp+44h] [ebp-20h]
  float v67; // [esp+48h] [ebp-1Ch]
  float v68; // [esp+48h] [ebp-1Ch]
  float v69; // [esp+4Ch] [ebp-18h]
  float v70; // [esp+4Ch] [ebp-18h]
  float v71; // [esp+4Ch] [ebp-18h]
  float v72; // [esp+50h] [ebp-14h]
  float v73; // [esp+50h] [ebp-14h]
  float v74; // [esp+50h] [ebp-14h]
  float v75; // [esp+54h] [ebp-10h]
  float v76; // [esp+54h] [ebp-10h]
  float v77; // [esp+54h] [ebp-10h]
  float v78; // [esp+60h] [ebp-4h]
  char *texture_aa; // [esp+6Ch] [ebp+8h]
  int texture_ab; // [esp+6Ch] [ebp+8h]
  float texture_ag; // [esp+6Ch] [ebp+8h]
  char *texture_ac; // [esp+6Ch] [ebp+8h]
  char *texture_ad; // [esp+6Ch] [ebp+8h]
  char *texture_ae; // [esp+6Ch] [ebp+8h]
  float texture_af; // [esp+6Ch] [ebp+8h]

  v8 = 0;
  self->kind = PATH_TEMPLATE_KIND_SWEEP;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = width_cells_;
  self->width_or_scale = 1.0;
  self->segment_count = 30;
  self->segment_count_f = 30.0;
  get_path_nodes(self);
  self->has_entry_mesh_transition = 0;
  texture_aa = nullptr;
  for ( i = 0; i < 3; ++i )
  {
    self->primary_samples[i].center_x = (double)(int)self->width_cells * 0.5 - 4.0;
    self->primary_samples[i].rotation_scalar_98 = 0.0;
    self->primary_samples[i].rotation_scalar_94 = 0.0;
    self->primary_samples[i].special_scalar = 0.0;
    self->primary_samples[i].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[i].transform);
    self->primary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    v52 = (float)(int)texture_aa;
    self->primary_samples[i].transform.position.y = 0.0;
    self->primary_samples[i].transform.position.z = v52;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->secondary_samples[i].transform.position.y = 0.49000001;
    self->secondary_samples[i].transform.position.z = v52;
    ++texture_aa;
  }
  v10 = 27;
  v11 = 27;
  texture_ab = 27;
  do
  {
    self->primary_samples[v11].center_x = 4.0 - (double)(int)self->width_cells * 0.5;
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
  while ( v10 - 27 < 3 );
  texture_ac = nullptr;
  for ( j = 3; j < 27; ++j )
  {
    primary_samples = self->primary_samples;
    v49 = (double)(int)texture_ac * 0.1308997;
    primary_samples[j].center_x = cosine(v49) * primary_samples->center_x;
    self->primary_samples[j].rotation_scalar_98 = 0.0;
    self->primary_samples[j].rotation_scalar_94 = 0.0;
    self->primary_samples[j].special_scalar = 0.0;
    self->primary_samples[j].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[j].transform);
    self->primary_samples[j].transform.position.x = self->primary_samples[j].center_x;
    self->primary_samples[j].transform.position.y = sine(v49) * -0.30000001;
    v53 = (float)(int)(texture_ac + 3);
    self->primary_samples[j].transform.position.z = v53;
    set_matrix_identity(&self->secondary_samples[j].transform);
    self->secondary_samples[j].transform.position.x = self->primary_samples[j].center_x;
    self->secondary_samples[j].transform.position.y = self->primary_samples[j].transform.position.y + 0.49000001;
    self->secondary_samples[j].transform.position.z = v53;
    if ( j <= 3 )
    {
      set_matrix_rotation_identity(&self->primary_samples[j - 1].transform);
      set_matrix_rotation_identity(&self->secondary_samples[j - 1].transform);
    }
    else
    {
      p_basis_up = &self->primary_samples[j - 1].transform.basis_up;
      p_basis_up->x = 0.0;
      p_basis_up->y = 1.0;
      p_basis_up->z = 0.0;
      v15 = &self->primary_samples[j];
      v16 = v15->transform.position.x - v15[-1].transform.position.x;
      v15 = (PathTemplateSample *)((char *)v15 - 136);
      v58 = v16;
      v60 = v15[1].transform.basis_up.y - v15->transform.basis_up.y;
      v17 = v15[1].transform.basis_up.z - v15->transform.basis_up.z;
      v15->transform.basis_right.x = v58;
      v15->transform.basis_right.y = v60;
      v62 = v17;
      v15->transform.basis_right.z = v62;
      normalize_vector(&self->primary_samples[j - 1].transform.basis_forward);
      cross_vectors(
        &self->primary_samples[j - 1].transform.basis_right,
        &self->primary_samples[j - 1].transform.basis_up,
        &self->primary_samples[j - 1].transform.basis_forward);
      v18 = &self->secondary_samples[j - 1].transform.basis_up;
      v18->x = 0.0;
      v18->y = 1.0;
      v18->z = 0.0;
      v19 = &self->secondary_samples[j];
      v20 = v19->transform.position.x - v19[-1].transform.position.x;
      v19 = (PathTemplateSample *)((char *)v19 - 136);
      v69 = v20;
      v72 = v19[1].transform.basis_up.y - v19->transform.basis_up.y;
      v21 = v19[1].transform.basis_up.z - v19->transform.basis_up.z;
      v19->transform.basis_right.x = v69;
      v19->transform.basis_right.y = v72;
      v75 = v21;
      v19->transform.basis_right.z = v75;
      normalize_vector(&self->secondary_samples[j - 1].transform.basis_forward);
      cross_vectors(
        &self->secondary_samples[j - 1].transform.basis_right,
        &self->secondary_samples[j - 1].transform.basis_up,
        &self->secondary_samples[j - 1].transform.basis_forward);
    }
    ++texture_ac;
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
      v70 = v25;
      v73 = v24->inverse_matrix.basis_up_w - v24[-1].inverse_matrix.basis_up_w;
      v26 = v24->inverse_matrix.basis_forward.x - v24[-1].inverse_matrix.basis_forward.x;
      v24->transform.basis_right.x = v70;
      v24->transform.basis_right.y = v73;
      v76 = v26;
      v24->transform.basis_right.z = v76;
      self->primary_samples[v23].delta_length = normalize_vector(&self->primary_samples[v23].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      p_x = &secondary_samples[v23].delta_dir_to_next.x;
      v63 = secondary_samples[v23 + 1].transform.position.x - secondary_samples[v23].transform.position.x;
      v65 = secondary_samples[v23 + 1].transform.position.y - secondary_samples[v23].transform.position.y;
      v29 = secondary_samples[v23 + 1].transform.position.z - secondary_samples[v23].transform.position.z;
      *p_x = v63;
      p_x[1] = v65;
      v67 = v29;
      p_x[2] = v67;
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
  v54 = vertices;
  facequads = object->facequads;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    do
    {
      width_cells = self->width_cells;
      v36 = nullptr;
      texture_ad = nullptr;
      for ( k = width_cells; (int)v36 <= width_cells; texture_ad = v36 )
      {
        v37 = (double)(int)texture_ad - (double)k * 0.5;
        v38 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v8);
        if ( v33 == self->segment_count )
        {
          vertices = v54;
          v56 = v37 * *(v38 - 42);
          v57 = v37 * *(v38 - 41);
          v41 = v37 * *(v38 - 40);
          v78 = *(v38 - 28) + 1.0;
          v64 = *(v38 - 30) + v56;
          v66 = *(v38 - 29) + v57;
          v39 = &v54[(_DWORD)&v36[v33 * (width_cells + 1)]].x;
          *v39 = v64;
          v68 = v78 + v41;
          v39[1] = v66;
          v40 = v68;
        }
        else
        {
          v59 = v37 * *v38;
          v61 = v37 * v38[1];
          v71 = v59 + v38[12];
          v74 = v61 + v38[13];
          v77 = v37 * v38[2] + v38[14];
          v39 = &vertices[(_DWORD)&v36[v33 * (width_cells + 1)]].x;
          *v39 = v71;
          v39[1] = v74;
          v40 = v77;
        }
        v39[2] = v40;
        width_cells = self->width_cells;
        ++v36;
        k = width_cells;
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
      texture_ae = nullptr;
      if ( (int)self->width_cells > 0 )
      {
        v45 = (double)(v8 % 8) * 0.125;
        v48 = (double)(v8 % 8 + 1) * 0.125;
        do
        {
          v43 = 0;
          v55 = v42 + 1;
          v50 = 0;
          texture_af = (double)(int)texture_ae * 0.125;
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
              v44->uv[0].v = v45;
              v44->uv[1].u = texture_af;
              v44->uv[1].v = v45;
              v44->uv[2].u = texture_af;
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
              v44->uv[0].u = texture_af;
              v44->uv[0].v = v45;
              v44->uv[1].u = v46;
              v44->uv[1].v = v45;
              v44->uv[2].u = v46;
              v44->uv[2].v = v48;
              v44->uv[3].u = texture_af;
            }
            v44->uv[3].v = v48;
            if ( ++v50 >= 2 )
              break;
            v43 = v50;
          }
          ++v42;
          texture_ae = (char *)v55;
        }
        while ( v55 < (signed int)self->width_cells );
      }
      ++v8;
    }
    while ( v8 < (signed int)self->segment_count );
  }
  calc_path_length_z(self);
}
