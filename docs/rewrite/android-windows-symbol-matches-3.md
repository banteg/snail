# Android → Windows Symbol Matches (Sweep 3)

Third cross-reference pass covering: 3D object/mesh infrastructure, sprite system, galaxy/score persistence, input/resource managers, visual effects, and miscellaneous gameplay helpers.

**Legend**: `NEW` = currently unnamed (`sub_XXXX`) in BN, `EXISTS` = already named, `INLINED` = no standalone Windows function, `ABSENT` = not in Windows build

---

## cRObject (3D Model/Mesh)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init` | 0x42f6f0 | `sub_42f6f0` | `initialize_object` | NEW |
| `Load` | 0x405640 | `load_x_mesh` | — | EXISTS |
| `RequestVertices(int)` | 0x42f710 | `sub_42f710` | `request_object_vertices` | NEW — "Object Vertex List", "Too many Vertices" |
| `RequestFaceQuads(int)` | 0x42f8c0 | `sub_42f8c0` | `request_object_facequads` | NEW — "Object FaceQuad List" |
| `RequestEdges(int)` | 0x430570 | `sub_430570` | `request_object_edges` | NEW — "Object Edges" |
| `RequestAlphas` | 0x42f850 | `sub_42f850` | `request_object_vertex_colours` | NEW — "Object Vertex Colours List" |
| `RequestAnim` | 0x430a70 | `sub_430a70` | `request_object_animation` | NEW — "Object Animation", keyframe lerp |
| `CopyVertices` | 0x42f790 | `sub_42f790` | `copy_object_vertices` | NEW — 12-byte per-vertex memcpy |
| `CalcEdges` | 0x4308b0 | `sub_4308b0` | `calc_object_edges` | NEW — 3 edges per tri, AddEdge loop |
| `CalcTextureGroups` | 0x4303f0 | `sub_4303f0` | `calc_object_texture_groups` | NEW — groups facequads by texture |
| `CalcFaceQuadNormals` | 0x42fcb0 | `sub_42fcb0` | `calc_object_facequad_normals` | NEW — cross product, "Normal Tally" |
| `ScaleVertices` | — | — | — | INLINED |
| `ApplyUV` | — | — | — | INLINED into path builders |
| `ApplyUVPath` | — | — | — | INLINED into path builders |
| `ApplyUVPathSuperTramp` | — | — | — | INLINED into supertramp builder |
| `Destroy` | — | — | — | INLINED (COM Release on Windows) |

Additional object infrastructure found during matching:

| Windows Addr | Proposed Name | Evidence |
|---|---|---|
| 0x42f800 | `request_object_facequad_normals` | "Object Vertex Normals List" + "Object FaceQuad Normals List" |
| 0x42f930 | `request_object_texture_groups` | "Object FaceQuad Texture Groups" |
| 0x42f7d0 | `request_object_vertices_copy` | Allocates backup vertex array |
| 0x42fa80 | `request_object_toon_buffers` | "Object Toon Vertices", flag 0x4001 |
| 0x42fb10 | `calc_object_bounding_box` | Min/max bounds, max radius |
| 0x430230 | `calc_object_facequad_normals_simple` | Per-face only (no vertex accumulation) |

---

## cRObjects (Mesh Collection Manager)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init(int)` | 0x42f990 | `sub_42f990` | `initialize_object_list` | NEW — "Object List", 0xbb8 (3000) slots |
| `Add` | 0x42fad0 | `sub_42fad0` | `add_object_to_list` | NEW — "Too many Objects" error |
| `BuildObjects` | 0x42f9e0 | `sub_42f9e0` | `build_all_objects` | NEW — CalcTextureGroups+CalcNormals+CalcEdges loop |
| `ReBuildObjects` | — | — | — | INLINED |
| `ReSetFlags` | — | — | — | INLINED |

---

## cRBod (Body/Entity Base)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `SetObject` | 0x42f5d0 | `sub_42f5d0` | `set_bod_object` | NEW — stores object ptr, OR flag 2 |
| `IsAfterSprites` | 0x42f5c0 | `sub_42f5c0` | `is_bod_after_sprites` | NEW — returns bit 7 of flags |
| `AI` | — | — | — | Empty stub |

---

## cRSprite

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `AI` | 0x44df30 | `sub_44df30` | `update_sprite` | NEW — fade, velocity, animation frame stepping |
| `Init` | 0x44de90 | `sub_44de90` | `initialize_sprite` | NEW — flags 0x49, scale=1 |
| `Kill` | 0x44e200 | `sub_44e200` | `kill_sprite` | NEW — "Sprite kill error, already dead" |
| `SetTextureRef` | 0x44e550 | `sub_44e550` | `set_sprite_texture_ref` | NEW — lookup from reference table |

