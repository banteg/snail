# Android → Windows Symbol Matches

Cross-reference of unstripped Android (`libsnailmail.so`) symbols against the stripped Windows binary (`SnailMail_unwrapped.exe`). Each match is confirmed by comparing decompiled code structure, constants, string references, and call patterns.

**Legend**: `NEW` = currently unnamed (`sub_XXXX`) in BN, `EXISTS` = already named, `INLINED` = no standalone Windows function

---

## cRSubGame (Game Controller)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Evidence |
|---|---|---|---|---|
| `CalcRealPos` | 0x4444b0 | `project_position_onto_track_attachment` | — | EXISTS |
| `SetRate` | 0x4404c0 | `sub_4404c0` | `set_subgame_rate` | Sets two speed fields to same arg |
| `CalcRate` | 0x4404d0 | `sub_4404d0` | `calc_subgame_rate` | Mode-branched speed calc with Sin threshold blend at 0.25/0.75 |
| `SetFeatures` | 0x435df0 | `sub_435df0` | `set_subgame_features` | Mode-branched build flag OR mask, called from rebuild_track |
| `BuildColours` | 0x435d40 | `sub_435d40` | `build_track_colours` | 53-iter loop calling White() 13×, stride 0x10 |
| `SmoothTrack` | 0x435a80 | `select_track_tile_edge_variants` | — | EXISTS |
| `WarnTrack` | 0x4355f0 | `promote_track_tiles_to_fringe_variants` | — | EXISTS |
| `SlideSmoothTrack` | 0x4356f0 | — | `harmonize_center_lane_floor_slide_variants` | Checks cols 3/5, swaps floor/slide, flag `|= 0x40` |
| `CondenseTrack` | 0x435180 | `merge_track_tile_runs` | — | EXISTS |
| `DeSaltTrack` | 0x4354f0 | `mark_track_warning_zones` | — | EXISTS |
| `SwitchMirror` | 0x435e60 | `sub_435e60` | `switch_track_mirror` | "Mirror" string, RAND>0.5, threshold 3, XOR toggle |
| `FringeEdgeTrack` | 0x434be0 | `build_track_fringe_objects` | — | EXISTS |
| `RemoveBods` | 0x440910 | `sub_440910` | `remove_subgame_bods` | Loops 0xe10 cells removing linked list + sprites, called from destroy_subgame |
| `GetSkirtColour` | 0x442120 | `get_track_skirt_color` | — | EXISTS |
| `GetRate` | — | — | — | INLINED (trivial getter) |
| `GetRealRate` | — | — | — | INLINED (trivial getter) |
| `WarpFade` | — | — | — | No-op stub on Android, not present on Windows |

---

## cRSnail / cRSnailSkin (Player Model)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Evidence |
|---|---|---|---|---|
| `cRSnail::SetAnimation` | 0x444600 | `dispatch_cutscene_animation` | — | EXISTS |
| `cRSnail::SetWeapon` | 0x445920 | `sub_445920` | `set_snail_weapon` | 3 weapon slots, bitmask switch (0x10,2,1,4,8,0x40,0x90,0xc0,0x20) |
| `cRSnail::SetJetPack` | 0x445860 | `sub_445860` | `set_snail_jetpack` | Maps 0→0, 1→4; sounds 0x1a/0x10 |
| `cRSnail::BuildHotSpots` | 0x445d50 | `sub_445d50` | `build_snail_hotspots` | Texture lookup iteration, vertex transforms |
| `cRSnail::ReleaseWeapons` | 0x442e40 | `sub_442e40` | `release_snail_weapons` | 4 random velocities × 0.3f, hover end |
| `cRSnailSkin::AI` | 0x445cd0 | `sub_445cd0` | `update_snail_skin` | 19 hotspot iterations, dual matrix source |
| `cRSnailSkin::Init` | 0x445f60 | `sub_445f60` | `initialize_snail_skin` | Sets state=0, links Game+0x432700 |
| `cRSnail::AI` | — | — | — | Empty virtual stub |
| `cRSnail::AIGoldy` | — | — | — | Empty virtual stub |

---

