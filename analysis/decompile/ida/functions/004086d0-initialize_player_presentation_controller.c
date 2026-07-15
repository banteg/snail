/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_player_presentation_controller @ 0x4086d0 */
/* selector: initialize_player_presentation_controller */

// Constructs the exact 0x19b4-byte authored `cRSnail` embedded at `Player +0x2984`: initializes its renderable prefix, ten visual slots, four animation channels, two hotspot sources, and cRInvincible child before installing their callback tables.
Snail *__thiscall initialize_player_presentation_controller(Snail *snail)
{
  PresentationAnimationSlot *cutscene_animation_slots; // edi
  int v3; // ebx
  PresentationAnimationSlot *animation_slots; // ebx
  int v5; // ebp

  initialize_renderable_bod(snail);
  cutscene_animation_slots = snail->cutscene_animation_slots;
  v3 = 10;
  do
  {
    initialize_renderable_bod(cutscene_animation_slots++);
    --v3;
  }
  while ( v3 );
  initialize_renderable_bod(&snail->weapon_channels[0].body.bod.bod.vtable);
  noop_runtime_slot_constructor((ObjectVertexBufferVtbl *)&snail->weapon_channels[0]._pad_80[64]);
  initialize_array_with_constructor(
    (int)snail->weapon_channels[0].animation_slots,
    128,
    5,
    (int (__thiscall *)(int))initialize_renderable_bod);
  snail->weapon_channels[0].body.bod.bod.vtable = g_weapon_noop_vtable;
  initialize_renderable_bod(&snail->weapon_channels[1].body.bod.bod.vtable);
  noop_runtime_slot_constructor((ObjectVertexBufferVtbl *)&snail->weapon_channels[1]._pad_80[64]);
  initialize_array_with_constructor(
    (int)snail->weapon_channels[1].animation_slots,
    128,
    5,
    (int (__thiscall *)(int))initialize_renderable_bod);
  snail->weapon_channels[1].body.bod.bod.vtable = g_weapon_noop_vtable;
  initialize_renderable_bod(&snail->weapon_channels[2].body.bod.bod.vtable);
  noop_runtime_slot_constructor((ObjectVertexBufferVtbl *)&snail->weapon_channels[2]._pad_80[64]);
  initialize_array_with_constructor(
    (int)snail->weapon_channels[2].animation_slots,
    128,
    5,
    (int (__thiscall *)(int))initialize_renderable_bod);
  snail->weapon_channels[2].body.bod.bod.vtable = g_weapon_noop_vtable;
  initialize_renderable_bod(&snail->jetpack_channel.body.bod.bod.vtable);
  noop_runtime_slot_constructor((ObjectVertexBufferVtbl *)snail->jetpack_channel._pad_80);
  noop_runtime_slot_constructor((ObjectVertexBufferVtbl *)&snail->jetpack_channel._pad_80[64]);
  animation_slots = snail->jetpack_channel.animation_slots;
  v5 = 5;
  do
  {
    initialize_renderable_bod(animation_slots++);
    --v5;
  }
  while ( v5 );
  snail->jetpack_channel.body.bod.bod.vtable = g_weapon_noop_vtable;
  initialize_renderable_bod(&snail->snail_hotspot_source_body.bod.bod.vtable);
  initialize_renderable_bod(&snail->snail_hotspot_body.bod.bod.vtable);
  initialize_renderable_bod(&snail->invincible_shell.body.bod.bod.vtable);
  snail->invincible_shell.body.bod.bod.vtable = &g_invincible_shell_update_vtable;
  snail->body.bod.bod.vtable = &g_player_presentation_noop_vtable;
  return snail;
}
