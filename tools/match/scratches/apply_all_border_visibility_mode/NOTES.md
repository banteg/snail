# apply_all_border_visibility_mode @ 0x404360

This is the shared transition stack behind
`cRBorderManager::HideBorders()` and `UnHideBorders()`. The embedded
`BorderStack` borrows FrontendWidget views of the manager's fixed 150-record
pool; it does not own or allocate them.

Modes 0 and 3 scan active records, set `0x1000` or `0x8000`, and append each
affected widget with the current generation before advancing that generation.
Modes 1 and 2 unwind only the newest generation in LIFO order and clear the
corresponding bit. Mode 1 additionally resets padding and hover-blend lanes to
their idle state.

Every known caller discards EAX, and the native exit paths leave mutually
incompatible incidental values there. The authored contract is therefore
modeled as `void`; the manager wrappers were corrected to the same contract.
