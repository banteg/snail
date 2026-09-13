# SlalomDouble: closing independent constraints

SlalomDouble now matches all 683 instructions and the complete 2,536-byte
encoded body. The proof verifies 45 reference fields at identical positions,
29 literal local branches, and all ordinary instruction bytes. The native
extent remains `0x425050..0x425a40`; only its eight terminal NOP bytes are
excluded from the code body.

The successful sequence deliberately retained a lower-scoring intermediate:

| Stage | Normalized agreement | Constraint resolved | Remaining evidence |
| --- | ---: | --- | --- |
| Previous source | 99.7072% | Existing reconstruction | Departure receiver and 17 aligned SIB bytes |
| Shared banks in flat phases | 95.6777% | Both flat loops, including literal encodings | Curved receiver, cleanup and address ordering |
| Shared banks through curve | 96.2637% | Secondary curve receiver and cleanup | Primary curve receiver and 15 aligned SIB bytes |
| Primary reference at curved sample initialization | 100% | All receivers and curve encodings | One departure SIB byte at body offset 381 |
| Path-owned departure primary read | 100% | Final ordinary encoding | Complete body exact |

Most normalized differences in the shared-bank stage were branch labels shifted
by one missing instruction. A separate diagnostic alignment checked that all
29 branches still targeted their corresponding instructions, and compared
ordinary bytes rather than treating normalized address expressions as exact.
That alignment explains the partial controls; final acceptance uses identical
instruction and byte positions without alignment.

The retained source shares a reference to the secondary bank across sample
phases. It binds the primary reference when the curved sample is initialized,
after calculating the falloff terms. The departure initializer reads the
primary sample through its Path owner. These are references to bank fields,
not cached sample pointers: the original reloads across Identity, Sin, Cos,
Normalize and Cross remain intact.

The one-byte control and final source have identical normalized disassembly.
Only body byte 381 changes, from `0x0f` to native `0x39`, selecting the native
base/index encoding of the primary center read after departure Identity.
Preserving C2 traces show its ADD operands changing from offset-first
(`0x101c0` versus `0x10007`) to bank-first (`0x14007` versus `0x101c0`).
The traces preserve whole COFF objects and never modify compiler decisions.
This supports the candidate compiler mechanism, not a claim to know the
original source spelling.

Moving the curve reference earlier, preserving the broad primary reference,
or merely changing helper parameter pointer syntax does not close the body.
Both Path pointer and Path reference departure owners do; the retained helper
specializes the flat secondary height and removes the unused conditional.

The [JSON receipt](slalomdouble-decomposition-20260913.json) keeps the frozen
baseline, replayable source edits, intermediate region diagnostics, independent
full-byte proofs, forward/reverse native probes and preserving compiler traces.
Reverting the source restores the old code hash. The final source leaves
compiler flags, shared headers, references, function boundaries and matching
policy unchanged.

Validation passes all 785 scratches, 1,140 tests, strict experiment/spec checks,
extern lint, and the exact-reference audit. All 44 source reconstructions
validate, and a fresh retained-source replay reproduces its code hash and
matching dimensions. The public report adds only SlalomDouble as a match;
other function changes are COFF timestamps. There are now 15/29 normalized
template-pair matches, including 13 complete byte-exact bodies. Core status is
616/662 matched.

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/slalomdouble-decomposition-20260913.json \
  --function initialize_slalomdouble_path_template_pair \
  --batch stages --label retained --replay
```
