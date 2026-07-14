# initialize_exit_prompt

- Target: `Exit::initialize_exit_prompt` at `0x4060d0`, the Windows
  `cRExit::Init()` owner recovered independently in Android and iOS.
- First-pass recovery from BN decompile/disassembly. The function hides the
  active border batch, switches on `state - 2`, then allocates/layouts the
  prompt title plus Yes/No buttons for most states.
- Native has several duplicated switch arms with shared tail jumps. Keep the
  C++ cases explicit until the matcher shows which duplicated blocks can be
  safely folded without losing branch shape.
- Known state layouts:
  - states 2, 3, 7 use the centered quit title plus Yes/No at `y=330`.
  - states 8 and 9 use `prompt_y` for Yes/No under the centered title.
  - state 4 uses absolute Yes/No positions without title.
  - state 5 uses absolute title and button positions.
  - state 10 uses the centered default layout.
- Focused match: `100.00%` (`441/441` instructions, `441/441` prefix,
  `109 ok`, `0 unresolved`, `0 mismatch`).
- `initialize_exit_prompt_jump_table` is curated at `0x4067b4` with ten entries
  (`0x28` bytes) between the function `ret` at `0x4067b0` and the `0x90`
  padding before `update_completion_screen`. The table now resolves cleanly.
- The two no-title branches end immediately after the final No-button
  initializer. Earlier analysis treated the call's incidental EAX as a scalar
  result; cross-port prototypes and caller evidence now identify both this
  owner and the cRBorder initializer as `void`.
- A shared `result` local still remains rejected: it introduces an `edi` result
  register, shifts the stack color locals, and drops to `92.20%`.
- 2026-07-11 local-label collision audit: the current compiler generation calls
  this table `$L1075`, a spelling also used by an unrelated backdrop table.
  The matcher now retains both the alias-bounded and relocation-bounded entry
  sequences, so the ten prompt destinations are proved by content without
  assigning a globally false label alias. The exact 441/441 body remains at
  109 clean masked operands.
- 2026-07-11 owner closure: `Exit` is the primary 0x1c-byte owner at
  `GameRoot +0x4f3ac`. It is distinct from the 0x50-byte subgame `Completion`
  at root `+0x12e6df0`. The rename is codegen-neutral at the exact baseline.
- 2026-07-13 root-owner cleanup: border hiding and every prompt allocation now
  reload the canonical `GameRoot::border_manager` member. The native duplicated
  switch bodies and their short borrow lifetimes remain untouched; output is
  still exact at 441/441 instructions with all 109 operands clean.
- 2026-07-14 return-contract audit: Android/iOS `cRExit::Init()` has a common
  side-effect-only epilogue, and the sole Windows caller discards EAX. Rewriting
  the tail branches as calls followed by `return;` preserves the exact 441/441
  body and all 109 clean operands. Binary Ninja now has the exact 0x1c-byte
  `Exit` owner; its void prototype preview verifies but live analysis restores
  the stale scalar form, so the sync script reports it as deferred.
