# Android → Windows Symbol Matches (Sweep 2)

Second cross-reference pass covering subsystems not covered in the first sweep: rendering/backdrop, core game lifecycle, level loading, audio, UI widgets, path builders, projectiles, and gameplay entities.

**Legend**: `NEW` = currently unnamed (`sub_XXXX`) in BN, `EXISTS` = already named, `INLINED` = no standalone Windows function, `ABSENT` = stripped from Windows build

---

## cRGame (Core Game Lifecycle)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `cRGame::Init0–Init5` | 0x40acf0 | `initialize_game_assets_and_world` | — | EXISTS (all 6 phases inlined into one function) |
| `cRGame::InitLast` | 0x410720 | `sub_410720` | `initialize_game_last` | NEW — calls initialize_backdrop |
| `cRGame::AI` | 0x40a2a0 | `run_frame_update` | — | EXISTS |
| `cRGame::Render` | 0x40a490 | `sub_40a490` | `render_game_frame` | NEW — "Loose Sprite scene viewport", "DEBUG RENDER" strings |
| `cRGame::LoadPaths` | 0x40acf0 | `initialize_game_assets_and_world` | — | INLINED into Init |
| `cRGame::UnInit` | — | — | — | Empty stub |
| `cRGame::LevelInit` | — | — | — | Empty stub |

---

## cRSubTracks (Level/Segment Loading)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init(char*)` | 0x447480 | `sub_447480` | `load_level_definition_file` | NEW — "Levels/%s", "Mode:Arcade"/"Mode:Challenge"/"Mode:Tutourial" parsing |
| `Load(int,int)` | 0x443650 | `sub_443650` | `load_frontend_level_by_mode_and_index` | NEW — "Arcade%03i.txt", "Challenge000.txt", "Tutorial.txt" format switch |
| `ImportSegment` | 0x447300 | `sub_447300` | `copy_segment_definition_to_level_slot` | NEW — "Cannot find segment %s for %s", 8-column tile copy |
| `Export` | — | — | — | ABSENT — editor function stripped |

---

## cRTime (Timer)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Add(float)` | 0x441b90 | `advance_timer_counters` | — | EXISTS |
| `Zero` | 0x441b70 | `sub_441b70` | `zero_timer_counters` | NEW — memset(0, 24 bytes) |
| `AddFraction` | — | — | — | INLINED |
| `Faster` | — | — | — | INLINED |

---

## cRTutorial

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init` | 0x448da0 | `sub_448da0` | `initialize_tutorial` | NEW — flags |= 0x600000, clears bit 1 |
| `AI` | 0x448de0 | `sub_448de0` | `update_tutorial` | NEW — get_track_grid_cell_at_world_position tailcall |
| `UnInit` | 0x448dd0 | `sub_448dd0` | `uninit_tutorial` | NEW — tailcalls UnInitTips |
| `Ressurect` | — | — | — | Empty stub |

---

## cRSubPause

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init` | 0x440660 | `sub_440660` | `initialize_pause_menu` | NEW — "End Game", "Options", "Resume" borders |
| `AI` | 0x4407a0 | `sub_4407a0` | `update_pause_menu` | NEW — 3-button press check, state 6/8 dispatch |
| `UnInit` | 0x440600 | `sub_440600` | `uninit_pause_menu` | NEW — kills 3 borders |

---

## cRExit / cRQuit / cRSure

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `cRExit::Init` | 0x4060d0 | `initialize_exit_prompt` | — | EXISTS — "Do you really want to quit?" |
| `cRExit::AI` | 0x4067e0 | `update_completion_screen` | — | EXISTS (shared with completion) |
| `cRExit::UnInit` | 0x406060 | `destroy_completion_screen` | — | EXISTS (shared) |
| `cRQuit::*` | — | — | — | INLINED into initialize_subgame / update_subgame |
| `cRSure::*` | — | — | — | ABSENT — confirmation dialog not in Windows |

---

## cRTimesUp / cRTimeTrial

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `cRTimesUp::Init` | 0x445e90 | `sub_445e90` | `show_times_up_message` | NEW — "Time's Up" border |
| `cRTimesUp::AI` | 0x445e20 | `sub_445e20` | `update_times_up` | NEW — 2-state, calls Kill on timeout |
| `cRTimesUp::UnInit` | 0x445e70 | `sub_445e70` | `uninit_times_up` | NEW — kills border widget |
| `cRTimeTrial::TimeString` | 0x448960 | `sub_448960` | `format_time_trial_string` | NEW — "%1i:%02i:%03i" / "-:--:--" formatting |
| `cRTimeTrial::Init` | — | — | — | INLINED (trivial memcpy) |

---

