# Preserving VC6 observations for Snail

`trace.py` adapts the sibling Crimson project's C2 observer to Snail's existing
compiler driver, source validation, function boundaries and native matcher.
Crimson must be checked out at `../crimson`, including its generalized
`src/crimson/match_c2.py`, `match_c2_replay.py`, `tools/match/c2` assets, Wibo,
compiler and generated Kernel32 import providers. The adapter neither edits
Crimson nor adds it as a package dependency.

```sh
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run tools/match/c2/trace.py \
  tools/match/scratches/initialize_slalomdouble_path_template_pair \
  --passes-only --out /private/tmp/snail-slalom-trace
```

The output directory must be new. Omit `--passes-only` to include the repeated
allocation hooks; the SlalomDouble pilot produced 382 events and about 900 MB
of raw observations. `--early-addresses` instead selects 12 earlier expression
passes around `C2+0xfc45`. This additional profile was verified on both retained
SlalomDouble sources. The original Crimson reader and comparator are available
as `c2.read_verified(path)`, `c2.summarize(events, line)` and
`c2.compare(left_events, right_events)` from this module.

Only the pinned `msvc6.5` bundle is supported. The adapter checks that both
projects have identical CL, C1, C1XX, C2, MSPDB and LINK binaries. The upstream
profile checks C2 SHA-256 before installing hooks; each instrumented CALL must
have the expected opcode and destination. The installed compiler stays intact.
Translation-unit members are rejected until their full source can be frozen.

Normal, captured, standalone-replayed and observed **whole COFF objects** must
agree except for timestamp bytes 4–7. Every object also passes Snail's matcher
with identical metrics. Withholding the expression stream must reject replay
without an object. The adapter verifies the frozen source, checks Snail's
content-based dependency digest before/after, then records its own receipt.
This is optional diagnostic tooling and earns no matching credit.

## SlalomDouble: the receiver swap happens before allocation

Reproduce the five preserving runs and their comparison:

```sh
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run tools/match/c2/receivers.py \
  --out /private/tmp/snail-slalom-receivers
```

[results.json](results.json) records both sources at the ordinary and earlier
pass boundaries plus a separate baseline repeat. The control moves the
existing departure position/secondary setup into an inline operation. It fixes
the departure receiver but loses the lead-in receiver. Both remain partial:
683/683 instructions, 99.707174% normalized agreement, 45 clean references;
matching prefixes are 84 and 42 respectively. Neither is byte-exact.
The harness also requires a different compiler profile and an incorrect hook
destination to fail without a success manifest.

All four Identity receiver additions enter `C2+0xfc45` with the same operand
kind sequence: bank memory (6), offset symbol (2), bank-address symbol (2).
After this pass the second addition is offset-first in the baseline, while the
fourth is offset-first in the control. The receiver CALL identities survive the
boundary, and the receipt follows each ADD result through its COPY to its CALL.
The distinction is therefore already decided before lowering and allocation.

The relevant packed costs after that pass are:

| Source / receiver | Bank cost | Offset cost | First operand |
| --- | --- | --- | --- |
| Baseline lead secondary | `0x10007` | `0x10160` | Offset |
| Baseline departure secondary | `0x1c007` | `0x101a0` | Bank |
| Control lead secondary | `0x1e007` | `0x10160` | Bank |
| Control departure secondary | `0x10007` | `0x101a0` | Offset |

[compiler-ordering.json](compiler-ordering.json) retains read-only Binary Ninja
excerpts and the comparator's literal instructions from the pinned backend.
`C2+0xd90c` computes operand costs at `+0xc`, then sorts commutative operands
through `0xf584` using comparator `0xf6ae`. That comparator orders the packed
32-bit values in descending unsigned order. The upper bits carry expression
cost information; `0xda9a` combines them with the low 16-bit value from
`0xdb59`, which incorporates symbol-derived hashes. Thus a distant change in
inline symbol ownership can change the tie-breaking order of equally cheap
address operands. The observed costs predict all four orders above.

