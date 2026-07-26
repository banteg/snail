/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: mirror_path @ 0x421dc0 */
/* selector: mirror_path */

// Clones one path-template pair, negates X-space samples, and flips strip winding for the mirrored half. iOS Path.o names this `cRPath::Mirror(cRPath*)`.
void __thiscall mirror_path(Path *self, Path *source)
{
  Object *object; // eax
  signed int v5; // edx
  int v6; // eax
  PathTemplateSample *secondary_samples; // ecx
  double v8; // st7
  float *p_x; // ecx
  Object *v10; // ecx
  Vec3 *vertices; // esi
  signed int v12; // edx
  signed int width_cells; // eax
  signed int j; // ecx
  uint32_t v15; // eax
  uint32_t v16; // eax
  uint32_t v17; // eax
  tColour *v18; // esi
  uint8_t *v19; // eax
  int v20; // edx
  uint32_t v21; // ecx
  uint32_t v22; // eax
  double v23; // st7
  double v24; // st7
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
  get_path_nodes(self);
  object = self->bod.object;
  self->has_entry_mesh_transition = source->has_entry_mesh_transition;
  object->flags = source->bod.object->flags;
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
      self->primary_samples[v6].delta_dir_to_next = source->primary_samples[v6].delta_dir_to_next;
      self->primary_samples[v6].delta_dir_to_next.x = self->primary_samples[v6].delta_dir_to_next.x * -1.0;
      self->primary_samples[v6].delta_length = source->primary_samples[v6].delta_length;
      qmemcpy(&self->secondary_samples[v6], &source->secondary_samples[v6], 0x40u);
      ++v5;
      self->secondary_samples[v6].transform.basis_right.x = self->secondary_samples[v6].transform.basis_right.x * -1.0;
      self->secondary_samples[v6].transform.basis_up.x = self->secondary_samples[v6].transform.basis_up.x * -1.0;
      self->secondary_samples[v6].transform.basis_forward.x = self->secondary_samples[v6].transform.basis_forward.x
                                                            * -1.0;
      self->secondary_samples[v6].transform.position.x = self->secondary_samples[v6].transform.position.x * -1.0;
      self->secondary_samples[v6].delta_dir_to_next = source->secondary_samples[v6].delta_dir_to_next;
      secondary_samples = self->secondary_samples;
      v8 = secondary_samples[v6].delta_dir_to_next.x * -1.0;
      p_x = &secondary_samples[v6++].delta_dir_to_next.x;
      *p_x = v8;
      self->secondary_samples[v6 - 1].delta_length = source->secondary_samples[v6 - 1].delta_length;
    }
    while ( v5 < (signed int)self->segment_count );
  }
  request_object_vertices(self->bod.object, (self->width_cells + 1) * (self->segment_count + 1));
  request_object_facequads(self->bod.object, 2 * self->width_cells * self->segment_count);
  v10 = self->bod.object;
  sourcea = nullptr;
  if ( (v10->flags & 0x10000) != 0 )
  {
    request_object_vertex_colours(v10);
    v10 = self->bod.object;
    sourcea = (PathTemplate *)v10->vertex_colours;
  }
  vertices = v10->vertices;
  facequads = v10->facequads;
  v12 = 0;
  for ( i = vertices; v12 <= (signed int)self->segment_count; ++v12 )
  {
    width_cells = self->width_cells;
    for ( j = 0; j <= width_cells; ++j )
    {
      vertices[j + v12 * (width_cells + 1)].x = -source->bod.object->vertices[j + v12 * (width_cells + 1)].x;
      v15 = j + v12 * (self->width_cells + 1);
      vertices[v15].y = source->bod.object->vertices[v15].y;
      v16 = j + v12 * (self->width_cells + 1);
      vertices[v16].z = source->bod.object->vertices[v16].z;
      if ( (self->bod.object->flags & 0x10000) != 0 )
      {
        v17 = j + v12 * (self->width_cells + 1);
        v18 = &source->bod.object->vertex_colours[v17];
        v19 = &sourcea->_pad_00[v17 * 16];
        *(float *)v19 = v18->r;
        *((_DWORD *)v19 + 1) = LODWORD(v18->g);
        *((_DWORD *)v19 + 2) = LODWORD(v18->b);
        *((_DWORD *)v19 + 3) = LODWORD(v18->a);
        vertices = i;
      }
      width_cells = self->width_cells;
    }
  }
  for ( k = 0; k < (signed int)self->segment_count; ++k )
  {
    for ( sourceb = nullptr; (int)sourceb < (signed int)self->width_cells; sourceb = (PathTemplate *)((char *)sourceb + 1) )
    {
      v20 = 0;
      do
      {
        v21 = 48 * (v20 + 2 * ((_DWORD)sourceb + k * self->width_cells));
        v22 = (uint32_t)facequads + v21;
        qmemcpy((char *)facequads + v21, (char *)source->bod.object->facequads + v21, sizeof(ObjectFaceQuad));
        LOWORD(v21) = *(uint16_t *)((char *)&facequads->vertex_0 + v21);
        *(_WORD *)(v22 + 2) = *(_WORD *)(v22 + 4);
        *(_WORD *)(v22 + 4) = v21;
        ++v20;
        LOWORD(v21) = *(_WORD *)(v22 + 6);
        *(_WORD *)(v22 + 6) = *(_WORD *)(v22 + 8);
        *(_WORD *)(v22 + 8) = v21;
        v23 = *(float *)(v22 + 16);
        *(float *)(v22 + 16) = *(float *)(v22 + 24);
        *(float *)(v22 + 24) = v23;
        v24 = *(float *)(v22 + 32);
        *(float *)(v22 + 32) = *(float *)(v22 + 40);
        *(float *)(v22 + 40) = v24;
      }
      while ( v20 < 2 );
    }
  }
  calc_path_length_z(self);
}