---

## cRSpriteManager

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init` | 0x44e160 | `sub_44e160` | `initialize_sprite_manager` | NEW — 2999 sprite pool, stride 0xb4 |
| `New(int,int,int,int)` | 0x44e2a0 | `sub_44e2a0` | `allocate_sprite` | NEW — pops from free list, gSpriteDummy fallback |
| `Load(char*,int,int)` | 0x44e0f0 | `register_sprite_texture` | — | EXISTS |
| `KillGame` | 0x44e3d0 | `sub_44e3d0` | `kill_game_sprites` | NEW — iterates 5 tag slots, kills flag 0x800 |
| `GetTexture(int)` | 0x44e570 | `sub_44e570` | `get_sprite_texture` | NEW — reference table lookup |
| `GetTextureRef(int)` | 0x44e580 | `sub_44e580` | `get_sprite_texture_ref` | NEW — platform handle from reference |
| `LoadSet`, `LoadAnim`, `SearchSet` | — | — | — | ABSENT (Android sprite set system not used on Windows) |
| `Pause`, `KillTag` | — | — | — | INLINED |

---

## cRTextures

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init(int)` | 0x44e800 | `sub_44e800` | `initialize_texture_list` | NEW — count=0, max=arg |
| `Add` | 0x44e810 | `get_or_create_texture_ref` | — | EXISTS |

---

## cRGalaxy (Route Map) Detail Methods

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init2` | 0x408cf0 | `initialize_galaxy` | — | EXISTS (merged into Init) |
| `BoxOn` | 0x409c50 | `open_galaxy_route` | — | EXISTS |
| `BoxOff` | 0x409bf0 | `close_galaxy_route` | — | EXISTS |
| `Render` | 0x4092f0 | `update_galaxy` | — | EXISTS (merged with AI) |
| `BorderBound` | 0x40a0c0 | `sub_40a0c0` | `galaxy_border_bound` | NEW — bounds-check rectangle against border widget |
| `AIControl` | — | — | — | INLINED (trivial field getter) |

---

## cRSubHighScore

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `AddArcade` | 0x4176a0 | `add_arcade_high_score` | — | EXISTS |
| `AddSurvival` | 0x417780 | `add_survival_high_score` | — | EXISTS |
| `AddTimeTrial` | 0x4178b0 | `add_time_trial_high_score` | — | EXISTS |
| `MiniInit` | 0x417540 | `initialize_high_score_tables` | — | EXISTS |
| `LoadMiniData` | 0x4175e0 | `load_high_scores_from_file` | — | EXISTS |
| `SaveMiniData` | 0x417940 | `save_high_scores_and_config` | — | EXISTS |
| `AddArcadePro` | — | — | — | ABSENT (Android-only pro mode) |
| `MiniLoad/Save/Delete/FileName` | — | — | — | ABSENT (Android uses per-entry files; Windows uses ScoreA/B/C.dat) |

---

## cRSubSolution (Replay/Save Data)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `ReSet` | 0x417a70 | `initialize_high_score_entry` | — | EXISTS |
| `Load` | 0x440020 | `deserialize_compact_high_score_record` | — | EXISTS — `(score*score) ^ 0xdeadbabe` checksum |
| `Save` | 0x440170 | `serialize_compact_high_score_record` | — | EXISTS |
| `Tip` | — | — | — | ABSENT (Android-only tooltip generation) |

---

## cRStarManager

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init` | 0x434310 | `sub_434310` | `initialize_star_field` | NEW — "StarField" sprites, Sin/Cos direction, blue tint |
| `AI` | 0x4346f0 | `sub_4346f0` | `update_star_field` | NEW — 4-state fade lifecycle |
| `Open(int)` | 0x4342c0 | `sub_4342c0` | `open_star_field` | NEW — "StarField" alloc |
| `Hide` | 0x434670 | — | `hide_star_field` | NEW — clears bit 6 on sprites |
| `UnHide` | 0x4346b0 | `sub_4346b0` | `unhide_star_field` | NEW — sets bit 6 on sprites |
| `UnInit` | 0x434270 | `sub_434270` | `destroy_star_field` | NEW — kills sprites, state=0 |
| `UpdateStars(float)` | 0x434800 | `sub_434800` | `update_star_positions` | NEW — orbit timer, camera offset × 50f |
| `ResetStars` | — | — | — | INLINED |

---

