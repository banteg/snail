/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: mirror_path_template_pair_x @ 0x421dc0 */
/* selector: mirror_path_template_pair_x */

// Clones one path-template pair, negates X-space samples, and flips strip winding for the mirrored half.
int32_t __thiscall mirror_path_template_pair_x(PathTemplate *self, PathTemplate *source)
{
  PathTemplateStripMesh *strip_mesh; // eax
  signed int v5; // edx
  int v6; // eax
  Vec3 *p_delta_dir_to_next; // ecx
  Vec3 *v8; // esi
  Vec3 *v9; // ecx
  Vec3 *v10; // esi
  PathTemplateSample *secondary_samples; // ecx
  double v12; // st7
  float *p_x; // ecx
  PathTemplateStripMesh *v14; // ecx
  Vec3 *vertices; // esi
  signed int v16; // edx
  signed int width_cells; // eax
  signed int j; // ecx
  uint32_t v19; // eax
  uint32_t v20; // eax
  uint32_t v21; // eax
  Color4f *v22; // esi
  uint8_t *v23; // eax
  int v24; // edx
  uint32_t v25; // ecx
  uint32_t v26; // eax
  double v27; // st7
  double v28; // st7
  Vec3 *i; // [esp+10h] [ebp-8h]
  signed int k; // [esp+10h] [ebp-8h]
  ObjectFaceQuad *facequads; // [esp+14h] [ebp-4h]
  PathTemplate *sourcea; // [esp+1Ch] [ebp+4h]
  PathTemplate *sourceb; // [esp+1Ch] [ebp+4h]

  self->is_mirrored_x = 1;
  self->segment_count = source->segment_count;
  self->segment_count_f = source->segment_count_f;
  self->width_or_scale = source->width_or_scale;
  self->width_cells = source->width_cells;
  allocate_path_nodes(self);
  strip_mesh = self->strip_mesh;
  self->special_runtime_flag_9c = source->special_runtime_flag_9c;
  strip_mesh->flags = source->strip_mesh->flags;
  self->kind = source->kind;
  self->side_exit_mode = source->side_exit_mode;
  v5 = 0;
  if ( (int)self->segment_count > 0 )
  {
    v6 = 0;
    do
    {
      self->primary_samples[v6].center_x = -source->primary_samples[v6].center_x;
      self->primary_samples[v6].lateral_scale = source->primary_samples[v6].lateral_scale;
      self->primary_samples[v6].rotation_scalar_98 = -source->primary_samples[v6].rotation_scalar_98;
      self->primary_samples[v6].rotation_scalar_94 = -source->primary_samples[v6].rotation_scalar_94;
      self->primary_samples[v6].special_scalar = source->primary_samples[v6].special_scalar;
      qmemcpy(&self->primary_samples[v6], &source->primary_samples[v6], 0x40u);
      self->primary_samples[v6].transform.basis_right.x = self->primary_samples[v6].transform.basis_right.x * -1.0;
      self->primary_samples[v6].transform.basis_up.x = self->primary_samples[v6].transform.basis_up.x * -1.0;
      self->primary_samples[v6].transform.basis_forward.x = self->primary_samples[v6].transform.basis_forward.x * -1.0;
      self->primary_samples[v6].transform.position.x = self->primary_samples[v6].transform.position.x * -1.0;
      p_delta_dir_to_next = &source->primary_samples[v6].delta_dir_to_next;
      v8 = &self->primary_samples[v6].delta_dir_to_next;
      v8->x = p_delta_dir_to_next->x;
      v8->y = p_delta_dir_to_next->y;
      v8->z = p_delta_dir_to_next->z;
      self->primary_samples[v6].delta_dir_to_next.x = self->primary_samples[v6].delta_dir_to_next.x * -1.0;
      self->primary_samples[v6].delta_length = source->primary_samples[v6].delta_length;
      qmemcpy(&self->secondary_samples[v6], &source->secondary_samples[v6], 0x40u);
      ++v5;
      self->secondary_samples[v6].transform.basis_right.x = self->secondary_samples[v6].transform.basis_right.x * -1.0;
      self->secondary_samples[v6].transform.basis_up.x = self->secondary_samples[v6].transform.basis_up.x * -1.0;
      self->secondary_samples[v6].transform.basis_forward.x = self->secondary_samples[v6].transform.basis_forward.x
                                                            * -1.0;
      self->secondary_samples[v6].transform.position.x = self->secondary_samples[v6].transform.position.x * -1.0;
      v9 = &source->secondary_samples[v6].delta_dir_to_next;
      v10 = &self->secondary_samples[v6].delta_dir_to_next;
      v10->x = v9->x;
      v10->y = v9->y;
      v10->z = v9->z;
      secondary_samples = self->secondary_samples;
      v12 = secondary_samples[v6].delta_dir_to_next.x * -1.0;
      p_x = &secondary_samples[v6++].delta_dir_to_next.x;
      *p_x = v12;
      self->secondary_samples[v6 - 1].delta_length = source->secondary_samples[v6 - 1].delta_length;
    }
    while ( v5 < (signed int)self->segment_count );
  }
  request_object_vertices(self->strip_mesh, (self->width_cells + 1) * (self->segment_count + 1));
  request_object_facequads(self->strip_mesh, 2 * self->width_cells * self->segment_count);
  v14 = self->strip_mesh;
  sourcea = nullptr;
  if ( (v14->flags & 0x10000) != 0 )
  {
    request_object_vertex_colours(v14);
    v14 = self->strip_mesh;
    sourcea = (PathTemplate *)v14->vertex_colours;
  }
  vertices = v14->vertices;
  facequads = v14->facequads;
  v16 = 0;
  for ( i = vertices; v16 <= (signed int)self->segment_count; ++v16 )
  {
    width_cells = self->width_cells;
    for ( j = 0; j <= width_cells; ++j )
    {
      vertices[j + v16 * (width_cells + 1)].x = -source->strip_mesh->vertices[j + v16 * (width_cells + 1)].x;
      v19 = j + v16 * (self->width_cells + 1);
      vertices[v19].y = source->strip_mesh->vertices[v19].y;
      v20 = j + v16 * (self->width_cells + 1);
      vertices[v20].z = source->strip_mesh->vertices[v20].z;
      if ( (self->strip_mesh->flags & 0x10000) != 0 )
      {
        v21 = j + v16 * (self->width_cells + 1);
        v22 = &source->strip_mesh->vertex_colours[v21];
        v23 = &sourcea->_pad_00[v21 * 16];
        *(float *)v23 = v22->r;
        *((_DWORD *)v23 + 1) = LODWORD(v22->g);
        *((_DWORD *)v23 + 2) = LODWORD(v22->b);
        *((_DWORD *)v23 + 3) = LODWORD(v22->a);
        vertices = i;
      }
      width_cells = self->width_cells;
    }
  }
  for ( k = 0; k < (signed int)self->segment_count; ++k )
  {
    for ( sourceb = nullptr; (int)sourceb < (signed int)self->width_cells; sourceb = (PathTemplate *)((char *)sourceb + 1) )
    {
      v24 = 0;
      do
      {
        v25 = 48 * (v24 + 2 * ((_DWORD)sourceb + k * self->width_cells));
        v26 = (uint32_t)facequads + v25;
        qmemcpy((char *)facequads + v25, (char *)source->strip_mesh->facequads + v25, 0x30u);
        LOWORD(v25) = *(_WORD *)((char *)&facequads->flags + v25 + 2);
        *(_WORD *)(v26 + 2) = *(_WORD *)(v26 + 4);
        *(_WORD *)(v26 + 4) = v25;
        ++v24;
        LOWORD(v25) = *(_WORD *)(v26 + 6);
        *(_WORD *)(v26 + 6) = *(_WORD *)(v26 + 8);
        *(_WORD *)(v26 + 8) = v25;
        v27 = *(float *)(v26 + 16);
        *(float *)(v26 + 16) = *(float *)(v26 + 24);
        *(float *)(v26 + 24) = v27;
        v28 = *(float *)(v26 + 32);
        *(float *)(v26 + 32) = *(float *)(v26 + 40);
        *(float *)(v26 + 40) = v28;
      }
      while ( v24 < 2 );
    }
  }
  return finalize_path_template_record(self);
}

