# Dip orientation and counter source recovery

`initialize_dip_path_template_pair` improves from **75.96302003% to
85.78016910%**, with **646/655** candidate/native instructions instead of
**643/655**. All **37 aligned references** remain resolved. The entry prefix
stays **8 instructions / 22 bytes**; the function remains partial.

## Retained source

The native orientation branch reloads the primary sample bank before the
vector calculation, after `Normalize`, and again for the `Cross` receiver
and operands. It then performs the corresponding operations on the secondary
bank. The old inlined helper retained sample pointers across those calls,
including a secondary pointer obtained before primary orientation. Direct
member expressions recover the native ownership and call boundaries for both
banks. The initial-sample branch likewise reloads each bank for `RotIdentity`.

Both forward vectors use `next.position - previous.position`. The logical
curve counter and its phase copy are initialized before the curve guard,
matching the native preheader. The endpoint Z conversion occurs after its
X/Y writes instead of before X. These eight coupled changes preserve the
sample/control graph and recover native instruction structure; they do not
identify original variable names or a unique C++ spelling. The new orientation
block is formatted, with an identical reference-aware function fingerprint
before and after formatting.

Compiler flags, shared headers, function extent, reference mappings, matcher,
Windows six-argument ABI and existing mesh implementation are unchanged.
Both before/after candidates reserve the native **0x50-byte** local frame.

## Positional and encoded evidence

The receipt retains full native bytes, full unlinked candidate bytes, separate
complete target and candidate instruction arrays, source and COFF identities,
all 37 alignment diagnostics, and fresh region audits.

The entry prefix remains native **[0x41e440, 0x41e456)**, candidate **[0, 22)**,
with one strict positional reference and no hidden encoded differences.

The retained orientation, rotation and cursor-update region is native
**[0x41e6d0, 0x41e84b)**, candidate **[651, 1030)**: **91 instructions / 379
bytes**. Native instruction indices **[165, 256)** map to candidate
**[163, 254)**. Its six call references are verified by relative position,
operand slot/kind and destination identity. This is a region-relative proof,
not equality of whole-function instruction indices or offsets. The local
jump is checked against its paired destination within this region, and its
encoded displacement is retained.

Normalized instructions agree across this region, but **three SIB bytes
differ** despite equivalent address expressions:

| Native instruction | Native bytes | Candidate bytes |
|---|---|---|
| `0x41e791`, secondary right-vector address | `8d8c0758ffffff` | `8d8c3858ffffff` |
| `0x41e7f5`, secondary Normalize receiver | `8d8c1778ffffff` | `8d8c3a78ffffff` |
| `0x41e835`, secondary RotIdentity receiver | `8d8c0f58ffffff` | `8d8c3958ffffff` |

After masking only the six identity-verified external relocation fields,
376 of the 379 region bytes agree. **The region is not encoded-exact.** These
three bytes are not excluded or normalized away, and this region receives no
whole-function exact credit. The full 37-reference alignment is diagnostic
and remains separate from the positional region proofs.

The native extent is **2,400 bytes**, **[0x41e440, 0x41eda0)**. The comparison
covers **[0, 2390)**; **[2390, 2400)** is recognized terminal padding. There
are no unexplained or inline-data ranges. The first mismatch remains index 8,
where the candidate clears EBX instead of native EBP. Header/endpoint register
lifetimes, receiver setup, curve and delta counter scheduling, three SIB bytes,
and mesh/face details remain open. Neither whole-body equality nor linked
code, data, image or runtime equivalence is established.

## Bounded controls and reversals

The forward recipe contains **58 distinct full sources** from **60
observations**: 13 orientation controls, 21 counter/endpoint controls,
13 coupled controls, eight endpoint/loop controls, three delta controls,
one retained observation and one formatting control. Two observations repeat
an existing full source; those aliases are recorded separately. Every formal
control compiles with 37 clean references.

The logical-cursor control scores slightly higher (**85.80199540%**, 648
instructions) but also changes receiver setup and adds two instructions. It
is preserved as an unpromoted alternative; this commit retains the existing
physical cursor and the eight verified changes. Equal fuzzy scores do not
establish byte identity: each control's function fingerprint is retained.

Each independent reversal regresses from the retained 85.78016910%:

| Reversed change | Match |
|---|---:|
| Primary-bank reloads | 78.67590454% |
| Secondary-bank reloads | 78.76923077% |
| Rotation-bank reloads | 75.97851113% |
| Primary vector subtraction | 85.31898540% |
| Secondary vector subtraction | 85.31898540% |
| Curve counter outside guard | 79.26267281% |
| Phase counter outside guard | 85.62644120% |
| Endpoint Z lifetime | 85.62644120% |
| All eight together | 75.96302003% |

The all-reverse control exactly restores the baseline reference-aware function
fingerprint. Earlier generator errors removed a pointer declaration from the
wrong branch or referenced a block-local delta index outside its scope. Those
errors are retained as harness diagnostics, corrected before recording the
formal recipes, and are not negative evidence about native source forms.
These controls do not establish a compiler limit or exhaust other lifetimes.

## Validation and progress

All **785 scratch checks** pass with zero type findings. The strict ledger
has **2,494 records**, zero malformed/current strict errors and **13 active
recipes, all runnable**. Full public refresh, separate saved-evidence
validation and `git diff --check` pass.

Dip gains **235.61 fuzzy-weighted bytes**, reducing its gap from **576.89 to
341.28 bytes**. Core fuzzy rises **92.47% → 92.55%** and its rounded residual
gap decreases **17,149 → 16,914 bytes**. Exact count stays **602/662**.
Only Dip's public ratio changes; all exact classifications, target spans and
measurement identities remain unchanged. Public exact credit stays
**714 functions / 165,216 normalized bytes** and **703 / 150,289 encoded
bytes**; linked-code credit remains zero.

The receipt reads the actual COFF object from the completed public refresh,
checks its recorded hash, and binds it to the isolated proof through the
canonical source hash, complete extracted bytes and reference-aware function
fingerprint. Different COFF container hashes are preserved explicitly.
