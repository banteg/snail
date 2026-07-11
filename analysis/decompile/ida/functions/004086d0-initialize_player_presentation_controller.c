/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_player_presentation_controller @ 0x4086d0 */
/* selector: initialize_player_presentation_controller */

// Constructs the embedded enemy-manager runtime object by seeding its visible bods and child renderable entries before the later gameplay reset in `initialize_enemy_manager`. Its `0x1804` footprint matches the native `cREnemyManager` size ledger from `construct_game_runtime`.
PlayerPresentationController *__thiscall initialize_player_presentation_controller(
        PlayerPresentationController *presentation)
{
  uint8_t *pad_14c; // edi
  int v3; // ebx
  uint8_t *pad_150; // ebx
  int v5; // ebp

  initialize_renderable_bod(presentation);
  pad_14c = presentation->_pad_14c;
  v3 = 10;
  do
  {
    initialize_renderable_bod(pad_14c);
    pad_14c += 128;
    --v3;
  }
  while ( v3 );
  initialize_renderable_bod(&presentation->weapon_channels[0].vtable);
  noop_runtime_slot_constructor((ObjectVertexBufferVtbl *)&presentation->weapon_channels[0]._pad_7c[68]);
  initialize_array_with_constructor(
    (int)presentation->weapon_channels[0]._pad_150,
    128,
    5,
    (int (__thiscall *)(int))initialize_renderable_bod);
  presentation->weapon_channels[0].vtable = g_presentation_animation_channel_noop_vtable;
  initialize_renderable_bod(&presentation->weapon_channels[1].vtable);
  noop_runtime_slot_constructor((ObjectVertexBufferVtbl *)&presentation->weapon_channels[1]._pad_7c[68]);
  initialize_array_with_constructor(
    (int)presentation->weapon_channels[1]._pad_150,
    128,
    5,
    (int (__thiscall *)(int))initialize_renderable_bod);
  presentation->weapon_channels[1].vtable = g_presentation_animation_channel_noop_vtable;
  initialize_renderable_bod(&presentation->weapon_channels[2].vtable);
  noop_runtime_slot_constructor((ObjectVertexBufferVtbl *)&presentation->weapon_channels[2]._pad_7c[68]);
  initialize_array_with_constructor(
    (int)presentation->weapon_channels[2]._pad_150,
    128,
    5,
    (int (__thiscall *)(int))initialize_renderable_bod);
  presentation->weapon_channels[2].vtable = g_presentation_animation_channel_noop_vtable;
  initialize_renderable_bod(&presentation->jetpack_channel.vtable);
  noop_runtime_slot_constructor((ObjectVertexBufferVtbl *)&presentation->jetpack_channel._pad_7c[4]);
  noop_runtime_slot_constructor((ObjectVertexBufferVtbl *)&presentation->jetpack_channel._pad_7c[68]);
  pad_150 = presentation->jetpack_channel._pad_150;
  v5 = 5;
  do
  {
    initialize_renderable_bod(pad_150);
    pad_150 += 128;
    --v5;
  }
  while ( v5 );
  presentation->jetpack_channel.vtable = g_presentation_animation_channel_noop_vtable;
  initialize_renderable_bod(presentation->wobble._pad_10);
  initialize_renderable_bod(&presentation->_pad_1644[8]);
  initialize_renderable_bod(&presentation->invincible_shell.vtable);
  presentation->invincible_shell.vtable = &g_invincible_shell_update_vtable;
  presentation->vtable = &g_player_presentation_noop_vtable;
  return presentation;
}
