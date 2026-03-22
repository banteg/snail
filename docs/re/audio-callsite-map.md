# Audio callsite map

This page turns the native audio xref inventory into a gameplay-system map. The raw address-complete source material lives in [../../analysis/runtime/native-audio-callsites.md](../../analysis/runtime/native-audio-callsites.md).

The point of this map is not “audio parity” in isolation. These callsites show where the Windows build still owns gameplay systems that the Zig port has either approximated, collapsed together, or routed through different subsystems.

## `play_sound_effect`

### Frontend and UI

| Audio | Native caller | Current interpretation | Current port equivalent | Gap |
| --- | --- | --- | --- | --- |
| `sfx 9` | [`update_frontend_widget_interaction`](../../artifacts/ida/functions/00402820-update_frontend_widget_interaction.c) at `0x402c25` | widget hover or focus-entry cue | frontend widget hover handling | low priority; keep for completeness |
| `sfx 8` | [`update_frontend_widget_interaction`](../../artifacts/ida/functions/00402820-update_frontend_widget_interaction.c) at `0x402c90` | widget activate or confirm cue, branch A | frontend widget activation | low priority; keep for completeness |
| `sfx 8` | [`update_frontend_widget_interaction`](../../artifacts/ida/functions/00402820-update_frontend_widget_interaction.c) at `0x402cf2` | widget activate or confirm cue, branch B | frontend widget activation | low priority; keep for completeness |
| `sfx 8` | [`update_galaxy`](../../artifacts/ida/functions/004092f0-update_galaxy.c) at `0x409ae4` | galaxy route confirmation | galaxy route UI | low priority; not a gameplay-system gap |
| `sfx 8` | [`update_options`](../../artifacts/ida/functions/0041af60-update_options.c) at `0x41b05c` | options sound-volume change cue | options UI | low priority; not a gameplay-system gap |
| `sfx 8` | [`update_thanks_for_playing_screen`](../../artifacts/ida/functions/004340f0-update_thanks_for_playing_screen.c) at `0x434129` | thanks-screen continue cue | thanks-screen continue flow | low priority; not a gameplay-system gap |
| `sfx 8` | [`update_click_start`](../../artifacts/ida/functions/00442290-update_click_start.c) at `0x4423ed` | tutorial click-start handoff cue after pointer recenter | tutorial click-start flow in `main.zig` | the click-start flow is ported, but this exact native cue and its ownership are still secondary |

### Row events and parcels

| Audio | Native caller | Current interpretation | Current port equivalent | Gap |
| --- | --- | --- | --- | --- |
| `sfx 49` | [`update_row_event_display`](../../artifacts/ida/functions/00404cf0-update_row_event_display.c) at `0x404e6f` | row-event state-`3` final-bonus payout cue | `RowEventDisplayController` | partial; the audible edge is ported from `completion_bonus`, but the row-event owner is still approximate |
| `sfx 8` | [`update_row_event_display`](../../artifacts/ida/functions/00404cf0-update_row_event_display.c) at `0x404ed2` | row-event accept or continue cue | `RowEventDisplayController` UI staging | partial; the port now arms the recovered confirm gate from gameplay confirm input and plays `SELECT.OGG`, but the wider row-event owner is still approximate |
| `sfx 45` | [`register_parcel_delivery`](../../artifacts/ida/functions/00405040-register_parcel_delivery.c) at `0x405070` | per-delivery mailbox payout cue | parcel home-flight and delivery runtime | ported; the app now keys this from registered-delivery count growth |
| `sfx 49` | [`register_parcel_delivery`](../../artifacts/ida/functions/00405040-register_parcel_delivery.c) at `0x4050a4` | final-delivery bonus cue | parcel target completion logic | ported more literally; the app now keys this from the final delivery-registration edge instead of a generic completion-bonus score delta |
| `sfx 27` | [`handle_subgoldy_collisions`](../../artifacts/ida/functions/00444cf0-handle_subgoldy_collisions.c) at `0x4452fb` | parcel pickup cue before the parcel enters its flight states | live parcel runtime pickup branch | ported; the app now keys this from parcel-count growth |

### Movement-state and runner surface audio

