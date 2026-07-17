/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: raise_backdrop_quad_edge_pair @ 0x41a170 */
/* selector: raise_backdrop_quad_edge_pair */

// Raises one of the two adjacent backdrop-quad edge pairs by 0.5 units using the small orientation tables consumed by the `Objects/Univers` variants.
void __cdecl raise_backdrop_quad_edge_pair(int32_t selector, Object *object)
{
  Vec3 *vertices; // ecx

  vertices = object->vertices;
  if ( selector > 0
    || (vertices[g_backdrop_raise_first_vertex_index].y = vertices[g_backdrop_raise_first_vertex_index].y + 0.5,
        selector >= 0) )
  {
    vertices[g_backdrop_raise_second_vertex_index].y = vertices[g_backdrop_raise_second_vertex_index].y + 0.5;
  }
}
