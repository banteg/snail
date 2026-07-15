# initialize_frontend_widget @ 0x401d30

Starter scratch for the shell-font front-end widget constructor.

Models list insertion, tooltip owner reset, border style presets 20-23, text
copy/layout anchors, highlight state, slider child creation, and the final
layout call. It uses the shared exact cRBorder/`FrontendWidget` view for the
owned fields and call surface, with raw offsets retained only where the
constructor's local scheduling is not yet source-shaped.

Expected residuals:
- stack-local color ordering is still decompiler-shaped.

2026-06-20 frontend type pass initially modeled the constructor and layout
helper as sharing one scalar result. The 2026-07-14 cross-port/callsite audit
supersedes that interpretation: the apparent result is incidental register
state from the final layout call, not an authored return value.

2026-06-20 shared frontend header pass: the local `FrontendWidget` list-prefix
view was removed in favor of `include/frontend_widget.h`. Focused matcher
evidence stayed unchanged at `45.21%`, `270/429` candidate/target
instructions, with the same `38 ok / 1 unresolved / 1 mismatch` masked audit.

2026-06-20 BorderManager ABI pass: the scratch now uses
`include/border_manager.h` for slider-child `allocate_border()` calls. The
shared allocator returns a `FrontendWidget*` view over `BorderRecord` storage,
so no local manager stub is needed. Focused matcher remains unchanged.

2026-06-20 constructor layout pass: focused matcher improved from `45.21%`
(`270/429`, `38 ok / 1 unresolved / 1 mismatch`) to `62.18%` (`433/429`,
`32 ok / 1 unresolved / 0 mismatch`). Accepted evidence-backed offsets:
`widget_type` stores at `+0x7c`, style font fields are `+0x6ec/+0x6f0`,
slider children are `more +0x71c`, `less +0x718`, and `value +0x720`, and the
constructor color lanes use `+0x1fc/+0x1cc` for the initial whites with style
presets flowing through `+0x1ec/+0x1fc/+0x1bc/+0x1cc`. Restoring the native
`0x104` color-temporary frame was the key source-shape change; making
`copy_color` inline before that frame rewrite regressed to `47.55%`, but after
the frame rewrite it improved the scratch to the final `62.18%`.

2026-06-20 switch-table audit: the widget-type table at `0x402484` is now
named `initialize_frontend_widget_type_jump_table` with candidate alias
`$L1110`. The focused matcher remains `62.18%`; masked audit is now `32 ok / 0
unresolved / 1 mismatch`, classifying the style-preset switch as table-layout
debt rather than an unknown relocation.

2026-07-12 border-tail ownership pass: the main anchor and both slider-child
anchors read the final `BorderManager::justify_centre` float at manager
`+0x435b0`, agreeing with the exact sprite initializer and exact raw-bit
mutator. This is codegen-neutral at the current `62.41%`, `433/429` result
with `32 ok / 1 mismatch`.

2026-07-12 mouse-history ownership: the constructor's native one store is at
`FrontendWidget +0x278`, not `+0x264`. It seeds
`mouse_history_warmup_frames`; the updater decrements it before comparing the
root cursor against `previous_mouse_x/+0x27c` and
`previous_mouse_y/+0x280`. Correcting the shared field is codegen-neutral at
the same 62.41% headline result but removes a false overlap with the teardown
progress lane.

2026-07-12 cRBorder layout closure: allocation and the exact sprite
initializer close the Windows object at 0x724 bytes, now verified by the live
Binary Ninja `FrontendWidget` type. The constructor/draw/update family owns
`border_texture_id +0x48`, `background_texture_id +0x60`, hit-test sprite
`+0x64`, style `+0x7c`, sprite shadow offset `+0x178`, six contiguous `tColour`
blocks at `+0x1ac..+0x20b`, sprite texture/layer `+0x270/+0x274`, and the three
slider children at `+0x718..+0x720`. In particular, warning AI writes
`hot_text_color.a +0x208`; it does not own a separate overlay field.

Promoting those fields into the shared source and repeatable Binary Ninja
header was initially codegen-neutral at 62.41%, 433/429 candidate/target
instructions, 32 clean masked operands, and one bounded switch-table mismatch.
The exact sprite initializer remains 157/157.

