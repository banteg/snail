/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: draw_frontend_widget @ 0x401130 */
/* selector: draw_frontend_widget */

// Authored void `cRBorder::Draw()` renderer for one owned front-end widget: emits slider strips, sprite/icon quads, the nine-slice border body, shadow, and the BorderManager-owned delayed glow. Android preserves the same receiver and render branches; the sole Windows caller discards EAX.
void __thiscall draw_frontend_widget(FrontendWidget *widget)
{
  FrontendWidgetFlag widget_flags; // eax
  int32_t v3; // ebx
  double slider_position_current; // st7
  float g; // edx
  double v6; // st7
  double v7; // st6
  double v8; // st7
  tColour *v9; // eax
  double v10; // st7
  double v11; // st7
  float v12; // edi
  float v13; // ebp
  float v14; // ebx
  float v15; // ebp
  float v16; // esi
  int32_t v17; // [esp-Ch] [ebp-C4h]
  float v18; // [esp+0h] [ebp-B8h]
  float v19; // [esp+0h] [ebp-B8h]
  int v20; // [esp+0h] [ebp-B8h]
  float v21; // [esp+0h] [ebp-B8h]
  float v22; // [esp+0h] [ebp-B8h]
  float v23; // [esp+4h] [ebp-B4h]
  float v24; // [esp+4h] [ebp-B4h]
  int v25; // [esp+4h] [ebp-B4h]
  float v26; // [esp+4h] [ebp-B4h]
  float v27; // [esp+4h] [ebp-B4h]
  float v28; // [esp+8h] [ebp-B0h]
  float v29; // [esp+8h] [ebp-B0h]
  float v30; // [esp+8h] [ebp-B0h]
  float v31; // [esp+8h] [ebp-B0h]
  float v32; // [esp+8h] [ebp-B0h]
  float v33; // [esp+Ch] [ebp-ACh]
  float v34; // [esp+Ch] [ebp-ACh]
  float v35; // [esp+Ch] [ebp-ACh]
  tColour *p_current_text_color; // [esp+14h] [ebp-A4h]
  int32_t texture_layer; // [esp+28h] [ebp-90h]
  float a; // [esp+2Ch] [ebp-8Ch]
  float aa; // [esp+2Ch] [ebp-8Ch]
  int texture_hit_y_low; // [esp+40h] [ebp-78h]
  int texture_hit_x_low; // [esp+44h] [ebp-74h]
  int32_t v42; // [esp+48h] [ebp-70h]
  float layout_height; // [esp+4Ch] [ebp-6Ch]
  float layout_width; // [esp+50h] [ebp-68h]
  float current_padding; // [esp+54h] [ebp-64h]
  int slider_position_current_low; // [esp+58h] [ebp-60h]
  float v47; // [esp+58h] [ebp-60h]
  int v48; // [esp+58h] [ebp-60h]
  float v49; // [esp+5Ch] [ebp-5Ch]
  float v50; // [esp+5Ch] [ebp-5Ch]
  float v51; // [esp+5Ch] [ebp-5Ch]
  float v52; // [esp+60h] [ebp-58h]
  float v53; // [esp+60h] [ebp-58h]
  float v54; // [esp+64h] [ebp-54h]
  float v55; // [esp+64h] [ebp-54h]
  float v56; // [esp+64h] [ebp-54h]
  Color4f color; // [esp+68h] [ebp-50h] BYREF
  tColour self; // [esp+78h] [ebp-40h] BYREF
  tColour r; // [esp+88h] [ebp-30h] BYREF
  _BYTE v60[12]; // [esp+98h] [ebp-20h] BYREF
  int v61; // [esp+A4h] [ebp-14h]
  _BYTE v62[16]; // [esp+A8h] [ebp-10h] BYREF

  noop_this_constructor(&r);
  noop_this_constructor(&self);
  noop_this_constructor(v62);
  noop_this_constructor(v60);
  if ( g_render_queue_active )
  {
    widget_flags = widget->widget_flags;
    if ( (BYTE1(widget_flags) & 0x10) == 0 )
    {
      if ( SLOBYTE(g_runtime_config.render_flags) < 0 )
      {
        v42 = 3;
        v3 = 3;
      }
      else
      {
        v3 = 0;
        r.a = 1.0;
        v61 = 1065353216;
        v42 = 0;
      }
      layout_width = widget->layout_width;
      layout_height = widget->layout_height;
      if ( (widget_flags & 0x100000) != 0 )
      {
        slider_position_current = widget->slider_position_current;
        slider_position_current_low = SLODWORD(widget->slider_position_current);
        g = widget->current_text_color.g;
        self.r = widget->current_text_color.r;
        self.g = g;
        self.b = widget->current_text_color.b;
        self.a = widget->current_text_color.a;
        if ( slider_position_current > 0.0 )
        {
          v28 = widget->slider_position_current * 256.0;
          v23 = widget->texture_hit_y + 50.0;
          v18 = layout_width * 0.5 + widget->texture_hit_x - 128.0;
          queue_axis_aligned_textured_quad_uv(
            37,
            v18,
            v23,
            v28,
            32.0,
            0x1000000u,
            &self,
            0.0,
            0.0,
            *(float *)&slider_position_current_low,
            1.0,
            v3,
            0.0);
        }
        if ( widget->slider_position_current < 1.0 )
        {
          v29 = (1.0 - widget->slider_position_current) * 256.0;
          v24 = widget->texture_hit_y + 50.0;
          v19 = layout_width * 0.5 + widget->texture_hit_x - 128.0 + widget->slider_position_current * 256.0;
          queue_axis_aligned_textured_quad_uv(
            36,
            v19,
            v24,
            v29,
            32.0,
            0x1000000u,
            &self,
            widget->slider_position_current,
            0.0,
            1.0,
            1.0,
            v3,
            0.0);
        }
      }
      if ( widget->texture_hit_test_enabled )
      {
        v6 = 0.0;
        if ( g_game_base->unknown_000b48[275876] )
        {
          if ( widget == *(FrontendWidget **)&g_game_base->unknown_000b48[275888] )
          {
            a = *(float *)&g_game_base->unknown_000b48[275880] * 3.1415927;
            v6 = sine(a) * 3.0;
            if ( !widget->sprite_wobble_positive )
              v6 = v6 * -1.0;
          }
        }
        v7 = widget->border_edge * 0.5;
        texture_layer = widget->texture_layer;
        p_current_text_color = &widget->current_text_color;
        v33 = widget->texture_hit_height + widget->border_edge;
        v30 = widget->texture_hit_width + widget->border_edge;
        *(float *)&v25 = widget->texture_hit_y - v7;
        *(float *)&v20 = v6 + widget->texture_hit_x - v7;
        if ( (widget->widget_flags & 2) != 0 )
          queue_axis_aligned_textured_quad_uv(
            widget->background_texture_id,
            *(float *)&v20,
            *(float *)&v25,
            v30,
            v33,
            0x1000000u,
            p_current_text_color,
            0.0,
            0.0,
            1.0,
            1.0,
            texture_layer,
            0.0);
        else
          queue_axis_aligned_textured_quad_uv(
            widget->texture_id,
            *(float *)&v20,
            *(float *)&v25,
            v30,
            v33,
            0x1000000u,
            p_current_text_color,
            0.0,
            0.0,
            1.0,
            1.0,
            texture_layer,
            0.0);
      }
      else
      {
        if ( (widget->widget_flags & 0x800) != 0 )
        {
          v8 = widget->border_edge * 0.5;
          v34 = widget->texture_hit_height + widget->border_edge;
          v31 = widget->border_edge + widget->texture_hit_width;
          v26 = widget->texture_hit_y - v8;
          v21 = widget->texture_hit_x - v8;
          queue_axis_aligned_textured_quad_uv(
            widget->texture_id,
            v21,
            v26,
            v31,
            v34,
            0x1000000u,
            &widget->current_text_color,
            0.0,
            0.0,
            1.0,
            1.0,
            widget->texture_layer,
            0.0);
          if ( widget->sprite_shadow_offset > 0.0 )
          {
            v54 = widget->border_edge * 0.5;
            v9 = set_color_rgba((tColour *)&color, 0.0, 0.0, 0.0, 0.89999998);
            v35 = widget->texture_hit_height + widget->border_edge;
            v32 = widget->border_edge + widget->texture_hit_width;
            v27 = widget->sprite_shadow_offset + widget->texture_hit_y - v54;
            v22 = widget->sprite_shadow_offset + widget->texture_hit_x - v54;
            queue_axis_aligned_textured_quad_uv(
              widget->texture_id,
              v22,
              v27,
              v32,
              v35,
              0x1000000u,
              v9,
              0.0,
              0.0,
              1.0,
              1.0,
              2,
              0.0);
          }
        }
        if ( (widget->widget_flags & 0x400000) == 0 )
        {
          if ( widget->render_inset_dynamic )
          {
            current_padding = 4.0;
            v47 = 0.1;
            v49 = 0.89999998;
            *(float *)&texture_hit_x_low = widget->texture_hit_x + 4.0;
            *(float *)&texture_hit_y_low = widget->texture_hit_y + 3.0;
            layout_width = layout_width - 8.0;
            layout_height = layout_height - 6.0;
          }
          else if ( widget->current_padding >= (double)widget->render_inset_base )
          {
            texture_hit_x_low = SLODWORD(widget->texture_hit_x);
            texture_hit_y_low = SLODWORD(widget->texture_hit_y);
            current_padding = widget->current_padding;
            v47 = 0.2;
            v49 = 0.80000001;
          }
          else
          {
            v10 = widget->render_inset_base - widget->current_padding;
            current_padding = widget->render_inset_base;
            widget->render_inset_delta = v10;
            *(float *)&texture_hit_x_low = v10 + widget->texture_hit_x;
            *(float *)&texture_hit_y_low = v10 + widget->texture_hit_y;
            v11 = v10 + v10;
            layout_width = layout_width - v11;
            layout_height = layout_height - v11;
            v47 = current_padding * 0.0078125;
            v49 = 1.0 - v47;
          }
          v12 = v47;
          v13 = current_padding;
          v52 = *(float *)&texture_hit_y_low - current_padding;
          v55 = *(float *)&texture_hit_x_low - current_padding;
          queue_axis_aligned_textured_quad_uv(
            widget->border_texture_id,
            v55,
            v52,
            current_padding,
            current_padding,
            0x1000000u,
            &widget->current_fill_color,
            0.0,
            0.0,
            v47,
            v47,
            v3,
            0.0);
          v17 = v3;
          v14 = v49;
          queue_axis_aligned_textured_quad_uv(
            widget->border_texture_id,
            *(float *)&texture_hit_x_low,
            v52,
            layout_width,
            current_padding,
            0x1000000u,
            &widget->current_fill_color,
            v12,
            0.0,
            v49,
            v12,
            v17,
            0.0);
          v50 = layout_width + *(float *)&texture_hit_x_low;
          queue_axis_aligned_textured_quad_uv(
            widget->border_texture_id,
            v50,
            v52,
            v13,
            v13,
            0x1000000u,
            &widget->current_fill_color,
            v14,
            0.0,
            1.0,
            v47,
            v42,
            0.0);
          queue_axis_aligned_textured_quad_uv(
            widget->border_texture_id,
            v55,
            *(float *)&texture_hit_y_low,
            current_padding,
            layout_height,
            0x1000000u,
            &widget->current_fill_color,
            0.0,
            v12,
            v12,
            v14,
            v42,
            0.0);
          queue_axis_aligned_textured_quad_uv(
            widget->border_texture_id,
            *(float *)&texture_hit_x_low,
            *(float *)&texture_hit_y_low,
            layout_width,
            layout_height,
            0x1000000u,
            &widget->current_fill_color,
            v12,
            v12,
            v14,
            v14,
            v42,
            0.0);
          queue_axis_aligned_textured_quad_uv(
            widget->border_texture_id,
            v50,
            *(float *)&texture_hit_y_low,
            current_padding,
            layout_height,
            0x1000000u,
            &widget->current_fill_color,
            v14,
            v47,
            1.0,
            v14,
            v42,
            0.0);
          *(float *)&v48 = layout_height + *(float *)&texture_hit_y_low;
          queue_axis_aligned_textured_quad_uv(
            widget->border_texture_id,
            v55,
            *(float *)&v48,
            v13,
            v13,
            0x1000000u,
            &widget->current_fill_color,
            0.0,
            v14,
            v12,
            1.0,
            v42,
            0.0);
          queue_axis_aligned_textured_quad_uv(
            widget->border_texture_id,
            *(float *)&texture_hit_x_low,
            *(float *)&v48,
            layout_width,
            current_padding,
            0x1000000u,
            &widget->current_fill_color,
            v12,
            v14,
            v14,
            1.0,
            v42,
            0.0);
          v15 = v50;
          queue_axis_aligned_textured_quad_uv(
            widget->border_texture_id,
            v50,
            *(float *)&v48,
            current_padding,
            current_padding,
            0x1000000u,
            &widget->current_fill_color,
            v14,
            v14,
            1.0,
            1.0,
            v42,
            0.0);
          if ( g_game_base->unknown_000b48[275876] )
          {
            if ( widget == *(FrontendWidget **)&g_game_base->unknown_000b48[275888] )
            {
              noop_this_constructor(&color);
              set_color_white(&r);
              aa = 1.0 - *(float *)&g_game_base->unknown_000b48[275880];
              store_color4f((tColour *)&color, r.r, r.g, r.b, aa);
              v56 = (*(float *)&g_game_base->unknown_000b48[275880] * 0.69999999 + 1.0) * current_padding;
              v16 = v56;
              v53 = *(float *)&texture_hit_y_low - v56;
              v51 = *(float *)&texture_hit_x_low - v56;
              queue_axis_aligned_textured_quad_uv(
                99,
                v51,
                v53,
                v56,
                v56,
                0x1000000u,
                (tColour *)&color,
                0.0,
                0.0,
                v12,
                v12,
                3,
                0.0);
              queue_axis_aligned_textured_quad_uv(
                99,
                *(float *)&texture_hit_x_low,
                v53,
                layout_width,
                v56,
                0x1000000u,
                (tColour *)&color,
                v12,
                0.0,
                v14,
                v12,
                3,
                0.0);
              queue_axis_aligned_textured_quad_uv(
                99,
                v15,
                v53,
                v16,
                v16,
                0x1000000u,
                (tColour *)&color,
                v14,
                0.0,
                1.0,
                v12,
                3,
                0.0);
              queue_axis_aligned_textured_quad_uv(
                99,
                v51,
                *(float *)&texture_hit_y_low,
                v56,
                layout_height,
                0x1000000u,
                (tColour *)&color,
                0.0,
                v12,
                v12,
                v14,
                3,
                0.0);
              queue_axis_aligned_textured_quad_uv(
                99,
                v15,
                *(float *)&texture_hit_y_low,
                v56,
                layout_height,
                0x1000000u,
                (tColour *)&color,
                v14,
                v12,
                1.0,
                v14,
                3,
                0.0);
              queue_axis_aligned_textured_quad_uv(
                99,
                v51,
                *(float *)&v48,
                v16,
                v16,
                0x1000000u,
                (tColour *)&color,
                0.0,
                v14,
                v12,
                1.0,
                3,
                0.0);
              queue_axis_aligned_textured_quad_uv(
                99,
                *(float *)&texture_hit_x_low,
                *(float *)&v48,
                layout_width,
                v56,
                0x1000000u,
                (tColour *)&color,
                v12,
                v14,
                v14,
                1.0,
                3,
                0.0);
              queue_axis_aligned_textured_quad_uv(
                99,
                v15,
                *(float *)&v48,
                v16,
                v16,
                0x1000000u,
                (tColour *)&color,
                v14,
                v14,
                1.0,
                1.0,
                3,
                0.0);
            }
          }
        }
      }
    }
  }
}
