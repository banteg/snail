/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_snail_hotspots @ 0x445d50 */
/* selector: build_snail_hotspots */

// Authored `cRSnail::ExtractHotSpots()`: fills the exact Snail's 19-entry local hotspot bank from named model textures, including CameraSkidStop, CameraSlugDeath, and CameraIntroTalk.
void __thiscall build_snail_hotspots(Snail *snail)
{
  Object *hotspot_model; // ebp
  char **hotspot_name_cursor; // ebx
  float *__shifted(SnailHotspotLocalZCursorView,8) hotspot_local_z_cursor; // esi
  TextureRef *texture_ref; // eax
  int32_t facequad_count; // edx
  int32_t v6; // ecx
  TextureRef **__shifted(ObjectFaceQuadTextureCursorView,0xC) hotspot_face_texture_cursor; // edi
  int vertex_0; // eax
  Vec3 *vertices; // ecx
  double v10; // st7
  Vec3 *hotspot_source_vertex; // eax
  float y; // ecx
  float z; // edx

  hotspot_model = snail->snail_hotspot_body.bod.object;
  hotspot_name_cursor = g_snail_hotspot_texture_names;
  hotspot_local_z_cursor = &snail->snail_hotspots_local[0].z;
  do
  {
    ADJ(hotspot_local_z_cursor)->hotspot.z = 0.0;
    ADJ(hotspot_local_z_cursor)->hotspot.y = 0.0;
    ADJ(hotspot_local_z_cursor)->hotspot.x = 0.0;
    texture_ref = get_or_create_texture_ref(&g_texture_refs, *hotspot_name_cursor, nullptr, 0);
    facequad_count = hotspot_model->facequad_count;
    v6 = 0;
    if ( facequad_count <= 0 )
    {
LABEL_6:
      report_errorf("Cannot find HotPoint Texture %s", *hotspot_name_cursor);
    }
    else
    {
      hotspot_face_texture_cursor = &hotspot_model->facequads->texture_ref;
      while ( ADJ(hotspot_face_texture_cursor)->face.texture_ref != texture_ref )
      {
        ++v6;
        hotspot_face_texture_cursor += 12;
        if ( v6 >= facequad_count )
          goto LABEL_6;
      }
      vertex_0 = hotspot_model->facequads[v6].vertex_0;
      vertices = hotspot_model->vertices;
      vertex_0 *= 3;
      v10 = ADJ(hotspot_local_z_cursor)->hotspot.x + *(&vertices->x + vertex_0);
      hotspot_source_vertex = (Vec3 *)((char *)vertices + 4 * vertex_0);
      ADJ(hotspot_local_z_cursor)->hotspot.x = v10;
      ADJ(hotspot_local_z_cursor)->hotspot.y = hotspot_source_vertex->y + ADJ(hotspot_local_z_cursor)->hotspot.y;
      ADJ(hotspot_local_z_cursor)->hotspot.z = hotspot_source_vertex->z + ADJ(hotspot_local_z_cursor)->hotspot.z;
      y = ADJ(hotspot_local_z_cursor)->hotspot.y;
      z = ADJ(hotspot_local_z_cursor)->hotspot.z;
      ADJ(hotspot_local_z_cursor)->hotspot.x = ADJ(hotspot_local_z_cursor)->hotspot.x;
      ADJ(hotspot_local_z_cursor)->hotspot.y = y;
      ADJ(hotspot_local_z_cursor)->hotspot.z = z;
    }
    ++hotspot_name_cursor;
    hotspot_local_z_cursor += 3;
  }
  while ( (int)hotspot_name_cursor < (int)g_snail_hotspot_texture_names_end );
  snail->snail_hotspots_local[18].y = snail->snail_hotspots_local[18].y + 0.30000001;
}
