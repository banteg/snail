# advance_frame_sequence

`FrameSequence::advance_frame_sequence` publishes the current frame record's
payload at `+0xec`, then advances the fractional phase unless the sequence is
stopped or already complete.

Recovered layout:

- `+0x54` frame count
- `+0x5c` pointer to 0x30-byte frame records
- frame record `+0x0c` payload
- `+0xdc` flags
- `+0xe0` current frame index
- `+0xe4` phase
- `+0xe8` phase step
- `+0xec` current frame payload

Flag meanings from this helper:

- `0x01`: complete/stopped
- `0x02`: wrap
- `0x04`: ping-pong
- `0x08`: reverse direction
- `0x10`: paused/stopped gate

The native return register is incidental: the no-advance path leaves the frame
offset in `eax`, while the advance path leaves the payload. The only known
caller ignores the return value, so the scratch models this as a `void` member.

## Scratch status

Added on 2026-06-18. Focused Wibo verifies a clean 100% match: 65/65
instructions, prefix 65/65, 2 masked operands OK, no unresolved or mismatched
operands.

Source-shape corrections made while matching:

- The reverse-direction block is the native fallthrough after `flags & 8`;
  spelling the forward path first regressed to 56.06%.
- Reverse underflow tests the decremented frame index against `-1`, not the old
  frame index against zero. The source therefore stages `next_frame_index =
  frame_index - 1` before the underflow branch.
- If the sequence is active but `phase + phase_step <= 1.0`, native still pops
  the x87 value and republishes `frames[current_frame_index].payload` to
  `current_frame_payload`. The final publish is therefore outside the phase-wrap
  branch but inside the active-state gate.
- `update_smtracks` now consumes the shared `FrameSequence` layout and remains
  exact at 19/19, confirming its old `replacement_scalar` field is the
  sequence's `current_frame_payload` at owner `+0x124`.
