# initialize_p_path_template_pair

Honest starter scratch for `initialize_p_path_template_pair @ 0x425a40`.

The constructor callsite shows nine explicit stack arguments and the target tail
is `ret 0x24`. The first argument selects runtime kinds `0x21..0x23`; the body
uses the width, endpoint X positions, segment count, and two track textures.

The scratch builds the endpoint samples, fills the three P-family curve formulas
seen in the decompile, derives orientation and deltas, generates the strip mesh,
and finalizes the template. Residuals are expected.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 10.58% (134/679
candidate/target instructions) to 18.55% (561/679), with masked operands
improving from 6 ok, 0 unresolved, 8 mismatch to 19 ok, 0 unresolved, 6
mismatch.

2026-07-03 path-template count/radius sweep: materialized the endpoint
`last_index = curve_segments + 1` and allocation `sample_count = last_index + 1`
spelling used by the native constructor, then kept the radius sign check on an
x87 temporary before storing the float radius. Focused Wibo moved from 18.55%
(561/679) to 19.22% (559/679), with masked operands unchanged at 19 ok, 0
unresolved, 6 mismatch. Rejected adjacent probes: reloading primary/secondary X
from `primary->center_x`, reloading secondary Y from the primary transform, and
branching on `kind - 0x21`; all reduced the focused score.

2026-07-03 Z-index helper spelling: keep the pair helper Z input as an integer
sample index and perform the int-to-float conversion inside the inlined helper
after primary identity. Focused Wibo moves from 19.22% (559/679) to 19.26%
(557/679), with masked operands unchanged at 19 ok, 0 unresolved, 6 mismatch.

2026-07-03 radius compare probe rejected: collapsing the radius sign check from
the double temporary to a float local made the visible compare use a dword
operand, but focused Wibo regressed from 19.26% (557/679) to 19.19% (561/679).
Masked operands stayed at 19 ok, 0 unresolved, 6 mismatch, so the native-shaped
temporary remains the retained spelling.

2026-07-03 mesh request order probe rejected: swapping the strip-mesh requests
to facequads-before-vertices was neutral in focused Wibo at 19.26% (557/679),
but simply flipped the remaining mesh call mismatch from target vertices vs
candidate facequads to target facequads vs candidate vertices. Masked operands
stayed at 19 ok, 0 unresolved, 6 mismatch, so the shared vertices-first helper
remains retained until the earlier loop/call alignment debt moves.

2026-07-03 mesh-face loop probe rejected: replacing the direct `a`/`b` face
writes with the two-iteration `face_index` loop regressed focused Wibo from
19.26% (557/679) to 18.14% (567/679). Masked operands dropped from 19 ok, 0
unresolved, 6 mismatch to 16 ok, 0 unresolved, 6 mismatch, so the direct face
writer stays retained for now.

2026-07-03 endpoint expansion probe rejected: flattening the first and terminal
sample setup out of `initialize_pair_sample`, matching the decompile's direct
endpoint writes and `center_x` reloads, regressed focused Wibo from 19.26%
(557/679) to 18.61% (557/679), with masked operands unchanged at 19 ok,
0 unresolved, 6 mismatch. Splitting the probe was also negative: first sample
only dropped to 18.28% and worsened the masked audit to 16 ok, 0 unresolved,
6 mismatch; terminal sample only matched the full regression at 18.61%. The
endpoint helper calls remain retained until the earlier loop/call alignment
debt moves.

2026-07-03 mesh-vertex staging probe rejected: unlike `start` and
`supertramp`, routing the strip-mesh vertex calculation through a local
`Vector3 generated_position` before assigning `*vertex` regressed focused Wibo
from 19.26% (557/679) to 13.01% (566/679). Masked operands dropped from 19 ok,
0 unresolved, 6 mismatch to 14 ok, 0 unresolved, 5 mismatch, so the `p` scratch
keeps direct component writes for now.

