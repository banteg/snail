/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_backdrop_tile_quad @ 0x41a4d0 */
/* selector: initialize_backdrop_tile_quad */

// Builds one oriented textured backdrop tile quad by choosing one of the eight UV-orientation cases and offsetting the local tile with the supplied row and column selectors.
void __cdecl initialize_backdrop_tile_quad(
        Object *object,
        int32_t edge_selector,
        int32_t orientation,
        int32_t row_selector,
        int32_t column_selector,
        char *texture_path)
{
  Vec3 *vertices; // edi
  ObjectFaceQuad *facequads; // esi
  float *p_z; // ecx
  int v9; // edi
  double v10; // st7
  double v11; // st7
  float v12; // [esp+0h] [ebp-4h]
  float row_selectora; // [esp+14h] [ebp+10h]
  int32_t row_selectorb; // [esp+14h] [ebp+10h]
  int32_t row_selectorc; // [esp+14h] [ebp+10h]
  int32_t row_selectord; // [esp+14h] [ebp+10h]
  int32_t row_selectore; // [esp+14h] [ebp+10h]

  v12 = (double)row_selector * 0.40000001;
  row_selectora = (double)column_selector * 0.40000001;
  request_object_vertices(object, 4);
  request_object_facequads(object, 1);
  vertices = object->vertices;
  facequads = object->facequads;
  vertices->y = 0.0;
  vertices[1].y = 0.0;
  vertices[2].y = 0.0;
  vertices[3].y = 0.0;
  facequads->header_word = 0;
  facequads->vertex_0 = 0;
  facequads->vertex_1 = 1;
  facequads->vertex_2 = 3;
  facequads->vertex_3 = 2;
  facequads->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, 0, 0);
  facequads->uv[1].u = 0.2;
  facequads->uv[2].u = 0.2;
  facequads->uv[0].u = 0.80000001;
  facequads->uv[0].v = 1.0;
  facequads->uv[1].v = 1.0;
  facequads->uv[2].v = 0.0;
  facequads->uv[3].u = 0.80000001;
  facequads->uv[3].v = 0.0;
  switch ( orientation )
  {
    case 0:
      vertices[2].x = 0.5;
      vertices->z = 0.89999998;
      vertices[1].z = 0.89999998;
      vertices[2].z = 0.5;
      vertices[3].x = -0.5;
      vertices->x = v12 + 0.5;
      vertices[3].z = 0.5;
      vertices[1].x = -0.5 - row_selectora;
      break;
    case 1:
      rotate_object_facequad_uv_pairs(facequads);
      vertices[1].x = 0.5;
      vertices->x = 0.89999998;
      vertices[1].z = 0.5;
      vertices[2].x = 0.89999998;
      vertices[3].x = 0.5;
      vertices->z = row_selectora + 0.5;
      vertices[3].z = -0.5;
      vertices[2].z = -0.5 - v12;
      break;
    case 2:
      rotate_object_facequad_uv_pairs(facequads);
      rotate_object_facequad_uv_pairs(facequads);
      rotate_object_facequad_uv_pairs(facequads);
      vertices->x = -0.5;
      vertices->z = 0.5;
      vertices[1].x = -0.89999998;
      vertices[2].x = -0.5;
      vertices[1].z = v12 + 0.5;
      vertices[2].z = -0.5;
      vertices[3].x = -0.89999998;
      vertices[3].z = -0.5 - row_selectora;
      break;
    case 3:
      rotate_object_facequad_uv_pairs(facequads);
      rotate_object_facequad_uv_pairs(facequads);
      vertices->x = 0.5;
      vertices->z = -0.5;
      vertices[1].x = -0.5;
      vertices[1].z = -0.5;
      vertices[2].x = row_selectora + 0.5;
      vertices[2].z = -0.89999998;
      vertices[3].z = -0.89999998;
      vertices[3].x = -0.5 - v12;
      break;
    default:
      break;
  }
  p_z = &vertices->z;
  v9 = 4;
  do
  {
    switch ( edge_selector )
    {
      case 1:
        if ( *(p_z - 2) < 0.0 && *p_z < 0.0 )
        {
          if ( *(p_z - 2) >= 0.0 )
            row_selectorb = *(p_z - 2) != 0.0;
          else
            row_selectorb = -1;
          *(p_z - 2) = *(p_z - 2) - (double)row_selectorb * 0.2;
          if ( *p_z >= 0.0 )
            *p_z = *p_z - (double)(*p_z != 0.0) * 0.2;
          else
            *p_z = *p_z - (double)-1 * 0.2;
        }
        break;
      case 2:
        if ( *(p_z - 2) < 0.0 && *p_z > 0.0 )
        {
          if ( *(p_z - 2) >= 0.0 )
            row_selectorc = *(p_z - 2) != 0.0;
          else
            row_selectorc = -1;
          *(p_z - 2) = *(p_z - 2) - (double)row_selectorc * 0.2;
          if ( *p_z >= 0.0 )
            *p_z = *p_z - (double)(*p_z != 0.0) * 0.2;
          else
            *p_z = *p_z - (double)-1 * 0.2;
        }
        break;
      case 3:
        if ( *(p_z - 2) > 0.0 && *p_z < 0.0 )
        {
          if ( *(p_z - 2) >= 0.0 )
            row_selectord = *(p_z - 2) != 0.0;
          else
            row_selectord = -1;
          *(p_z - 2) = *(p_z - 2) - (double)row_selectord * 0.2;
          if ( *p_z >= 0.0 )
            *p_z = *p_z - (double)(*p_z != 0.0) * 0.2;
          else
            *p_z = *p_z - (double)-1 * 0.2;
        }
        break;
      case 4:
        if ( *(p_z - 2) > 0.0 && *p_z > 0.0 )
        {
          if ( *(p_z - 2) >= 0.0 )
            row_selectore = *(p_z - 2) != 0.0;
          else
            row_selectore = -1;
          *(p_z - 2) = *(p_z - 2) - (double)row_selectore * 0.2;
          if ( *p_z >= 0.0 )
            *p_z = *p_z - (double)(*p_z != 0.0) * 0.2;
          else
            *p_z = *p_z - (double)-1 * 0.2;
        }
        break;
      case 5:
        if ( *(p_z - 2) > 0.0 )
          goto LABEL_43;
        break;
      case 6:
        goto LABEL_43;
      case 7:
        if ( *(p_z - 2) < 0.0 )
        {
LABEL_43:
          if ( *p_z > 0.0 )
          {
            v10 = *(p_z - 1);
            if ( *(_DWORD *)p_z == 1056964608 )
              v11 = v10 + 0.5;
            else
              v11 = v10 + 0.60000002;
            *(p_z - 1) = v11;
          }
        }
        break;
      default:
        break;
    }
    p_z += 3;
    --v9;
  }
  while ( v9 );
}