## cRBackdrop

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `AI` | 0x4112f0 | `update_backdrop` | — | EXISTS |
| `Init(int)` | 0x410e20 | `initialize_backdrop` | — | EXISTS |
| `Change` | 0x410d50 | `change_backdrop` | — | EXISTS |
| `ChangeReal` | 0x410dc0 | `change_backdrop_real` | — | EXISTS |
| `SetDistort(float)` | 0x410c40 | `set_backdrop_distort` | — | EXISTS |
| `Render` | 0x411040 | `render_backdrop` | — | EXISTS |
| `SetWorld(int)` | 0x410f40 | `set_backdrop_texture_target` | — | EXISTS |
| `Open`, `SetZoom`, `UnInit` | — | — | — | INLINED or optimized away |

---

## cRDistort

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init` | 0x410710 | `sub_410710` | `initialize_distort` | NEW — zeros 3 distort vector fields |
| `Build(cRObject*)` | 0x41aa50 | `sub_41aa50` | `apply_distort_to_object` | NEW — sin-based y displacement, 3-channel distort via pi/2 |
| `BuildMatrix` | — | — | — | INLINED into rendering pipeline |

---

## cRLandscapeManager

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init(int)` | 0x418870 | `activate_landscape_entry` | — | EXISTS |
| `Open` | 0x4182e0 | `sub_4182e0` | `reset_landscape_manager` | NEW — resets count to 0 |
| `Import(char*)` | 0x4182f0 | `load_landscape_script_by_name` | — | EXISTS |
| `UnInit` | — | — | — | Empty stub |

---

## cRLoadingBar

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init` | 0x418b50 | `initialize_loading_screen` | — | EXISTS |
| `UnInit` | 0x418e50 | `destroy_loading_screen` | — | EXISTS |
| `Signal` | 0x418e80 | `update_loading_screen` | — | EXISTS |
| `AI`, `Finish`, `ScriptAI`, `TgaRender` | — | — | — | INLINED into init/signal |

---

## cRFade (Frontend Transition)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `AI` | 0x40abf0 | `update_frontend_transition_overlay` | — | EXISTS |
| `Start(callback)` | 0x40abc0 | `begin_frontend_fade_out` | — | EXISTS |
| `StartOn` | 0x40abe0 | `begin_frontend_fade_in` | — | EXISTS |
| `Init`, `FadeIn` | — | — | — | INLINED |

---

## cRFlash (Color Flash Overlay)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init(int)` | 0x40ab00 | `initialize_frontend_overlay_color_lerp` | — | EXISTS |
| `AI` | 0x40ab40 | `draw_frontend_overlay_color_lerp` | — | EXISTS |
| `Off`, `Flash` | — | — | — | INLINED |

---

## cRPath Build Methods

These Android `cRPath::Build*` methods map to the already-named Windows `initialize_*_path_template_pair` functions. New matches found:

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `BuildSBend` | 0x42df00 | `sub_42df00` | `initialize_sbend_path_template_pair` | NEW — Cos height profile, 0x3efae148 rail offset |
| `BuildScrew` | 0x41eda0 | `sub_41eda0` | `initialize_screw_path_template_pair` | NEW — type 0x19, Cos/Sin spiral body |
| `BuildSlalom` | 0x41f760 | `initialize_slalom_path_template_pair` | — | EXISTS — Sin×5.0 displacement, RotLocalZ twist |
| `BuildSlalomBig` | 0x4221f0 | `initialize_slalombig_path_template_pair` | — | EXISTS — Sin×4.44444466 displacement, sample_count=`arg2+8` |
| `BuildWorm` | 0x420170 | `initialize_worm_path_template_pair` | — | EXISTS — 24 fixed nodes, width=96.0, 16-subdivision body |
| `BuildHalfPipe` | 0x41d030 | `sub_41d030` | `initialize_halfpipe_path_template_pair` | NEW — 7+body+7 nodes, Cos radius |
| `BuildHalfPole` | 0x41da30 | `sub_41da30` | `initialize_halfpole_path_template_pair` | NEW — negated HalfPipe variant |
| `BuildDip` | 0x425050 | `sub_425050` | `initialize_dip_path_template_pair` | NEW — 70 nodes, (1-Cos) height |
| `BuildDetour` | 0x42e720 | `sub_42e720` | `initialize_detour_path_template_pair` | NEW — 22 nodes, Sin×-0.3 y-offset |
| `CalcLengthZ` | 0x4217b0 | `sub_4217b0` | `calc_path_length_z` | NEW — node distance accumulation, Dot camber |
| `GetNodes` | 0x41b0a0 | `sub_41b0a0` | `allocate_path_template_samples` | NEW — allocates paired `0xa8`-stride sample arrays, "Path Tile Nodes" / "Path Ball nodes" |