## cRCompletion / cRCutScene / cRClickStart

| Android Symbol | Windows Addr | Current Name | Proposed Name | Evidence |
|---|---|---|---|---|
| `cRCompletion::Init` | 0x404920 | `initialize_completion_screen` | — | EXISTS |
| `cRCompletion::AI` | 0x4067e0 | `update_completion_screen` | — | EXISTS |
| `cRCompletion::UnInit` | 0x406060 | `destroy_completion_screen` | — | EXISTS |
| `cRCompletion::RegisterParcel` | 0x405040 | `sub_405040` | `register_parcel_delivery` | ScoreAdd type 4, bonus type 5, parcel counter |
| `cRCutScene::Init` | 0x4428d0 | `sub_4428d0` | `initialize_cutscene` | Camera matrix copy, constants -0.785f/6.283f/1.4f |
| `cRCutScene::AI` | 0x4466d0 | `sub_4466d0` | `update_cutscene` | 12-case switch, death/completion voice dispatch |
| `cRClickStart::Init` | 0x442170 | `sub_442170` | `initialize_click_start` | "Click to Start", linked list add, state=2 |
| `cRClickStart::AI` | 0x442290 | `sub_442290` | `update_click_start` | Level select, click detect, RandSeed, states 2/3/4 |
| `cRContinue::*` | — | — | — | Integrated into `update_frontend_state_machine` (states 0x1a–0x1c) |

---

## cRTipManager

| Android Symbol | Windows Addr | Current Name | Proposed Name | Evidence |
|---|---|---|---|---|
| `cRTipManager::Init` | 0x448cf0 | `sub_448cf0` | `initialize_tip_manager` | 3 slots zeroed, stride 0x20 |
| `cRTipManager::AI` | 0x448d80 | `sub_448d80` | `update_tip_manager` | 3-slot iteration, calls tip AI |
| `cRTipManager::TipNew` | 0x448d30 | `enqueue_tip_message` | — | EXISTS |
| `cRTipManager::UnInitTips` | 0x448d10 | `sub_448d10` | `uninit_tips` | 3-slot iteration, calls tip UnInit |

---

## cRInvincible

| Android Symbol | Windows Addr | Current Name | Proposed Name | Evidence |
|---|---|---|---|---|
| `cRInvincible::Init` | 0x446e80 | `sub_446e80` | `initialize_invincible` | State=0, shield sprite, timer 0x3daaaaab |
| `cRInvincible::AI` | 0x446f80 | `sub_446f80` | `update_invincible` | 4-state, checks damage bit 0x80, skin change |
| `cRInvincible::Start` | 0x446f30 | `sub_446f30` | `start_invincible` | State=2, timer=1.0f, unhide sprite |

---

## cRNuke (Explode Ring Effect)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Evidence |
|---|---|---|---|---|
| `cRNuke::Init` | 0x447110 | `sub_447110` | `initialize_nuke` | 25-sprite ring, immediate tail-call into update, `y-5`, `2*dt`, radius `7.0`, collision-only caller |
| `cRNuke::AI` | 0x4471e0 | `sub_4471e0` | `update_nuke` | State==1, Sin/Cos orbital motion over 25 sprites, radius `7.0` |
| `cRNuke::UnInit` | 0x4470e0 | `sub_4470e0` | `uninit_nuke` | Kill 25 sprites loop, state=0 |

---

## cRDirectX (X File Loading)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Evidence |
|---|---|---|---|---|
| `cRDirectX::Load` | 0x405640 | `load_x_mesh` | — | EXISTS |
| `cRDirectX::LoadAnim` | 0x405d60 | `load_x_animation_clip` | — | EXISTS |
| `cRDirectX::Init` | 0x405c90 | `sub_405c90` | `initialize_directx_loader` | Loads "X/_Animation.txt" |

---

