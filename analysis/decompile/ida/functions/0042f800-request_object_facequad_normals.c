/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: request_object_facequad_normals @ 0x42f800 */
/* selector: request_object_facequad_normals */

// Ensures one object's toon-normal storage exists by allocating the per-vertex accumulated normal list and the per-face quad-normal pairs consumed by the outline pass.
_BYTE *__thiscall sub_42F800(_DWORD *this)
{
  _BYTE *result; // eax

  if ( !*(this + 17) )
    *(this + 17) = allocate_tracked_memory(12 * *(this + 11), (int)aObjectVertexNo);
  result = (_BYTE *)*(this + 24);
  if ( !result )
  {
    result = allocate_tracked_memory(24 * *(this + 21), (int)aObjectFacequad_0);
    *(this + 24) = result;
  }
  return result;
}

