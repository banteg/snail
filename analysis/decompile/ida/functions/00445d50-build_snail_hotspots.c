/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_snail_hotspots @ 0x445d50 */
/* selector: build_snail_hotspots */

// Authored `cRSnail::ExtractHotSpots()`: fills the exact Snail's 19-entry local hotspot bank from named model textures, including CameraSkidStop, CameraSlugDeath, and CameraIntroTalk.
void __thiscall build_snail_hotspots(Snail *snail)
{
  Object *object; // ebp
  char **v2; // ebx
  float *p_z; // esi
  TextureRef *texture_ref; // eax
  int facequad_count; // edx
  int v6; // ecx
  TextureRef **p_texture_ref; // edi
  int vertex_0; // eax
  Vec3 *vertices; // ecx
  double v10; // st7
  float *v11; // eax
  int v12; // ecx
  int v13; // edx

  object = snail->snail_hotspot_body.bod.object;
  v2 = g_snail_hotspot_texture_names;
  p_z = &snail->snail_hotspots_local[0].z;
  do
  {
    *p_z = 0.0;
    *(p_z - 1) = 0.0;
    *(p_z - 2) = 0.0;
    texture_ref = get_or_create_texture_ref(&g_texture_refs, *v2, 0, 0);
    facequad_count = object->facequad_count;
    v6 = 0;
    if ( facequad_count <= 0 )
    {
LABEL_6:
      report_errorf("Cannot find HotPoint Texture %s", *v2);
    }
    else
    {
      p_texture_ref = &object->facequads->texture_ref;
      while ( *p_texture_ref != texture_ref )
      {
        ++v6;
        p_texture_ref += 12;
        if ( v6 >= facequad_count )
          goto LABEL_6;
      }
      vertex_0 = object->facequads[v6].vertex_0;
      vertices = object->vertices;
      vertex_0 *= 3;
      v10 = *(p_z - 2) + *(&vertices->x + vertex_0);
      v11 = &vertices->x + vertex_0;
      *(p_z - 2) = v10;
      *(p_z - 1) = v11[1] + *(p_z - 1);
      *p_z = v11[2] + *p_z;
      v12 = *((_DWORD *)p_z - 1);
      v13 = *(_DWORD *)p_z;
      *(p_z - 2) = *(p_z - 2);
      *((_DWORD *)p_z - 1) = v12;
      *(_DWORD *)p_z = v13;
    }
    ++v2;
    p_z += 3;
  }
  while ( (int)v2 < (int)g_snail_hotspot_texture_names_end );
  snail->snail_hotspots_local[18].y = snail->snail_hotspots_local[18].y + 0.30000001;
}
