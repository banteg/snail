/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: request_object_edges @ 0x430570 */
/* selector: request_object_edges */

// Allocates the packed toon-edge records and companion selection buffer that `render_object_toon` consumes when it emits silhouette line segments.
void __thiscall request_object_edges(Object *object, int32_t edge_count)
{
  if ( !object->edge_count )
  {
    object->edge_count = edge_count;
    object->edges = (ObjectToonEdge *)allocate_tracked_memory(36 * edge_count, aObjectEdges);
  }
}