2026-07-04 loop-counter probe rejected: rewriting the curved body as a
zero-based counter with `sample_index = i + 1` regressed focused Wibo from
19.26% (557/679) to 18.74% (559/679). Masked operands dropped from 19 ok,
0 unresolved, 6 mismatch to 16 ok, 0 unresolved, 6 mismatch, so the current
one-based loop with `(i - 1)` angle ownership stays retained.

2026-07-04 retained orientation scheduling expansion: expanding the curved-body
orientation helper calls in place matches the native shape that builds both lane
orientations inside the loop and keeps the `i <= 1` identity branch together.
Focused Wibo moves from 19.26% (557/679) to 19.40% (558/679). This is not a
masked-audit cleanup: masked operands worsen from 19 ok, 0 unresolved,
6 mismatch to 19 ok, 0 unresolved, 9 mismatch, so the new residual call
pairings remain explicit.

Post-orientation mesh request-order retest: swapping strip-mesh requests to
facequads-before-vertices stayed neutral at 19.40% (558/679), with masked
operands unchanged at 19 ok, 0 unresolved, 9 mismatch, and only flipped the
remaining mesh allocation call pairing. The vertices-first order remains
retained.

Post-orientation branch-shape retest: rewriting the curved center selection as
independent `kind == 0x21` / `0x22` / `0x23` branches, matching the decompiler's
surface spelling, regressed focused Wibo from 19.40% (558/679) to 19.31%
(564/679). Masked operands stayed at 19 ok, 0 unresolved, 9 mismatch, so the
retained source keeps the `else if` branch chain.

2026-07-15 ownership cascade: flattening the delta producer into the constructor
and indexing `primary_samples` / `secondary_samples` directly recovered the
native owner and moved focused Wibo from 19.40% to 25.72%. Expanding the two
endpoint samples then improved the masked call audit from 21 ok, 7 mismatch to
24 ok, 5 mismatch and nudged Wibo to 25.83%.

Flattening curved-sample initialization was the main unlock: focused Wibo moved
to 38.76%, with 26 masked operands correct and one mismatch. Recovering the
native zero-based angle counter plus one-based sample index then moved Wibo to
40.81% and cleared the masked audit. Finally, direct center stores in an
explicit three-case `switch` recovered the target's `0x21..0x23` dispatch and
unknown-kind fallthrough, moving focused Wibo to 44.05% (615/679 candidate/
target instructions), with 33 masked operands correct and no unresolved or
mismatched operands.

The target also proves that face headers are initialized as a 16-bit word, so
the retained direct mesh writer now uses `header_word`. This ownership change
is score-neutral. The native two-face loop and checkerboard-shaped redundant
texture branches remain documented family structure, but are not retained yet:
the simple face loop regressed Wibo to 22.05%, while the fuller shared-family
loop reached 36.46% (37.47% with explicit terminal vertex branches), both below
the 40.81% pre-dispatch baseline. Direct orientation array indexing similarly
regressed to 21.09%; pointer aliases remain retained for compiler scheduling.

Post-cascade radius and vertex probes were also rejected. A float radius local
produced the visible dword comparison but regressed Wibo from 40.81% to 40.71%
and reintroduced one masked call mismatch. Explicit terminal/nonterminal vertex
branches regressed to 40.74%. The x87 radius temporary and collapsed vertex
selection remain until surrounding stack and mesh ownership moves again.

## 2026-07-17 constructor ABI closure

The Windows tail returns with `retn 0x24`, proving nine stack arguments after
the `Path*` receiver. The three world-initializer calls independently expose
variants 0/1/2, float scale, integer width, start/end X, curve segment count,
two surface textures, and the Windows-only cap texture. The iOS `BuildP`
symbol preserves the same portable prefix through the two surface textures.

Guarded Binary Ninja recreation and readback now recover that exact void member
ABI and the full owner flow (`kind = variant + 0x21`, width, samples, mesh, and
finalizer). This is analysis-only: focused Wibo remains 44.05% (615/679), with
33 clean operands and no unresolved or mismatched operands.
