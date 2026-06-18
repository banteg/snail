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

Remaining residual: the bonus award sound call still schedules `mov ecx,
ADDR` and `push 0x31` in the opposite order from native. Do not force this
with fake helpers or dummy symbols.

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

Pinned at 99.53%. Do not churn this scratch for percentage unless new source
evidence explains the call setup order without introducing a fake helper or
dummy temporary.

2026-06-16 type consolidation: `FrontendWidget` moved out of
`row_event_display.h` into `frontend_widget.h`. The row-event widgets still use
the shared +0x1a0 `widget_flags` and +0x2cc `text_buffer` fields; focused match
remains pinned.

2026-06-18 vector alias cleanup: the scratch-local x/y/z `Vec3` view now aliases
the shared `Vector3` type. Focused Wibo remains pinned at `99.53%`, `213/213`,
with `37 ok` masked operands; the only residual is still the bonus sound
thiscall setup order.
