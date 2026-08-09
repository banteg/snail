# Exact match

`initialize_tip_manager` matches exactly at 7/7 instructions and is the Windows
`cRTipManager::Init()` member. It clears the three inline 0x20-byte Tips at
Windows manager offset 0x38. The corresponding iOS array begins at 0x2c because
that port's BodBase prefix is smaller; the array ownership and element layout
are otherwise independently confirmed.

## 2026-07-14 complete tip-bank lifecycle

`TIP_SLOT_COUNT` now owns the three-entry extent shared by the embedded array,
exact initializer, exact active-slot allocator, exact updater, and exact
teardown. Binary Ninja field xrefs find precisely those four sibling methods;
iOS independently preserves the complete `cRTipManager::{Init,TipNew,AI,
UnInitTips}` family over the same three Tips. The allocator's exhaustion check
therefore comes from storage capacity rather than an unrelated magic limit.

2026-07-18 durable decompiler replay: an exact 0x98-byte `TipManager` assertion
and explicit `Tip*` cursor view make both tracked decompilers walk
`manager->tips` directly. Paired checks reject the old `this + 14`, scalar
word-pointer, and compensating-offset forms. Matching remains exact at 7/7.

## 2026-08-09 primary cRTipManager ownership

The initializer now emits as `cRTipManager::Init()` over a `cRTip*` cursor and
selects `?Init@cRTipManager@@QAEXXZ`; `TipManager` remains a compatibility
typedef. Windows calls it once from `initialize_game_assets_and_world` at
`0x410210`. Android and iOS preserve the same authored manager member and
three-entry inline cRTip bank despite their smaller BodBase prefix. The
owner/symbol promotion is byte-neutral and remains exact at 7/7 instructions.
