# advance_frame_sequence

`FrameSequence::advance_frame_sequence` publishes the current face record's
`TextureRef*` at `+0xec`, then advances the fractional phase unless the
sequence is stopped or already complete.

Recovered layout:

- inherited `Object::facequad_count +0x54` is the frame count
- inherited `Object::facequads +0x5c` points to the 0x30-byte frame records
- inherited `ObjectFaceQuad::texture_ref +0x0c` is the frame payload
- `+0xdc` sequence flags
- `+0xe0` current frame index
- `+0xe4` phase
- `+0xe8` phase step
- `+0xec` current `TextureRef*`

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
  the x87 value and republishes
  `facequads[current_frame_index].texture_ref` to `current_texture_ref`. The
  final publish is outside the phase-wrap branch but inside the active-state
  gate.
- `update_smtracks` now consumes the shared `FrameSequence` layout and remains
  exact at 19/19, confirming the published field at outer owner `+0x124` is a
  `TextureRef*`, not a scalar.

## 2026-07-11 Object inheritance closure

- The constructor at subgame `+0x10013dc` calls the generic `Object`
  constructor thunk on the exact `FrameSequence` base.
- The independently recovered 0x30-byte sequence-record stride equals
  `ObjectFaceQuad`, and its `+0x0c` payload is the same `TextureRef*` field that
  `update_smtracks` installs on the active mesh.
- Modeling `FrameSequence : Object` preserves the exact 65/65 method while
  retiring the duplicate prefix and generic integer payload.