This identifies the candidate compiler mechanism, not the unavailable original
source or its compiler history. Equal trace signatures do not prove semantic
equivalence. Raw arena addresses are event-local, not stable value identities.
For this C++ function, the recorded line words are relative to the function
body and inlined operations inherit their callsite line; they are not direct
physical line numbers in `scratch.cpp`.

The receiver reproducer uses the frozen pre-match source from the
[decomposition receipt](../slalomdouble-decomposition-20260913.json), so these
observations remain reproducible after the live scratch changes.

The subsequent [SlalomDouble decomposition](../slalomdouble-decomposition-20260913.md)
retained a regressed shared-bank control, then recovered the curved primary
owner and the departure primary read. It closes the complete native body.
Compiler observations still earn no acceptance credit; the result has a
separate positional reference, branch and literal-byte proof.

## Turnover: interpolation read and destination ordering

[Turnover's follow-up](../turnover-address-order-20260922.md) traces the bank
borrow that fixed one interpolation SIB byte while leaving its destination
byte unmatched. `turnover.py` verifies the saved expression chains and 58
rejected source controls; `--out` reproduces both preserving compiler runs.
Logical indexing can recover the last local byte while regressing other code,
so Turnover remains a partial encoded match.

## Heightmap: preserving the converted column coordinate

[`heightmap.py`](heightmap.py) follows the column conversion and row multiply
through entry/return hooks on `C2+0x11afa`. With separate scalar locals, this
pass removes the column assignment and moves its conversion after the row
multiply. A local coordinate pair retains the assignment and the native order.
Both observations preserve the complete ordinary COFF object, with only its
timestamp ignored. Run `uv run tools/match/c2/heightmap.py --out <new-directory>`
to repeat them. The [source and byte audit](../heightmap-coordinates-20260922.md)
records the subsequent 97.25% partial; the compiler observation earns no exact
credit and does not establish an original type name.

## LoopOut: the two interpolation indices bound bank-only changes

[`loopout.py`](loopout.py) checks and reproduces two preserving observations.
The [complete evidence](../loopout-address-order-20260922.md) follows both
address and value chains, independently audits both 2,615-byte bodies and
retains 76 non-matching source controls. In each captured tree, native's two
address orders would require one bank cost above the endpoint cost and below
the smaller destination cost. Changing only that bank cannot satisfy both.
This directs further source work toward the indices or separate ownership;
it does not establish source exhaustion. Canonical LoopOut remains unchanged.

## Rotation: the local allocator's eax/ecx/edx cursor

[`rotation.py`](rotation.py) traces every call to C2's local register selector
and reports the rotation cursor, the path and the chosen register for each
temporary. It also shows whether the instruction survives and which register
native uses at the aligned instruction. The summary lists where native's
implied cursor moves away from ours. The selector rule and which source
constructs take or skip a slot are in
[register-rotation.md](register-rotation.md).

```sh
uv run tools/match/c2/rotation.py update_subgame --source overlay.cpp
```

## Global allocation: callee-saved register choice

[`globalregs.py`](globalregs.py) traces C2's global allocator. For each live
range it lists the priority and tie key, the allowed registers, the cost table
the chooser builds, the register chosen and the register native implies. It
also re-derives every choice from the rule in
[global-allocation.md](global-allocation.md), which covers weights, queue
order, the esi/edi/ebx/ebp order and neighbour penalties.

```sh
uv run tools/match/c2/globalregs.py set_snail_weapon --source overlay.cpp
```

## Related compiler notes (crimson)

The sibling Crimson project keeps further C2 notes in
`../crimson/tools/match/c2/compiler/` (x87 allocation and spills, forward
propagation and FROUND, frame packing, layout, register allocation corrections),
with tracers in `../crimson/scripts/c2/`.