---

## Gameplay Entities

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `cRSubHealth::AI` | 0x43ecc0 | `sub_43ecc0` | `update_track_health_pickup` | NEW — Sin bobble, z-threshold kill |
| `cRSubSpeedUp::AI` | 0x43ee50 | `sub_43ee50` | `update_track_jetpack_pickup` | NEW — same pattern, wider struct offsets |
| `cRSubLazer::AI` | 0x43e830 | `sub_43e830` | `update_subgoldy_bullet` | NEW — position advance, path collision flags |
| `cRGolbLazer::AI` | 0x43d880 | `sub_43d880` | — | Empty stub (both platforms) |
| `cRGolbRocket::AI` | 0x43d880 | `sub_43d880` | — | Empty stub (both platforms) |
| `cRParcel::AI` | 0x4431d0 | `update_track_parcel` | — | EXISTS — 7-state machine, homing to mailbox, RegisterParcel on arrival |
| `cRSubRingStar::AI` | 0x43e830 | `sub_43e830` | `update_ring_star_system` | NEW — orbital angle, 10-star array |
| `cRSubRingStar::Shower` | 0x43e690 | `sub_43e690` | `emit_ring_star_shower` | NEW — pi/3 angular, velocity×0.3 radial |
| `cRWall::AI` | 0x43efb0 | `sub_43efb0` | `update_wall2_ambient_hazard` | NEW — phase advance, SubLazer shoot at -0.1 |
| `cRSubLoc::IsFloor` | — | — | — | INLINED (tile type lookup table) |
| `cRSubLoc::IsSlide` | — | — | — | INLINED |
| `cRSubLoc::IsEmpty` | — | — | — | INLINED |
| `cRSubLoc::IsRamp` | — | — | — | INLINED |

---

## Hypotheses

- **cRGame Init phases**: Windows collapses all 6 Android init phases (Init0–Init5) plus LoadPaths into the single `initialize_game_assets_and_world` function. The original class decomposition is lost in the Windows build.
- **cRSubTracks**: `load_frontend_level_by_mode_and_index` at 0x443650 is the central level-loading dispatcher. It uses format strings like "Arcade%03i.txt" to locate level definitions, confirming the level naming convention. The typo "Tutourial" in the mode parser is present in both platforms.
- **cRSure (confirmation dialog)**: Entirely absent from Windows. The "Are you sure?" dialog before starting a new adventure only exists on Android/iOS.
- **cRQuit (in-game menu button)**: Not a standalone class on Windows — the quit button sprite (0x7a) is initialized inline in `initialize_subgame` and handled inline in `update_subgame`.
- **cRParcel::AI**: The 7-state parcel flight machine confirms the parcel delivery path described in the binary comparison report — parcels are physics-driven flight objects that home to the mailbox, not instant row-event pickups. The earlier `0x43f520` guess is rejected; that function is only a tiny phase helper under `update_slug_hazard_ai`.
- **cRWall::AI**: Confirms the Wall2 ambient hazard fires a -0.1 velocity laser downward through the SubLazer manager, matching the `+0.02` damage path identified in the first report.
- **Path builders**: The `BuildSBend`, `BuildScrew`, `BuildSlalom`, `BuildShimmy`, `BuildHalfPipe`, `BuildHalfPole`, `BuildDip`, and `BuildDetour` functions are all confirmed as separate path template initializers, extending the already-identified set. `CalcLengthZ` and `GetNodes` (`allocate_path_template_samples`) are shared infrastructure used by all builders.

---

## cRSound

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init` | 0x44dcb0 | `sub_44dcb0` | `initialize_sound_bank` | NEW — loops bank entries calling RShellSoundRegister |
| `Play(int)` | — | — | — | INLINED — callers pass resolved handle to `play_sound_effect` (0x44dde0) |
| `Play(int,float)` | — | — | — | INLINED |
| `PlayVolume(int,float)` | — | — | — | INLINED |
| `StopLooped(int)` | — | — | — | INLINED |

---

## cRVoiceManager

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init` | 0x448ee0 | `sub_448ee0` | `initialize_voice_manager` | NEW — "Voice/_Voice.txt", 16 voice set names (Damage, Dying, Enemies, etc.) |
| `AI` | 0x4492a0 | `sub_4492a0` | `update_voice_manager` | NEW — iterates 16 sets, adds 1/60 to timer |
| `Play(int,int,int)` | 0x4492d0 | `sub_4492d0` | `play_voice_manager` | NEW — mode 0/1/2, frequency check, timer reset |
| `ReSet` | 0x448ec0 | `sub_448ec0` | `reset_voice_manager` | NEW — zeros timer, clears 16 entries |
| `IsPlaying` | 0x449410 | `sub_449410` | `is_voice_playing` | NEW — iterates sets, BASS channel check |
| `FindSample` | — | — | — | ABSENT — Windows VoiceBites store handles only, no names |

