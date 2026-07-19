/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_runtime_pools_and_path_template_bank @ 0x408060 */
/* selector: initialize_runtime_pools_and_path_template_bank */

// Initializes the embedded subgame pools, including exactly 126 0xa8-byte path-template records at SubgameRuntime+0xff2914. Those records form the same 63 primary/secondary pairs later constructed through the GameRoot+0x1066f2c alias; their 0x52b0 extent ends at the barrier actor at +0xff7bc4.
SubgameRuntime *__thiscall initialize_runtime_pools_and_path_template_bank(SubgameRuntime *game)
{
  SegmentCache *p_segment_cache; // edi
  SubHealth *health_pickups; // edi
  int v4; // ebx
  SlugPool *p_slug_hazards; // edi
  int v6; // ebx
  BannerPool *p_banners; // edi
  int v8; // ebx
  SubGarbage *slots; // edi
  int v10; // ebx
  SubRingPool *p_ring_effects; // edi
  int v12; // ebx
  TrackRowCell *v13; // edi
  int v14; // ebx
  SubRow *runtime_rows; // edi
  int v16; // ebx
  PathPair *path_pairs; // edi
  int v18; // ebx

  p_segment_cache = &game->segment_cache;
  noop_this_constructor(&game->segment_cache);
  initialize_array_with_constructor(
    p_segment_cache->slots,
    60,
    715,
    (void *(__thiscall *)(void *))initialize_active_bod);
  initialize_array_with_constructor(game->level_definition.segment_slots, 16928, 100, noop_runtime_slot_constructor);
  initialize_array_with_constructor(game->level_definition.first_segment.rows, 56, 256, noop_runtime_slot_constructor);
  initialize_array_with_constructor(game->level_definition.last_segment.rows, 56, 256, noop_runtime_slot_constructor);
  noop_this_constructor(&game->level_definition.fringe_color);
  initialize_array_with_constructor(
    game->level_definition_scratch.segment_slots,
    16928,
    100,
    noop_runtime_slot_constructor);
  initialize_array_with_constructor(
    game->level_definition_scratch.first_segment.rows,
    56,
    256,
    noop_runtime_slot_constructor);
  initialize_array_with_constructor(
    game->level_definition_scratch.last_segment.rows,
    56,
    256,
    noop_runtime_slot_constructor);
  noop_this_constructor(&game->level_definition_scratch.fringe_color);
  initialize_bod_base(&game->fringe_attachment_list_head);
  initialize_bod_base(&game->track_body_list_head);
  initialize_bod_base(&game->barrier_sub_lazer_list_head);
  initialize_bod_base(&game->salt_hazard_list_head);
  initialize_bod_base(&game->landscape_slice_list_head);
  initialize_bod_base(&game->unknown_bod_355c7c);
  initialize_bod_base(&game->special_track_cell_list_head);
  initialize_bod_base(&game->unknown_bod_355cec);
  initialize_bod_base(&game->golb_vapour_list_head);
  initialize_bod_base(&game->unknown_bod_355d5c);
  initialize_track_speedup_runtime(&game->speedup_pickup);
  initialize_track_jetpack_pickup_runtime(&game->jetpack_pickup);
  health_pickups = game->health_pickups;
  v4 = 8;
  do
  {
    initialize_track_health_pickup_runtime(health_pickups++);
    --v4;
  }
  while ( v4 );
  p_slug_hazards = &game->slug_hazards;
  v6 = 8;
  do
  {
    initialize_slug_hazard_runtime(p_slug_hazards->slots);
    p_slug_hazards = (SlugPool *)((char *)p_slug_hazards + 236);
    --v6;
  }
  while ( v6 );
  initialize_array_with_constructor(
    &game->sub_lazers,
    176,
    20,
    (void *(__thiscall *)(void *))initialize_sub_lazer_runtime);
  initialize_array_with_constructor(
    &game->salt_hazards,
    152,
    40,
    (void *(__thiscall *)(void *))initialize_salt_hazard_runtime);
  p_banners = &game->banners;
  v8 = 2;
  do
  {
    initialize_bod_base((BodBase *)p_banners);
    p_banners->slots[0].bod.bod.vtable = &g_banner_callback_table;
    p_banners = (BannerPool *)((char *)p_banners + 96);
    --v8;
  }
  while ( v8 );
  slots = game->garbage_hazards.slots;
  v10 = 50;
  do
  {
    initialize_garbage_hazard(slots++);
    --v10;
  }
  while ( v10 );
  p_ring_effects = &game->ring_effects;
  v12 = 2;
  do
  {
    initialize_track_ring_or_special_effect_runtime(p_ring_effects->slots);
    p_ring_effects = (SubRingPool *)((char *)p_ring_effects + 504);
    --v12;
  }
  while ( v12 );
  initialize_array_with_constructor(
    &game->fringe_manager,
    56,
    7000,
    (void *(__thiscall *)(void *))initialize_fringe_object);
  initialize_renderable_bod(&game->player.body);
  initialize_click_start_controller_runtime(&game->player.click_start);
  noop_runtime_slot_constructor(&game->player.cameraman);
  noop_runtime_slot_constructor(&game->player.follow_state);
  initialize_array_with_constructor(
    game->player.golb_shots,
    744,
    12,
    (void *(__thiscall *)(void *))initialize_golb_shot);
  initialize_player_presentation_controller(&game->player.presentation);
  game->player.body.bod.bod.vtable = &g_subgoldy_callback_table;
  v13 = game->runtime_cells[0];
  v14 = 25600;
  do
  {
    initialize_sub_loc(v13++);
    --v14;
  }
  while ( v14 );
  runtime_rows = game->runtime_rows;
  v16 = 3200;
  do
  {
    initialize_track_row_runtime(runtime_rows++);
    --v16;
  }
  while ( v16 );
  path_pairs = game->path_pairs;
  v18 = 126;
  do
  {
    initialize_path_template_record_pair(path_pairs);
    path_pairs = (PathPair *)((char *)path_pairs + 168);
    --v18;
  }
  while ( v18 );
  initialize_bod_base(&game->barrier.bod);
  game->barrier.bod.bod.vtable = &g_barrier_actor_callback_table;
  initialize_array_with_constructor(
    &game->landscape_manager,
    144,
    10,
    (void *(__thiscall *)(void *))initialize_active_landscape_entry);
  initialize_array_with_constructor(game->landscape_manager.scripts, 292, 128, initialize_landscape_script_record);
  initialize_bod_base(&game->smtrack_heightfield.bod);
  initialize_object_constructor_thunk((Object *)&game->smtrack_heightfield.frame_sequence);
  game->smtrack_heightfield.bod.bod.vtable = g_smtracks_callback_table;
  initialize_array_with_constructor(game->sm_tracks.entries, 16520, 150, noop_runtime_slot_constructor);
  initialize_array_with_constructor(
    &game->parcel_manager,
    140,
    50,
    (void *(__thiscall *)(void *))initialize_track_parcel_runtime);
  initialize_array_with_constructor(game->galaxy.route_slots, 672, 101, noop_runtime_slot_constructor);
  initialize_array_with_constructor(
    game->galaxy.route_names,
    160,
    10,
    (void *(__thiscall *)(void *))initialize_galaxy_route_name_record);
  initialize_array_with_constructor(game->enemy_manager.entries, 24, 256, noop_runtime_slot_constructor);
  return game;
}
