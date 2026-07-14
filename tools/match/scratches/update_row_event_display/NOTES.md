# update_row_event_display

update_row_event_display @ 0x404cf0 drives the parcel row-event widget,
parcel-home spawn prompt, delivered-count text, completion fast-forward gate,
and bonus award sound.

## Iteration gain (loop session 2026-06-12): 78.52% -> 85.06%

The two sound calls are THISCALL on a global manager
(`mov ecx, ADDR; push id; call`) — converted from the old __stdcall
decl; +6.5 points. Remaining: the float-accumulation region around
target lines 161-196 spills intermediate sums to slots (the dual-slot
temp class — break the expression tree into named float temps per the
IDA rendering, output pointer lea [esi+0x34] suggests the sums build
into a member vector through a temp), and the frame is 0x3c vs 0x30.

## Iteration gain (2026-06-13): 85.06% -> 85.19%

The widget-world output now writes through a typed `Vec3*` view of
`controller+0x34` instead of a separate local copied back to the
controller. This is source-plausible for the native member-vector store
owner and trims three candidate instructions without changing the
recovered row-event semantics. A `< 10` spelling of the delivered-count
tens branch was tested because it matched the local branch direction, but
it regressed the whole function to 82.87%, so the clearer `>= 10` source
form remains.

## Iteration gain (2026-06-13): 85.19% -> 96.38%

The widget-world block now keeps a local `widget_world` plus a typed
member-output pointer, and splits the camera calculation into a
`base_target` vector followed by the final camera-forward add. This recovers
the native `0x3c` stack frame and the staged x/y/z local stores in the
camera/widget projection tail without changing the semantics.

With that frame shape recovered, spelling the delivered-count branch as
`< 10` now matches the native branch direction and keeps the tens-space
store in the same block. The earlier `< 10` regression only applied to the
old direct-member widget-world form.

Rejected experiment: reusing a local `bonus_score` for the sound id after
`add_subgoldy_score` did not change the residual call setup order at 96.38%,
so the simpler constant sound call remains.
Rejected experiment: introducing a real `SoundEffectManager*` local for the
bonus award sound also emitted the same `mov ecx, ADDR; push 0x31` order at
96.38%, so it does not explain native's `push 0x31; mov ecx, ADDR` setup.

Historical residual, resolved by the authored member recovery below: the bonus award sound call scheduled `mov ecx,
ADDR` and `push 0x31` in the opposite order from native. Do not force this
with fake helpers or dummy symbols.

2026-07-09 thiscall setup retry: block-scoped `SoundEffectManager*`, named
`sound_id = 0x31`, and manager+id pairs are all codegen-neutral at 99.53% and
leave the same `push 0x31` / `mov ecx` order residual.

## Pin audit (2026-06-13)

Focused verification now reports 99.53%, 213/213 instructions
(`tools/match/match.sh tools/match/scratches/update_row_event_display --full`).
The terminal object-padding normalizer strips the inert `ret`-after padding
that previously counted as candidate instructions. The remaining diff is
limited to the bonus sound thiscall setup order (`push 0x31` versus loading
the global sound manager into `ecx`). The state machine, pause widget hiding,
parcel spawn call, bonus score award, skip/confirm sound, widget-world vector
staging, and delivered-count tens/ones stores all match the recovered native
behavior.

This 99.53% pin is historical and is superseded by the exact authored-member
result below; no dummy temporary or fake helper was introduced.

2026-06-16 type consolidation: `FrontendWidget` moved out of the former
row-event header into `frontend_widget.h`. The row-event widgets still use
the shared +0x1a0 `widget_flags` and +0x2cc `text_buffer` fields; focused match
remains pinned.

2026-06-18 vector alias cleanup: the scratch-local x/y/z `Vec3` view now aliases
the shared `Vector3` type. Focused Wibo remains pinned at `99.53%`, `213/213`,
with `37 ok` masked operands; the only residual is still the bonus sound
thiscall setup order.

2026-06-18 row-event naming pass: three widget fields now have role names
backed by multiple callsites. `delivered_count_widget` is the two-character
count text updated in the tail, `bonus_widget` is the hidden/blinking bonus
summary widget, and `continue_widget` is unhidden when the controller reaches
the acknowledge/continue state. `widget_a` and `widget_d` deliberately remain
generic because their allocation/setup path has not been recovered yet.

