/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_path_nodes @ 0x41b0a0 */
/* selector: get_path_nodes */

// Allocates the primary and secondary `PathTemplateSample` arrays for one path template and stores both pointers on the template object. Constructors treat it as a pure allocator; the old returned secondary-sample pointer is not meaningfully consumed.
void __fastcall get_path_nodes(cRPath *self)
{
  PathTemplateSample *tracked_memory; // eax
  uint32_t segment_count; // ecx

  tracked_memory = (PathTemplateSample *)allocate_tracked_memory(168 * self->segment_count, aPathTileNodes);
  segment_count = self->segment_count;
  self->primary_samples = tracked_memory;
  self->secondary_samples = (PathTemplateSample *)allocate_tracked_memory(168 * segment_count, aPathBallNodes);
}
