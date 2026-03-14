# Android → Windows Symbol Matches (Sweep 4)

Fourth cross-reference pass covering: remaining cRSubGame spawn/level methods, cRPath position helpers and remaining builders, cRSubGoldy/cRFireWork/cRSubLazerManager, cRSplashManager, remaining cRObject methods, and miscellaneous.

**Legend**: `NEW` = currently unnamed (`sub_XXXX`) in BN, `EXISTS` = already named, `INLINED` = no standalone Windows function, `ABSENT` = not in Windows build

---

## cRSubGame Spawn/Add Methods

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `AddSlug` | 0x43dc80 | `spawn_slug_hazard` | — | EXISTS |
| `AddGarbage` | 0x43da80 | `spawn_track_garbage_hazard` | — | EXISTS |
| `AddHealth` | 0x43d6c0 | `spawn_track_health_pickup` | — | EXISTS |
| `AddJetPack` | 0x43d890 | `spawn_track_jetpack_pickup` | — | EXISTS |
| `AddRing` | 0x43df10 | `spawn_track_ring_or_special_effect` | — | EXISTS |
| `AddSpeedUp` | 0x43d880 | `sub_43d880` | `spawn_track_speedup` | NEW — empty stub (both platforms) |
| `AddParcel` | 0x443730 | `sub_443730` | `spawn_track_parcel` | NEW — sprite 0x79, animation "!\rR<", parcel-to-goldy pointer |

---

## cRSubGame Level Building Helpers

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `BuildLevel` | 0x435eb0 | `populate_runtime_track_cells_from_segments` | — | EXISTS |
| `GenerateLevel` | 0x437de0 | `rebuild_track_runtime_from_segments` | — | EXISTS |
| `StartLevel` | 0x437eb0 | `build_subgame_level` | — | EXISTS |
| `LevelConvert` | 0x437270 | `normalize_segment_glyph_for_track_flags` | — | EXISTS |
| `PlaceParcels` | 0x4438e0 | `place_parcels_on_track` | — | EXISTS |
| `PlaceParcelsSurvival` | 0x444240 | `place_challenge_parcels_on_track` | — | EXISTS |
| `LocFromPos` | 0x43d410 | `get_track_grid_cell_at_world_position` | — | EXISTS |
| `RowFromPos` | 0x43d480 | `get_track_runtime_cell_at_world_z` | — | EXISTS |
| `GetY` | 0x43d4d0 | `sample_track_floor_height_at_position` | — | EXISTS |
| `TestLoc` | 0x434b60 | `is_neighbor_cell_solid` | — | EXISTS |
| `BlinkRandInit` | 0x4408c0 | `sub_4408c0` | `initialize_blink_random` | NEW — fills 24 entries with `1/((rand+1)*60)` |
| `BlinkRand` | 0x4408a0 | `sub_4408a0` | `advance_blink_random` | NEW — modular increment, returns float |
| `HideScores` | 0x445f10 | `sub_445f10` | `hide_gameplay_scores` | NEW — HideInit on 2 borders |
| `UnHideScores` | 0x445f40 | `sub_445f40` | `unhide_gameplay_scores` | NEW — UnHideInit on 2 borders |
| `CalcSliderToRate` | 0x437e80 | `sub_437e80` | `calc_slider_to_rate` | NEW — `if(x>=1) 1.1 else x*0.9+0.2` |
| `ReSet` | 0x437b10 | `sub_437b10` | `reset_subgame` | NEW — loop array init, state=1 |
| `InitSchoolPlay` | — | — | — | Dead code (zero callers) |
| `TrampolineJoin` | — | — | — | Dead code (zero callers) |
| `CalcRateToSlider` | — | — | — | Dead code (zero callers) |

---

## cRPath Position Helpers

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `GetPos` | 0x42b9c0 | `sub_42b9c0` | `get_path_position_at_node` | NEW — stride 0xA8, vector component math at path sample offsets |
| `SearchPos` | 0x42ca90 | `is_point_inside_track_attachment` | — | EXISTS |
| `HalfPipePos` | — | — | — | INLINED into `update_track_attachment_follow_state` |
| `HalfPolePos` | — | — | — | INLINED into `update_track_attachment_follow_state` |

---

## cRPath Remaining Build Methods

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `BuildCage2` | 0x41e440 | `sub_41e440` | `initialize_cage2_path_template_pair` | NEW — Cos loop with 2π/arg, CalcLengthZ tail call |
| `BuildFringe` | 0x4246a0 | `sub_4246a0` | `build_track_fringe_mesh` | NEW — 0.4f vertex offset, flag 0x100040, called 120× |
| `BuildFringeSuperTramp` | 0x424ad0 | `sub_424ad0` | `build_track_fringe_supertramp_mesh` | NEW — flag 0x100000 (no 0x40), reversed winding |
| `BuildInvert1` | — | — | — | ABSENT — kind 0x38 not in Windows |

---

## Path Builder Naming Corrections

The Android symbols reveal **three existing Windows function names are wrong**:

| Current Windows Name | Correct Android Name | Evidence |
|---|---|---|
| `initialize_shimmy_path_template_pair` (0x420170) | `BuildWorm` | sample_count=24, width=96.0, 16-subdivision body |
| `initialize_slalom_path_template_pair` (0x4221f0) | `BuildSlalomBig` | Sin×4.444 amplitude, sample_count=arg2+8 |
| `initialize_slalomdouble_path_template_pair` (0x41f760) | `BuildSlalom` | Sin×5.0 amplitude, 4+4 bookend |

