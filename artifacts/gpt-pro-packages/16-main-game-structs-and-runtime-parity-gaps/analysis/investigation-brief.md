# Investigation Brief

The port is materially closer to Windows parity than it was a few weeks ago, but it is still not safe to treat the main gameplay owners as fully understood. Several earlier guesses have now been replaced by better subsystem models, and the remaining errors are narrower and more actionable.

## What Is Already On Firmer Ground

- Replay-bearing score records now preserve the recovered compact lanes for replay mode, build flags, build seed, and several challenge scalars.
- Selected-record replay launch now rebuilds the level from the saved record instead of falling back to a generic mode or index load.
- Replay playback now consumes the saved `lateral` lane and uses it as a direct world-`x` override.
- Parcel pickup and delivery now run through the live parcel runtime slots instead of a row-visitation shortcut.
- Completion handoff is no longer blocked on crude score-side shortcuts; it is closer to the gameplay row-event controller.
- Attachment exit and completion handoff are now modeled as explicit controller state instead of one collapsed helper path.

## Systems Still Not Fully Understood

### 1. Replay Playback

What we know:

- `deserialize_compact_high_score_record` exposes a 5-byte replay payload per runtime row: `i16 lateral`, `i16 forward`, `u8 flags`.
- `update_subgoldy` clearly consumes the `lateral` lane early and converts it with the same type-16 helper we now use for world `x`.
- `update_subgoldy` also consumes the second `i16` lane later, around `0x43cd59` and `0x43cd74`, but the semantic meaning of that lane is still unresolved.
- Bits `0x1` and `0x2` in the replay flags are tested around `0x43d12c` and `0x43d17c` and feed movement-state or sound paths.
- Bit `0x8` marks the recorded tail and is now ported.

What may still be wrong in Zig:

- replay forward or progress may still be free-running locally when Windows uses the saved lane
- replay-owned movement or sound transitions tied to flags `0x1` and `0x2` are still missing
- replay fade or exit ownership may still belong to a native owner outside the current port-side handoff

What to look for:

- identify the exact semantic role of the `forward` `i16` lane
- identify whether it is absolute `z`, backdrop progress, current-row payload, or something else entirely
- identify the exact effects of replay bits `0x1` and `0x2`
- identify the native owner that transitions replay out of gameplay at the tail

### 2. Row Event Display Controller

What we know:

- `game + 0x12727d8` is the gameplay `RowEventDisplayController`.
- `state`, parcel counters, progress, and widget anchor floats are now typed.
- `update_subgoldy` reads from the controller and `update_row_event_display` clears internal gate state.
- `register_parcel_delivery` belongs to this controller and not to the completion screen.

What is still missing:

- the exact meaning of the byte lane at `row_event_display + 0x18`
- the native writer or init path for that lane
- the full release condition that promotes completion from in-game row-event handling to the cutscene or completion owner

What may still be wrong in Zig:

- completion still likely uses an approximation for one startup or fast-forward gate
- any replay-specific interaction with row-event completion may still be missing

What to look for:

- find the writer or initializer for `row_event_display + 0x18`
- confirm whether it is replay-only, selected-record-only, or normal postal gameplay
- confirm the exact condition under which `update_subgoldy` fast-forwards or bypasses the handoff timer

### 3. Core `Game` Field Semantics

What we know:

- `Game.selected_level_record_active`, `.selected_level_record_persistent`, `.selected_level_record`, `.replay_track_index`, `.runtime_track_index`, `.track_parcels`, and `.row_event_display` are now grounded enough to use directly.
- `Game.runtime_flags` is real and useful, but not fully exhausted.

What is still unsafe:

- `game + 0x44` still appears overloaded and should not be frozen to one meaning yet
- `game + 0x48` is not a global simulation-rate lane, but its true subsystem role is still incomplete

What to look for:

- narrow the live consumers and writers for `game + 0x44` and `game + 0x48`
- identify whether those fields are owner-specific scratch, per-mode config, or long-lived runtime control state

### 4. Parcel Runtime And Delivery Handoff

What we know:

- the 50-slot parcel runtime at `game + 0x125e480` is now typed
- pickup and delivery flight are much closer to native
- `update_track_parcel` owns the state machine, bobbing, and delivery vectors

What may still be wrong in Zig:

- the mailbox or home-anchor vectors used for delivery arcs may still be approximated
- one or more parcel presentation or owner handoff details may still be using port-side scaffolding

What to look for:

- identify the exact source of the delivery target vectors and owner object
- confirm whether the current arc seeding and slot lifecycle match Windows through delivery completion

### 5. Attachment Follow, Installed Banks, And Nonlinear Family Semantics

What we know:

- installed attachments are no longer collapsed to one winner row
- follow, exit carryover, and completion handoff are now separated instead of sharing one helper
- kind-`42` no longer clamps away the recovered negative local height at entry

What is still missing:

- the exact installed-bank generation and pairing rules
- remaining family-specific kind-`42` entry or exit behavior
- the last Windows-specific owner-record semantics for post-follow carryover

What may still be wrong in Zig:

- some installed-entry cases may still succeed or fail on the wrong rows
- some nonlinear exits may still take the wrong carryover path

What to look for:

- validate the template-generation and bank-pairing chain upstream of installed entry
- validate any kind-`42` special-case state writes inside `update_subgoldy`

### 6. Fall, `NoFall`, And Jetpack

What we know:

- `JetPack=Off` and `NoFall` now feed runtime lanes instead of raw annotation shortcuts
- jetpack warning intensity and more of the hover controller shape are now ported

What may still be wrong in Zig:

- world-`y` fall entry and suppression may still be only a controlled proxy
- some hover or warning-edge transitions may still be incomplete

What to look for:

- the exact native world-`y` drop and recovery path
- any remaining jetpack owner fields that should replace current Zig scaffolding

## Specific Output Requested

Please return:

1. A ranked list of the systems above that are still most likely wrong in the current Zig port.
2. For each ranked item, the exact native evidence to inspect next.
3. Any `Game` or `Player` field names that should be renamed, split, or kept intentionally vague until more evidence lands.
