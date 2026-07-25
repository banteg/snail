/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_track_fringe_supertramp_mesh @ 0x424ad0 */
/* selector: build_track_fringe_supertramp_mesh */

// Windows `cRPath::BuildFringeSuperTramp(char*)`: owns a generated fringe Object through the Path's second BodBase, emits the two extruded side strips, extrapolates two terminal cap vertices, and appends the final cap facequad. Android and iOS preserve the authored method name.
void __thiscall build_track_fringe_supertramp_mesh(Path *self, char *texture_path)
{
  Object *v3; // eax
  Object *object; // ebx
  ObjectFlag flags; // edi
  Vec3 *vertices; // edi
  ObjectFaceQuad *facequads; // ebx
  signed int v8; // ebp
  float *__shifted(FringeVertexRowCursorView,0x14) row_cursor; // edi
  FringeVertexRowCursorView *v10; // ecx
  Vec3 *v11; // edx
  Vec3 *p_inner_a; // ecx
  Vec3 *v13; // eax
  double v14; // st7
  float v15; // edx
  Vec3 *v16; // ecx
  Vec3 *v17; // eax
  double v18; // st7
  float v19; // edx
  __int16 v20; // bp
  uint16_t *__shifted(FringeFaceQuadPairCursorView,2) face_pair_cursor; // edi
  TextureRef *texture_ref; // eax
  uint16_t v23; // dx
  uint16_t v24; // bp
  float *p_x; // eax
  double v26; // st7
  float *v27; // ecx
  double v28; // st7
  float v29; // eax
  float *v30; // eax
  double v31; // st7
  double v32; // st6
  double v33; // st7
  float v34; // edx
  uint32_t segment_count; // eax
  _DWORD *v36; // edx
  _DWORD *v37; // eax
  _DWORD *v38; // edi
  _DWORD *v39; // ecx
  int v40; // [esp+10h] [ebp-5Ch]
  Vec3 *v41; // [esp+14h] [ebp-58h]
  Vec3 vector; // [esp+18h] [ebp-54h] BYREF
  Vec3 v43; // [esp+24h] [ebp-48h]
  float v44; // [esp+30h] [ebp-3Ch]
  float v45; // [esp+34h] [ebp-38h]
  float v46; // [esp+38h] [ebp-34h]
  Vec3 v47; // [esp+3Ch] [ebp-30h]
  float v48; // [esp+48h] [ebp-24h]
  float v49; // [esp+4Ch] [ebp-20h]
  float v50; // [esp+50h] [ebp-1Ch]
  float v51; // [esp+58h] [ebp-14h]
  float v52; // [esp+5Ch] [ebp-10h]
  float v53; // [esp+64h] [ebp-8h]
  float v54; // [esp+68h] [ebp-4h]

  v3 = add_object_to_list(&g_object_list);
  set_bod_object(&self->fringe_mesh_bod, v3);
  object = self->fringe_mesh_bod.object;
  flags = object->flags;
  object->blend_mode = 5;
  object->flags = flags | 0x100000;
  request_object_vertices(object, 4 * self->segment_count + 6);
  request_object_facequads(object, 2 * self->segment_count + 1);
  vertices = object->vertices;
  facequads = object->facequads;
  v8 = 0;
  v41 = vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    row_cursor = &vertices[1].z;
    do
    {
      v10 = ADJ(row_cursor);
      v11 = &self->bod.object->vertices[v8 * (self->width_cells + 1) + 1];
      v10->outer_a.x = v11->x;
      v10->outer_a.y = v11->y;
      v10->outer_a.z = v11->z;
      p_inner_a = &ADJ(row_cursor)->inner_a;
      v13 = &self->bod.object->vertices[v8 * (self->width_cells + 1)];
      p_inner_a->x = v13->x;
      p_inner_a->y = v13->y;
      ADJ(row_cursor)->inner_a.z = v13->z;
      v43.x = ADJ(row_cursor)->inner_a.x - ADJ(row_cursor)->outer_a.x;
      v43.y = ADJ(row_cursor)->inner_a.y - ADJ(row_cursor)->outer_a.y;
      v43.z = ADJ(row_cursor)->inner_a.z - ADJ(row_cursor)->outer_a.z;
      vector = v43;
      normalize_vector(&vector);
      v51 = vector.y * 0.40000001;
      v52 = vector.z * 0.40000001;
      v44 = vector.x * 0.40000001 + ADJ(row_cursor)->inner_a.x;
      v45 = v51 + ADJ(row_cursor)->inner_a.y;
      v14 = v52 + ADJ(row_cursor)->inner_a.z;
      v15 = v45;
      ADJ(row_cursor)->outer_a.x = v44;
      ADJ(row_cursor)->outer_a.y = v15;
      v46 = v14;
      ADJ(row_cursor)->outer_a.z = v46;
      v16 = &self->bod.object->vertices[self->width_cells - 1 + v8 * (self->width_cells + 1)];
      ADJ(row_cursor)->outer_b.x = v16->x;
      ADJ(row_cursor)->outer_b.y = v16->y;
      ADJ(row_cursor)->outer_b.z = v16->z;
      v17 = &self->bod.object->vertices[self->width_cells + v8 * (self->width_cells + 1)];
      ADJ(row_cursor)->inner_b.x = v17->x;
      ADJ(row_cursor)->inner_b.y = v17->y;
      ADJ(row_cursor)->inner_b.z = v17->z;
      v47.x = ADJ(row_cursor)->inner_b.x - ADJ(row_cursor)->outer_b.x;
      v47.y = ADJ(row_cursor)->inner_b.y - ADJ(row_cursor)->outer_b.y;
      v47.z = ADJ(row_cursor)->inner_b.z - ADJ(row_cursor)->outer_b.z;
      vector = v47;
      normalize_vector(&vector);
      ++v8;
      row_cursor += 12;
      v53 = vector.y * 0.40000001;
      v54 = vector.z * 0.40000001;
      v48 = vector.x * 0.40000001 + *(row_cursor - 8);
      v49 = v53 + *(row_cursor - 7);
      v18 = v54 + *(row_cursor - 6);
      v19 = v49;
      *(row_cursor - 11) = v48;
      *(row_cursor - 10) = v19;
      v50 = v18;
      *(row_cursor - 9) = v50;
    }
    while ( v8 <= (signed int)self->segment_count );
    vertices = v41;
  }
  v20 = 0;
  v40 = 0;
  if ( (int)self->segment_count > 0 )
  {
    face_pair_cursor = &facequads->vertex_0;
    while ( 1 )
    {
      texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0);
      v23 = 4 * v20 + 4;
      ADJ(face_pair_cursor)->first_face.texture_ref = texture_ref;
      v24 = 4 * v20;
      ADJ(face_pair_cursor)->first_face.vertex_0 = v23;
      ADJ(face_pair_cursor)->first_face.vertex_1 = v24 + 5;
      ADJ(face_pair_cursor)->first_face.vertex_2 = v24 + 1;
      ADJ(face_pair_cursor)->first_face.vertex_3 = v24;
      ADJ(face_pair_cursor)->first_face.uv[3].u = 0.5;
      ADJ(face_pair_cursor)->first_face.uv[3].v = 1.0;
      ADJ(face_pair_cursor)->first_face.uv[0].u = 0.5;
      ADJ(face_pair_cursor)->first_face.uv[0].v = 1.0;
      ADJ(face_pair_cursor)->first_face.uv[1].u = 0.5;
      ADJ(face_pair_cursor)->first_face.uv[1].v = 0.0;
      ADJ(face_pair_cursor)->first_face.uv[2].u = 0.5;
      ADJ(face_pair_cursor)->first_face.uv[2].v = 0.0;
      ADJ(face_pair_cursor)->second_face.texture_ref = get_or_create_texture_ref(
                                                         &g_texture_refs,
                                                         texture_path,
                                                         nullptr,
                                                         0);
      ADJ(face_pair_cursor)->second_face.vertex_0 = v24 + 7;
      ADJ(face_pair_cursor)->second_face.vertex_1 = v24 + 6;
      ADJ(face_pair_cursor)->second_face.vertex_2 = v24 + 2;
      ADJ(face_pair_cursor)->second_face.vertex_3 = v24 + 3;
      ADJ(face_pair_cursor)->second_face.uv[3].u = 0.5;
      ADJ(face_pair_cursor)->second_face.uv[3].v = 0.0;
      ADJ(face_pair_cursor)->second_face.uv[0].u = 0.5;
      ADJ(face_pair_cursor)->second_face.uv[0].v = 0.0;
      ADJ(face_pair_cursor)->second_face.uv[1].u = 0.5;
      ADJ(face_pair_cursor)->second_face.uv[1].v = 1.0;
      ADJ(face_pair_cursor)->second_face.uv[2].u = 0.5;
      ADJ(face_pair_cursor)->second_face.uv[2].v = 1.0;
      face_pair_cursor += 48;
      if ( ++v40 >= (signed int)self->segment_count )
        break;
      v20 = v40;
    }
    vertices = v41;
  }
  p_x = &vertices[4 * self->segment_count].x;
  v26 = *p_x - *(p_x - 12);
  v27 = &vertices[4 * self->segment_count + 4].x;
  v53 = p_x[1] - *(p_x - 11);
  v54 = p_x[2] - *(p_x - 10);
  v51 = v53 * 0.40000001;
  v52 = v54 * 0.40000001;
  v48 = v26 * 0.40000001 + *p_x;
  v49 = v51 + p_x[1];
  v28 = v52 + p_x[2];
  v29 = v49;
  *v27 = v48;
  v27[1] = v29;
  v50 = v28;
  v27[2] = v50;
  v30 = &vertices[4 * self->segment_count].x;
  v31 = v30[6] - *(v30 - 6);
  v32 = v30[7] - *(v30 - 5);
  v30 += 15;
  v53 = v32;
  v54 = *(v30 - 7) - *(v30 - 19);
  v51 = v53 * 0.40000001;
  v52 = v54 * 0.40000001;
  v48 = v31 * 0.40000001 + *(v30 - 9);
  v49 = v51 + *(v30 - 8);
  v33 = v52 + *(v30 - 7);
  v34 = v49;
  *v30 = v48;
  v30[1] = v34;
  v50 = v33;
  v30[2] = v50;
  segment_count = self->segment_count;
  v36 = (_DWORD *)&vertices[4 * segment_count + 4].x;
  v37 = (_DWORD *)&vertices[4 * segment_count].x;
  *v37 = *v36;
  v37[1] = v36[1];
  v37[2] = v36[2];
  v38 = (_DWORD *)&vertices[4 * self->segment_count].x;
  v39 = v38 + 15;
  v38 += 6;
  *v38 = *v39;
  v38[1] = v39[1];
  v38[2] = v39[2];
  facequads[2 * self->segment_count].texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0);
  facequads[2 * self->segment_count].vertex_0 = 4 * LOWORD(self->segment_count) + 1;
  facequads[2 * self->segment_count].vertex_1 = 4 * LOWORD(self->segment_count) + 3;
  facequads[2 * self->segment_count].vertex_2 = 4 * LOWORD(self->segment_count) + 5;
  facequads[2 * self->segment_count].vertex_3 = 4 * (LOWORD(self->segment_count) + 1);
  facequads[2 * self->segment_count].uv[0].u = 0.5;
  facequads[2 * self->segment_count].uv[0].v = 0.0;
  facequads[2 * self->segment_count].uv[1].u = 0.5;
  facequads[2 * self->segment_count].uv[1].v = 0.0;
  facequads[2 * self->segment_count].uv[2].u = 0.5;
  facequads[2 * self->segment_count].uv[2].v = 1.0;
  facequads[2 * self->segment_count].uv[3].u = 0.5;
  facequads[2 * self->segment_count].uv[3].v = 1.0;
}
