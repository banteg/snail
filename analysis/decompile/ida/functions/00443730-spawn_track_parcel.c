/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_track_parcel @ 0x443730 */
/* selector: spawn_track_parcel */

// Exact `SubgameRuntime` allocator/initializer for one live Parcel from the owned `ParcelManager`. Android explicitly returns the allocated `cRParcel*` or null, confirming the Windows return contract; iOS v1.9 adds the source `cRSubRow*` argument.
Parcel *__thiscall spawn_track_parcel(SubgameRuntime *runtime, Vec3 *world_position, Player *source_player)
{
  Parcel *track_parcel_slot; // eax
  Parcel *v5; // esi
  Vec3 *p_position; // edi
  Sprite *sprite; // eax
  SpriteFlag flags; // ecx
  void **v9; // eax
  Color4f color; // [esp+8h] [ebp-10h] BYREF

  track_parcel_slot = allocate_track_parcel_slot(&runtime->parcel_manager);
  v5 = track_parcel_slot;
  if ( !track_parcel_slot )
    return nullptr;
  p_position = &track_parcel_slot->bod.position;
  track_parcel_slot->state = PARCEL_STATE_TRACK_ACTIVE;
  track_parcel_slot->bod.position = *world_position;
  track_parcel_slot->owner_player = &runtime->player;
  sprite = allocate_sprite(&g_sprite_manager, runtime->player.player_slot, 121, -1, -1);
  v5->sprite = sprite;
  flags = sprite->flags;
  BYTE1(flags) |= 8u;
  sprite->flags = flags;
  v5->sprite->progress = 0.0;
  v5->sprite->progress_step = 0.0;
  v5->sprite->gravity_step = 0.0;
  v5->sprite->color = *set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  v5->sprite->size_start = 1.0;
  v5->sprite->size_end = 1.0;
  v9 = (void **)&v5->sprite->position;
  *v9 = (void *)LODWORD(p_position->x);
  v9[1] = (void *)LODWORD(v5->bod.position.y);
  v9[2] = (void *)LODWORD(v5->bod.position.z);
  if ( ((__int64)world_position->z & 1) != 0 )
    v5->bob_phase = 0.0;
  else
    v5->bob_phase = 0.5;
  v5->bob_phase_step = 0.012820513;
  return v5;
}
