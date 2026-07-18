/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: apply_distort_to_object @ 0x41aa50 */
/* selector: apply_distort_to_object */

// Applies the embedded ObjectDistort subobject's optional Z-wave, Y-squash, and XYZ-scale passes to an Object's copied vertex array, chaining active passes through that copy before redirecting the live vertex view and refreshing simple face normals.
void __thiscall apply_distort_to_object(ObjectDistort *distort, Object *object)
{
  char v4; // cl
  Vec3 *vertices; // ebx
  double z; // st7
  char v8; // c0
  double v10; // st6
  char v11; // c0
  double v13; // st7
  char v14; // c0
  char v16; // c0
  int32_t vertex_count; // eax
  int32_t v18; // ebp
  int v19; // edi
  float *p_z; // ebx
  double v22; // st7
  char v23; // c0
  double v24; // st7
  int32_t v25; // edx
  int v26; // eax
  float *v27; // ecx
  double v28; // st7
  double v29; // st7
  int32_t v30; // edx
  int v31; // eax
  float *v32; // ecx
  double v33; // st7
  float v34; // [esp+0h] [ebp-1Ch]
  float v35; // [esp+0h] [ebp-1Ch]
  float v36; // [esp+0h] [ebp-1Ch]
  float v37; // [esp+0h] [ebp-1Ch]
  float v38; // [esp+0h] [ebp-1Ch]
  ObjectDistort *v39; // [esp+14h] [ebp-8h]
  float v40; // [esp+14h] [ebp-8h]
  float v41; // [esp+18h] [ebp-4h]
  float v42; // [esp+18h] [ebp-4h]
  float objecta; // [esp+20h] [ebp+4h]
  float objectb; // [esp+20h] [ebp+4h]
  float objectc; // [esp+20h] [ebp+4h]

  v4 = 0;
  v39 = distort;
  vertices = object->vertices;
  if ( distort->z_wave == 0.0 )
    goto LABEL_18;
  z = object->bounds_min.z;
  if ( v8 )
    z = -z;
  v10 = object->bounds_max.z;
  if ( v11 )
    v10 = -v10;
  if ( z >= v10 )
  {
    v13 = object->bounds_min.z;
    if ( v16 )
LABEL_10:
      v13 = -v13;
  }
  else
  {
    v13 = object->bounds_max.z;
    if ( v14 )
      goto LABEL_10;
  }
  vertex_count = object->vertex_count;
  v18 = 0;
  objecta = v13;
  if ( vertex_count > 0 )
  {
    v19 = 0;
    p_z = &vertices->z;
    do
    {
      object->copied_vertices[v19].x = *(p_z - 2);
      v22 = object->vertices[v19].z;
      if ( v23 )
        v22 = -v22;
      v34 = v22 * 1.5707964 / objecta + 4.712389;
      ++v18;
      ++v19;
      p_z += 3;
      object->copied_vertices[v19 - 1].y = (sine(v34) + 1.0) * v39->z_wave + *(p_z - 4);
      object->copied_vertices[v19 - 1].z = *(p_z - 3);
    }
    while ( v18 < object->vertex_count );
    distort = v39;
  }
  vertices = object->copied_vertices;
  v4 = 1;
LABEL_18:
  if ( distort->y_squash != 0.0 )
  {
    v35 = distort->y_squash * 1.5707964;
    v40 = sine(v35) + 1.0;
    v36 = distort->y_squash * 1.5707964;
    v24 = sine(v36);
    v25 = 0;
    v41 = 1.0 - v24;
    objectb = object->bounds_min.y;
    if ( object->vertex_count > 0 )
    {
      v26 = 0;
      v27 = &vertices->z;
      do
      {
        v28 = v40 * *(v27 - 2);
        ++v25;
        ++v26;
        v27 += 3;
        object->copied_vertices[v26 - 1].x = v28;
        object->copied_vertices[v26 - 1].y = (*(v27 - 4) - objectb) * v41 + objectb;
        object->copied_vertices[v26 - 1].z = *(v27 - 3);
      }
      while ( v25 < object->vertex_count );
    }
    vertices = object->copied_vertices;
    v4 = 1;
  }
  if ( distort->xyz_scale == 0.0 )
  {
    if ( !v4 )
      return;
  }
  else
  {
    v37 = distort->xyz_scale * 1.5707964;
    objectc = sine(v37) * 0.1 + 1.0;
    v38 = distort->xyz_scale * 1.5707964;
    v29 = sine(v38);
    v30 = 0;
    v42 = 1.0 - v29;
    if ( object->vertex_count > 0 )
    {
      v31 = 0;
      v32 = &vertices->z;
      do
      {
        v33 = objectc * *(v32 - 2);
        ++v30;
        ++v31;
        v32 += 3;
        object->copied_vertices[v31 - 1].x = v33;
        object->copied_vertices[v31 - 1].y = objectc * *(v32 - 4);
        object->copied_vertices[v31 - 1].z = v42 * *(v32 - 3);
      }
      while ( v30 < object->vertex_count );
    }
  }
  object->vertices = object->copied_vertices;
  calc_object_facequad_normals_simple(object);
}