| Audio | Native caller | Current interpretation | Current port equivalent | Gap |
| --- | --- | --- | --- | --- |
| `sfx 17..24` | [`play_movement_state_sound`](../../artifacts/ida/functions/0043afd0-play_movement_state_sound.c) at `0x43b114` | dedicated movement-state family chosen from `movement_flags`, with distance attenuation during attachment exit | player-fire families now use native random family selection, the recovered selector-to-family ladder, selector-owned fire cooldown steps, the startup cooldown reseed window from `update_subgoldy`, explicit live press-vs-held input lanes, the runtime fire feature flag, replay raw-bit fire gating, native attachment-exit suppression/gain, and the recovered turbo-spread plus laser/rocket speed ratios from `create_golb` | partial; the remaining gap is the deeper emitter owner and literal input-device source, not the family choice, live/replay gates, cadence, startup hold, or the recovered shot-family shapes |
| `sfx 41` | [`update_subgoldy`](../../artifacts/ida/functions/0043b120-update_subgoldy.c) at `0x43c3f8` | trampoline landing cue on runtime tile `22` | runner trampoline handling in `gameplay.zig` | partial; the port can now play `BOING`, but it still lacks the native bounce controller |
| `sfx 47` | [`update_subgoldy`](../../artifacts/ida/functions/0043b120-update_subgoldy.c) at `0x43c4c1` | first-entry cue for runtime tile `14` (`'|'`) before the native hold-and-drop timer runs | runner wall or barrier contact in `gameplay.zig` | partial; the port now plays the one-shot entry cue, but still lacks the native hold-and-drop controller |

### Score, completion arm, and milestone cues

| Audio | Native caller | Current interpretation | Current port equivalent | Gap |
| --- | --- | --- | --- | --- |
| `sfx 44` | [`add_subgoldy_score`](../../artifacts/ida/functions/004402c0-add_subgoldy_score.c) at `0x440374` | extra-life cue when score crosses a `50_000` bucket | score and postal-life logic in `gameplay.zig` | ported; the app keys `EXTRALIFE` from the same visible-life gain edge |
| `sfx 0` | [`update_subgoldy`](../../artifacts/ida/functions/0043b120-update_subgoldy.c) at `0x43c79d` | first completion-handoff arm cue before the later voice and `complete_subgame` path | completion-screen init and finalize split | ported; the app keys the recovered `CHEERS.OGG` cue from the completion-handoff arm edge |
| `sfx 46` | [`update_cutscene`](../../artifacts/ida/functions/004466d0-update_cutscene.c) at `0x446c0a` | completion cutscene state `6` initializes the completion screen and plays `SFX2/SKIDSTOP.OGG` | early completion-screen handoff | ported; the app now plays the recovered `SKIDSTOP` cue on the early completion-screen handoff |

### Collisions, pickups, and powerups

| Audio | Native caller | Current interpretation | Current port equivalent | Gap |
| --- | --- | --- | --- | --- |
| `sfx 39/40` | [`handle_subgoldy_collisions`](../../artifacts/ida/functions/00444cf0-handle_subgoldy_collisions.c) at `0x44500a` | garbage collision impact family after score add and `+0.04` damage | garbage-hit handling and asteroid-impact pair in `playGameplayRunnerAudio()` | partial; audible result is close, native owner and exact family still deserve documentation |
| `sfx 14` | [`handle_subgoldy_collisions`](../../artifacts/ida/functions/00444cf0-handle_subgoldy_collisions.c) at `0x44542f` | health pickup cue | live health-pickup runtime slots with the recovered `world_y >= 0.49`, `delta_z < 1.0`, `abs(delta_y) < 0.4`, and normalized-distance `< 0.98` gates, dispatched as the shipped `heart` sound plus an 8-smoke pickup burst on the gameplay-effect side | partial; runtime-slot ownership, collision gates, and the smoke-sprite aftermath are now ported, but the original sprite-bod owner and exact motion source are still approximated |
| `sfx 43` | [`handle_subgoldy_collisions`](../../artifacts/ida/functions/00444cf0-handle_subgoldy_collisions.c) at `0x4456f2` | ring types `3/7` negative-velocity cue | live runtime ring-slot collision handling keyed from the exact native ring-kind `3/7` token, dispatched as the shipped slow-ring cue | partial; the slot owner and collision gate are now ported, but the exact negative-velocity motion lane is still owned by the runner |
| `sfx 1..7` | [`handle_subgoldy_collisions`](../../artifacts/ida/functions/00444cf0-handle_subgoldy_collisions.c) at `0x445763` | tiered weapon-upgrade pickup family after ring types `4/5` and `8`, indexed by the post-increment movement selector | live runtime ring-slot collision handling plus the shipped `PW1..PW7` pickup ladder keyed from the exact native ring-kind token and `movement_flag_selector` | partial; the ring-slot owner and pickup ladder are now ported, but the deeper movement-flag presentation owner is still flatter in Zig |
| `sfx 1` | [`handle_subgoldy_collisions`](../../artifacts/ida/functions/00444cf0-handle_subgoldy_collisions.c) at `0x44578d` | ring type `1` pickup cue | live runtime ring-slot collision handling keyed from the exact native ring-kind `1` token | ported; the app now keys `PW1` from the recovered ring-kind `1` path instead of generic pickup progression |
| `sfx 42` | [`handle_subgoldy_collisions`](../../artifacts/ida/functions/00444cf0-handle_subgoldy_collisions.c) at `0x44580d` | explode-ring pickup, immediately before `initialize_nuke` | live runtime ring-slot collision handling keyed from the exact native ring-kind `2/6` token plus existing explode-ring gameplay/runtime | partial; the pickup cue is now keyed from the native ring-kind path and live ring-slot owner, but the underlying `initialize_nuke` owner is still not a literal port |

