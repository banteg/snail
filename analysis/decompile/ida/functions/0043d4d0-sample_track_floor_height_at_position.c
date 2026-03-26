/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: sample_track_floor_height_at_position @ 0x43d4d0 */
/* selector: sample_track_floor_height_at_position */

// Evaluates the runtime floor-height sampler for the current gameplay-grid cell, including ramp tiles and the special cell-stored height used by tile 0x16.
double __thiscall sample_track_floor_height_at_position(Game *game, Vec3 *position)
{
  TrackRowCell *track_grid_cell_at_world_position; // eax
  uint8_t tile_id; // cl

  track_grid_cell_at_world_position = get_track_grid_cell_at_world_position(game, position);
  tile_id = track_grid_cell_at_world_position->tile_id;
  switch ( tile_id )
  {
    case 1u:
    case 0xFu:
    case 0xEu:
      return 0.0;
    case 2u:
    case 3u:
    case 4u:
    case 5u:
    case 6u:
    case 7u:
    case 0xBu:
    case 0xCu:
    case 0xDu:
      return (position->z - (double)(int)(__int64)position->z) * 0.40000001;
    case 8u:
    case 9u:
    case 0xAu:
      return (position->z - (double)(int)(__int64)position->z) * 0.40000001 + 0.5;
    case 0x16u:
      return track_grid_cell_at_world_position->anchor_position.y;
  }
  return -100.0;
}

