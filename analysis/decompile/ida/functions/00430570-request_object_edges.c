/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: request_object_edges @ 0x430570 */
/* selector: request_object_edges */

// Authored `cRObject::RequestEdges(int)` member: installs the requested edge count and allocates the Object-owned packed `ObjectToonEdge` bank when no edge bank is active; an existing bank is retained. Android confirms the one-time owner but adds a separate index bank and uses a different edge stride, so those mobile layout details do not transfer.
void __thiscall request_object_edges(Object *object, int32_t edge_count)
{
  if ( object->edge_count == 0 )
  {
    object->edge_count = edge_count;
    object->edges = (ObjectToonEdge *)allocate_tracked_memory(36 * edge_count, aObjectEdges);
  }
}
