/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: sample_track_floor_height_at_position @ 0x43d4d0 */
/* selector: sample_track_floor_height_at_position */

// Evaluates the runtime floor-height sampler for the current gameplay-grid cell, including ramp tiles and the special cell-stored height used by tile 0x16.
double __thiscall sample_track_floor_height_at_position(SubgameRuntime *game, Vec3 *position)
{
  TrackRowCell *track_grid_cell_at_world_position; // eax
  SubLocTileId tile_id; // cl

  track_grid_cell_at_world_position = get_track_grid_cell_at_world_position(game, position);
  tile_id = track_grid_cell_at_world_position->tile_id;
  switch ( tile_id )
  {
    case SUBLOC_TILE_FLOOR_DOT:
    case SUBLOC_TILE_SLIDE_UNDERSCORE:
    case SUBLOC_TILE_WALL2:
      return 0.0;
    case SUBLOC_TILE_RAMP_LEFT_BRACE:
    case SUBLOC_TILE_RAMP_GREATER:
    case SUBLOC_TILE_RAMP_RIGHT_BRACE:
    case SUBLOC_TILE_RAMP_LEFT_BRACKET:
    case SUBLOC_TILE_RAMP_LESS:
    case SUBLOC_TILE_RAMP_RIGHT_BRACKET:
    case SUBLOC_TILE_RAMP_LEFT_BRACE_BACKPATCH:
    case SUBLOC_TILE_RAMP_GREATER_BACKPATCH:
    case SUBLOC_TILE_RAMP_RIGHT_BRACE_BACKPATCH:
      return (position->z - (double)(int)(__int64)position->z) * 0.40000001;
    case SUBLOC_TILE_RAMP_LEFT_BRACE_RAISED:
    case SUBLOC_TILE_RAMP_GREATER_RAISED:
    case SUBLOC_TILE_RAMP_RIGHT_BRACE_RAISED:
      return (position->z - (double)(int)(__int64)position->z) * 0.40000001 + 0.5;
    case SUBLOC_TILE_TRAMPOLINE:
      return track_grid_cell_at_world_position->anchor_position.y;
  }
  return -100.0;
}