### Jetpack, weapon, and warning presentation controllers

| Audio | Native caller | Current interpretation | Current port equivalent | Gap |
| --- | --- | --- | --- | --- |
| `sfx 26` | [`set_snail_jetpack`](../../artifacts/ida/functions/00445860-set_snail_jetpack.c) at `0x4458b4` | jetpack visual-state shutdown cue, mapped by the recovered sound bank to `SFX2/SERVO2.OGG` | jetpack timer / warning controller | partial; the port now keys the exact shutoff asset from the native warning-threshold and early-disarm edges |
| `sfx 16` | [`set_snail_jetpack`](../../artifacts/ida/functions/00445860-set_snail_jetpack.c) at `0x4458ec` | jetpack visual-state activation cue, mapped by the recovered sound bank to `SFX2/JETPACK.OGG` | jetpack timer / warning controller | partial; the port now keys the exact activation asset from the real jetpack arm edge instead of the pickup counter |
| `sfx 25` | [`set_snail_weapon`](../../artifacts/ida/functions/00445920-set_snail_weapon.c) at `0x445b62` | shared weapon visual-state change cue, branch A, mapped by the recovered sound bank to `SFX2/SERVO1.OGG` | `weapon_change` cue in `playGameplayRunnerAudio()` | partial; the asset is now correct and the cue now follows powerup progression as well as coarse weapon-tier changes, but the native movement-flag owner is still flatter in Zig |
| `sfx 25` | [`set_snail_weapon`](../../artifacts/ida/functions/00445920-set_snail_weapon.c) at `0x445b9f` | shared weapon visual-state change cue, branch B, mapped by the recovered sound bank to `SFX2/SERVO1.OGG` | `weapon_change` cue in `playGameplayRunnerAudio()` | partial; the asset is now correct and the cue now follows powerup progression as well as coarse weapon-tier changes, but the native movement-flag owner is still flatter in Zig |
| `sfx 25` | [`set_snail_weapon`](../../artifacts/ida/functions/00445920-set_snail_weapon.c) at `0x445bca` | shared weapon visual-state change cue, branch C, mapped by the recovered sound bank to `SFX2/SERVO1.OGG` | `weapon_change` cue in `playGameplayRunnerAudio()` | partial; the asset is now correct and the cue now follows powerup progression as well as coarse weapon-tier changes, but the native movement-flag owner is still flatter in Zig |
| `sfx 25` | [`set_snail_weapon`](../../artifacts/ida/functions/00445920-set_snail_weapon.c) at `0x445be2` | shared weapon visual-state change cue, branch D, mapped by the recovered sound bank to `SFX2/SERVO1.OGG` | `weapon_change` cue in `playGameplayRunnerAudio()` | partial; the asset is now correct and the cue now follows powerup progression as well as coarse weapon-tier changes, but the native movement-flag owner is still flatter in Zig |
| `sfx 50` | [`update_warning`](../../artifacts/ida/functions/00446f80-update_warning.c) at `0x447000` | warning overlay loop cue as the warning controller cycles `state 2 -> 1` | once-per-second warning loop in `playGameplayRunnerAudio()` | partial; current port reproduces the broad behavior, but not the original owner/controller object |

## `play_voice_manager`

### Row events, tutorial speech, and completion handoff