2026-06-18 input-owner naming pass: the continue/confirm gate now uses the
shared `GameInput`/`InputState` layout. The old scratch-local
`control_flags` at owner `+0x3c` is really `input.pressed_buttons`, because
`update_game_input` proves the embedded runtime input block starts at owner
`+0x38`.

2026-06-20 near-proof retry: focused Wibo still reports 99.53%, 213/213
instructions, 102/213 prefix, and 37 clean masked operands. The exact sibling
`register_parcel_delivery` proves that the same
`g_sound_effect_manager.play_sound_effect(0x31)` source spelling can emit the
native `push 0x31; mov ecx, ADDR` order, but the surrounding state-machine
shape here still schedules `mov ecx` first. Removing the retained `game` local,
staging `int sound_id = 0x31`, and calling through a real
`SoundEffectManager*` pointer were all codegen-neutral. Keep the current clear
bonus-award source until a stronger owner/lifetime lead explains the call setup
order.

2026-06-20 call-setup follow-up: focused Wibo still reports 99.53%, 213/213
instructions, 102/213 prefix, and 37 clean masked operands. A
`SoundEffectManager&` reference is codegen-neutral, as are direct `g_game_base`
reads in the bonus-award branch, removing the `bonus_enabled` local, and
staging `Player* player` plus `int bonus_score` before `add_subgoldy_score`.
Those variants leave the exact same residual (`mov ecx, ADDR; push 0x31`
instead of native `push 0x31; mov ecx, ADDR`). Keep this scratch pinned; the
remaining mismatch is a call-setup scheduling artifact with no new
source-plausible lifetime lead.

2026-06-20 row-event lifecycle retry: focused Wibo still reports `99.53%`,
`213/213` candidate/target instructions, `102/213` prefix, and 37 clean masked
operands. The exact `flush_row_event_display` and `register_parcel_delivery`
siblings still prove the row-event lifecycle and show that the same
`g_sound_effect_manager.play_sound_effect(0x31)` spelling can emit native's
`push 0x31; mov ecx, ADDR` order in the shorter payout helper. In this larger
state-machine body, spelling the id as decimal `49`, folding the
`parcel_target_count == 0` and game-mode gates into one condition, and calling
through `(&g_sound_effect_manager)->play_sound_effect(0x31)` are all
codegen-neutral. The retained nested gate and direct member call remain the
clearest source; the residual is still local thiscall setup scheduling, not
evidence for a second audio API.

2026-07-11 pause-owner closure: the widget-hide gate now reads
`GameRoot::subgame.subgame_pause_gate`; removing the synthetic `GamePauseView`
is codegen-neutral at 99.53%, 213/213 instructions, prefix 102/213, and 37
clean masked operands.

2026-07-11 parcel return ownership: the state-2 spawn now receives a `Parcel*`
from `SubgameRuntime::spawn_track_parcel`, backed by the embedded
`ParcelManager`. Android `cRSubGame::AddParcel(...)` independently proves that
the pointer-or-null result is real. The focused Windows result remains 99.53%,
213/213 instructions, prefix 102/213, with all 37 operands clean.

2026-07-11 authored-member recovery: mobile symbols identify this function as
`cRCompletion::AI()`, on the same 0x50-byte object as Init, UnInit, and
RegisterParcel. Defining it as `Completion::update_row_event_display()` rather
than a free `__fastcall` function is the missing Windows source shape: the
scratch is now exact at 100.00%, 213/213, full prefix, with all 38 operands
clean. The old separate `RowEventDisplayController` header is retired.

2026-07-13 widget destination ownership: the producer's typed output at
`Completion +0x34` is now the direct `Vector3 widget_world` member rather than
a cast over three scalar names. The 100.00%, 213/213 exact result is unchanged,
and `update_track_parcel` independently consumes the same owned vector in its
state-7 delivery expression.

2026-07-14 root player closure: parcel staging now passes
`SubgameRuntime::parcel_home_anchor()` and the embedded `subgame.player` to the
parcel manager, while the zero-parcel bonus gate names `subgame.level_mode`
and awards the same player. This removes the raw `root + 0x433f34`,
`+0x42fd7c`, and `+0x74658` expressions without changing the exact 213/213
body or its 38 clean operands.