2026-07-12 constructor source-shape recovery: focused Wibo rises from 62.41%
to 99.30%, with identical 429/429 instruction counts, prefix 55/429, 49 clean
masked operands, and one honest jump-table mismatch. The accepted changes all
recover durable ownership or evaluation order visible in native code:

- the text constructor does not clear `sprite_shadow_offset`; that extra store
  was removed rather than treating sprite-button setup as shared state;
- the active-list head is acquired after the initial cRBorder field stores,
  reproducing the native prologue through the switch dispatch;
- the native style-body order is `20, 22, 23, 21`, with direct `tColour`
  assignments rather than an aliasing copy helper;
- `current_padding = target_padding = idle_padding` restores the native x87
  chained stores;
- the authored x/y writes use native evaluation order, and slider children are
  assigned and called through their owned `+0x718/+0x71c/+0x720` slots instead
  of synthetic local child pointers;
- the adjusted anchor is evaluated before the mouse-history seed, and the
  first child is allocated before computing its shared y coordinate.

The only instruction differences are three compiler temporary stack slots:
target uses `+0xa4`, `+0x114`, and `+0x24` where the readable candidate cycles
them as `+0x24`, `+0xa4`, and `+0x114`. The first short displacement also moves
three case-label offsets by three bytes, so candidate `$L1214` is deliberately
not accepted as the curated jump table. Declaration-order and temp-name probes
were codegen-neutral or regressed; no volatile or fake alias was retained.

2026-07-14 root-client consolidation: the active-list head, shared justify
scalar, and three slider-child allocations now all traverse
`GameRoot::border_manager`. The ownership-only rewrite leaves the honest
temporary-slot/jump-table residual byte-for-byte unchanged at 99.30%, 429/429
instructions, 49 clean operands, and one mismatch.

2026-07-14 base ownership closure: `FrontendWidget` is now the semantic
`cRBorder` view of the same storage that `BorderManager` owns as
`BorderRecord`. The exact 21/21 `initialize_border_record` constructor first
initializes `BodBase`, constructs its color members, and then installs the
front-end widget vtable; `allocate_border` subsequently returns that record
through the widget view. The shared type therefore inherits the actual
`BodBase` prefix and begins widget-specific semantics at `+0x38`, rather than
duplicating only its intrusive-list lanes. This ownership-only change preserves
the honest 99.30%, 429/429 result, 55-instruction prefix, 49 clean operands,
and one bounded jump-table mismatch.

## 2026-07-14 authored void contract

Android preserves this text constructor as
`cRBorder::Init(int, char*, int, float, float, tColour, int, float)` and ends
through the void `RePosition()` member. All 83 Windows callsites discard EAX;
the former Exit/HighScore tail returns only propagated incidental call state.
The shared method is now `void`. Focused matching remains 99.30%, 429/429,
prefix 55, with 49 clean operands and the same bounded jump-table mismatch.

## 2026-07-15 persisted constructor receiver

The iOS symbol inventory independently preserves the same
`cRBorder::Init(int, char*, int, float, float, tColour, int, float)` member as
Android. The repository's rollback-safe Binary Ninja preview verified the
authored `void` receiver and restored the old scalar type before apply. The
durable sync now owns the `FrontendWidget*` receiver, `tColour*` argument, and
void result directly; persistence requires a saved snapshot plus independent
prototype readback. IDA already carries the same contract. None of this changes
the scratch: it remains the honest 99.30%, 429/429-instruction transcription
with 49 clean operands and one bounded jump-table mismatch.

The Binary Ninja replay also pins the two `set_color_rgba` EAX values that its
HLIL otherwise merges with integer outgoing-stack lanes. Both calls return the
same proven `tColour*` as the other constructor color initializers; the narrow
user-variable annotations prevent later root-layout reanalysis from degrading
those two values back to `int32_t*`.

## 2026-07-14 final raw-lane cleanup

Text copying, all flag tests, and both slider-child flag derivations now use
the shared `FrontendWidget::text_buffer` and `widget_flags` members instead of
reconstructing `this +0x2cc/+0x1a0`. Together with the exact sprite initializer
pass, both authored constructors now exercise every semantically recovered
widget field through the canonical owner. The constructor-only dword at
`+0x38` remains deliberately unnamed because neither Windows constructor nor
the available consumers establish its role.

The rewrite is codegen-neutral: focused matching remains 99.30%, 429/429
instructions, prefix 55, with 49 clean operands and the one documented
jump-table layout mismatch.
