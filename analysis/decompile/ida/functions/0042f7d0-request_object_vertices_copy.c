/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: request_object_vertices_copy @ 0x42f7d0 */
/* selector: request_object_vertices_copy */

int __thiscall sub_42F7D0(unsigned int *this)
{
  *(this + 15) = (unsigned int)allocate_tracked_memory(12 * *(this + 11), (int)aObjectVertexLi);
  return copy_object_vertices(this);
}