## cRSlug (Slug Hazard)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Evidence |
|---|---|---|---|---|
| `cRSlug::AI` | 0x43f930 | `sub_43f930` | `update_slug_hazard_ai` | 4-state switch, Sin oscillation, blink decay, voice AI |
| `cRSlug::Hit` | 0x43f620 | `sub_43f620` | `hit_slug_hazard` | Health subtract, Kill if depleted, VoicePlay |
| `cRSlug::Kill` | 0x43f8b0 | `sub_43f8b0` | `kill_slug_hazard` | State check, ScoreAdd(1), collision_side, Explode |
| `cRSlug::Explode` | 0x43f680 | `sub_43f680` | `explode_slug_hazard` | 20-iter particle loop, random scatter, texture 0x81 |
| `cRSlug::VoiceAI` | 0x43f520 | `sub_43f520` | `update_slug_voice_ai` | Timer advance, flag reset at 1.0f |
| `cRSlug::VoicePlay` | 0x43f560 | `sub_43f560` | `play_slug_voice` | Global busy check, timer reset |

---

## cRSalt / cRSaltManager

| Android Symbol | Windows Addr | Current Name | Proposed Name | Evidence |
|---|---|---|---|---|
| `cRSalt::AI` | 0x4417d0 | `update_salt_hazard` | — | EXISTS |
| `cRSalt::Smoke` | — | — | — | INLINED into spawn_salt_hazard |
| `cRSaltManager::Init` | 0x441540 | `initialize_salt_hazard_pool` | — | EXISTS |
| `cRSaltManager::Add` | 0x441560 | `spawn_salt_hazard` | — | EXISTS |

---

## cRSubGarbage

| Android Symbol | Windows Addr | Current Name | Proposed Name | Evidence |
|---|---|---|---|---|
| `cRSubGarbage::AI` | 0x43f200 | `update_garbage_hazard` | — | EXISTS |
| `cRSubGarbage::Kill` | 0x43f130 | `destroy_garbage_hazard` | — | EXISTS |
| `cRSubGarbage::Smoke` | 0x43d5a0 | `sub_43d5a0` | `spawn_garbage_smoke_particle` | Sprite texture 0x21, scale by track_center_x |

---

## cRSubRing / cRSubTrampRing / cRFringe

| Android Symbol | Windows Addr | Current Name | Proposed Name | Evidence |
|---|---|---|---|---|
| `cRSubRing::AI` | 0x43e830 | `sub_43e830` | `update_ring_hazard_ai` | 5-state, Sin oscillation, 8 star sub-sprites |
| `cRSubRing::Init` | 0x43df10 | `spawn_track_ring_or_special_effect` | — | EXISTS |
| `cRSubTrampRing::AI` | 0x43efb0 | `sub_43efb0` | `update_tramp_ring_ai` | Cos bob, fade-out, list remove |
| `cRFringe::AI` | 0x43ee50 | `sub_43ee50` | `update_fringe_ai` | Kill-behind check, 3-state |

---

## cRSubGolb (Golb Enemy / Parcel Flight Object)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Evidence |
|---|---|---|---|---|
| `cRSubGolb::AI` | 0x414820 | `sub_414820` | `update_golb_ai` | Massive function: path follow, homing, collision vs garbage/slugs |
| `cRSubGolb::Kill` | 0x414670 | `sub_414670` | `kill_golb` | List remove, 3-type switch for cleanup |
| `cRSubGolb::Create` | 0x415280 | `sub_415280` | `create_golb` | Type from bitfield (0x7/0x18/0x60), linked list add |
| `cRSubGolb::Smoke` | 0x415c60 | `sub_415c60` | `spawn_golb_smoke` | Sprite texture 0x80, velocity from self * 0.4f |

---

## cRPath / cRPathFollowGoldy

| Android Symbol | Windows Addr | Current Name | Proposed Name | Evidence |
|---|---|---|---|---|
| `cRPath::Search` | 0x415e30 | `sub_415e30` | `search_path_for_golb` | Triangle intersection, z-range [0,30], segment backward iteration |
| `cRPathFollowGoldy::Init` | — | — | — | NOT FOUND (inlined) |
| `cRPathFollowGoldy::Traverse` | — | — | — | NOT FOUND (inlined) |

---

