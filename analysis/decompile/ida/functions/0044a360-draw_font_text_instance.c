/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: draw_font_text_instance @ 0x44a360 */
/* selector: draw_font_text_instance */

// Void FontPrintReal counterpart over one cFontPrintBuffer: maps each byte through the atlas slot table and submits textured glyph quads. The queue drain discards EAX on every path.
void __cdecl draw_font_text_instance(cFontPrintBuffer *entry)
{
  int32_t horizontal_align; // eax
  char *text; // ebx
  char i; // al
  int v5; // ebp
  int v6; // ecx
  int32_t font_id; // eax
  double v8; // st7
  int32_t v9; // eax
  int v10; // edi
  int32_t v11; // ebx
  Color4f *v12; // eax
  int32_t v13; // eax
  float v14; // [esp+0h] [ebp-8Ch]
  float v15; // [esp+4h] [ebp-88h]
  float v16; // [esp+20h] [ebp-6Ch]
  float v17; // [esp+20h] [ebp-6Ch]
  float v18; // [esp+24h] [ebp-68h]
  float v19; // [esp+24h] [ebp-68h]
  float v20; // [esp+40h] [ebp-4Ch]
  float v21; // [esp+40h] [ebp-4Ch]
  float v22; // [esp+54h] [ebp-38h]
  float font_kind; // [esp+58h] [ebp-34h]
  float line_marker_fraction; // [esp+5Ch] [ebp-30h]
  float v25; // [esp+60h] [ebp-2Ch]
  int line_step_low; // [esp+64h] [ebp-28h]
  float v27; // [esp+68h] [ebp-24h]
  float v28; // [esp+6Ch] [ebp-20h]
  float v29; // [esp+70h] [ebp-1Ch]
  float v30; // [esp+70h] [ebp-1Ch]
  int32_t v31; // [esp+74h] [ebp-18h]
  char *v32; // [esp+78h] [ebp-14h]
  Color4f color; // [esp+7Ch] [ebp-10h] BYREF
  float entrya; // [esp+90h] [ebp+4h]

  entrya = entry->x0;
  horizontal_align = entry->horizontal_align;
  switch ( horizontal_align )
  {
    case 2:
      entrya = entry->anchor_x + 320.0 - measure_font_text_width(entry->text, entry->font_id, entry->text_scale) * 0.5;
      break;
    case 1:
      measure_font_text_width(entry->text, entry->font_id, entry->text_scale);
      entrya = entry->anchor_x + 320.0;
      break;
    case 3:
      entrya = entry->anchor_x + 320.0 - measure_font_text_width(entry->text, entry->font_id, entry->text_scale);
      break;
  }
  text = entry->text;
  v22 = 0.0;
  v32 = text;
  for ( i = *text;
        i;
        entrya = (double)(int)(__int64)g_font_sheets[entry->font_id].glyph_width[v5]
               * g_font_sheets[entry->font_id].width_scale
               * g_font_sheets[entry->font_id].spacing_scale
               * entry->text_scale
               + entrya )
  {
    v5 = font_slot_index_for_char(i);
    v6 = v5 + 522 * entry->font_id;
    v27 = g_font_sheets[0].u0[v6];
    v25 = g_font_sheets[0].v0[v6];
    v20 = g_font_wave_phase_a + v22;
    v31 = g_font_sheets[0].texture_page[v6];
    font_id = entry->font_id;
    line_step_low = LODWORD(g_font_sheets[font_id].line_step);
    line_marker_fraction = g_font_sheets[font_id].line_marker_fraction;
    v8 = sine(v20);
    v29 = v8 * entry->text_wave_amplitude + v8 * entry->text_wave_amplitude;
    v21 = v22 * 3.0 + g_font_wave_phase_a;
    v22 = v22 + 1.0;
    v30 = (float)(int)(__int64)(v29 + entrya);
    v28 = (float)(int)(__int64)(cosine(v21) * entry->text_wave_amplitude * 4.0 + entry->y0);
    if ( v5 != 53 )
    {
      if ( entry->text_wave_enabled )
      {
        if ( g_font_sheets[entry->font_id].font_kind > 0 )
        {
          v9 = entry->font_id;
          v10 = 2088 * v9;
          font_kind = (float)g_font_sheets[v9].font_kind;
          v11 = v9;
          v12 = (Color4f *)set_color_rgba((tColour *)&color, 0.0, 0.0, 0.0, 0.80000001);
          v18 = *(float *)(v10 + 7830276) * entry->text_scale * *(float *)(v10 + 7830288);
          v16 = g_font_sheets[v11].glyph_width[v5] * entry->text_scale * *(float *)(v10 + 7830288);
          v15 = font_kind + v28;
          v14 = font_kind + v30;
          draw_textured_quad_immediate(
            *((_DWORD *)&g_font_sheets[0].texture_ref_a + v31 + v11 * 522),
            v14,
            v15,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            v16,
            v18,
            v27,
            *(float *)&line_step_low,
            v25,
            line_marker_fraction,
            v12,
            2,
            0.0);
          text = v32;
        }
      }
      v13 = entry->font_id;
      v19 = g_font_sheets[entry->font_id].line_marker_y
          * entry->text_scale
          * g_font_sheets[entry->font_id].spacing_scale;
      v17 = g_font_sheets[v13].glyph_width[v5] * entry->text_scale * g_font_sheets[entry->font_id].spacing_scale;
      draw_textured_quad_immediate(
        *((_DWORD *)&g_font_sheets[0].texture_ref_a + v31 + v13 * 522),
        v30,
        v28,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        v17,
        v19,
        v27,
        *(float *)&line_step_low,
        v25,
        line_marker_fraction,
        (Color4f *)&entry->color,
        1,
        0.0);
    }
    i = *++text;
    v32 = text;
  }
}