| Audio | Native caller | Current interpretation | Current port equivalent | Gap |
| --- | --- | --- | --- | --- |
| `voice 13` `mode 2` | [`update_subgoldy`](../../artifacts/ida/functions/0043b120-update_subgoldy.c) at `0x43b84d` | row-event or tutorial voice payload dispatch from the live runtime row | runner-owned logical row-message token, prompt queue, and native-style payload playback for authored `Sample:` rows | partial; row-message dispatch now keys from the runner instead of frontend segment-sync, but the original payload tables and tip actor/controller are still not ported literally |
| `voice 8` `mode 2` | [`update_subgoldy`](../../artifacts/ida/functions/0043b120-update_subgoldy.c) at `0x43c874` | delayed completion-handoff voice after roughly `2.0s` | split completion handoff in `gameplay.zig` | ported; the app now keys `Victory` from the recovered `2.0s` handoff timer instead of the older `2.5s` approximation |

### Attachment-follow and post-follow voices

| Audio | Native caller | Current interpretation | Current port equivalent | Gap |
| --- | --- | --- | --- | --- |
| `voice 12` `mode 0` | [`update_subgoldy`](../../artifacts/ida/functions/0043b120-update_subgoldy.c) at `0x43b8b7` | WORM entry voice when attachment follow begins on kind `24` | attachment begin in `gameplay.zig` | ported; the app now routes the recovered kind-`24` entry edge through the native `WormTunnel` set |
| `voice 4` `mode 1` | [`update_track_attachment_follow_state`](../../artifacts/ida/functions/00420cb0-update_track_attachment_follow_state.c) at `0x420d30` | milestone voice at `2 * sample_count` | attachment follow update in `gameplay.zig` | missing; suggests the follow state still has unrecovered milestone semantics |
| `voice 15` `mode 0` | [`update_track_attachment_follow_state`](../../artifacts/ida/functions/00420cb0-update_track_attachment_follow_state.c) at `0x421046` | kind-`31` tail-launch completion voice | attachment follow completion / launch | partial; the app now keys `Supertramp` from the positive-velocity launch handoff, but the broader follow milestone controller is still incomplete |
| `voice 3` `mode 0` | [`update_subgoldy`](../../artifacts/ida/functions/0043b120-update_subgoldy.c) at `0x43cebd` | attachment-exit gate A once `progress > 0.7` | attachment exit gates in `gameplay.zig` | ported; the app now routes this gate through the native `Fall` set |
| `voice 1` `mode 2` | [`update_subgoldy`](../../artifacts/ida/functions/0043b120-update_subgoldy.c) at `0x43cf19` | attachment-exit gate B once `world_y < -7.0` | attachment exit gates in `gameplay.zig` | ported; the app now routes this gate through the native `Dying` set |

### Damage and warning controller

| Audio | Native caller | Current interpretation | Current port equivalent | Gap |
| --- | --- | --- | --- | --- |
| `voice 14` `mode 0` | [`update_damage_gauge`](../../artifacts/ida/functions/00440fd0-update_damage_gauge.c) at `0x44115e` | damage-warning escalation voice after the fill state commits | `damage_gauge` plus warning loop | ported; the app now keys this from the runner's warning-state escalation edge |
| `voice 0` `mode 1` | [`apply_damage_gauge_delta`](../../artifacts/ida/functions/004413f0-apply_damage_gauge_delta.c) at `0x44148e` | first positive-damage entry voice | damage collision handling | ported; the app now tries the native `Damage` set on the first positive entry from zero |
| `voice 9` `mode 0` | [`apply_damage_gauge_delta`](../../artifacts/ida/functions/004413f0-apply_damage_gauge_delta.c) at `0x4414a2` | fallback voice if `voice 0` is blocked by the manager | damage collision handling | ported; the app now falls back to the native `Ouch` set when the first request is rejected |

### Collision, pickups, and hazards