## cRSubGoldy (Player)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Evidence |
|---|---|---|---|---|
| `SetShootFlags` | 0x43a1a0 | `sub_43a1a0` | `update_player_movement_flags` | 9-case switch with power-of-2 flags (1,2,4,8,0x10,0x20,0x40,0xc0,0x90), matching float rate constants |
| `PlayShootSfx` | 0x43afd0 | `sub_43afd0` | `play_movement_state_sound` | Flag bitmask checks `& 7`, `& 0x18`, `& 0x60` → sound IDs 0x11, 0x13, 0x16 |
| `Shoot` | 0x441ad0 | `sub_441ad0` | `shoot_subgoldy` | Iterates bullet slots for free state, creates projectile, plays sound |
| `Kill` | 0x445840 | `sub_445840` | `kill_subgoldy` | Calls FallingInit, sets position.y = -8.0 |
| `DeathInit` | 0x446e30 | `initialize_subgoldy_death` | — | EXISTS |
| `RessurectInit` | 0x441fa0 | `initialize_subgoldy_resurrect` | — | EXISTS |
| `RessurectAI` | 0x441fd0 | `update_subgoldy_resurrect` | — | EXISTS |
| `FallingInit` | 0x43af60 | `initialize_subgoldy_fall_state` | — | EXISTS |
| `GhostInit` | 0x43d230 | `sub_43d230` | `initialize_subgoldy_ghost` | Creates 2 trail sprites, x-offsets ±4.5, scale 0.5 |
| `HealthCollect` | 0x43a010 | `sub_43a010` | `health_collect_particles` | 8-sprite loop, Sin/Cos × 0.015 circular distribution, velocity × 3.0 |
| `ScoreStatsInit` | 0x444960 | `sub_444960` | `initialize_score_stats` | Zeros 6–7 dword score counter block |
| `ScoreAdd` | 0x4402c0 | `add_subgoldy_score` | — | EXISTS |
| `Init` | 0x43a9c0 | `initialize_subgoldy` | — | EXISTS |
| `AI` | 0x43b120 | `update_subgoldy` | — | EXISTS |
| `ShowLives` | 0x43af10 | `show_subgoldy_lives` | — | EXISTS |
| `Collision` | 0x444cf0 | `handle_subgoldy_collisions` | — | EXISTS |
| `SpeedUpCollect` | — | — | — | Empty stub on Android |
| `Passed` | — | — | — | INLINED (trivial field store) |
| `Echo` | — | — | — | Empty stub on Android |
| `SameViewport` | — | — | — | INLINED (simple bitmask check) |
| `GhostDraw` | — | — | — | INLINED (sprite transparency set) |

---

## cRSubHover (Jetpack/Hover Controller)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Evidence |
|---|---|---|---|---|
| `Init` | 0x43a930 | `initialize_jetpack_gauge` | — | EXISTS |
| `On` | 0x43a980 | `arm_jetpack_gauge` | — | EXISTS |
| `AI` | 0x43a390 | `update_jetpack_gauge` | — | EXISTS |
| `End` | 0x43a370 | `sub_43a370` | `end_jetpack_hover` | Checks state==1, clamps progress to 0.94 threshold |
| `JetInit` | 0x43a5b0 | `sub_43a5b0` | `initialize_jet_particles` | 15×2 sprite loop, alpha 0x3f7fbe77, type 0x9e |
| `JetUnInit` | 0x43a580 | `sub_43a580` | `uninit_jet_particles` | 15×2 sprite kill loop |
| `Jets` | 0x43a690 | `sub_43a690` | `update_jet_particles` | 15×2 loop, velocity × 0.85, sparkle at iter 14 |
| `Hover` | 0x43d880 | `sub_43d880` | — | Empty stub (both platforms) |

---

## cRWarning (Damage Warning Controller)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Evidence |
|---|---|---|---|---|
| `Init` | 0x446e80 | `sub_446e80` | `initialize_warning` | Border widget, alpha 0x3f7fbe77, rate 0x3daaaaab |
| `AI` | 0x446f80 | `sub_446f80` | `update_warning` | 3-state (off/fade-in/fade-out), sound 0x32 |
| `Start` | 0x446f30 | `sub_446f30` | `start_warning` | Timer=1.0, state=2, UnHideInit |
| `Stop` | 0x446f50 | `sub_446f50` | `stop_warning` | State=0, HideInit |
| `StopSample` | 0x446f60 | `sub_446f60` | `stop_warning_sample` | Stops sound 0x32 |
| `UnInit` | 0x446f10 | `sub_446f10` | `uninit_warning` | Border cleanup |

