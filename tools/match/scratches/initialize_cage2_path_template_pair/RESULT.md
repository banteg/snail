# `initialize_cage2_path_template_pair` result

## Matcher summary

| Metric | Before | After |
|---|---:|---:|
| Match | 0.19% on coarse range | **56.54%** focused |
| Target instructions | 1029 coarse | **648** |
| Candidate instructions | 2 | **629** |
| Common prefix | 0 / 1029 | 0 / 648 |
| Masked operands | none | **39 ok, 0 unresolved, 1 mismatch** |

The current focused score is **56.54%**. The first mismatch is the native
`sub esp, 0x54` versus the candidate's `sub esp, 0x48`.

The single masked mismatch is at the curve-loop call alignment: target
instruction 127 resolves to `set_matrix_identity`, while candidate instruction
148 resolves to `set_matrix_rotation_identity`. There are no unresolved masked
symbols or constants.

## Accepted source-shape changes

- Corrected the native member signature to four explicit stack arguments and
  `ret 0x10`; the fourth texture argument is semantically unused.
- Added exact scratch-local `0xa8` sample and `0x30` facequad overlays plus the
  required path-template fields.
- Reconstructed constructor fields, endpoint samples, the 20-sample cage curve,
  basis construction, both delta loops, terminal vectors, strip-mesh allocation,
  vertex generation, facequads, UVs, texture selection, and finalization.
- Used real `Vector3` temporaries for basis, delta, and vertex work to recover
  VC6 stack-copy and x87 scheduling patterns.
- Kept repeated 16-bit width/stride expressions in the face loop rather than
  optimizing them into a cached stride.
- Preserved the target's redundant parity branches around texture lookup.
- Preserved the rotation constant sequence with an explicit float conversion.
- Added a terminal-row lateral-offset vector, yielding the final increase from
  `43.49%` / 622 instructions to `43.55%` / 629 instructions.

## Rejected trials

- Branch inversion: `27.74%`; it removed the masked mismatch but destroyed the
  useful whole-body alignment.
- Named rotation-factor local: about `28.73%`; register allocation moved across
  the whole curve loop.
- Direct-cast and double loop counters: `43.20%` and `43.26%`; the double form
  also emitted qword constants absent from the target.
- Late destination-vertex calculation: about `28.82%`; locally plausible but a
  severe global register-allocation regression.
- Shared/terminal vectors, explicit scalar arrays, and multi-vector terminal-row
  forms: no native frame recovery and lower scores (up to `43.12%`).
- Cached face stride: lower score because it removed native word reloads.
- `register` hints and named `0.49f` constants: no useful code-generation change.

## Target-range correction

Promoting `load_png_image @ 0x42f0a0` removes its 371 instructions from this
target. The corrected Cage2 range contains 648 decoded instructions: 645 through
the main `ret 0x10`, followed by the real three-instruction out-of-line block at
`0x42f08c..0x42f095`. Alignment NOPs before `0x42f0a0` are not counted. The
candidate source is unchanged; correcting ownership alone raises its focused
score from 43.55% to 56.54%.

## Next region to attack

Recover the interior-loop integer induction and `fild` schedule first. The
candidate currently strength-reduces the argument-slot counter into a floating
induction value, shifting the identity/basis call alignment. Once that is fixed,
revisit the terminal vertex-row scalar lifetimes that account for the remaining
`0x48` versus `0x54` frame difference.

## Final audit

- Toolchain: `msvc6.5 /O2 /G5 /W3`.
- Final score: `56.54%`.
- Target/candidate: `648 / 629` instructions.
- Prefix: `0 / 648`.
- Masks: `39 ok, 0 unresolved, 1 mismatch`.
- No inline assembly, naked functions, volatile padding, fake globals, dummy
  externs, artificial stack padding, or matcher/normalizer gaming.
