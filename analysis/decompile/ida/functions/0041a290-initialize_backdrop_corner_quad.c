/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_backdrop_corner_quad @ 0x41a290 */
/* selector: initialize_backdrop_corner_quad */

// Builds one sliced backdrop quad and offsets the selected edge pair by 0.3 units using the four-entry corner selector table.
void __cdecl initialize_backdrop_corner_quad(int32_t selector, Object *object, char *texture_path)
{
  Vec3 *vertices; // edx
  float *p_x; // ecx
  float *p_z; // ecx
  int texture_patha; // [esp+10h] [ebp+Ch]

  initialize_backdrop_slice_quad(object, texture_path, 0.0);
  vertices = object->vertices;
  p_x = &vertices[g_backdrop_corner_vertex_indices[selector]].x;
  if ( *p_x >= 0.0 )
    texture_patha = *p_x != 0.0;
  else
    texture_patha = -1;
  *p_x = (double)texture_patha * 0.30000001;
  p_z = &vertices[g_backdrop_corner_vertex_indices[selector]].z;
  if ( *p_z >= 0.0 )
    *p_z = (double)(*p_z != 0.0) * 0.30000001;
  else
    *p_z = (double)-1 * 0.30000001;
}