---

## cRDamageGuage

| Android Symbol | Windows Addr | Current Name | Proposed Name | Evidence |
|---|---|---|---|---|
| `Init` | 0x440fa0 | `sub_440fa0` | `initialize_damage_gauge` | Zeros fill/state fields |
| `AI` | 0x440fd0 | `update_damage_gauge` | — | EXISTS |
| `Take` | 0x4413f0 | `apply_damage_gauge_delta` | — | EXISTS |

---

## cRBarrier

| Android Symbol | Windows Addr | Current Name | Proposed Name | Evidence |
|---|---|---|---|---|
| `cRBarrier::AI` | 0x440f80 | `sub_440f80` | `update_barrier_ai` | Stores y=0.4f, reads owner z position |

---

## Utility (tVector / tMatrix)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Evidence |
|---|---|---|---|---|
| `tVector::Normalize` | 0x44cca0 | `sub_44cca0` | `normalize_vector` | Dot→Sqrt→divide, returns magnitude |
| `tVector::Magnitude` | 0x44ccf0 | `sub_44ccf0` | `vector_magnitude` | sqrt(x²+y²+z²) |
| `tMatrix::Identity` | 0x44d210 | `sub_44d210` | `set_matrix_identity` | Diagonal 1.0f, off-diagonal 0 |
| `tMatrix::RotWorldY` | 0x44cec0 | `sub_44cec0` | `rotate_matrix_world_y` | Cos/Sin on cols 0,2 |
| `tMatrix::RotWorldX` | 0x44ce30 | `sub_44ce30` | `rotate_matrix_world_x` | Cos/Sin on cols 1,2 |

---

## Hypotheses: Naming Conventions

The Android binary reveals the original class architecture:

- **`cRSubGoldy`** = the player character controller. Windows currently uses `subgoldy` naming, which is correct.
- **`cRSubGolb`** = the enemy/parcel-flight projectile. Currently `sub_414820` etc. "Golb" is "Gölb" — the enemy snails. The massive `sub_414820` that was previously unclear is confirmed as the Golb AI with path-following, homing, and collision against garbage/slugs.
- **`cRSubHover`** = the jetpack hover subsystem. The `sub_43a5b0`/`sub_43a690` cluster that was grouped near the jetpack gauge is confirmed as JetInit/Jets particle effects, separate from the gauge timer.
- **`cRWarning`** = the damage warning overlay. The `sub_446e80`–`sub_446f80` cluster near the invincible controller is the warning system, not part of invincibility.
- **`cRNuke`** = the explode-ring clearance effect. The real Windows match is the `sub_447110` / `sub_4471e0` / `sub_4470e0` cluster, not the earlier jet-particle guess at `sub_43a5b0` / `sub_43a690`.
- **`cRInvincible`** = the invincibility shell controller. Separate from the warning system — both use similar sprite patterns but track different state.
- **`cRCompletion::RegisterParcel`** = `sub_405040`. This is the parcel delivery scoring function that awards ScoreAdd type 4 (100 pts) per delivery and optionally type 5 (custom bonus) when all parcels delivered.
- **`cRCutScene`** = `sub_4428d0` (Init) and `sub_4466d0` (AI). The 12-case cutscene state machine handles both death and completion camera sequences.
- **`cRClickStart`** = `sub_442170`/`sub_442290`. The tutorial "Click to Start" prompt controller.
- **`cRContinue`** has no standalone Windows equivalent — its functionality is folded into `update_frontend_state_machine` states 0x1a–0x1c.

---

## Statistics

- **Total Android C++ symbols examined**: ~120
- **Confirmed matches to Windows functions**: 85
- **New identifications** (currently `sub_XXXX`): **55**
- **Already named in Windows**: 23
- **Inlined / not found / empty stubs**: ~12
