/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: finalize_path_template @ 0x42c600 */
/* selector: finalize_path_template */

// Finalizes one built path template after constructor or mirror edits by recomputing derived per-sample lengths, inverting sample transforms, updating the derived sample scalar at `+0xa4`, and normalizing the nested strip-mesh state.
int32_t __fastcall finalize_path_template_record(PathTemplate *self)
{
  signed int segment_count; // ebx
  signed int v3; // ebp
  float *p_z; // edi
  __int64 v5; // rax
  signed int v6; // ebp
  int v7; // edi
  signed int v8; // ebx
  int v9; // edi
  PathTemplateSample *primary_samples; // edx
  uint8_t *pad_a4; // ecx
  PathTemplateStripMesh *strip_mesh; // eax
  PathTemplateStripMeshFlags flags; // ecx
  PathTemplateStripMesh *v14; // esi
  int32_t result; // eax
  Vec3 v16; // [esp+10h] [ebp-Ch] BYREF

  segment_count = self->segment_count;
  self->_pad_48 = 0;
  if ( segment_count > 0 )
  {
    v3 = segment_count;
    p_z = &self->secondary_samples->transform.position.z;
    do
    {
      v5 = (__int64)(*p_z + 1.0);
      if ( (int)v5 > (signed int)self->_pad_48 )
        self->_pad_48 = v5;
      p_z += 42;
      --v3;
    }
    while ( v3 );
  }
  v6 = 0;
  if ( segment_count > 0 )
  {
    v7 = 0;
    do
    {
      invert_matrix_from_source(
        (float *)self->primary_samples[v7]._pad_40,
        &self->primary_samples[v7].transform.basis_right.x);
      invert_matrix_from_source(
        (float *)self->secondary_samples[v7]._pad_40,
        &self->secondary_samples[v7].transform.basis_right.x);
      ++v6;
      ++v7;
    }
    while ( v6 < (signed int)self->segment_count );
  }
  v8 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v9 = 0;
    do
    {
      cross_vectors(
        &v16,
        (Vec3 *)&self->primary_samples[v9].transform.basis_forward,
        (Vec3 *)&self->primary_samples[v9 + 1].transform.basis_forward);
      *(float *)self->primary_samples[v9]._pad_a4 = dot_vector(
                                                      &v16.x,
                                                      &self->primary_samples[v9].transform.basis_right.x);
      if ( self->is_mirrored_x )
        *(float *)self->primary_samples[v9]._pad_a4 = *(float *)self->primary_samples[v9]._pad_a4 * -1.0;
      primary_samples = self->primary_samples;
      if ( *(float *)primary_samples[v9]._pad_a4 > 0.0 )
        *(_DWORD *)primary_samples[v9]._pad_a4 = 0;
      pad_a4 = self->primary_samples[v9]._pad_a4;
      if ( *(float *)pad_a4 < -0.1 )
        *(_DWORD *)pad_a4 = -1110651699;
      ++v8;
      ++v9;
    }
    while ( v8 < (signed int)(self->segment_count - 1) );
  }
  *(_DWORD *)self->primary_samples[self->segment_count - 1]._pad_a4 = 0;
  strip_mesh = self->strip_mesh;
  flags = strip_mesh->flags;
  LOBYTE(flags) = flags | 0x80;
  strip_mesh->flags = flags;
  v14 = self->strip_mesh;
  result = v14->flags & 0xFFEFFFFF;
  v14->flags = result;
  return result;
}