---

## cRVoiceSet

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init(int)` | 0x448df0 | `sub_448df0` | `initialize_voice_set` | NEW — allocates "Playlist"/"VoiceBite" arrays, sequential init, tail-calls Shuffle |
| `AI` | 0x449360 | `sub_449360` | `update_voice_set` | NEW — timer advance, reset at 1.0 |
| `Play(int)` | 0x449390 | `sub_449390` | `play_voice_set` | NEW — timer check, playlist advance, wrapping |
| `Shuffle` | 0x448e60 | `sub_448e60` | `shuffle_voice_set` | NEW — 100 random swaps (Fisher-Yates) |

---

## cRSlugVoiceManager

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init` | 0x43f5c0 | `sub_43f5c0` | `initialize_slug_voice_manager` | NEW — timer=0, rate=1/60 |
| `AI` | 0x43f5e0 | `sub_43f5e0` | `update_slug_voice_manager` | NEW — cooldown advance, reset at 1.0 |

---

## cRBorder (UI Widget)

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `Init(sprite)` | 0x401a70 | `initialize_frontend_sprite_button` | — | EXISTS |
| `Init(text)` | 0x401d30 | `initialize_frontend_widget` | — | EXISTS |
| `AI` | 0x402820 | `update_frontend_widget_interaction` | — | EXISTS |
| `Draw` | 0x401130 | `draw_frontend_widget` | — | EXISTS |
| `RePosition` | 0x4024a0 | `layout_frontend_widget` | — | EXISTS |
| `MouseTest` | 0x404580 | `sub_404580` | `border_mouse_test` | NEW — sprite alpha check, bounds test vs mouse |
| `Highlight` | 0x402800 | `sub_402800` | `highlight_border` | NEW — sets +0x20c=1.0, copies color |
| `UnHighlight` | 0x4027e0 | `sub_4027e0` | `unhighlight_border` | NEW — sets +0x20c=0 |
| `HideInit` | 0x4010e0 | `sub_4010e0` | `hide_border_init` | NEW — sets 0x10 flag, tooltip reset |
| `UnHideInit` | 0x401110 | `sub_401110` | `unhide_border_init` | NEW — sets +0x44=1.0, clears 0x10 flag |
| `InputTextInit` | 0x403410 | `sub_403410` | `border_input_text_init` | NEW — cursor '|', max length, cRInputOK::Init |
| `InputText` | 0x4035b0 | `sub_4035b0` | `border_input_text` | NEW — key handling, cursor blink, capitalization |
| `AddTextNumber` | 0x401030 | `sub_401030` | `border_add_text_number` | NEW — comma formatting, digit-by-digit |
| `SpriteExtend` | 0x404540 | `sub_404540` | `border_sprite_extend` | NEW — multi-frame sprite setup |
| `Scale` | — | — | — | INLINED |
| `HideAI` | — | — | — | Empty stub |

---

## cRBorderManager

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `GetBorder` | 0x4032a0 | `sub_4032a0` | `allocate_border` | NEW — scans 0x96 entries, "Run out of Borders" error |
| `Kill` | 0x403360 | `sub_403360` | `kill_border` | NEW — recursive child cleanup, flag reset |
| `AI` | 0x403fc0 | `sub_403fc0` | `update_border_manager` | NEW — timer advance, delayed flag apply |
| `HideBorders` | 0x4033f0 | `sub_4033f0` | `hide_all_borders` | NEW — BorderStack::Perform(0) |
| `UnHideBorders` | 0x403400 | `sub_403400` | `unhide_all_borders` | NEW — BorderStack::Perform(1) |
| `ActivateBorders` | 0x403300 | `sub_403300` | `activate_all_borders` | NEW — clears flags, resets animations |
| `KillBorders` | 0x4033c0 | `sub_4033c0` | `kill_all_borders` | NEW — mass kill active borders |
| `SetJustifyCentre` | 0x404730 | `sub_404730` | `set_border_justify_centre` | NEW — single field store |
| `DeActivateBorders` | — | — | — | Dead code |
| `CentreRow` | — | — | — | Not found / possibly inlined |

---

## Statistics (Sweep 2)

- **Total Android symbols examined**: ~130
- **New identifications** (currently `sub_XXXX`): **~65**
- **Already named in Windows**: ~30
- **Inlined / absent / empty stubs**: ~25
- **Combined with Sweep 1**: ~120 total new identifications across both sweeps
