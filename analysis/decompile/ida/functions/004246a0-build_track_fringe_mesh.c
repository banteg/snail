/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_track_fringe_mesh @ 0x4246a0 */
/* selector: build_track_fringe_mesh */

// Windows `cRPath::BuildFringe(char*, float)`: owns a generated fringe Object through the Path's second BodBase, extrudes both strip edges with authored Vector3 operations, emits two textured facequads per segment, and clamps X only for exact side sentinels -1 or +1. Android and iOS preserve the authored method name.
void __thiscall build_track_fringe_mesh(Path *self, char *texture_path, float clamp_side)
{
  Object *v4; // eax
  tColour *track_skirt_color; // eax
  Object *object; // ebx
  int v7; // ebp
  float *p_z; // esi
  uint32_t width_cells; // eax
  uint32_t v10; // ecx
  int v11; // edx
  float *v12; // ebx
  Vec3 *v13; // edx
  float *v14; // eax
  float *v15; // ebp
  Vec3 *v16; // eax
  double v17; // st7
  float v18; // eax
  Vec3 *v19; // eax
  Vec3 *v20; // edx
  double v21; // st7
  float v22; // ecx
  int v23; // ecx
  int v24; // ecx
  uint16_t *p_vertex_0; // esi
  signed int v26; // [esp+10h] [ebp-68h]
  signed int v27; // [esp+10h] [ebp-68h]
  int v28; // [esp+14h] [ebp-64h]
  uint32_t v29; // [esp+18h] [ebp-60h]
  ObjectFaceQuad *facequads; // [esp+1Ch] [ebp-5Ch]
  Vec3 vector; // [esp+20h] [ebp-58h] BYREF
  Vec3 v32; // [esp+2Ch] [ebp-4Ch]
  float v33; // [esp+38h] [ebp-40h]
  float v34; // [esp+3Ch] [ebp-3Ch]
  float v35; // [esp+40h] [ebp-38h]
  Vec3 v36; // [esp+44h] [ebp-34h]
  float v37; // [esp+50h] [ebp-28h]
  float v38; // [esp+54h] [ebp-24h]
  float v39; // [esp+58h] [ebp-20h]
  float v40; // [esp+60h] [ebp-18h]
  float v41; // [esp+64h] [ebp-14h]
  tColour out; // [esp+68h] [ebp-10h] BYREF

  v4 = add_object_to_list(&g_object_list);
  set_bod_object(&self->fringe_mesh_bod, v4);
  track_skirt_color = get_track_skirt_color(&g_game_base->subgame, &out);
  object = self->fringe_mesh_bod.object;
  self->fringe_mesh_bod.color = *track_skirt_color;
  v7 = object->flags | 0x100040;
  object->blend_mode = 5;
  object->flags = v7;
  request_object_vertices(object, 4 * self->segment_count + 4);
  request_object_facequads(object, 2 * self->segment_count);
  facequads = object->facequads;
  v26 = 0;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    p_z = &object->vertices[1].z;
    do
    {
      width_cells = self->width_cells;
      if ( self->is_mirrored_x )
      {
        v28 = 1;
        v10 = self->width_cells;
        v29 = 0;
        v11 = width_cells - 1;
      }
      else
      {
        v10 = 0;
        v11 = 1;
        v29 = self->width_cells;
        v28 = width_cells - 1;
      }
      v12 = p_z - 5;
      v13 = &self->bod.object->vertices[v11 + v26 * (width_cells + 1)];
      v14 = p_z - 5;
      *v14 = v13->x;
      v14[1] = v13->y;
      v15 = p_z - 2;
      v14[2] = v13->z;
      v16 = &self->bod.object->vertices[v10 + v26 * (self->width_cells + 1)];
      *v15 = v16->x;
      v15[1] = v16->y;
      *p_z = v16->z;
      v32.x = *(p_z - 2) - *(p_z - 5);
      v32.y = *(p_z - 1) - *(p_z - 4);
      v32.z = *p_z - *(p_z - 3);
      vector = v32;
      normalize_vector(&vector);
      v40 = vector.y * 0.40000001;
      v41 = vector.z * 0.40000001;
      v33 = vector.x * 0.40000001 + *(p_z - 2);
      v34 = v40 + *(p_z - 1);
      v17 = v41 + *p_z;
      v18 = v34;
      *v12 = v33;
      v12[1] = v18;
      v35 = v17;
      v12[2] = v35;
      v19 = &self->bod.object->vertices[v28 + v26 * (self->width_cells + 1)];
      p_z[1] = v19->x;
      p_z[2] = v19->y;
      p_z[3] = v19->z;
      v20 = &self->bod.object->vertices[v29 + v26 * (self->width_cells + 1)];
      p_z[4] = v20->x;
      p_z[5] = v20->y;
      p_z[6] = v20->z;
      v36.x = p_z[4] - p_z[1];
      v36.y = p_z[5] - p_z[2];
      v36.z = p_z[6] - p_z[3];
      vector = v36;
      normalize_vector(&vector);
      out.g = vector.y * 0.40000001;
      out.b = vector.z * 0.40000001;
      v37 = vector.x * 0.40000001 + p_z[4];
      v38 = out.g + p_z[5];
      v21 = out.b + p_z[6];
      v22 = v38;
      p_z[1] = v37;
      p_z[2] = v22;
      v39 = v21;
      p_z[3] = v39;
      if ( clamp_side == -1.0 )
      {
        v23 = 4;
        do
        {
          if ( *v12 > 0.0 )
            *v12 = 0.0;
          v12 += 3;
          --v23;
        }
        while ( v23 );
      }
      else if ( clamp_side == 1.0 )
      {
        v24 = 4;
        do
        {
          if ( *v12 < 0.0 )
            *v12 = 0.0;
          v12 += 3;
          --v24;
        }
        while ( v24 );
      }
      p_z += 12;
      ++v26;
    }
    while ( v26 <= (signed int)self->segment_count );
  }
  v27 = 0;
  if ( (int)self->segment_count > 0 )
  {
    p_vertex_0 = &facequads->vertex_0;
    do
    {
      *(_DWORD *)(p_vertex_0 + 5) = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0);
      *p_vertex_0 = 4 * v27 + 5;
      p_vertex_0[1] = 4 * v27 + 4;
      p_vertex_0[2] = 4 * v27;
      p_vertex_0[3] = 4 * v27 + 1;
      *(_DWORD *)(p_vertex_0 + 19) = 1056964608;
      *(_DWORD *)(p_vertex_0 + 21) = 0;
      *(_DWORD *)(p_vertex_0 + 7) = 1056964608;
      *(_DWORD *)(p_vertex_0 + 9) = 0;
      *(_DWORD *)(p_vertex_0 + 11) = 1056964608;
      *(_DWORD *)(p_vertex_0 + 13) = 1065353216;
      *(_DWORD *)(p_vertex_0 + 15) = 1056964608;
      *(_DWORD *)(p_vertex_0 + 17) = 1065353216;
      *(_DWORD *)(p_vertex_0 + 29) = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0);
      p_vertex_0[24] = 4 * v27 + 6;
      p_vertex_0[25] = 4 * v27 + 7;
      p_vertex_0[26] = 4 * v27 + 3;
      p_vertex_0[27] = 4 * v27 + 2;
      *(_DWORD *)(p_vertex_0 + 43) = 1056964608;
      *(_DWORD *)(p_vertex_0 + 45) = 1065353216;
      *(_DWORD *)(p_vertex_0 + 31) = 1056964608;
      *(_DWORD *)(p_vertex_0 + 33) = 1065353216;
      *(_DWORD *)(p_vertex_0 + 35) = 1056964608;
      *(_DWORD *)(p_vertex_0 + 37) = 0;
      *(_DWORD *)(p_vertex_0 + 39) = 1056964608;
      *(_DWORD *)(p_vertex_0 + 41) = 0;
      p_vertex_0 += 48;
      ++v27;
    }
    while ( v27 < (signed int)self->segment_count );
  }
}
