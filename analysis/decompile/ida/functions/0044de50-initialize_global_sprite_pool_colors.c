/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: initialize_global_sprite_pool_colors @ 0x44de50 */
/* selector: initialize_global_sprite_pool_colors */

// Runs the folded trivial tColour constructor over the +0x2c color member of all 3000 cRSprite records embedded in the global cRSpriteManager at a 0xb4-byte Windows stride.
ObjectVertexBufferVtbl *initialize_global_sprite_pool_colors()
{
  tColour *p_color; // esi
  int i; // edi
  ObjectVertexBufferVtbl *result; // eax

  p_color = &g_sprite_manager.sprites[0].color;
  for ( i = 3000; i != 0; --i )
  {
    result = (ObjectVertexBufferVtbl *)noop_this_constructor(p_color);
    p_color = (tColour *)((char *)p_color + 180);
  }
  return result;
}