---

## cRPathFollowGolb

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init` | 0x421770 | `sub_421770` | `initialize_path_follow_golb` | NEW — sets state=1, kind, subloc, z-offset, y-0.49 |
| `Traverse` | 0x420cb0 | `update_track_attachment_follow_state` | — | EXISTS |

---

## cRSubGoldy Remaining

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `ScoreStatsDisplay` | 0x4403c0 | `sub_4403c0` | `display_score_stats` | NEW — "Score Stats: %i", per-category ×100/total percentages |
| `JetPackCollect` | — | — | — | ABSENT — 24-sprite particle burst not in Windows build |
| `Jet` | — | — | — | ABSENT — replaced by trail-based system (JetInit/Jets) |

---

## cRFireWork

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Shoot` | 0x441dd0 | `sub_441dd0` | `firework_shoot` | NEW — flags |=0x802, decay 0x3e8e38e4, size 0.5/0.1, random velocities |

---

## cRSubLazerManager (Bullet/Projectile Pool)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init` | 0x441650 | `initialize_wall2_ambient_hazard_pool` | — | EXISTS (20 slots, stride 0xb0) |
| `Shoot` | 0x441ad0 | `shoot_subgoldy` | — | EXISTS (20-slot search, sound 0xf) |

---

## cRSplashManager

All 7 Android methods are consolidated into 2 Windows functions:

| Android Methods | Windows Addr | Current Name | Status |
|---|---|---|---|
| `Init`, `SetSplash`, `SetBar`, `SetBarPos` | 0x418b50 | `initialize_loading_screen` | EXISTS (all inlined) |
| `Render`, `RenderStart`, `RenderEnd` | 0x418e80 | `update_loading_screen` | EXISTS (all inlined) |

---

## cRObject Remaining Methods

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `AddEdge` | 0x4305a0 | `sub_4305a0` | `add_object_edge` | NEW — magnitude<0.9f, gEdgeStore globals |
| `ApplyToon` | 0x42fa80 | `sub_42fa80` | `apply_object_toon` | NEW — flag |=0x4001, "Object Toon Vertices" |
| `VerticesPush` | 0x42f7d0 | `sub_42f7d0` | `push_object_vertices` | NEW — allocates backup, copies |
| `RequestFaceQuadNormals` | 0x42f800 | `sub_42f800` | `request_object_facequad_normals` | NEW — "Object FaceQuad Normals List" |
| `RequestFaceQuadTextureGroups` | 0x42f930 | `sub_42f930` | `request_object_texture_groups` | NEW — "Fixed FaceQuadTextureGroupsNumber too small" |
| `RequestColoursPointer` | 0x42f850 | `sub_42f850` | `request_object_colours` | NEW — "Object Vertex Colours List", init 1.0f |
| `ReLoad` | — | — | — | ABSENT (Android binary SMO; Windows text-based) |
| `Save` | — | — | — | ABSENT (no SMO serialization) |
| `SmoGetFixed*` (4 variants) | — | — | — | ABSENT (Android-only SMO parsing) |
| `RequestVerticesCopy` | — | — | — | Handled through VerticesPush/Pop |

---

## cRSnailSkin / cRSnail Remaining

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `cRSnailSkin::Change` | 0x445fd0 | `sub_445fd0` | `change_snail_skin` | NEW — `1.0/(float×60.0)` rate, state toggle |
| `cRSnail::ExtractHotSpots` | 0x445d50 | `build_snail_hotspots` | — | EXISTS — "Cannot find HotPoint Texture %s" |

---

## cRBod / cRGalaxy Remaining

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `cRBod::ApplyPos` | 0x42f680 | `sub_42f680` | `apply_bod_position` | NEW — object vertex × matrix loop |
| `cRGalaxy::Line` | 0x409b00 | `sub_409b00` | `draw_galaxy_line` | NEW — normalize, perpendicular ×0.5, quad render |

---

## cRSubGame Skirt Colour

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `GetSkirtColour` | 0x442120 | `get_track_skirt_color` | — | EXISTS |
| `GetSkirtColourRandom` | — | — | — | ABSENT (Android TGA palette; Windows level def text) |
| `GetSkirtColourRandomOpen` | — | — | — | ABSENT |

---

## Utility / Rendering

| Android Symbol | Windows Addr | Proposed Name | Status |
|---|---|---|---|
| `cGLVertexArray::WorldFlatten` | — | — | ABSENT (OpenGL-only) |
| `cGLVertexArray::CalcTriStripSimple` | — | — | ABSENT (OpenGL-only) |
| `cGLVertexArray::WorldAdd` | — | — | ABSENT (OpenGL-only) |
| `cRGame::CollisionListAdd` | — | — | Empty stub; inlined on Windows |
| `cRGame::CollisionListRemove` | — | — | Empty stub; inlined on Windows |

---

## Statistics (Sweep 4)

- **New identifications** (currently `sub_XXXX`): **~30**
- **Already named in Windows**: ~25
- **Inlined / absent / dead code**: ~20
- **Naming corrections**: 3 path builder misnomers identified
- **Grand total across all 4 sweeps**: **~215 new function identifications**