| Audio | Native caller | Current interpretation | Current port equivalent | Gap |
| --- | --- | --- | --- | --- |
| `voice 10` `mode 1` | [`handle_subgoldy_collisions`](../../artifacts/ida/functions/00444cf0-handle_subgoldy_collisions.c) at `0x4452ef` | parcel pickup voice before the parcel begins its home-flight states | parcel pickup runtime | ported; the app now routes this through the native `Package` voice set and manager gate |
| `voice 5` `mode 1` | [`handle_subgoldy_collisions`](../../artifacts/ida/functions/00444cf0-handle_subgoldy_collisions.c) at `0x4457d4` | weapon-upgrade voice when ring kinds `4/5` land, the local weapon tier actually increases, the runtime `0x10` flag is set, and mode is not time trial | live runtime ring-slot collision handling plus the recovered ring-kind `4/5` path and runtime-mode gate | partial; the slot owner and gate are now ported, but the deeper movement/presentation owner is still flatter in Zig |
| `voice 2` `mode 1` | [`update_slug_hazard_ai`](../../artifacts/ida/functions/0043f930-update_slug_hazard_ai.c) at `0x43fbd5` | slug engagement voice when the player enters the local alert window | ambient slug voice cooldowns in `main.zig` | partial; current port has nearby slug barks, but the native owner and gate are different enough to matter |

### Death and cutscene voices

| Audio | Native caller | Current interpretation | Current port equivalent | Gap |
| --- | --- | --- | --- | --- |
| `voice 7` `mode 2` | [`update_subgoldy`](../../artifacts/ida/functions/0043b120-update_subgoldy.c) at `0x43cf69` | startup bark from the timer seeded in `initialize_subgoldy` | runner startup handoff in `gameplay.zig` and `main.zig` | ported; the app now fires the native `Start` set on the recovered timer edge |
| `voice 6` `mode 1` | [`update_subgoldy`](../../artifacts/ida/functions/0043b120-update_subgoldy.c) at `0x43cff3` | low-speed commentary from a dedicated slowdown timer | runner slowdown controller in `main.zig` and `gameplay.zig` | partial; the port now uses the recovered `1/60` timer and narrow forward-speed band, but it still infers the live forward-motion lane from row delta instead of a literal native field |
| `voice 3` `mode 2` | [`update_cutscene`](../../artifacts/ida/functions/004466d0-update_cutscene.c) at `0x44697c` | death cutscene entry voice | cutscene handoff and death camera | partial; the app now keys the native `Fall` set from the first live death-cutscene `state == 11` tick |
| `voice 11` `mode 2` | [`update_cutscene`](../../artifacts/ida/functions/004466d0-update_cutscene.c) at `0x446b25` | death cutscene fallback voice if `initialize_subgoldy_death` did not already consume the gate | cutscene handoff and death camera | partial; the app now routes the native `Slugged` fallback from the first `state == 12` tick while the gate-B lane is still clear |

## System recovery targets

1. Recover the rest of `update_subgoldy` audio ownership.
   Audio evidence: `sfx 0`, `sfx 41`, `sfx 47`, `voice 1`, `voice 3`, `voice 6`, `voice 7`, `voice 8`, `voice 12`, `voice 13`.
   Native implication: one runner-owned function still controls trampoline and barrier tile feedback, row-event speech, WORM entry, startup bark timing, attachment-exit one-shots, completion-handoff voice timing, and a separate slowdown commentary timer.
   Current Zig suspicion: several of these cues are now ported, including startup bark timing, completion arm, attachment-exit voices, the narrow-band slowdown timer, and runner-owned row-message dispatch, but the original payload-table/tip-controller path is still not literal.
   Next trace boundary: `update_subgoldy`, plus nearby `enqueue_tip_message`, `initialize_subgoldy_death`, `update_subgoldy_resurrect`, and `flush_row_event_display`.
   Likely Zig subsystem: [`zig/src/gameplay.zig`](../../zig/src/gameplay.zig) and [`zig/src/main.zig`](../../zig/src/main.zig).

2. Reconstruct parcel and row-event audio as one system instead of separate pickup/UI guesses.
   Audio evidence: `sfx 27`, `sfx 45`, `sfx 49`, `voice 10`, `voice 13`.
   Native implication: parcel pickup, mailbox delivery, final bonus payout, and tutorial or row-event speech are all facets of one runtime-owned controller family.
   Current Zig suspicion: pickup and delivery cues are now mostly covered, and tutorial `TUT*` samples now key from a runner-owned row-message token with the native `Tutorial` set semantics, but the broader payload-table and tip-controller ownership still is not literal.
   Next trace boundary: `handle_subgoldy_collisions`, `register_parcel_delivery`, `update_row_event_display`, `flush_row_event_display`.
   Likely Zig subsystem: [`zig/src/gameplay.zig`](../../zig/src/gameplay.zig) row-event and parcel runtime, plus [`zig/src/main.zig`](../../zig/src/main.zig) prompt/audio routing.

