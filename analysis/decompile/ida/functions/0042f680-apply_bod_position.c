/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: apply_bod_position @ 0x42f680 */
/* selector: apply_bod_position */

// Exact void Windows `cRBod::ApplyPos(tMatrix&)`: transforms every vertex of the body's borrowed `cRObject` in place through the supplied matrix reference. Android and iOS preserve the authored owner and signature, and all eight Windows callers discard EAX.
void __thiscall apply_bod_position(BodBase *bod, TransformMatrix *matrix)
{
  int32_t v3; // ebx
  Object *object; // eax
  int v5; // esi
  Vec3 *v6; // eax
  Vec3 *v7; // ecx
  Vec3 out; // [esp+8h] [ebp-Ch] BYREF

  v3 = 0;
  object = bod->object;
  if ( object->vertex_count > 0 )
  {
    v5 = 0;
    do
    {
      v6 = multiply_vector_by_matrix_copy(&object->vertices[v5], &out, matrix);
      v7 = &bod->object->vertices[v5];
      ++v3;
      ++v5;
      *v7 = *v6;
      object = bod->object;
    }
    while ( v3 < object->vertex_count );
  }
}
