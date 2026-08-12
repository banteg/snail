/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: construct_game_runtime @ 0x407b60 */
/* selector: construct_game_runtime */

// Allocates the exact `0x12e6ff4`-byte `cRGame` root object with C++ exception cleanup, runs its inlined constructor, and publishes the live global game pointer. Android `cRGame::cRGame()` independently confirms the root owner and construction topology, including 150 border records, 128 cached object slots, Backdrop, StarManager, the logo banks, embedded cRSubGame, and TipManager; the surrounding Windows size ledger and global publication remain wrapper-only work.
int32_t construct_game_runtime()
{
  struct GameRoot *v0; // eax
  struct GameRoot *game; // esi
  struct cRGameInput *game_input_cursor; // edi
  int i; // ebx
  struct GamePlayer *player_cursor; // edi
  int j; // ebx
  struct Viewport *viewport_cursor; // edi
  int k; // ebx
  struct BodBase *root_bod_cursor; // edi
  int m; // ebx

  debug_report_stub("Size of cRGame %i\n", 19820532);
  debug_report_stub("Size of cRSubGame %i\n", 19343416);
  debug_report_stub("   Size of cRSegmentCache %i\n", 43000);
  debug_report_stub("   Size of cRTutorial\t%i\n", 28);
  debug_report_stub("   Size of cRSubTracks %i\n", 1726840);
  debug_report_stub("   Size of cRSubSpeedUp %i\n", 180);
  debug_report_stub("   Size of cRJetPack %i\n", 412);
  debug_report_stub("   Size of cRSubHealth %i\n", 928);
  debug_report_stub("   Size of cRSlug %i\n", 1888);
  debug_report_stub("   Size of cRSubLazerManager %i\n", 3520);
  debug_report_stub("   Size of cRSaltManager %i\n", 6080);
  debug_report_stub("   Size of cRSubGarbage %i\n", 9800);
  debug_report_stub("   Size of cRSubRing %i\n", 1008);
  debug_report_stub("   Size of cRFringeManager %i\n", 392004);
  debug_report_stub("   Size of cRSubGoldy %i\n", 17252);
  debug_report_stub("   Size of cRSubLoc %i\n", 2150400);
  debug_report_stub("   Size of cRSubRow %i\n", 780800);
  debug_report_stub("   Size of cRSubHighScore %i\n", 9729608);
  debug_report_stub("   Size of cRSubSolution %i\n", 129728);
  debug_report_stub("   Size of cRTimeTrial %i\n", 816);
  debug_report_stub("   Size of cRPathManager %i\n", 1);
  debug_report_stub("   Size of cRPath %i\n", 21168);
  debug_report_stub("   Size of cRLandscapeManager %i\n", 38820);
  debug_report_stub("   Size of cRSMTracks %i\n", 2478004);
  debug_report_stub("   Size of cRParcelManager %i\n", 7000);
  debug_report_stub("   Size of cRGUI %i\n", 40);
  debug_report_stub("   Size of cRGalaxy %i\n", 69544);
  debug_report_stub("   Size of cREnemyManager %i\n", 6148);
  debug_report_stub("   Size of cRCompletion %i\n", 80);
  debug_report_stub("   Size of cRTimesUp %i\n", 16);
  debug_report_stub("Size of cRSubHighScore %i\n", 9729608);
  debug_report_stub("Size of cRBod %i\n", 56);
  debug_report_stub("Size of cRSubLoc %i\n", 84);
  debug_report_stub("Solutions %i\n", 9729608);
  v0 = (struct GameRoot *)operator_new(0x12E6FF4u);
  game = v0;
  if ( v0 != nullptr )
  {
    noop_this_constructor(&v0->fog_color);
    game_input_cursor = game->game_inputs;
    for ( i = 2; i != 0; --i )
    {
      initialize_bod_base((BodBase *)game_input_cursor);
      game_input_cursor->bod.vtable = &g_game_input_callback_table;
      ++game_input_cursor;
    }
    player_cursor = game->players;
    for ( j = 2; j != 0; --j )
      initialize_game_player(player_cursor++);
    initialize_bod_base((BodBase *)&game->inactive_bod_sentinel);
    viewport_cursor = game->viewports;
    for ( k = 5; k != 0; --k )
      initialize_render_camera_slot(viewport_cursor++);
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
    for ( m = 352; m != 0; --m )
      initialize_bod_base(root_bod_cursor++);
    initialize_array_with_constructor(
      game->directx_loader.cached_x_mesh_slots,
      188,
      128,
      (void *(__thiscall *)(void *))initialize_cached_x_mesh_slot);
    initialize_bod_base(&game->backdrop.bod);
    noop_this_constructor(&game->backdrop.primary_world_blend);
    noop_this_constructor(&game->backdrop.secondary_world_blend);
    game->backdrop.bod.bod.vtable = &g_backdrop_callback_table;
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
  debug_report_stub("BodCount=%i  Memory=%i\n", g_bod_base_init_count, 56 * g_bod_base_init_count);
  debug_report_stub("LocCount=%i Memory=%i\n", g_sub_loc_count, 84 * g_sub_loc_count);
  return debug_report_stub("LocMirrorCount=%i Memory=%i\n", g_loc_mirror_count, 348 * g_loc_mirror_count);
}