3. Recover the native damage-warning owner instead of only mirroring its visible fill and warning loop.
   Audio evidence: `sfx 50`, `voice 0`, `voice 9`, `voice 14`.
   Native implication: the damage gauge has its own voice escalation and fallback logic, while the warning overlay is a separate actor with its own loop cadence.
   Current Zig suspicion: the runner now owns the warning actor cadence, display-fill smoothing, and `sfx 50` loop edge, but the remaining global-flag exits and `stop_warning_sample` handle behavior are still unresolved.
   Next trace boundary: `apply_damage_gauge_delta`, `update_damage_gauge`, `stop_warning_sample`.
   Likely Zig subsystem: [`zig/src/gameplay.zig`](../../zig/src/gameplay.zig) damage and warning controllers, plus [`zig/src/main.zig`](../../zig/src/main.zig) audio routing.

4. Treat attachment-follow milestone audio as evidence that the live follow state still has missing semantics.
   Audio evidence: `voice 4`, `voice 12`, `voice 15`, `voice 1`, `voice 3`.
   Native implication: attachment begin, milestone crossing, kind-`31` launch completion, and exit-fall thresholds all belong to one richer follow-state controller.
   Current Zig suspicion: the port has improved follow geometry and exit handling, but still lacks the native milestone and kind-specific completion semantics.
   Next trace boundary: `begin_track_attachment_follow_state` and `update_track_attachment_follow_state`.
   Likely Zig subsystem: [`zig/src/gameplay.zig`](../../zig/src/gameplay.zig) attachment begin, follow update, and exit handling.

5. Recover the movement-state sound controller instead of treating gameplay audio as mostly event-based.
   Audio evidence: `sfx 17..24`.
   Native implication: there is a dedicated movement controller that samples `movement_flags`, picks families, and even switches to an attenuated path during attachment exit.
   Current Zig suspicion: the port now has the recovered family ladder, selector-owned cooldown steps, the startup cooldown reseed window, explicit live press-vs-held input lanes, replay raw-bit gating, the runtime fire feature flag, attachment-exit suppression/gain, and the recovered turbo-spread plus laser/rocket speed ratios, but it still does not mirror the deeper emitter owner or literal input-device source.
   Next trace boundary: `play_movement_state_sound`, `update_player_movement_flags`, and the fire-gate block in `update_subgoldy`.
   Likely Zig subsystem: [`zig/src/gameplay.zig`](../../zig/src/gameplay.zig) movement-state and surface-state lanes, plus [`zig/src/main.zig`](../../zig/src/main.zig) gameplay SFX dispatch.

6. Split collision and powerup feedback back into their native families.
   Audio evidence: `sfx 39/40`, `sfx 42`, `sfx 43`, `sfx 1..7`, `sfx 14`, `sfx 16`, `sfx 26`, `voice 5`, `voice 10`.
   Native implication: garbage, health, explode rings, negative-velocity rings, weapon-upgrade rings, parcel pickup, and jetpack state changes are all distinct systems with different owners.
   Current Zig suspicion: the exact ring-kind ladder is now ported for `sfx 1`, `sfx 1..7`, `sfx 42`, `sfx 43`, and `voice 5`, but health, parcel, jetpack, garbage-impact, and the deeper weapon/jetpack presentation owners are still not fully literal.
   Next trace boundary: `handle_subgoldy_collisions`, `set_snail_jetpack`, `set_snail_weapon`.
   Likely Zig subsystem: [`zig/src/gameplay.zig`](../../zig/src/gameplay.zig) collision runtime and pickup state, plus [`zig/src/main.zig`](../../zig/src/main.zig) gameplay effect mapping.

7. Recover cutscene audio ownership as part of the cutscene state machine, not as loose frontend polish.
   Audio evidence: `sfx 46`, `voice 3`, `voice 11`.
   Native implication: completion-screen init and death voices are both owned by explicit cutscene states.
   Current Zig suspicion: cutscene timing and cameras are closer now, but audio still lags behind the recovered state machine.
   Next trace boundary: `initialize_cutscene`, `update_cutscene`, and the death or completion entry helpers it calls.
   Likely Zig subsystem: [`zig/src/gameplay.zig`](../../zig/src/gameplay.zig) cutscene controller and [`zig/src/main.zig`](../../zig/src/main.zig) completion/death handoff.
