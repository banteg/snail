# destroy_intro_screen @ 0x419920

Unlinks each intro/credits crawl renderable from the shared BOD active list and
pushes it back onto the shared free list before the intro screen exits.

Layout recovered from the target loop:

- `+0x0c`: render flags restored into `g_render_flags` (`data_4df934`);
- `+0x14`: renderable count;
- `+0x18`: first renderable slot;
- renderable slot stride: `0x90`;
- each slot starts with a `BodNode`, so the native loop cursor at slot `+0x0c`
  is the node's `list_next` field.

The proof-grade source mirrors the existing matched BOD list removal idiom and
uses the native `node->list_next` cursor shape. The final fix was spelling the
two diagnostic paths as explicit `goto next_renderable` exits before the shared
loop update. With simple locals hoisted above the jumps, VC6 emits the native
separate `report_errorf` callsites and lands at `61/61` instructions,
`100.00%`, with seven clean masked operands.

Rejected same-family probes:

- flattening the equivalent state-2 error checks in `update_salt_hazard`
  remained neutral at `75.78%`; its residual is a duplicated error-tail shape
  plus `game+0x5a8` materialization, not the intro-loop tail merge;
- `remove_sub_loc` was rechecked at `91.19%`; its documented
  residual is the fringe-loop active-flag reload/register-allocation tradeoff,
  so this goto-tail insight should not be transplanted there.

2026-07-12 authored-owner correction: iOS v1.9 preserves this lifecycle edge
as `cRLogo::UnInit()`, and the v1.5 `cRLogo::AI()` body inlines the same
active-letter list teardown. Windows factors it into this exact 61/61 helper.

2026-07-14 root-owner closure: root `+0x30d` is player 0's
`high_score_entry_pending` latch and root `+0x1b8` is the same player's
`frontend_state`. The crawl slots borrow `GameRoot::active_bod_list` for
teardown. Naming all three owners preserves the exact 61/61 instructions and
all seven operands.

2026-07-14 intrusive-node offset closure: the native loop still keeps its
cursor at `BodNode::list_next`, but all backward reaches to `list_flags`,
`list_prev`, and the containing node now derive from the shared member offsets.
The ownership cleanup remains exact at 61/61 with all seven operands clean.

2026-07-15 return-ownership closure: the only Windows call at `0x419a24`
immediately reloads the logo state instead of reading EAX. The count left by
the native teardown loop is incidental, so the authored `cRLogo::UnInit()`
contract is void. Removing the synthetic return preserves the exact 61/61
instructions and all seven operands.
