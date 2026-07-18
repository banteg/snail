/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: request_object_texture_groups @ 0x42f930 */
/* selector: request_object_texture_groups */

void __thiscall request_object_texture_groups(Object *object, int32_t group_count)
{
  int32_t *tracked_memory; // eax

  if ( object->texture_group_count )
  {
    if ( group_count > object->texture_group_capacity )
      report_errorf(aFixedFacequadt);
    object->texture_group_count = group_count;
  }
  else
  {
    tracked_memory = (int32_t *)allocate_tracked_memory(4 * group_count, aObjectFacequad_1);
    object->texture_group_capacity = group_count;
    object->texture_group_count = group_count;
    object->texture_group_ends = tracked_memory;
  }
}
