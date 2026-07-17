/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_progress_bar @ 0x437c40 */
/* selector: update_progress_bar */

// Exact `cRProgressBar::AI()` method for the empty authored class at Player +0x3f0. It ignores `this`, derives track progress from the containing Goldy's z position and SubgameRuntime row bounds, and queues the three left-column HUD quads. Android and iOS preserve the same owner role.
void __thiscall update_progress_bar(ProgressBar *progress_bar)
{
  double st6_1; // st6
  double v2; // st7
  tColour *v3; // eax
  tColour *v4; // eax
  tColour *v5; // eax
  float y; // [esp+0h] [ebp-4Ch]
  float v7; // [esp+8h] [ebp-44h]
  float height; // [esp+30h] [ebp-1Ch]
  float v9; // [esp+34h] [ebp-18h]
  float v1; // [esp+38h] [ebp-14h]
  Color4f color; // [esp+3Ch] [ebp-10h] BYREF

  st6_1 = (g_game_base->subgame.player.body.transform.position.z - (double)g_game_base->subgame.first_block_row_count)
        / ((double)g_game_base->subgame.completion_row_start - (double)g_game_base->subgame.first_block_row_count);
  v2 = st6_1;
  if ( st6_1 >= 0.0 )
  {
    if ( st6_1 > 1.0 )
      v2 = 1.0;
  }
  else
  {
    v2 = 0.0;
  }
  height = (1.0 - v2) * 232.0 + 12.0;
  v9 = height + 150.0;
  v3 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  y = v9 - 39.0;
  queue_axis_aligned_textured_quad_uv(157, 12.0, y, 64.0, 64.0, 0x1000000u, v3, 0.0, 0.0, 1.0, 1.0, 3, 0.0);
  v1 = height * 0.00390625;
  v4 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  queue_axis_aligned_textured_quad_uv(155, 13.0, 150.0, 64.0, height, 0x1000000u, v4, 0.0, 0.0, 1.0, v1, 3, 0.0);
  v5 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  v7 = 256.0 - height;
  queue_axis_aligned_textured_quad_uv(156, 13.0, v9, 64.0, v7, 0x1000000u, v5, 0.0, v1, 1.0, 1.0, 3, 0.0);
}
