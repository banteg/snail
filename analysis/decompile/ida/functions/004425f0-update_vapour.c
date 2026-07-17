/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_vapour @ 0x4425f0 */
/* selector: update_vapour */

// Exact void Windows `cRVapour::AI()`: clamps retained transform samples, expands each segment into four borrowed `cRObject` vertices, maps facequad V coordinates from 0 through 0.5 to 1 across the strip, and publishes `2 * point_count - 2` through `Object::group_primitive_counts`. Android preserves the same direct-return void contract and real cRObject ownership.
void __thiscall update_vapour(Vapour *vapour)
{
  int32_t point_count; // eax
  uint32_t list_flags; // eax
  int32_t v3; // ebx
  int v4; // edi
  float *z_floor; // esi
  float *p_z; // edx
  int i; // edi
  double half_width; // st7
  TransformMatrix *v9; // eax
  double v10; // st7
  int v11; // eax
  Vec3 *v12; // esi
  double v13; // st7
  TransformMatrix *v14; // esi
  double v15; // st7
  TransformMatrix *v16; // esi
  double v17; // st7
  TransformMatrix *v18; // edx
  int32_t v19; // edx
  Object *object; // edx
  bool v21; // zf
  float v22; // [esp+0h] [ebp-60h]
  float v23; // [esp+4h] [ebp-5Ch]
  float v24; // [esp+8h] [ebp-58h]
  float v25; // [esp+30h] [ebp-30h]
  float v26; // [esp+34h] [ebp-2Ch]
  float v27; // [esp+3Ch] [ebp-24h]
  float v28; // [esp+40h] [ebp-20h]
  float v29; // [esp+48h] [ebp-18h]
  float v30; // [esp+4Ch] [ebp-14h]
  float v31; // [esp+54h] [ebp-Ch]
  float v32; // [esp+58h] [ebp-8h]
  Vec3 v33; // 0:^1C.12
  Vec3 v34; // 0:^28.12
  Vec3 v35; // 0:^34.12

  point_count = vapour->point_count;
  if ( point_count < 2 )
  {
    list_flags = vapour->body.bod.bod.list_flags;
    LOBYTE(list_flags) = list_flags & 0xDF;
    vapour->body.bod.bod.list_flags = list_flags;
    return;
  }
  vapour->body.bod.bod.list_flags |= 0x20u;
  vapour->body.bod.object->vertex_count = 4 * point_count - 4;
  if ( vapour->z_floor )
  {
    v3 = 0;
    if ( vapour->point_count > 0 )
    {
      v4 = 0;
      do
      {
        z_floor = vapour->z_floor;
        p_z = &vapour->points[v4].position.z;
        if ( *p_z < (double)*z_floor )
          *p_z = *z_floor;
        ++v3;
        ++v4;
      }
      while ( v3 < vapour->point_count );
    }
  }
  for ( i = 0; i < vapour->point_count - 1; ++i )
  {
    half_width = vapour->half_width;
    v9 = &vapour->points[i];
    v25 = half_width * v9->basis_right.x;
    v26 = half_width * v9->basis_right.y;
    v22 = v25 + v9->position.x;
    v23 = v26 + v9->position.y;
    v10 = half_width * v9->basis_right.z + v9->position.z;
    v11 = i;
    v12 = &vapour->body.bod.object->vertices[4 * i];
    v24 = v10;
    v12->x = v22;
    v12->y = v23;
    v12->z = v24;
    v13 = -vapour->half_width;
    v14 = &vapour->points[i];
    v27 = v13 * v14->basis_right.x;
    v28 = v13 * v14->basis_right.y;
    v33.x = v27 + v14->position.x;
    v33.y = v28 + v14->position.y;
    v33.z = v13 * v14->basis_right.z + v14->position.z;
    vapour->body.bod.object->vertices[4 * i + 1] = v33;
    v15 = -vapour->half_width;
    v16 = &vapour->points[i];
    v29 = v15 * v16->basis_right.x;
    v30 = v15 * v16->basis_right.y;
    v34.x = v29 + v16[1].position.x;
    v34.y = v30 + v16[1].position.y;
    v34.z = v15 * v16->basis_right.z + v16[1].position.z;
    vapour->body.bod.object->vertices[4 * i + 2] = v34;
    v17 = vapour->half_width;
    v18 = &vapour->points[i];
    v31 = v17 * v18->basis_right.x;
    v32 = v17 * v18->basis_right.y;
    v35.x = v31 + v18[1].position.x;
    v35.y = v32 + v18[1].position.y;
    v35.z = v17 * v18->basis_right.z + v18[1].position.z;
    vapour->body.bod.object->vertices[4 * i + 3] = v35;
    v19 = vapour->point_count;
    if ( v19 == 2 )
    {
      vapour->body.bod.object->facequads[v11].uv[0].v = 0.0;
      vapour->body.bod.object->facequads[v11].uv[1].v = 0.0;
      object = vapour->body.bod.object;
    }
    else
    {
      if ( !i )
      {
        vapour->body.bod.object->facequads->uv[0].v = 0.0;
        vapour->body.bod.object->facequads->uv[1].v = 0.0;
        vapour->body.bod.object->facequads->uv[2].v = 0.5;
        vapour->body.bod.object->facequads->uv[3].v = 0.5;
        continue;
      }
      v21 = i == v19 - 2;
      vapour->body.bod.object->facequads[v11].uv[0].v = 0.5;
      vapour->body.bod.object->facequads[v11].uv[1].v = 0.5;
      object = vapour->body.bod.object;
      if ( !v21 )
      {
        object->facequads[v11].uv[2].v = 0.5;
        vapour->body.bod.object->facequads[v11].uv[3].v = 0.5;
        continue;
      }
    }
    object->facequads[v11].uv[2].v = 1.0;
    vapour->body.bod.object->facequads[v11].uv[3].v = 1.0;
  }
  *vapour->body.bod.object->group_primitive_counts = 2 * vapour->point_count - 2;
}
