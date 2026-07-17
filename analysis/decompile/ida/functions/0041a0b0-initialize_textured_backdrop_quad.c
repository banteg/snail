/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_textured_backdrop_quad @ 0x41a0b0 */
/* selector: initialize_textured_backdrop_quad */

// Builds one shared 4-vertex textured backdrop quad with full-range UVs for the `Objects/Univers*` lane.
void __cdecl initialize_textured_backdrop_quad(Object *object, char *texture_path, float x_offset)
{
  double v3; // st7
  Vec3 *vertices; // eax
  ObjectFaceQuad *facequads; // esi
  TextureRef *texture_ref; // eax
  double v7; // st7

  request_object_vertices(object, 4);
  request_object_facequads(object, 1);
  v3 = x_offset + 0.5;
  vertices = object->vertices;
  facequads = object->facequads;
  vertices->y = 0.0;
  vertices->x = v3;
  vertices[2].x = v3;
  vertices->z = 0.5;
  vertices[1].x = -0.5;
  vertices[1].y = 0.0;
  vertices[1].z = 0.5;
  vertices[2].y = 0.0;
  vertices[2].z = -0.5;
  vertices[3].x = -0.5;
  vertices[3].y = 0.0;
  vertices[3].z = -0.5;
  facequads->header_word = 0;
  facequads->vertex_0 = 0;
  facequads->vertex_1 = 1;
  facequads->vertex_2 = 3;
  facequads->vertex_3 = 2;
  texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, 0, 0);
  v7 = x_offset + 1.0;
  facequads->texture_ref = texture_ref;
  texture_ref->flags |= 2u;
  facequads->uv[1].u = v7;
  facequads->uv[2].u = v7;
  facequads->uv[0].u = 0.0;
  facequads->uv[2].v = 0.0;
  facequads->uv[3].u = 0.0;
  facequads->uv[3].v = 0.0;
  facequads->uv[0].v = 1.0;
  facequads->uv[1].v = 1.0;
}
