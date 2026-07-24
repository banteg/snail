/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: construct_game_runtime @ 0x407b60 */
/* selector: construct_game_runtime */

// Allocates the exact `0x12e6ff4`-byte `cRGame` root object with C++ exception cleanup, seeds its embedded managers and callback tables, constructs the fixed 352-entry cRBod array at `+0x44100` and the standalone cRBod at `+0x4f3c8`, initializes the runtime pools, constructs the owned `TipManager` at `+0x12e6f58`, and publishes the live global game pointer at `data_4df904`.
int construct_game_runtime()
{
  struct GameRoot *v0; // eax
  struct GameRoot *game; // esi
  struct GameInput *game_input_cursor; // edi
  int v3; // ebx
  struct GamePlayer *player_cursor; // edi
  int v5; // ebx
  struct Viewport *viewport_cursor; // edi
  int v7; // ebx
  struct BodBase *root_bod_cursor; // edi
  int v9; // ebx

  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  debug_report_stub();
  v0 = (struct GameRoot *)operator_new(0x12E6FF4u);
  game = v0;
  if ( v0 )
  {
    noop_this_constructor(&v0->fog_color);
    game_input_cursor = game->game_inputs;
    v3 = 2;
    do
    {
      initialize_bod_base((BodBase *)game_input_cursor);
      game_input_cursor->bod.vtable = &g_game_input_callback_table;
      ++game_input_cursor;
      --v3;
    }
    while ( v3 );
    player_cursor = game->players;
    v5 = 2;
    do
    {
      initialize_game_player(player_cursor++);
      --v5;
    }
    while ( v5 );
    initialize_bod_base((BodBase *)&game->inactive_bod_sentinel);
    viewport_cursor = game->viewports;
    v7 = 5;
    do
    {
      initialize_render_camera_slot(viewport_cursor++);
      --v7;
    }
    while ( v7 );
    initialize_renderable_bod((RenderableBod *)&game->overlay_0);
    initialize_noop_renderable_bod((RenderableBod *)&game->overlay_0.camera);
    game->overlay_0.bod.bod.bod.vtable = (void **)g_overlay_callback_table;
    initialize_renderable_bod((RenderableBod *)&game->overlay_1);
    initialize_noop_renderable_bod((RenderableBod *)&game->overlay_1.camera);
    game->overlay_1.bod.bod.bod.vtable = (void **)g_overlay_callback_table;
    initialize_renderable_bod((RenderableBod *)&game->overlay_2);
    initialize_noop_renderable_bod((RenderableBod *)&game->overlay_2.camera);
    game->overlay_2.bod.bod.bod.vtable = (void **)g_overlay_callback_table;
    initialize_renderable_bod((RenderableBod *)&game->root_noop_renderable);
    noop_runtime_slot_constructor(game->unknown_000ae0);
    game->root_noop_renderable.bod.bod.vtable = &g_noop_runtime_callback_table;
    initialize_bod_base((BodBase *)&game->border_manager);
    initialize_array_with_constructor(
      game->border_manager.borders,
      1828,
      150,
      (void *(__thiscall *)(void *))initialize_border_record);
    game->border_manager.vtable = g_border_manager_callback_table;
    root_bod_cursor = (struct BodBase *)&game->root_bod_catalog;
    v9 = 352;
    do
    {
      initialize_bod_base(root_bod_cursor++);
      --v9;
    }
    while ( v9 );
    initialize_array_with_constructor(game->directx_loader.cached_x_mesh_slots, 188, 128, initialize_cached_x_mesh_slot);
    initialize_bod_base((BodBase *)&game->backdrop);
    noop_this_constructor(&game->backdrop.primary_world_blend);
    noop_this_constructor(&game->backdrop.secondary_world_blend);
    *(_DWORD *)game->backdrop.bod_base = &g_backdrop_callback_table;
    initialize_bod_base(&game->star_manager.bod);
    game->star_manager.bod.bod.vtable = &g_star_field_callback_table;
    initialize_bod_base(&game->root_bod_4f3c8);
    initialize_array_with_constructor(
      game->logo.letters,
      144,
      1024,
      (void *(__thiscall *)(void *))initialize_intro_logo_renderable);
    initialize_array_with_constructor(
      game->logo.image_donors,
      144,
      32,
      (void *(__thiscall *)(void *))initialize_intro_logo_renderable);
    initialize_runtime_pools_and_path_template_bank(&game->subgame);
    initialize_bod_base(&game->tip_manager.bod);
    game->tip_manager.bod.bod.vtable = &g_tip_manager_callback_table;
    game->vtable = &g_root_runtime_callback_table;
  }
  else
  {
    game = nullptr;
  }
  g_game_base = game;
  debug_report_stub();
  debug_report_stub();
  return debug_report_stub();
}
