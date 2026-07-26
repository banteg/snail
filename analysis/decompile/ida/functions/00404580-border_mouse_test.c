/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: border_mouse_test @ 0x404580 */
/* selector: border_mouse_test */

// Runs cRBorder::MouseTest() on one FrontendWidget: tests the player-zero saved cursor position against either the padded layout rectangle or a normalized per-pixel RGB hit mask selected by the widget's texture-hit sprite.
uint8_t __thiscall border_mouse_test(FrontendWidget *widget)
{
  TgaImageView *sprite_tga; // ebp
  int width; // esi
  int v3; // edi
  int height; // ebx
  __int64 v5; // rax
  float v7; // [esp+4h] [ebp-8h]
  float v8; // [esp+8h] [ebp-4h]

  if ( widget->texture_hit_test_enabled != 0 )
  {
    if ( g_game_base->players[0].mouse_cursor.saved_x >= (double)widget->texture_hit_x
      && widget->texture_hit_width + widget->texture_hit_x > g_game_base->players[0].mouse_cursor.saved_x
      && g_game_base->players[0].mouse_cursor.saved_y >= (double)widget->texture_hit_y
      && widget->texture_hit_height + widget->texture_hit_y > g_game_base->players[0].mouse_cursor.saved_y )
    {
      v7 = (g_game_base->players[0].mouse_cursor.saved_x - widget->texture_hit_x) / widget->texture_hit_width;
      v8 = (g_game_base->players[0].mouse_cursor.saved_y - widget->texture_hit_y) / widget->texture_hit_height;
      sprite_tga = get_sprite_tga(&g_sprite_manager, widget->texture_hit_test_sprite);
      width = sprite_tga->width;
      v3 = (__int64)((double)(unsigned __int16)width * v7);
      height = sprite_tga->height;
      v5 = (__int64)((double)(unsigned __int16)height * v8);
      if ( v3 >= 0 )
      {
        if ( v3 > width - 1 )
          v3 = width - 1;
      }
      else
      {
        v3 = 0;
      }
      if ( (int)v5 >= 0 )
      {
        if ( (int)v5 > height - 1 )
          LODWORD(v5) = height - 1;
      }
      else
      {
        LODWORD(v5) = 0;
      }
      if ( sprite_tga->pixels[2 * v5 * width + 2 * v3 + v5 * width + v3] == 0 )
        return 1;
    }
  }
  else if ( widget->layout_left - widget->target_padding < g_game_base->players[0].mouse_cursor.saved_x
         && widget->layout_width + widget->target_padding + widget->layout_left > g_game_base->players[0].mouse_cursor.saved_x
         && widget->layout_top - widget->target_padding < g_game_base->players[0].mouse_cursor.saved_y
         && widget->layout_height + widget->layout_top + widget->target_padding > g_game_base->players[0].mouse_cursor.saved_y )
  {
    return 1;
  }
  return 0;
}
