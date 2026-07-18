/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_point_inside_track_attachment @ 0x42ca90 */
/* selector: is_point_inside_track_attachment */

// Tests whether one by-value probe lies inside a borrowed attachment cell by subtracting each anchored secondary-sample origin as a real vector expression and rotating the result through the sample inverse matrix. Android retains `cRPath::SearchPos` by name, iOS Path.o gives `cRPath::SearchPos(tVector, tVector, cRSubLoc*)`, and the exact Windows candidate confirms that the second by-value vector remains ABI-owned even though this split does not read it.
bool __thiscall is_point_inside_track_attachment(Path *self, Vec3 probe, Vec3 swept_motion, TrackRowCell *cell)
{
  signed int v5; // edi
  unsigned int i; // esi
  PathTemplateSample *secondary_samples; // ecx
  double v8; // st7
  Vec3 vector; // [esp+Ch] [ebp-30h] BYREF
  Vec3 anchor_position; // [esp+18h] [ebp-24h]
  Vec3 v12; // [esp+24h] [ebp-18h]
  float v13; // [esp+34h] [ebp-8h]
  float v14; // [esp+38h] [ebp-4h]

  v5 = self->segment_count - 1;
  anchor_position = cell->anchor_position;
  if ( v5 < 0 )
    return 0;
  for ( i = v5; ; --i )
  {
    secondary_samples = self->secondary_samples;
    v8 = anchor_position.x + secondary_samples[i].transform.position.x;
    v13 = anchor_position.y + secondary_samples[i].transform.position.y;
    v14 = anchor_position.z + secondary_samples[i].transform.position.z;
    v12.x = probe.x - v8;
    v12.y = probe.y - v13;
    v12.z = probe.z - v14;
    vector = v12;
    rotate_vector_by_matrix(&vector, &secondary_samples[i].inverse_matrix);
    if ( (double)((signed int)self->width_cells / -2) - 0.30000001 < vector.x
      && (double)((signed int)self->width_cells / 2) + 0.30000001 > vector.x
      && vector.y >= -0.30000001
      && vector.y < 0.30000001
      && vector.z > 0.0
      && vector.z < (double)self->secondary_samples[i].delta_length )
    {
      break;
    }
    if ( --v5 < 0 )
      return 0;
  }
  return 1;
}