## cRInput / cRGameInput

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `cRInput::Init` | 0x40aa50 | `sub_40aa50` | `initialize_input` | NEW — 320.0f center, 0xffffffff initial |
| `cRInput::Update` | 0x40aa80 | `sub_40aa80` | `update_input` | NEW — button edge detection (XOR + AND) |
| `cRGameInput::AI` | 0x40aab0 | `sub_40aab0` | `update_game_input` | NEW — input retrieve + update |

---

## cRMouse

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `AI` | 0x44bc50 | `sub_44bc50` | `update_mouse` | NEW — DirectInput, clamp [0,639]×[0,479] |
| `ConvertScreenXY` | 0x44c100 | `sub_44c100` | `convert_mouse_screen_xy` | NEW — GetCursorPos, sensitivity scaling |
| `ClickScreen` | 0x44c060 | `sub_44c060` | `click_mouse_screen` | NEW — SetCursorPos + coordinate store |
| `Init/ClickOn/Off/SetActive/SetInActive/IsActive/ClickOnly` | — | — | — | INLINED (simple flag stores in globals) |

---

## cRFringeManager / cRPathManager / cREnemyManager / cRDuplicateVertices / cRTrack

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `cRFringeManager::Init` | 0x447090 | `initialize_fringe_manager` | — | EXISTS |
| `cRFringeManager::GetFringe` | 0x4470a0 | `allocate_fringe_object` | — | EXISTS |
| `cRPathManager::NameCode` | 0x429ae0 | `find_segment_path_index_by_name` | — | EXISTS |
| `cREnemyManager::Init` | 0x415e20 | `sub_415e20` | `initialize_enemy_manager` | NEW — `*arg1 = 0` |
| `cRDuplicateVertices::Init` | 0x419f50 | `sub_419f50` | `initialize_duplicate_vertices` | NEW — "Duplicate vertices" alloc |
| `cRDuplicateVertices::Clean` | 0x419f80 | `sub_419f80` | `clean_duplicate_vertices` | NEW — int16 stride pairing |
| `cRTrack::Change` | 0x410730 | `select_level_track_texture_set` | — | EXISTS |

---

## cRHash / cRResourceManager / cRWorld / cRBorderStack

| Android Symbol | Windows Addr | Proposed Name | Status |
|---|---|---|---|
| `cRHash::*` (all) | — | — | ABSENT — Android-only O(1) texture lookup optimization; Windows uses linear scan |
| `cRResourceManager::*` (all) | — | — | ABSENT — Android async loading state machine; Windows loads synchronously |
| `cRWorld::*` (Init/Add/ReSet) | — | — | INLINED into track build/render cache functions |
| `cRBorderStack::*` (Init/Perform) | — | — | INLINED into border manager functions |

---

## cRLogo / cRLogoRow / cRLogoLetter (Title Logo)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `cRLogo::Init` | 0x4191e0 | `initialize_intro_screen` | — | EXISTS |
| `cRLogo::AI` | 0x4199e0 | `update_intro_screen` | — | EXISTS |
| `cRLogo::Open` | 0x419110 | `sub_419110` | `open_logo` | NEW — loads "Objects/Font3D", "Intro/*.tga" |
| `cRLogo::UnInit` | 0x419920 | `destroy_intro_screen` | — | EXISTS |
| `cRLogoRow::AI` | 0x419a90 | `sub_419a90` | `update_logo_row` | NEW — velocity add, alpha fade by z |
| `cRLogoLetter::AI` | 0x419a90 | `sub_419a90` | — | Merged with cRLogoRow::AI by compiler |

---

## cRSquidge (Screen Transition Squish)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `AI` | 0x4449c0 | `sub_4449c0` | `update_squidge` | NEW — 0.15f damping, 0.82f decay, 0.001f threshold |
| `StartY` | 0x444980 | `sub_444980` | `start_squidge_y` | NEW — arg×0.5f |
| `StartZ` | 0x4449a0 | `sub_4449a0` | `start_squidge_z` | NEW — arg×-0.003f |

---

## cRVapour (Trail Effect)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init` | 0x442500 | `sub_442500` | `initialize_vapour` | NEW — "Vapour Trail" alloc |
| `AI` | 0x4425f0 | `sub_4425f0` | `update_vapour` | NEW — trail vertex processing |
| `Add` | 0x442560 | `sub_442560` | `add_vapour_point` | NEW — memcpy 0x40, buffer shift |
| `ReSet` | 0x442540 | `sub_442540` | `reset_vapour` | NEW — count=0, clear flag 0x20 |

---

