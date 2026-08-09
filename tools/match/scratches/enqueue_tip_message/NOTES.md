# Exact match

`enqueue_tip_message` matches exactly at 26/26 instructions.

The exact source shape is a plain `while (1)` scan over the three tip slots:
break when the current slot is inactive, otherwise advance the slot pointer and
index, and report `"Run out of Tips"` as soon as the index reaches three.

Rejected source-shaped probes:

- a natural `for (slot = slots; slot->active; ++slot)` form made VC6 look ahead
  to the next slot and moved the exhaustion path after the success path;
- label/goto spellings kept the right semantics but still rotated the loop into
  a bottom-tested shape;
- a post-loop exhaustion check kept the cold path near the target but emitted a
  redundant compare before the error call.

Keep the current `while (1)` form as the tip-slot allocator idiom.

2026-06-16 type consolidation: the manager, tip, and definition layouts now
come from shared `tip_manager.h`. The allocator keeps
the exact 26/26-instruction match.

2026-07-12 authored-owner promotion: symbol-preserving iOS builds identify the
member as `cRTipManager::TipNew(cRTipData*, bool)` in v1.5 and use a signed-char
second formal in v1.9. Both return the selected `cRTip*`. Windows independently
loads that gate as a 32-bit argument, so this exact member returns `Tip*`, takes
`TipData*`, and retains `int hide_disable_button`.

2026-07-18 durable decompiler replay: both tracked decompilers now retain the
`TipManager*`, `TipData*`, and returned `Tip*` ownership, and index the embedded
`manager->tips` array without pointer-to-array artifacts or offset correction.
Paired health checks pin that graph. Matching remains exact at 26/26 with three
clean masked operands.

## 2026-08-09 primary cRTipManager ownership

The allocator now emits as
`cRTipManager::TipNew(cRTipData*, int)`, returns `cRTip*`, calls the authored
`cRTip::Init`, and selects the exact VC6 symbol
`?TipNew@cRTipManager@@QAEPAVcRTip@@PAUcRTipData@@H@Z`. Windows calls it from
Goldy row-event handling at `0x43b866`; Android and iOS preserve the same
authored owner, return type, first-inactive scan, and three-entry exhaustion
boundary. As with cRTip::Init, the Windows 32-bit gate remains authoritative
over the mobile bool/signed-char spellings. Instruction matching remains exact
at 26/26; the shared reference manifest binds the owner-qualified Init
relocation, keeping its call operand audit-clean.
