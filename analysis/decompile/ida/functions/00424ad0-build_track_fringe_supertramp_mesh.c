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
  float *p_z; // edi
  float *v10; // ecx
  Vec3 *v11; // edx
  float *v12; // ecx
  Vec3 *v13; // eax
  double v14; // st7
  float v15; // edx
  Vec3 *v16; // ecx
  Vec3 *v17; // eax
  double v18; // st7
  float v19; // edx
  __int16 v20; // bp
  uint16_t *p_vertex_0; // edi
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
    p_z = &vertices[1].z;
    do
    {
      v10 = p_z - 5;
      v11 = &self->bod.object->vertices[v8 * (self->width_cells + 1) + 1];
      *v10 = v11->x;
      v10[1] = v11->y;
      v10[2] = v11->z;
      v12 = p_z - 2;
      v13 = &self->bod.object->vertices[v8 * (self->width_cells + 1)];
      *v12 = v13->x;
      v12[1] = v13->y;
      *p_z = v13->z;
      v43.x = *(p_z - 2) - *(p_z - 5);
      v43.y = *(p_z - 1) - *(p_z - 4);
      v43.z = *p_z - *(p_z - 3);
      vector = v43;
      normalize_vector(&vector);
      v51 = vector.y * 0.40000001;
      v52 = vector.z * 0.40000001;
      v44 = vector.x * 0.40000001 + *(p_z - 2);
      v45 = v51 + *(p_z - 1);
      v14 = v52 + *p_z;
      v15 = v45;
      *(p_z - 5) = v44;
      *(p_z - 4) = v15;
      v46 = v14;
      *(p_z - 3) = v46;
      v16 = &self->bod.object->vertices[self->width_cells - 1 + v8 * (self->width_cells + 1)];
      p_z[1] = v16->x;
      p_z[2] = v16->y;
      p_z[3] = v16->z;
      v17 = &self->bod.object->vertices[self->width_cells + v8 * (self->width_cells + 1)];
      p_z[4] = v17->x;
      p_z[5] = v17->y;
      p_z[6] = v17->z;
      v47.x = p_z[4] - p_z[1];
      v47.y = p_z[5] - p_z[2];
      v47.z = p_z[6] - p_z[3];
      vector = v47;
      normalize_vector(&vector);
      ++v8;
      p_z += 12;
      v53 = vector.y * 0.40000001;
      v54 = vector.z * 0.40000001;
      v48 = vector.x * 0.40000001 + *(p_z - 8);
      v49 = v53 + *(p_z - 7);
      v18 = v54 + *(p_z - 6);
      v19 = v49;
      *(p_z - 11) = v48;
      *(p_z - 10) = v19;
      v50 = v18;
      *(p_z - 9) = v50;
    }
    while ( v8 <= (signed int)self->segment_count );
    vertices = v41;
  }
  v20 = 0;
  v40 = 0;
  if ( (int)self->segment_count > 0 )
  {
    p_vertex_0 = &facequads->vertex_0;
    while ( 1 )
    {
      texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0);
      v23 = 4 * v20 + 4;
      *(_DWORD *)(p_vertex_0 + 5) = texture_ref;
      v24 = 4 * v20;
      *p_vertex_0 = v23;
      p_vertex_0[1] = v24 + 5;
      p_vertex_0[2] = v24 + 1;
      p_vertex_0[3] = v24;
      *(_DWORD *)(p_vertex_0 + 19) = 1056964608;
      *(_DWORD *)(p_vertex_0 + 21) = 1065353216;
      *(_DWORD *)(p_vertex_0 + 7) = 1056964608;
      *(_DWORD *)(p_vertex_0 + 9) = 1065353216;
      *(_DWORD *)(p_vertex_0 + 11) = 1056964608;
      *(_DWORD *)(p_vertex_0 + 13) = 0;
      *(_DWORD *)(p_vertex_0 + 15) = 1056964608;
      *(_DWORD *)(p_vertex_0 + 17) = 0;
      *(_DWORD *)(p_vertex_0 + 29) = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0);
      p_vertex_0[24] = v24 + 7;
      p_vertex_0[25] = v24 + 6;
      p_vertex_0[26] = v24 + 2;
      p_vertex_0[27] = v24 + 3;
      *(_DWORD *)(p_vertex_0 + 43) = 1056964608;
      *(_DWORD *)(p_vertex_0 + 45) = 0;
      *(_DWORD *)(p_vertex_0 + 31) = 1056964608;
      *(_DWORD *)(p_vertex_0 + 33) = 0;
      *(_DWORD *)(p_vertex_0 + 35) = 1056964608;
      *(_DWORD *)(p_vertex_0 + 37) = 1065353216;
      *(_DWORD *)(p_vertex_0 + 39) = 1056964608;
      *(_DWORD *)(p_vertex_0 + 41) = 1065353216;
      p_vertex_0 += 48;
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
