/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_runtime_pools_and_path_template_bank @ 0x408060 */
/* selector: initialize_runtime_pools_and_path_template_bank */

// Initializes the embedded subgame pools, including exactly 126 0xa8-byte path-template records at SubgameRuntime+0xff2914. Those records form the same 63 primary/secondary pairs later constructed through the GameRoot+0x1066f2c alias; their 0x52b0 extent ends at the barrier actor at +0xff7bc4.
_DWORD *__thiscall initialize_runtime_pools_and_path_template_bank(_DWORD *this)
{
  _DWORD *v2; // edi
  _DWORD *v3; // edi
  int v4; // ebx
  _DWORD *v5; // edi
  int v6; // ebx
  _DWORD *v7; // edi
  int v8; // ebx
  _DWORD *v9; // edi
  int v10; // ebx
  _DWORD *v11; // edi
  int v12; // ebx
  _DWORD *v13; // edi
  int v14; // ebx
  char *v15; // edi
  int v16; // ebx
  _DWORD *v17; // edi
  int v18; // ebx

  v2 = this + 23;
  noop_this_constructor(this + 23);
  initialize_array_with_constructor((int)(v2 + 22), 60, 715, (int (__thiscall *)(int))initialize_active_bod);
  initialize_array_with_constructor(
    (int)(this + 10782),
    16928,
    100,
    (int (__thiscall *)(int))noop_runtime_slot_constructor);
  initialize_array_with_constructor(
    (int)(this + 434499),
    56,
    256,
    (int (__thiscall *)(int))noop_runtime_slot_constructor);
  initialize_array_with_constructor(
    (int)(this + 438731),
    56,
    256,
    (int (__thiscall *)(int))noop_runtime_slot_constructor);
  noop_this_constructor(this + 442448);
  initialize_array_with_constructor(
    (int)(this + 442492),
    16928,
    100,
    (int (__thiscall *)(int))noop_runtime_slot_constructor);
  initialize_array_with_constructor(
    (int)(this + 866209),
    56,
    256,
    (int (__thiscall *)(int))noop_runtime_slot_constructor);
  initialize_array_with_constructor(
    (int)(this + 870441),
    56,
    256,
    (int (__thiscall *)(int))noop_runtime_slot_constructor);
  noop_this_constructor(this + 874158);
  initialize_bod_base(this + 874201);
  initialize_bod_base(this + 874215);
  initialize_bod_base(this + 874229);
  initialize_bod_base(this + 874243);
  initialize_bod_base(this + 874257);
  initialize_bod_base(this + 874271);
  initialize_bod_base(this + 874285);
  initialize_bod_base(this + 874299);
  initialize_bod_base(this + 874313);
  initialize_bod_base(this + 874327);
  initialize_track_speedup_runtime(this + 874348);
  initialize_track_jetpack_pickup_runtime(this + 874393);
  v3 = this + 874496;
  v4 = 8;
  do
  {
    initialize_track_health_pickup_runtime(v3);
    v3 += 29;
    --v4;
  }
  while ( v4 );
  v5 = this + 874728;
  v6 = 8;
  do
  {
    initialize_slug_hazard_runtime(v5);
    v5 += 59;
    --v6;
  }
  while ( v6 );
  initialize_array_with_constructor(
    (int)(this + 875200),
    176,
    20,
    (int (__thiscall *)(int))initialize_sub_lazer_runtime);
  initialize_array_with_constructor(
    (int)(this + 876080),
    152,
    40,
    (int (__thiscall *)(int))initialize_salt_hazard_runtime);
  v7 = this + 877600;
  v8 = 2;
  do
  {
    initialize_bod_base(v7);
    *v7 = &g_banner_callback_table;
    v7 += 24;
    --v8;
  }
  while ( v8 );
  v9 = this + 877649;
  v10 = 50;
  do
  {
    initialize_garbage_hazard(v9);
    v9 += 49;
    --v10;
  }
  while ( v10 );
  v11 = this + 880099;
  v12 = 2;
  do
  {
    initialize_track_ring_or_special_effect_runtime(v11);
    v11 += 126;
    --v12;
  }
  while ( v12 );
  initialize_array_with_constructor((int)(this + 880367), 56, 7000, (int (__thiscall *)(int))initialize_fringe_object);
  initialize_renderable_bod(this + 978393);
  initialize_click_start_controller_runtime(this + 978433);
  noop_runtime_slot_constructor((ObjectVertexBufferVtbl *)(this + 978521));
  noop_runtime_slot_constructor((ObjectVertexBufferVtbl *)(this + 978618));
  initialize_array_with_constructor((int)(this + 978669), 744, 12, (int (__thiscall *)(int))initialize_golb_shot);
  initialize_player_presentation_controller((PlayerPresentationController *)(this + 981050));
  *(this + 978393) = &g_subgoldy_callback_table;
  v13 = this + 982706;
  v14 = 25600;
  do
  {
    initialize_sub_loc(v13);
    v13 += 21;
    --v14;
  }
  while ( v14 );
  v15 = &byte_5CCAC8[(_DWORD)this];
  v16 = 3200;
  do
  {
    initialize_track_row_runtime(v15);
    v15 += 244;
    --v16;
  }
  while ( v16 );
  v17 = this + 4180549;
  v18 = 126;
  do
  {
    initialize_path_template_record_pair(v17);
    v17 += 42;
    --v18;
  }
  while ( v18 );
  initialize_bod_base(this + 4185841);
  *(this + 4185841) = &g_barrier_actor_callback_table;
  initialize_array_with_constructor(
    (int)(this + 4185856),
    144,
    10,
    (int (__thiscall *)(int))initialize_active_landscape_entry);
  initialize_array_with_constructor((int)(this + 4186217), 292, 128, initialize_landscape_script_record);
  initialize_bod_base(this + 4195561);
  initialize_object_constructor_thunk(this + 4195575);
  *(this + 4195561) = g_smtracks_callback_table;
  initialize_array_with_constructor(
    (int)(this + 4195636),
    16520,
    150,
    (int (__thiscall *)(int))noop_runtime_slot_constructor);
  initialize_array_with_constructor(
    (int)(this + 4815136),
    140,
    50,
    (int (__thiscall *)(int))initialize_track_parcel_runtime);
  initialize_array_with_constructor(
    (int)(this + 4816908),
    672,
    101,
    (int (__thiscall *)(int))noop_runtime_slot_constructor);
  initialize_array_with_constructor((int)(this + 4833876), 160, 10, initialize_solution_record);
  initialize_array_with_constructor(
    (int)(this + 4834294),
    24,
    256,
    (int (__thiscall *)(int))noop_runtime_slot_constructor);
  return this;
}

