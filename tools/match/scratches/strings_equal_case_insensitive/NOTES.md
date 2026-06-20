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

Focused Wibo result after the peeled-loop rewrite: 66.02%, 53/50
candidate/target instructions, 5/50 prefix, no masked operands. The source now
keeps the prefix-style semantics (`right` reaching NUL is success) while
avoiding the old pointer-delta loop shape.

Remaining residual: native loads the initial right/left raw bytes straight into
`dl`/`bl`, copies them to `cl`/`al`, and tests left then right. The current
source still has VC6 load the fold lanes first (`cl`/`al`), then copy to
`dl`/`bl`, with the same recovered semantics but different byte-lane ordering.

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
