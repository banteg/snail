/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: allocate_path_nodes @ 0x41b0a0 */
/* selector: allocate_path_nodes */

PathTemplateSample *__fastcall allocate_path_nodes(PathTemplate *self)
{
  PathTemplateSample *tracked_memory; // eax
  uint32_t segment_count; // ecx
  PathTemplateSample *result; // eax

  tracked_memory = (PathTemplateSample *)allocate_tracked_memory(168 * self->segment_count, (int)aPathTileNodes);
  segment_count = self->segment_count;
  self->primary_samples = tracked_memory;
  result = (PathTemplateSample *)allocate_tracked_memory(168 * segment_count, (int)aPathBallNodes);
  self->secondary_samples = result;
  return result;
}

