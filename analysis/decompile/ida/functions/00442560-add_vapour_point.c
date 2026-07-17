/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: add_vapour_point @ 0x442560 */
/* selector: add_vapour_point */

// Exact void Windows `cRVapour::Add(tMatrix&)`: appends one transform to the owned history or shifts the full fixed-capacity window before replacing its tail. Android and iOS preserve the owner and method contract.
void __thiscall add_vapour_point(Vapour *vapour, const TransformMatrix *point)
{
  int32_t point_count; // edi
  int32_t capacity; // ecx
  int v5; // ebx
  int v6; // edx
  TransformMatrix *points; // ecx
  TransformMatrix *v8; // esi
  TransformMatrix *v9; // edi

  point_count = vapour->point_count;
  capacity = vapour->capacity;
  if ( point_count >= capacity )
  {
    v5 = 0;
    if ( capacity - 1 > 0 )
    {
      v6 = 0;
      do
      {
        points = vapour->points;
        ++v5;
        v8 = &points[v6 + 1];
        v9 = &points[v6++];
        qmemcpy(v9, v8, sizeof(TransformMatrix));
      }
      while ( v5 < vapour->capacity - 1 );
    }
    qmemcpy(&vapour->points[vapour->point_count - 1], point, sizeof(vapour->points[vapour->point_count - 1]));
  }
  else
  {
    qmemcpy(&vapour->points[point_count], point, sizeof(vapour->points[point_count]));
    ++vapour->point_count;
  }
}
