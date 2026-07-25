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
  float *__shifted(FringeVertexRowCursorView,0x14) row_cursor; // esi
  uint32_t width_cells; // eax
  uint32_t v10; // ecx
  int v11; // edx
  FringeVertexRowCursorView *v12; // ebx
  Vec3 *v13; // edx
  FringeVertexRowCursorView *v14; // eax
  Vec3 *p_inner_a; // ebp
  Vec3 *v16; // eax
  double v17; // st7
  float v18; // eax
  Vec3 *v19; // eax
  Vec3 *v20; // edx
  double v21; // st7
  float v22; // ecx
  int v23; // ecx
  int v24; // ecx
  uint16_t *__shifted(FringeFaceQuadPairCursorView,2) face_pair_cursor; // esi
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
    row_cursor = &object->vertices[1].z;
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
      v12 = ADJ(row_cursor);
      v13 = &self->bod.object->vertices[v11 + v26 * (width_cells + 1)];
      v14 = ADJ(row_cursor);
      v14->outer_a.x = v13->x;
      v14->outer_a.y = v13->y;
      p_inner_a = &ADJ(row_cursor)->inner_a;
      v14->outer_a.z = v13->z;
      v16 = &self->bod.object->vertices[v10 + v26 * (self->width_cells + 1)];
      p_inner_a->x = v16->x;
      p_inner_a->y = v16->y;
      ADJ(row_cursor)->inner_a.z = v16->z;
      v32.x = ADJ(row_cursor)->inner_a.x - ADJ(row_cursor)->outer_a.x;
      v32.y = ADJ(row_cursor)->inner_a.y - ADJ(row_cursor)->outer_a.y;
      v32.z = ADJ(row_cursor)->inner_a.z - ADJ(row_cursor)->outer_a.z;
      vector = v32;
      normalize_vector(&vector);
      v40 = vector.y * 0.40000001;
      v41 = vector.z * 0.40000001;
      v33 = vector.x * 0.40000001 + ADJ(row_cursor)->inner_a.x;
      v34 = v40 + ADJ(row_cursor)->inner_a.y;
      v17 = v41 + ADJ(row_cursor)->inner_a.z;
      v18 = v34;
      v12->outer_a.x = v33;
      v12->outer_a.y = v18;
      v35 = v17;
      v12->outer_a.z = v35;
      v19 = &self->bod.object->vertices[v28 + v26 * (self->width_cells + 1)];
      ADJ(row_cursor)->outer_b.x = v19->x;
      ADJ(row_cursor)->outer_b.y = v19->y;
      ADJ(row_cursor)->outer_b.z = v19->z;
      v20 = &self->bod.object->vertices[v29 + v26 * (self->width_cells + 1)];
      ADJ(row_cursor)->inner_b.x = v20->x;
      ADJ(row_cursor)->inner_b.y = v20->y;
      ADJ(row_cursor)->inner_b.z = v20->z;
      v36.x = ADJ(row_cursor)->inner_b.x - ADJ(row_cursor)->outer_b.x;
      v36.y = ADJ(row_cursor)->inner_b.y - ADJ(row_cursor)->outer_b.y;
      v36.z = ADJ(row_cursor)->inner_b.z - ADJ(row_cursor)->outer_b.z;
      vector = v36;
      normalize_vector(&vector);
      out.g = vector.y * 0.40000001;
      out.b = vector.z * 0.40000001;
      v37 = vector.x * 0.40000001 + ADJ(row_cursor)->inner_b.x;
      v38 = out.g + ADJ(row_cursor)->inner_b.y;
      v21 = out.b + ADJ(row_cursor)->inner_b.z;
      v22 = v38;
      ADJ(row_cursor)->outer_b.x = v37;
      ADJ(row_cursor)->outer_b.y = v22;
      v39 = v21;
      ADJ(row_cursor)->outer_b.z = v39;
      if ( clamp_side == -1.0 )
      {
        v23 = 4;
        do
        {
          if ( v12->outer_a.x > 0.0 )
            v12->outer_a.x = 0.0;
          v12 = (FringeVertexRowCursorView *)((char *)v12 + 12);
          --v23;
        }
        while ( v23 );
      }
      else if ( clamp_side == 1.0 )
      {
        v24 = 4;
        do
        {
          if ( v12->outer_a.x < 0.0 )
            v12->outer_a.x = 0.0;
          v12 = (FringeVertexRowCursorView *)((char *)v12 + 12);
          --v24;
        }
        while ( v24 );
      }
      row_cursor += 12;
      ++v26;
    }
    while ( v26 <= (signed int)self->segment_count );
  }
  v27 = 0;
  if ( (int)self->segment_count > 0 )
  {
    face_pair_cursor = &facequads->vertex_0;
    do
    {
      ADJ(face_pair_cursor)->first_face.texture_ref = get_or_create_texture_ref(
                                                        &g_texture_refs,
                                                        texture_path,
                                                        nullptr,
                                                        0);
      ADJ(face_pair_cursor)->first_face.vertex_0 = 4 * v27 + 5;
      ADJ(face_pair_cursor)->first_face.vertex_1 = 4 * v27 + 4;
      ADJ(face_pair_cursor)->first_face.vertex_2 = 4 * v27;
      ADJ(face_pair_cursor)->first_face.vertex_3 = 4 * v27 + 1;
      ADJ(face_pair_cursor)->first_face.uv[3].u = 0.5;
      ADJ(face_pair_cursor)->first_face.uv[3].v = 0.0;
      ADJ(face_pair_cursor)->first_face.uv[0].u = 0.5;
      ADJ(face_pair_cursor)->first_face.uv[0].v = 0.0;
      ADJ(face_pair_cursor)->first_face.uv[1].u = 0.5;
      ADJ(face_pair_cursor)->first_face.uv[1].v = 1.0;
      ADJ(face_pair_cursor)->first_face.uv[2].u = 0.5;
      ADJ(face_pair_cursor)->first_face.uv[2].v = 1.0;
      ADJ(face_pair_cursor)->second_face.texture_ref = get_or_create_texture_ref(
                                                         &g_texture_refs,
                                                         texture_path,
                                                         nullptr,
                                                         0);
      ADJ(face_pair_cursor)->second_face.vertex_0 = 4 * v27 + 6;
      ADJ(face_pair_cursor)->second_face.vertex_1 = 4 * v27 + 7;
      ADJ(face_pair_cursor)->second_face.vertex_2 = 4 * v27 + 3;
      ADJ(face_pair_cursor)->second_face.vertex_3 = 4 * v27 + 2;
      ADJ(face_pair_cursor)->second_face.uv[3].u = 0.5;
      ADJ(face_pair_cursor)->second_face.uv[3].v = 1.0;
      ADJ(face_pair_cursor)->second_face.uv[0].u = 0.5;
      ADJ(face_pair_cursor)->second_face.uv[0].v = 1.0;
      ADJ(face_pair_cursor)->second_face.uv[1].u = 0.5;
      ADJ(face_pair_cursor)->second_face.uv[1].v = 0.0;
      ADJ(face_pair_cursor)->second_face.uv[2].u = 0.5;
      ADJ(face_pair_cursor)->second_face.uv[2].v = 0.0;
      face_pair_cursor += 48;
      ++v27;
    }
    while ( v27 < (signed int)self->segment_count );
  }
}
