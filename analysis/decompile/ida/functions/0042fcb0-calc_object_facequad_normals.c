/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: calc_object_facequad_normals @ 0x42fcb0 */
/* selector: calc_object_facequad_normals */

// Builds one object's toon-normal data: face-pair normals per quad plus averaged inverted vertex normals for silhouette edge tests. Called from the object build path and again when animated geometry is refreshed. iOS RObject.o names this `cRObject::CalcFaceQuadNormals()`.
void __thiscall calc_object_facequad_normals(Object *object)
{
  float *normal_tally; // ebx
  uint32_t byte_offset; // edi
  Vec3 *vertices; // ecx
  unsigned __int16 *v5; // eax
  float *p_x; // ebp
  float *v7; // edx
  float *v8; // ebp
  double v9; // st7
  Vec3 *v10; // ecx
  char *v11; // eax
  Vec3 *v12; // ecx
  float *v13; // ebp
  float *v14; // edx
  float *v15; // ebp
  double v16; // st7
  Vec3 *v17; // ecx
  char *v18; // ecx
  Vec3 *vertex_normals; // eax
  double v20; // st7
  float *v21; // eax
  Vec3 *v22; // eax
  double v23; // st7
  float *v24; // eax
  Vec3 *v25; // eax
  double v26; // st7
  float *v27; // eax
  ObjectFaceQuad *facequads; // ecx
  Vec3 *v29; // eax
  double v30; // st7
  Vec3 *v31; // eax
  unsigned __int16 v32; // dx
  unsigned __int16 v33; // dx
  Vec3 *v34; // eax
  double v35; // st7
  float *v36; // eax
  Vec3 *v37; // eax
  double v38; // st7
  float *v39; // eax
  Vec3 *v40; // eax
  double v41; // st7
  float *v42; // eax
  ObjectFaceQuad *v43; // ecx
  Vec3 *v44; // eax
  double v45; // st7
  Vec3 *v46; // eax
  unsigned __int16 v47; // dx
  unsigned __int16 v48; // dx
  int32_t vertex_count; // ecx
  unsigned __int16 *v50; // eax
  bool v51; // cc
  float *v52; // ebp
  double v53; // st7
  Vec3 *v54; // eax
  Vec3 *v55; // eax
  double v56; // st7
  float y; // edx
  int32_t face_index; // [esp+10h] [ebp-68h]
  int32_t vertex_index; // [esp+10h] [ebp-68h]
  int32_t normal_index; // [esp+14h] [ebp-64h]
  Vec3 quad_normal; // [esp+18h] [ebp-60h] BYREF
  Vec3 face_normal; // [esp+24h] [ebp-54h] BYREF
  Vec3 rhs; // [esp+30h] [ebp-48h] BYREF
  Vec3 lhs; // [esp+3Ch] [ebp-3Ch] BYREF
  Vec3 v65; // [esp+48h] [ebp-30h]
  Vec3 v66; // [esp+54h] [ebp-24h]
  Vec3 v67; // [esp+60h] [ebp-18h]
  Vec3 v68; // [esp+6Ch] [ebp-Ch]

  request_object_facequad_normals(object);
  normal_tally = (float *)allocate_tracked_memory(4 * object->vertex_count, aNormalTally);
  memset(normal_tally, 0, 4 * object->vertex_count);
  byte_offset = 0;
  face_index = 0;
  if ( object->facequad_count > 0 )
  {
    normal_index = 0;
    do
    {
      vertices = object->vertices;
      v5 = (uint16_t *)((char *)&object->facequads->header_word + byte_offset);
      p_x = &vertices[v5[1]].x;
      v7 = &vertices[v5[2]].x;
      v65.x = *v7 - *p_x;
      v65.y = v7[1] - p_x[1];
      v65.z = v7[2] - p_x[2];
      lhs = v65;
      v8 = &vertices[v5[1]].x;
      LOWORD(v7) = v5[3];
      v9 = vertices[(unsigned __int16)v7].x - *v8;
      v10 = &vertices[(unsigned __int16)v7];
      v66.x = v9;
      v66.y = v10->y - v8[1];
      v66.z = v10->z - v8[2];
      rhs = v66;
      cross_vectors(&face_normal, &lhs, &rhs);
      normalize_vector(&face_normal);
      object->facequad_normals[normal_index] = face_normal;
      v11 = (char *)object->facequads + byte_offset;
      if ( *v11 >= 0 )
      {
        v12 = object->vertices;
        v13 = &v12[*((unsigned __int16 *)v11 + 1)].x;
        v14 = &v12[*((unsigned __int16 *)v11 + 3)].x;
        v67.x = *v14 - *v13;
        v67.y = v14[1] - v13[1];
        v67.z = v14[2] - v13[2];
        lhs = v67;
        v15 = &v12[*((unsigned __int16 *)v11 + 1)].x;
        LOWORD(v14) = *((_WORD *)v11 + 4);
        v16 = v12[(unsigned __int16)v14].x - *v15;
        v17 = &v12[(unsigned __int16)v14];
        v68.x = v16;
        v68.y = v17->y - v15[1];
        v68.z = v17->z - v15[2];
        rhs = v68;
        cross_vectors(&quad_normal, &lhs, &rhs);
        normalize_vector(&quad_normal);
        object->facequad_normals[normal_index + 1] = quad_normal;
      }
      v18 = (char *)object->facequads + byte_offset;
      if ( *v18 >= 0 )
      {
        vertex_normals = object->vertex_normals;
        v20 = quad_normal.x + vertex_normals[*((unsigned __int16 *)v18 + 1)].x;
        v21 = &vertex_normals[*((unsigned __int16 *)v18 + 1)].x;
        *v21 = v20;
        v21[1] = quad_normal.y + v21[1];
        v21[2] = quad_normal.z + v21[2];
        v22 = object->vertex_normals;
        v23 = quad_normal.x + v22[*(unsigned __int16 *)((char *)&object->facequads->vertex_1 + byte_offset)].x;
        v24 = &v22[*(unsigned __int16 *)((char *)&object->facequads->vertex_1 + byte_offset)].x;
        *v24 = v23;
        v24[1] = quad_normal.y + v24[1];
        v24[2] = quad_normal.z + v24[2];
        v25 = object->vertex_normals;
        v26 = quad_normal.x + v25[*(unsigned __int16 *)((char *)&object->facequads->vertex_2 + byte_offset)].x;
        v27 = &v25[*(unsigned __int16 *)((char *)&object->facequads->vertex_2 + byte_offset)].x;
        *v27 = v26;
        v27[1] = quad_normal.y + v27[1];
        v27[2] = quad_normal.z + v27[2];
        facequads = object->facequads;
        v29 = object->vertex_normals;
        v30 = quad_normal.x + v29[*(unsigned __int16 *)((char *)&facequads->vertex_3 + byte_offset)].x;
        v31 = &v29[*(unsigned __int16 *)((char *)&facequads->vertex_3 + byte_offset)];
        v31->x = v30;
        v31->y = quad_normal.y + v31->y;
        v31->z = quad_normal.z + v31->z;
        v32 = *(uint16_t *)((char *)&object->facequads->vertex_0 + byte_offset);
        normal_tally[v32] = normal_tally[v32] + 1.0;
        LOWORD(facequads) = *(uint16_t *)((char *)&object->facequads->vertex_1 + byte_offset);
        normal_tally[(unsigned __int16)facequads] = normal_tally[(unsigned __int16)facequads] + 1.0;
        LOWORD(v31) = *(uint16_t *)((char *)&object->facequads->vertex_2 + byte_offset);
        normal_tally[(unsigned __int16)v31] = normal_tally[(unsigned __int16)v31] + 1.0;
        v33 = *(uint16_t *)((char *)&object->facequads->vertex_3 + byte_offset);
        normal_tally[v33] = normal_tally[v33] + 1.0;
      }
      v34 = object->vertex_normals;
      v35 = face_normal.x + v34[*(unsigned __int16 *)((char *)&object->facequads->vertex_0 + byte_offset)].x;
      v36 = &v34[*(unsigned __int16 *)((char *)&object->facequads->vertex_0 + byte_offset)].x;
      *v36 = v35;
      v36[1] = face_normal.y + v36[1];
      v36[2] = face_normal.z + v36[2];
      v37 = object->vertex_normals;
      v38 = face_normal.x + v37[*(unsigned __int16 *)((char *)&object->facequads->vertex_1 + byte_offset)].x;
      v39 = &v37[*(unsigned __int16 *)((char *)&object->facequads->vertex_1 + byte_offset)].x;
      *v39 = v38;
      v39[1] = face_normal.y + v39[1];
      v39[2] = face_normal.z + v39[2];
      v40 = object->vertex_normals;
      v41 = face_normal.x + v40[*(unsigned __int16 *)((char *)&object->facequads->vertex_2 + byte_offset)].x;
      v42 = &v40[*(unsigned __int16 *)((char *)&object->facequads->vertex_2 + byte_offset)].x;
      *v42 = v41;
      v42[1] = face_normal.y + v42[1];
      v42[2] = face_normal.z + v42[2];
      v43 = object->facequads;
      v44 = object->vertex_normals;
      v45 = face_normal.x + v44[*(unsigned __int16 *)((char *)&v43->vertex_3 + byte_offset)].x;
      v46 = &v44[*(unsigned __int16 *)((char *)&v43->vertex_3 + byte_offset)];
      v46->x = v45;
      v46->y = face_normal.y + v46->y;
      v46->z = face_normal.z + v46->z;
      v47 = *(uint16_t *)((char *)&object->facequads->vertex_0 + byte_offset);
      normal_tally[v47] = normal_tally[v47] + 2.0999999;
      LOWORD(v43) = *(uint16_t *)((char *)&object->facequads->vertex_1 + byte_offset);
      normal_tally[(unsigned __int16)v43] = normal_tally[(unsigned __int16)v43] + 2.0999999;
      LOWORD(v46) = *(uint16_t *)((char *)&object->facequads->vertex_2 + byte_offset);
      normal_tally[(unsigned __int16)v46] = normal_tally[(unsigned __int16)v46] + 2.0999999;
      v48 = *(uint16_t *)((char *)&object->facequads->vertex_3 + byte_offset);
      normal_tally[v48] = normal_tally[v48] + 2.0999999;
      vertex_count = object->vertex_count;
      v50 = (uint16_t *)((char *)&object->facequads->header_word + byte_offset);
      if ( v50[1] > vertex_count || v50[2] > vertex_count || v50[3] > vertex_count || v50[4] > vertex_count )
        report_errorf(aInvalidFaceVer);
      byte_offset += 48;
      v51 = ++face_index < object->facequad_count;
      normal_index += 2;
    }
    while ( v51 );
    byte_offset = 0;
  }
  vertex_index = 0;
  if ( object->vertex_count > 0 )
  {
    v52 = normal_tally;
    do
    {
      v53 = *v52;
      v54 = &object->vertex_normals[byte_offset / 0xC];
      v54->x = v54->x / v53;
      v54->y = v54->y / v53;
      v54->z = v54->z / v53;
      normalize_vector(&object->vertex_normals[byte_offset / 0xC]);
      ++v52;
      v55 = &object->vertex_normals[byte_offset / 0xC];
      byte_offset += 12;
      v68.x = v55->x * -1.0;
      v68.y = v55->y * -1.0;
      v56 = v55->z * -1.0;
      y = v68.y;
      v55->x = v68.x;
      v55->y = y;
      v68.z = v56;
      v55->z = v68.z;
      ++vertex_index;
    }
    while ( vertex_index < object->vertex_count );
  }
  free_tracked_memory(normal_tally);
}
