/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: apply_bod_position @ 0x42f680 */
/* selector: apply_bod_position */

// Applies one body's position into the supplied matrix before object rendering; iOS RObject.o names this `cRBod::ApplyPos(tMatrix&)`.
Object *__thiscall apply_bod_position(BodBase *bod, TransformMatrix *matrix)
{
  int32_t v3; // ebx
  Object *result; // eax
  int v5; // esi
  Vec3 *v6; // eax
  Vec3 *v7; // ecx
  Vec3 out; // [esp+8h] [ebp-Ch] BYREF

  v3 = 0;
  result = bod->object;
  if ( result->vertex_count > 0 )
  {
    v5 = 0;
    do
    {
      v6 = multiply_vector_by_matrix_copy(&result->vertices[v5], &out, matrix);
      v7 = &bod->object->vertices[v5];
      ++v3;
      ++v5;
      *v7 = *v6;
      result = bod->object;
    }
    while ( v3 < result->vertex_count );
  }
  return result;
}
