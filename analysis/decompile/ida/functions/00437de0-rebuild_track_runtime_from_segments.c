/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: rebuild_track_runtime_from_segments @ 0x437de0 */
/* selector: rebuild_track_runtime_from_segments */

// Normalizes the generated runtime grid, copies authored metadata into runtime cells, and runs the post-build render passes.
int __thiscall sub_437DE0(int *this, int a2)
{
  float *v3; // eax
  int v5[4]; // [esp+4h] [ebp-10h] BYREF

  *(this + 17) = a2;
  set_subgame_features((int)this);
  build_track_colours();
  populate_runtime_track_cells_from_segments((int)this);
  place_parcels_on_track(this);
  select_track_tile_edge_variants(this);
  promote_track_tiles_to_fringe_variants(this);
  harmonize_center_lane_floor_slide_variants(this);
  merge_track_tile_runs(this);
  mark_track_warning_zones((int)this);
  build_track_fringe_objects(this);
  v3 = (float *)get_track_skirt_color((int *)MEMORY[0x4DF904] + 119174, v5);
  return build_track_render_caches((int)(this + 23), *v3, *((_DWORD *)v3 + 1), *((_DWORD *)v3 + 2), *((_DWORD *)v3 + 3));
}

