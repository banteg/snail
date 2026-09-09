# Path compiler context and ownership, 2026-09-09

The vertex reduction now isolates the terminal branch/expression as the part
of the preceding loop that changes the later face-address calculation. No
tested reduction produces the native texture-call continuation, and no
S-bend source change is retained. The [receipt](path-context-and-ownership-20260909.json)
pins the native inventory, diagnostic inputs and observed instruction shapes.

## Find an existing positive source control

`scan_call_continuations.py` scans all call targets, extending the previous
texture-only search to the executable's 2,286 inventory owners and all 785
canonical source functions. It rebuilds stale source objects and checks
source/config identities during and after the scan. Native image, manifest,
inventory, tool and dependency hashes accompany the result.

The full inventory has 2,356 completely decoded ranges and two incomplete
ranges. Its positives are still the same **55 unique branch sites in 28 path
builders**. The source corpus has 782 completely decoded functions and three
incomplete bodies; none produces the recognized shape. Incomplete ranges are
listed explicitly, and no absence or compiler-limitation claim follows from
these finite controls.

The recognizer now requires actual instruction adjacency in the alternate
`mov`/`push`/`jmp` block and in the common receiver/call block. Flattening
discontiguous inventory ranges cannot synthesize a match from mnemonic order
alone. Tests include a valid backward continuation after `ret`, both physical
gap cases, a mismatched pushed register, an incomplete tail, and a source
change during compilation.

## Separate vertex-loop factors

The eleven new `vertex_factor_` controls derive from the same member-mesh
reduction and deliberately store only X. They are compiler diagnostics, not
complete mesh implementations or runtime fixtures.

| Reduced vertex phase | Candidate instructions | Face-address stride |
| --- | ---: | --- |
| Original terminal branch, vector expressions | 240 | Between winding test and branch |
| Scalar expressions, typed sample addressing, or float lateral | 240 | Between winding test and branch |
| Terminal branch removed, ordinary rows only | 236 | Inside both winding branches |
| Terminal branch removed, extra row retained | 236 | Inside both winding branches |
| Terminal branch retained in source, ordinary-row bound | 240 | Between winding test and branch |

Both vector and scalar forms reproduce the last three rows. Removing the
terminal branch changes placement even when the extra iteration remains;
changing only the row bound does not. This narrows the dependency beyond the
previous whole-vertex-loop experiment. It does not yet separate terminal
arithmetic from branch formation or explain the native continuation.
All eleven controls have zero strict call-continuation matches.

The whole-function destination-lifetime replay is separately meaningful:
earlier probes predated the recovered nested endpoint expression. All 15
single and paired early-destination, direct-pointer and direct-array forms
now compile to the baseline fingerprint. S-bend stays **91.0977%, 578/579
instructions, a 443-instruction prefix and 39 clean references**. The complete
grid is recorded in `recovered-terminal-destination-lifetimes-20260909.json`
and the append-only experiment ledger.

## Gameplay ownership replay

The gameplay ownership replays also remain partial. Initializer vapour-owner
references clear its two unaudited operands but regress the whole function;
the post-firing player-state variants likewise trade away instruction shape.
The runtime track's current parcel-source replay improves 75.7406% to
77.7555% and clears all four unaudited entries, but drops the exact prefix
from 76 to 9. A further eleven-case setup-lifetime grid does not restore it.
No gameplay source change from these experiments is retained. Their ledgers,
per-function notes and the runtime-track results in the tracked receipt retain
the tradeoffs for subsequent producer/consumer work.

## Reproduce

```sh
uv run tools/match/scan_call_continuations.py --include-sources \
  --out artifacts/match/call-continuations/receipt.json
uv run tools/match/probe_face_emission_context.py \
  --variant-prefix vertex_factor_ --out artifacts/match/vertex-factors
uv run snail match mutate initialize_sbend_path_template_pair \
  --spec tools/match/scratches/initialize_sbend_path_template_pair/recovered-terminal-destination-lifetimes-20260909.json \
  --max-changes 2 --max-variants 15 --json
```

The next source hypothesis must explain the terminal branch's effect on the
later face loop and generate the native continuation before transfer to a
second builder can establish a shared recovery. These controls do not close
that work or justify a compiler ceiling.
