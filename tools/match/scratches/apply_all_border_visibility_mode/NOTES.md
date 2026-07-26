# apply_all_border_visibility_mode @ 0x404360

This is the shared transition stack behind
`cRBorderManager::HideBorders()` and `UnHideBorders()`. The embedded
`BorderStack` borrows FrontendWidget views of the manager's fixed 150-record
pool; it does not own or allocate them.

Modes 0 and 3 scan active records, set `FRONTEND_WIDGET_FLAG_HIDDEN` or
`FRONTEND_WIDGET_FLAG_DISABLED`, and append each affected widget with the
current generation before advancing that generation. Modes 1 and 2 unwind only
the newest generation in LIFO order and clear the corresponding bit. Mode 1
additionally resets padding and hover-blend lanes to their idle state.

Every known caller discards EAX, and the native exit paths leave mutually
incompatible incidental values there. The authored contract is therefore
modeled as `void`; the manager wrappers were corrected to the same contract.

## 2026-07-26 authored stack owner

Android exports the complete body as `cRBorderStack::Perform(int)`. All four
modes agree with Windows: 0 and 3 push hidden or disabled transitions across
the 150-record manager pool, while 1 and 2 unwind only the newest generation.
Mode 1 additionally restores the affected borders' idle padding and hover
lanes.

Android's stack reaches a pointer-backed pool through its platform-specific
owner link. Windows keeps the manager pool inline and its `BorderStack::owner`
at `+0x648`. The mobile body therefore proves the authored owner, four-mode
contract, and borrowed handle semantics without supplying Windows offsets. The
Windows member remains exact at 137/137 instructions with one clean operand.
