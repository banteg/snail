/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: border_mouse_test @ 0x404580 */
/* selector: border_mouse_test */

uint8_t __thiscall border_mouse_test(FrontendWidget *widget)
{
  int sprite_texture_ref; // ebp
  int v2; // esi
  int v3; // edi
  int v4; // ebx
  __int64 v5; // rax
  float v7; // [esp+4h] [ebp-8h]
  float v8; // [esp+8h] [ebp-4h]

  if ( widget->texture_hit_test_enabled )
  {
    if ( *((float *)g_game_base + 167) >= (double)widget->texture_hit_x
      && widget->texture_hit_width + widget->texture_hit_x > *((float *)g_game_base + 167)
      && *((float *)g_game_base + 168) >= (double)widget->texture_hit_y
      && widget->texture_hit_height + widget->texture_hit_y > *((float *)g_game_base + 168) )
    {
      v7 = (*((float *)g_game_base + 167) - widget->texture_hit_x) / widget->texture_hit_width;
      v8 = (*((float *)g_game_base + 168) - widget->texture_hit_y) / widget->texture_hit_height;
      sprite_texture_ref = get_sprite_texture_ref(widget->texture_hit_test_sprite);
      v2 = *(unsigned __int16 *)(sprite_texture_ref + 12);
      v3 = (__int64)((double)(unsigned __int16)v2 * v7);
      v4 = *(unsigned __int16 *)(sprite_texture_ref + 14);
      v5 = (__int64)((double)(unsigned __int16)v4 * v8);
      if ( v3 >= 0 )
      {
        if ( v3 > v2 - 1 )
          v3 = v2 - 1;
      }
      else
      {
        v3 = 0;
      }
      if ( (int)v5 >= 0 )
      {
        if ( (int)v5 > v4 - 1 )
          LODWORD(v5) = v4 - 1;
      }
      else
      {
        LODWORD(v5) = 0;
      }
      if ( !*(_BYTE *)(v5 * v2 + v3 + 6 + sprite_texture_ref + 2 * (v5 * v2 + v3 + 6)) )
        return 1;
    }
  }
  else if ( widget->layout_left - widget->target_padding < *((float *)g_game_base + 167)
         && widget->layout_width + widget->target_padding + widget->layout_left > *((float *)g_game_base + 167)
         && widget->layout_top - widget->target_padding < *((float *)g_game_base + 168)
         && widget->layout_height + widget->layout_top + widget->target_padding > *((float *)g_game_base + 168) )
  {
    return 1;
  }
  return 0;
}