## cRWeapon / cROverlay / cRCamera / cRPlayer

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `cRWeapon::SetAnimation` | 0x4446e0 | `sub_4446e0` | `set_weapon_animation` | NEW — queue or direct path, flag 0x20 |
| `cRWeapon::AI` | 0x407b50 | `sub_407b50` | — | Empty stub |
| `cROverlay::Init` | 0x40a240 | `sub_40a240` | `initialize_overlay` | NEW — Identity+Invert, rotation constants |
| `cROverlay::AI` | 0x40a1b0 | `sub_40a1b0` | `update_overlay` | NEW — rotation wrap 2π, RotLocalZ |
| `cRCamera::AI` | 0x407b50 | `sub_407b50` | — | Empty stub |
| `cRPlayer::AI` | 0x4107d0 | `update_frontend_state_machine` | — | EXISTS |

---

## cRProgressBar / cRToolTip / cRTwinkle / cRInputOK / cRJetPack

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `cRProgressBar::AI` | 0x437c40 | `sub_437c40` | `update_progress_bar` | NEW — OSD with sprite 0x9d/0x9b/0x9c |
| `cRToolTip::AI` | 0x403c20 | `sub_403c20` | `update_tooltip` | NEW — "Tool tip overload", flag 0x20000 |
| `cRToolTip::ReSet` | 0x403be0 | `sub_403be0` | `reset_tooltip` | NEW — state transitions, border kill |
| `cRTwinkle::AI` | 0x404080 | `sub_404080` | `update_twinkle` | NEW — 2π wrap, "fff?" alpha, 3-state |
| `cRTwinkle::Draw` | 0x404070 | `sub_404070` | `draw_twinkle` | NEW — trivial wrapper |
| `cRTwinkleManager::AI` | 0x404030 | `sub_404030` | `update_twinkle_manager` | NEW — iterates twinkles at stride 0xc |
| `cRInputOK::Init` | 0x403560 | `sub_403560` | `initialize_input_ok` | NEW — "OK" widget |
| `cRInputOK::AI` | 0x4034d0 | `sub_4034d0` | `update_input_ok` | NEW — flag 4/8, position calc |
| `cRJetPack::AI` | 0x4431d0 | `sub_4431d0` | `update_jetpack_visual` | NEW — Sin×0.3f oscillation |

---

## cRCheat

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init` | 0x404740 | `sub_404740` | `initialize_cheat` | NEW |
| `AI` | 0x404750 | `sub_404750` | `update_cheat` | NEW — "NEWTON", "AUTUMN", "SHEEP" codes |
| `MatchText` | 0x4047d0 | `sub_4047d0` | `match_cheat_text` | NEW — "Cheat text too long", backward compare |

---

## cRSplash (Thanks For Playing)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init` | 0x433fd0 | `sub_433fd0` | `initialize_thanks_screen` | NEW — "Splash.txt", "introtext" music |
| `AI` | 0x4340f0 | `sub_4340f0` | `update_thanks_screen` | NEW — "Test your reflexes in Challenge Mode!" |
| `Open` | 0x433fc0 | `sub_433fc0` | `open_thanks_screen` | NEW — stores game+0x74618 |
| `UnInit` | 0x4340c0 | `sub_4340c0` | `uninit_thanks_screen` | NEW — kills border, state 0xe |

---

## cRBanner / cRRowModel / cRAnimManager / cRBall

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `cRBanner::AI` | 0x441d40 | `sub_441d40` | `update_banner` | NEW — Sin×0.26f oscillation, 40/46f thresholds |
| `cRRowModel::AI` | 0x443070 | `sub_443070` | `update_row_model` | NEW — velocity add, z-threshold, list remove |
| `cRAnimManager::Init` | 0x4447c0 | `sub_4447c0` | `initialize_anim_manager` | NEW |
| `cRAnimManager::AI` | 0x4447d0 | `sub_4447d0` | `update_anim_manager` | NEW — bounce formula, mode flags loop/bounce/clamp |
| `cRBall::AI` | 0x407b50 | `sub_407b50` | — | Empty stub |

---

## cGlowManager

All 4 methods (`Init`, `AI`, `UnInit`, `GetGlow`) are **ABSENT** — mobile-only (used by cKeyPad touch input glow).

---

## Statistics (Sweep 3)

- **Total Android symbols examined**: ~140
- **New identifications** (currently `sub_XXXX`): **~75**
- **Already named in Windows**: ~30
- **Inlined / absent / empty stubs**: ~35
- **Grand total across all 3 sweeps**: **~185 new function identifications**
