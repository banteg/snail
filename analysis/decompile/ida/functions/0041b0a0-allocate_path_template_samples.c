/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: allocate_path_template_samples @ 0x41b0a0 */
/* selector: allocate_path_template_samples */

// Allocates the primary and secondary `PathTemplateSample` arrays for one path template and stores both pointers on the template object. Constructors treat it as a pure allocator; the old returned secondary-sample pointer is not meaningfully consumed.
void __fastcall allocate_path_template_samples(PathTemplate *self)
{
  PathTemplateSample *tracked_memory; // eax
  uint32_t segment_count; // ecx

  tracked_memory = (PathTemplateSample *)allocate_tracked_memory(168 * self->segment_count, (int)aPathTileNodes);
  segment_count = self->segment_count;
  self->primary_samples = tracked_memory;
  self->secondary_samples = (PathTemplateSample *)allocate_tracked_memory(168 * segment_count, (int)aPathBallNodes);
}

