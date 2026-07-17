/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_backdrop_slice_quad @ 0x41a1c0 */
/* selector: initialize_backdrop_slice_quad */

// Builds one shared 4-vertex textured backdrop quad using a horizontal 1/8 UV slice selected by the panel index for the `Objects/World00*` lane.
void __cdecl initialize_backdrop_slice_quad(Object *object, char *texture_path, float x_offset)
{
  ObjectFlag flags; // edx
  Vec3 *vertices; // eax
  double v5; // st7
  ObjectFaceQuad *facequads; // esi
  TextureRef *texture_ref; // eax
  double v8; // st7

  request_object_vertices(object, 4);
  request_object_facequads(object, 1);
  flags = object->flags;
  vertices = object->vertices;
  v5 = x_offset + 0.5;
  LOBYTE(flags) = flags | 0x80;
  object->flags = flags;
  facequads = object->facequads;
  vertices->x = v5;
  vertices[2].x = v5;
  vertices->y = 0.0;
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
  facequads->texture_ref = texture_ref;
  v8 = (x_offset + 1.0) * -0.125;
  texture_ref->flags |= 2u;
  facequads->uv[1].u = 0.0;
  facequads->uv[2].u = 0.0;
  facequads->uv[2].v = 0.0;
  facequads->uv[3].v = 0.0;
  facequads->uv[0].u = v8;
  facequads->uv[3].u = v8;
  facequads->uv[0].v = 0.125;
  facequads->uv[1].v = 0.125;
}
