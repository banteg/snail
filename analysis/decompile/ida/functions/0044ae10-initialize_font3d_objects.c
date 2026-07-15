/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_font3d_objects @ 0x44ae10 */
/* selector: initialize_font3d_objects */

// Void materializer for the registered font atlas: borrows one ObjectList slot per glyph into the fixed 128-entry g_font3d_bods array, applies the glyph UVs and x scale, and records the matching scale in g_font3d_scales.
void __cdecl initialize_font3d_objects(int16_t font_id)
{
  int v1; // ebx
  float *v2; // ebp
  void **p_object; // esi
  int v4; // edi
  Object *v5; // eax
  Object *v6; // eax
  int32_t slot_count; // ecx
  int32_t v8; // [esp+4h] [ebp-8h]
  int v9; // [esp+8h] [ebp-4h]
  float font_ida; // [esp+10h] [ebp+4h]

  v8 = 0;
  v1 = 2088 * font_id;
  if ( g_font_sheets[v1 / 0x828u].slot_count > 0 )
  {
    v2 = g_font3d_scales;
    p_object = &g_font3d_bods[0].object;
    v9 = 522 * font_id;
    v4 = 2088 * font_id + 7828740;
    do
    {
      font_ida = *(float *)(v4 + 512) / *(float *)(v1 + 7830276);
      v5 = add_object_to_list(&g_object_list);
      set_bod_object(p_object - 9, (int)v5);
      load_object_definition(aObjectsFont3d, (Object *)*p_object);
      *(p_object - 2) = nullptr;
      *(p_object - 1) = nullptr;
      *(_DWORD *)(*((_DWORD *)*p_object + 23) + 12) = *((_DWORD *)&g_font_sheets[0].texture_ref_a
                                                      + *(_DWORD *)(v4 + 1024)
                                                      + v9);
      *(_DWORD *)(*((_DWORD *)*p_object + 23) + 16) = *(_DWORD *)(v4 - 512);
      *(float *)(*((_DWORD *)*p_object + 23) + 20) = 1.0 - *(float *)(v1 + 7830280);
      *(_DWORD *)(*((_DWORD *)*p_object + 23) + 24) = *(_DWORD *)v4;
      *(float *)(*((_DWORD *)*p_object + 23) + 28) = 1.0 - *(float *)(v1 + 7830280);
      *(_DWORD *)(*((_DWORD *)*p_object + 23) + 32) = *(_DWORD *)v4;
      *(float *)(*((_DWORD *)*p_object + 23) + 36) = 1.0 - *(float *)(v1 + 7830284);
      *(_DWORD *)(*((_DWORD *)*p_object + 23) + 40) = *(_DWORD *)(v4 - 512);
      *(float *)(*((_DWORD *)*p_object + 23) + 44) = 1.0 - *(float *)(v1 + 7830284);
      **((float **)*p_object + 14) = font_ida * **((float **)*p_object + 14);
      *(float *)(*((_DWORD *)*p_object + 14) + 12) = font_ida * *(float *)(*((_DWORD *)*p_object + 14) + 12);
      *(float *)(*((_DWORD *)*p_object + 14) + 24) = font_ida * *(float *)(*((_DWORD *)*p_object + 14) + 24);
      *(float *)(*((_DWORD *)*p_object + 14) + 36) = font_ida * *(float *)(*((_DWORD *)*p_object + 14) + 36);
      *((_DWORD *)*p_object + 5) = 1;
      v6 = (Object *)*p_object;
      p_object += 14;
      v4 += 4;
      ++v2;
      v6->flags |= 0x10u;
      slot_count = g_font_sheets[v1 / 0x828u].slot_count;
      *(v2 - 1) = font_ida;
      ++v8;
    }
    while ( v8 < slot_count );
  }
}
