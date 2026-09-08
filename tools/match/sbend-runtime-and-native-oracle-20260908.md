# S-bend runtime recovery and native comparison

S-bend now runs with recovered math, allocation, mesh, and texture-registry
dependencies. Its source build and a separately relocated original-code oracle
produce identical **18,204-byte serialized geometry** across four fixtures.
Both pass 60 behavioral checks. The source-only fault control corrupts one
face index and reliably fails one check with exit status one.

**Exact instruction matching remains open:** S-bend is still 91.10%,
578/579 instructions, prefix 443, with 39 clean native references. The native
oracle contains original machine code and receives no source-matching or
linked-reconstruction credit. Neither runtime success nor equal fixture data
changes that matching status.

## Source and link changes

Three S-bend identity calls now use the existing `tMatrix::Identity()` method
instead of the unimplemented compatibility free-function spelling. A recorded
reverse probe proves the native instruction stream, score, prefix, and all
39 reference identities are unchanged. The texture registry now uses the
shared C `report_errorf` declaration already used by the recovered reporter.
Its complete 79-instruction native body and four references remain exact.

The source integration group contains 45 functions representing 4,972 native
bytes: 44 exact functions and the partial S-bend builder. Its real dependencies
include `cRTextures::Init`, `cRTextures::Add`, `RTextCopy`, and `RTextCompStart`.
The registry uses its existing 500-entry backing type; there are no fabricated
texture callbacks or D3D resources. Each fixture registers two descriptors and
reuses them for all corresponding front/back faces.

`link_path_math.py` requires exact functions by default. Only an explicit
`--group sbend --diagnostic-sbend` permits this one partial function, and only
with a clean native reference audit. All 44 dependencies must still be exact.
The receipt reports the partial function, its ratio, and `normalized_exact:
false`. A negative build control confirms the ordinary strict mode rejects
S-bend and emits no success receipt.

## Fixtures and compared data

| Width | Height | Centered | Samples per bank | Vertices | Faces | Serialized bytes |
| ---: | ---: | :---: | ---: | ---: | ---: | ---: |
| 2 | 1 | yes | 4 | 15 | 16 | 2,868 |
| 4 | 2 | no | 7 | 40 | 56 | 6,496 |
| 2 | 0 | yes | 1 | 6 | 4 | 1,032 |
| 3 | 3 | yes | 10 | 44 | 60 | 7,808 |

All fixtures use a Z amplitude of 3. The last crosses the eight-row UV wrap.
Checks cover allocation counts and sizes, distinct primary/secondary banks,
start positions, the fixed secondary normal offset, terminal state, valid face
indices, opposite winding, UVs, texture reuse, terminal-row extrapolation,
mesh flags, and freeing all five tracked allocation banks.

The binary comparison includes every byte of both sample banks, all vertex
and colour data, face headers/indices/padding, and all UVs. Texture pointers
are serialized as their registry slot IDs so different executable addresses
cannot cause a false difference. The complete registered texture descriptors
(names, flags, and null payloads) are also compared, so equal slot IDs cannot
hide swapped texture bindings. It compares the complete serialized byte
strings directly; the SHA-256 below identifies the verified result:

```text
7367771bd5f4efb64a8b208ff48019e58220e0143db843fd9a67e8bb4e736934
```

## Native oracle integrity

`compare_sbend_native.py` reads the original 2,068-byte body at `0x42df00`.
Its original body SHA-256 is:

```text
301f050c8095cec1aa8cae9e0656f050acef902c0315f1661fb9a1b661a8b380
```

The tool reconstructs a small COFF oracle object from those original bytes.
It relocates only the 39 operands already covered by the clean native reference
audit, copies original floating-point constants, and uses the recovered helper
symbols for external calls and global data. It rejects unaccounted original
image addresses and unsupported relocation forms. All internal branches and
non-relocation instruction bytes are preserved.

Before linking, the oracle round-trips through the native matcher at 100%
with clean references. After linking, the tool independently checks its
non-relocation bytes, every resolved operand, and copied constants. It then
runs the original-code oracle and source executable under Wibo with the same
recovered dependencies and CRT. A comparison receipt is emitted only if both
programs pass their checks and every serialized geometry byte agrees.

This is an isolated native-routine comparison, not execution of the original
game process. It shares recovered helper implementations and the harness CRT;
it does not validate rendering, loaded image pixels, the game's constructor
lifecycle, arbitrary inputs, allocation failure, or overflow behavior. The
earlier path-constructor projection and BSS ownership limits still apply.

## Matching experiments retained as evidence

Fifteen bounded sweeps record 125 variants, plus the identity-call reverse
probe. No face-body variant was retained. The tested hypotheses cover:

- signedness and byte/row indexing of the face bank;
- winding continuations coupled to UV and loop-counter lifetimes;
- parity continuations outside the mesh loops;
- paired-face storage, cell snapshots, and fixed winding indices;
- real Path dependencies and the preceding Toad builder in the same unit,
  including an explicit-inline-only compiler control;
- nested mesh/texture-choice operation boundaries;
- face initialization through an inline method, explicit constructor, and
  placement construction;
- UV publication shared after the winding branch;
- branch-local face-index conversions;
- complete checkerboard arms with repeated geometry prefixes.

One reversed winding continuation reaches 579 instructions and 91.36%, but
moves the prefix from 443 to 405 and reverses the face-block layout; it is not
accepted as progress. Other controls are neutral or regress. These receipts
bound those hypotheses; they do not establish that the face tail is exhausted
or that the remaining differences are compiler-only.

The final three sweeps add 35 variants. Five common UV-tail forms regress to
58.68–78.04%. Nine branch-local unsigned/long/negated index forms are byte-neutral;
the three short-index controls regress and would additionally require native
range evidence before use because they truncate large indices. Eighteen forms
that duplicate some or all geometry into the checkerboard arms regress to
65.84–87.80%. All compile with 39 clean references. None changes the retained
source, and none supplies the missing native face-tail structure.

## Reproduce

```sh
UV_CACHE_DIR=/private/tmp/snail-decomp-uv uv run tools/match/compare_sbend_native.py \
  --out artifacts/match/sbend-comparison \
  --runtime-library /path/to/vc6/vc98/lib/msvcrt.lib
```

For source-only diagnostics, run `link_path_math.py --group sbend
--diagnostic-sbend --run` with the same runtime-library argument. Omit the
diagnostic flag to require an exact builder. Binaries, original-code oracle
objects, geometry dumps, maps, and detailed receipts remain under ignored
`artifacts/`; no original binary is added to the source tree.

Validation includes the four-fixture comparison, fault and strict-build
controls, full native status, strict experiment/spec audit, extern lint,
158 matching/report tests, source-bound progress refresh, and whitespace checks.
