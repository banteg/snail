# Scratch status

`flush_row_event_display` @ 0x404830 forces the row-event display controller
to its completed state: it pays out any remaining parcel deliveries, applies
the optional bonus, kills all five row-event widgets, restores the display
token, and clears the controller state.

Current result: 89.39%, 65/67 instructions, 4/67 prefix. The accepted source
matches the real control-flow split where an already-complete delivery count
skips the bonus block, while `delivered > target` still reaches it.

Residuals:

- native spells the post-bonus delivery-count bump as load/inc/store scheduled
  around the first widget kill argument; VC6 emits the equivalent
  `inc dword [esi+0x28]`;
- the shorter candidate shifts the local branch labels, but the teardown order
  is still widget A, B, D, C, E and the display-token/state tail is semantic.

Rejected variants: duplicating the first widget kill across bonus/non-bonus
paths regressed to 79.17% by splitting the teardown flow; local-count and
pointer-to-field spellings for the bonus increment were neutral and still
lowered to `inc dword [mem]`.
