/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: calc_path_length_z @ 0x42c600 */
/* selector: calc_path_length_z */

// Windows `cRPath::CalcLengthZ()`: recomputes one built path's derived row span and per-sample lateral length scalars, inverts both sample-transform banks, and normalizes the nested strip-mesh flags. Android and iOS Path.o independently preserve the exact authored owner and name. The former `finalize_path_template` label remains only as a compatibility alias.
void __fastcall calc_path_length_z(cRPath *self)
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
  float *p_lateral_source; // ecx
  Object *object; // eax
  ObjectFlag flags; // ecx
  Vec3 out; // [esp+10h] [ebp-Ch] BYREF

  segment_count = self->segment_count;
  self->row_span_count = 0;
  if ( segment_count > 0 )
  {
    v3 = segment_count;
    p_z = &self->secondary_samples->transform.position.z;
    do
    {
      v5 = (__int64)(*p_z + 1.0);
      if ( (int)v5 > (signed int)self->row_span_count )
        self->row_span_count = v5;
      p_z += 42;
      --v3;
    }
    while ( v3 != 0 );
  }
  v6 = 0;
  if ( segment_count > 0 )
  {
    v7 = 0;
    do
    {
      invert_matrix_from_source(&self->primary_samples[v7].inverse_matrix, &self->primary_samples[v7].transform);
      invert_matrix_from_source(&self->secondary_samples[v7].inverse_matrix, &self->secondary_samples[v7].transform);
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
        &out,
        &self->primary_samples[v9].transform.basis_forward,
        &self->primary_samples[v9 + 1].transform.basis_forward);
      self->primary_samples[v9].lateral_source = dot_vector(&out, &self->primary_samples[v9].transform.basis_right);
      if ( self->is_mirrored_x != 0 )
        self->primary_samples[v9].lateral_source = self->primary_samples[v9].lateral_source * -1.0;
      primary_samples = self->primary_samples;
      if ( primary_samples[v9].lateral_source > 0.0 )
        primary_samples[v9].lateral_source = 0.0;
      p_lateral_source = &self->primary_samples[v9].lateral_source;
      if ( *p_lateral_source < -0.1 )
        *p_lateral_source = -0.1;
      ++v8;
      ++v9;
    }
    while ( v8 < (signed int)(self->segment_count - 1) );
  }
  self->primary_samples[self->segment_count - 1].lateral_source = 0.0;
  object = self->bod.object;
  flags = object->flags;
  LOBYTE(flags) = flags | 0x80;
  object->flags = flags;
  self->bod.object->flags &= ~0x100000u;
}
