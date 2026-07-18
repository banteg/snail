/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: calc_object_bounding_box @ 0x42fb10 */
/* selector: calc_object_bounding_box */

// Recomputes one cRObject's min/max bounds and maximum vertex magnitude in place. Its sole native caller discards EAX, confirming this is a void object mutator rather than the decompiler-derived count-returning helper.
void __thiscall calc_object_bounding_box(Object *object)
{
  Vec3 *p_bounds_max; // edi
  Vec3 *p_bounds_min; // ebx
  int v4; // ebp
  Vec3 *v5; // ecx
  double x; // st7
  double v7; // st7
  double y; // st7
  double v9; // st7
  double z; // st7
  double v11; // st7
  double v12; // st7
  int32_t v13; // [esp+10h] [ebp-10h]

  p_bounds_max = &object->bounds_max;
  object->bounds_max.x = -1.0e10;
  p_bounds_min = &object->bounds_min;
  object->bounds_max.y = -1.0e10;
  object->bounds_max.z = -1.0e10;
  object->bounds_min.x = 1.0e10;
  v4 = 0;
  object->bounds_min.y = 1.0e10;
  object->bounding_radius = 0.0;
  v13 = 0;
  for ( object->bounds_min.z = 1.0e10; v13 < object->vertex_count; ++v13 )
  {
    v5 = &object->vertices[v4];
    if ( p_bounds_max->x <= (double)v5->x )
    {
      x = v5->x;
    }
    else
    {
      x = object->bounds_max.x;
      p_bounds_max = &object->bounds_max;
    }
    p_bounds_max->x = x;
    if ( v5->x <= (double)p_bounds_min->x )
    {
      v7 = v5->x;
    }
    else
    {
      v7 = object->bounds_min.x;
      p_bounds_min = &object->bounds_min;
    }
    p_bounds_min->x = v7;
    if ( object->bounds_max.y <= (double)v5->y )
      y = v5->y;
    else
      y = object->bounds_max.y;
    object->bounds_max.y = y;
    if ( v5->y <= (double)object->bounds_min.y )
      v9 = v5->y;
    else
      v9 = object->bounds_min.y;
    object->bounds_min.y = v9;
    if ( object->bounds_max.z <= (double)v5->z )
      z = v5->z;
    else
      z = object->bounds_max.z;
    object->bounds_max.z = z;
    if ( v5->z <= (double)object->bounds_min.z )
      v11 = v5->z;
    else
      v11 = object->bounds_min.z;
    object->bounds_min.z = v11;
    v12 = vector_magnitude(v5);
    if ( v12 > object->bounding_radius )
      object->bounding_radius = v12;
    ++v4;
  }
}
