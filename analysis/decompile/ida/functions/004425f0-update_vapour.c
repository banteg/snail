/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_vapour @ 0x4425f0 */
/* selector: update_vapour */

int32_t __thiscall update_vapour(VapourTrail *trail)
{
  int32_t point_count; // eax
  int32_t result; // eax
  int32_t v3; // ebx
  int v4; // edi
  float *z_floor; // esi
  float *p_z; // edx
  int i; // edi
  double half_width; // st7
  TransformMatrix *v9; // eax
  double v10; // st7
  int v11; // eax
  VapourQuadVertices *v12; // esi
  double v13; // st7
  TransformMatrix *v14; // esi
  double v15; // st7
  TransformMatrix *v16; // esi
  double v17; // st7
  TransformMatrix *v18; // edx
  int32_t v19; // edx
  VapourTrailOwner *owner; // edx
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

  point_count = trail->point_count;
  if ( point_count < 2 )
  {
    result = trail->flags;
    LOBYTE(result) = result & 0xDF;
    trail->flags = result;
    return result;
  }
  trail->flags |= 0x20u;
  trail->owner->vertex_count = 4 * point_count - 4;
  if ( trail->z_floor )
  {
    v3 = 0;
    if ( trail->point_count > 0 )
    {
      v4 = 0;
      do
      {
        z_floor = (float *)trail->z_floor;
        p_z = &trail->points[v4].position.z;
        if ( *p_z < (double)*z_floor )
          *p_z = *z_floor;
        ++v3;
        ++v4;
      }
      while ( v3 < trail->point_count );
    }
  }
  for ( i = 0; i < trail->point_count - 1; ++i )
  {
    half_width = trail->half_width;
    v9 = &trail->points[i];
    v25 = half_width * v9->basis_right.x;
    v26 = half_width * v9->basis_right.y;
    v22 = v25 + v9->position.x;
    v23 = v26 + v9->position.y;
    v10 = half_width * v9->basis_right.z + v9->position.z;
    v11 = 12 * i;
    v12 = &trail->owner->vertices[i];
    v24 = v10;
    v12->corner_a.x = v22;
    v12->corner_a.y = v23;
    v12->corner_a.z = v24;
    v13 = -trail->half_width;
    v14 = &trail->points[i];
    v27 = v13 * v14->basis_right.x;
    v28 = v13 * v14->basis_right.y;
    v33.x = v27 + v14->position.x;
    v33.y = v28 + v14->position.y;
    v33.z = v13 * v14->basis_right.z + v14->position.z;
    trail->owner->vertices[i].corner_b = v33;
    v15 = -trail->half_width;
    v16 = &trail->points[i];
    v29 = v15 * v16->basis_right.x;
    v30 = v15 * v16->basis_right.y;
    v34.x = v29 + v16[1].position.x;
    v34.y = v30 + v16[1].position.y;
    v34.z = v15 * v16->basis_right.z + v16[1].position.z;
    trail->owner->vertices[i].corner_c = v34;
    v17 = trail->half_width;
    v18 = &trail->points[i];
    v31 = v17 * v18->basis_right.x;
    v32 = v17 * v18->basis_right.y;
    v35.x = v31 + v18[1].position.x;
    v35.y = v32 + v18[1].position.y;
    v35.z = v17 * v18->basis_right.z + v18[1].position.z;
    trail->owner->vertices[i].corner_d = v35;
    v19 = trail->point_count;
    if ( v19 == 2 )
    {
      trail->owner->vertex_attributes[v11 + 5] = 0;
      trail->owner->vertex_attributes[v11 + 7] = 0;
      owner = trail->owner;
    }
    else
    {
      if ( !i )
      {
        trail->owner->vertex_attributes[5] = 0;
        trail->owner->vertex_attributes[7] = 0;
        trail->owner->vertex_attributes[9] = 1056964608;
        trail->owner->vertex_attributes[11] = 1056964608;
        continue;
      }
      v21 = i == v19 - 2;
      trail->owner->vertex_attributes[v11 + 5] = 1056964608;
      trail->owner->vertex_attributes[v11 + 7] = 1056964608;
      owner = trail->owner;
      if ( !v21 )
      {
        owner->vertex_attributes[v11 + 9] = 1056964608;
        trail->owner->vertex_attributes[v11 + 11] = 1056964608;
        continue;
      }
    }
    owner->vertex_attributes[v11 + 9] = 1065353216;
    trail->owner->vertex_attributes[v11 + 11] = 1065353216;
  }
  result = 2 * trail->point_count - 2;
  *trail->owner->index_count_out = result;
  return result;
}

