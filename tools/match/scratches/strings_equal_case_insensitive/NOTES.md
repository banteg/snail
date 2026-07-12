# strings_equal_case_insensitive

Initial scratch for the shared ASCII case-insensitive equality helper at
`0x431dc0`.

Recovered relationships:

- Used by `get_or_create_texture_ref` and `load_object_definition`.
- Converts only lowercase ASCII `a..z` to uppercase by subtracting `0x20`; it
  is not locale aware and does not call CRT string helpers.
- Returns whether the right cursor reached the null terminator after the
  comparison loop. This means prefix-style matches can succeed when `right`
  ends at the current comparison point.

Focused Wibo result after the left-byte loop rewrite: 84.00%, 50/50
candidate/target instructions, 5/50 prefix, no masked operands. The source now
keeps the prefix-style semantics (`right` reaching NUL is success), tests the
left byte as the loop gate, and preserves the native explicit boolean tail.

Remaining residual: native loads the initial right/left raw bytes straight into
`dl`/`bl`, copies them to `cl`/`al`, and repeats that raw-before-fold lane
ownership in the loop. The current source still has VC6 load the fold lanes
first (`cl`/`al`), then copy to `dl`/`bl`, with the same recovered semantics
but different byte-lane ordering.

2026-06-20 caller-shape pass: two direct decompiler-shaped rewrites were tested
and rejected. Explicit `left_cursor`/`right_cursor` locals made VC6 collapse the
two pointers into a pointer-delta loop and regressed to 29.13%. A direct
IDA-style `do` loop over the original arguments also regressed to 35.85% by
materializing `sub 0x20` lanes and extra tests. Keep the peeled-loop source
until a source shape preserves the native `dl`/`bl` raw-byte lanes without
introducing the pointer-delta form.

2026-06-20 larger-helper pass: retesting the native left-byte outer gate with
raw-byte locals declared before folded-byte locals regressed to 36.19% by
switching to `sub 0x20` lanes and extra zero tests. Changing only the outer gate
was score-neutral at 66.02% and merely swapped the scratch raw-byte lane roles,
so the retained source stays on the existing peeled-loop spelling.

2026-06-21 resource-string family pass: the same byte-lane hypothesis was
retested with the current parser-neighborhood context and still did not hold.
Declaring raw right/left byte locals before folded byte locals again regressed
to 36.19% by changing the fold lanes to `sub 0x20` temporaries. Moving the
outer guard to the left byte and making the right byte the loop condition
regressed further to 36.00% by swapping the active fold/raw lanes away from the
native `dl`/`bl` story. The retained 66.02% peeled-loop source remains the best
observed form; remaining debt is byte-register allocation and test order, not a
missing semantic branch.

2026-06-20 parser/string helper follow-up: after proving the adjacent signed
integer parser, the full decompiler guard spelling was retested in the peeled
local style: outer gate on the left byte, loop gate on the right byte, and an
explicit folded mismatch break. Focused Wibo stayed neutral at 66.02% and only
swapped the scratch raw/fold byte lanes (`bl`/`dl`) without approaching the
native initial `dl`/`bl` ownership. Keep the current peeled-loop source; the
exact `strings_equal_case_insensitive_path` increment-before-fold style is not
evidence for changing this prefix-style comparator.

2026-06-20 larger helper sweep: focused Wibo still reports 66.02%, 53/50
candidate/target instructions, 5/50 prefix, and no masked operands. A stricter
IDA-shaped prefix comparator with explicit left/right cursor locals regressed
to 29.09% by reintroducing the pointer-delta and stack-byte family. Naming the
tail byte before `return tail == 0` was codegen-neutral and kept the same
early-zeroed boolean epilogue. The retained peeled-loop source is still the
best observed shape; the residual is byte-register allocation/test scheduling,
not missing prefix-comparison control flow.

2026-06-21 byte-lane/control-flow pass: promoting the source to a plain
`while (left_value != 0)` loop with explicit `right_value == 0` and folded
mismatch breaks recovered the native branch topology and improved focused Wibo
from 66.02% to 77.23%. Spelling the tail as explicit true/false returns
recovered instruction-count parity and improved the score to 84.00%. Retested
raw-byte-first declarations, declaration/reload order matrices, `register`
qualifiers, signed/const argument spellings, and return types; none improved
the remaining lane allocation, and raw-byte-first forms still regress by
switching the fold math to the worse `sub 0x20` family. Remaining debt is the
raw-before-fold byte-register allocation only.

2026-06-21 byte-lane retry: raw-byte-first reloads, right-fold-first ordering,
left-then-right reloads, unsigned byte locals, volatile raw loads, a
macro-style fold expression, and a fold-at-top `for (;;)` loop were retested.
All raw-first source shapes still fall into the bad 31-43% codegen family with
extra instructions or different fold arithmetic. `register` annotations are
neutral at 84.00%. Keep the current folded-byte-first source despite the
remaining `dl`/`bl` raw-lane ownership mismatch.

## 2026-07-12 authored RString provenance

iOS preserves this global as `Rstrcmp(char*, char*)` in `RString.o`, and the
Android body independently confirms the same ASCII-only fold and asymmetric
termination rule: matching succeeds when the right argument reaches NUL, even
if the left argument continues. This rules out both CRT `stricmp` ownership and
the later strict path comparator at `0x44e6c0`.

The provenance does not explain Windows' remaining raw/fold byte-register
allocation, so focused matching stays honestly pinned at 84.00%, 50/50
instructions. No source change is made to chase that compiler-only residual.
