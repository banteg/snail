# advance_frame_sequence / cRMovie::AI()

`Movie::advance_frame_sequence` publishes the current face record's
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
- `update_smtracks` now consumes the shared `Movie` layout and remains
  exact at 19/19, confirming the published field at outer owner `+0x124` is a
  `TextureRef*`, not a scalar.

## 2026-07-11 Object inheritance closure

- The constructor at subgame `+0x10013dc` calls the generic `Object`
  constructor thunk on the exact `Movie` base.
- The independently recovered 0x30-byte sequence-record stride equals
  `ObjectFaceQuad`, and its `+0x0c` payload is the same `TextureRef*` field that
  `update_smtracks` installs on the active mesh.
- Modeling `Movie : Object` preserves the exact 65/65 method while
  retiring the duplicate prefix and generic integer payload.

## 2026-07-16 analysis-owner closure

- The exact 0xf0-byte `Movie` is now replayed into both analysis lanes
  with its complete `Object` base and five-field tail. The path/subgame replay
  carries a bounded Object-prefix view so a later broad replay cannot replace
  the recovered type with the former size-only byte shell.
- The five proven state bits are shared as `MovieFlag` constants, and
  the sole Windows caller proves the method's `void` thiscall contract.
- Focused matching remains exact at 65/65 instructions with two clean operands;
  strict paired export now renders `object.facequads`, `object.facequad_count`,
  and `current_texture_ref` in both tools.

## 2026-07-27 dual-mobile owner recovery

Android and iOS both preserve the exact authored symbol `cRMovie::AI()` in
`RObject.o`. Their bodies match the Windows state machine field-for-field:

- publish the current 0x30-byte face record's texture before testing flags;
- gate on complete `0x01` and paused `0x10`;
- add phase step, wrap above `1.0`, and move the frame index;
- apply loop `0x02`, ping-pong `0x04`, and reverse `0x08`; and
- publish the possibly changed texture again before returning.

Both `cRFace::AI()` ports call this method on their embedded `cRMovie`, exactly
where Windows `update_smtracks` calls `advance_frame_sequence`. This recovers
the authored `Movie` owner and `cRMovie_AI` alias without importing mobile
offsets: Android and iOS use a larger platform `cRObject`, while the exact
Windows `Object + five-field tail = 0xf0` layout remains independently proven.
