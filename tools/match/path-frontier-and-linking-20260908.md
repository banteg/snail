# Path construction: matching and first link milestone

The live WIP triage selects Path.o: 32 partial functions cover 76,739 native
bytes and approximately 17,133 fuzzy-gap bytes. Game.o has about 4,783 gap
bytes and SubGame.o about 4,739. These are current source-object groupings,
not claims that every function came from a separately proven original object.
The path group has the largest gap and shared sample, vector and mesh
dependencies. Existing labels and experiment counts were not used to exclude
targets.

## Three retained face-loop improvements

| Builder | Before | After | Candidate / native instructions | Exact prefix | Clean references |
| --- | ---: | ---: | ---: | ---: | ---: |
| Turnunder | 56.78% | 57.23% | 662 / 687 | 6 | 45 |
| Toad | 65.46% | 66.82% | 663 / 663 | 89 | 33 |
| Invert | 83.13% | 84.46% | 603 / 600 | 120 | 35 |

Each retained change initializes the face column before the positive-width
guard, moves the row UV calculations inside that guard, and uses the guarded
post-tested column loop. The native boundaries are:

- Turnunder `0x428759..0x4287ae`;
- Toad `0x42d32b..0x42d380`;
- Invert `0x429898..0x4298ed`.

These ranges independently show column initialization, the width guard, signed
row modulo eight, and the two UV conversions, in that order. Whole-function
before/after comparisons localize the changes to the face preheaders and
conversion temporaries. Instruction counts, prefixes and reference quality
are unchanged. The combined gain is 72.92 fuzzy-weighted bytes; no additional
function becomes exact.

P and SlalomDouble are neutral under the same isolated control. Turnunder's
additional face-index lifetime is also neutral. Adding both native
checkerboard branches to its guarded loop regresses the whole function by
35.39 weighted bytes against the original baseline, while adding 13
instructions. Those variants were recorded but not retained. This does not
establish a common original mesh helper or settle the remaining checkerboard
control-flow differences.

The recipes are `face-loop-and-parity-ownership-20260908.json` in Turnunder
and `face-column-scope-20260908.json` in the other four scratch directories.
Their complete evaluations are recorded in the corresponding
`experiments.jsonl` files. Reverse source probes independently reproduce all
three original code-and-relocation hashes.

## A real link blocker, then a four-function link

`CalcLengthZ` called the pointer-parameter compatibility declaration
`tVector::cross_vectors`, while the recovered implementation defines the
authored const-reference method `tVector::Cross`. Both names resolve to
Windows `0x44cd40` in the matcher, so the individual scratch was exact even
though the object files could not link to one another.

The original four-object link fails with exactly this unresolved external:

```text
?cross_vectors@tVector@@QAEXPBU1@0@Z
```

Switching the caller to `Cross` and passing the two vector lvalues removes
that undefined symbol. The complete function remains 113/113 instructions,
with all nine native references clean. No wrapper, linker alias, fabricated
symbol, original-image code, or forced unresolved-symbol option is used.
The group now links:

| Recovered definition | Native address | Body bytes |
| --- | --- | ---: |
| `cRPath::CalcLengthZ()` | `0x42c600` | 363 |
| `tVector::Cross(const tVector&, const tVector&)` | `0x44cd40` | 131 |
| `tVector::Dot(const tVector&)` | `0x44cb70` | 27 |
| `tMatrix::Invert(const tMatrix&)` | `0x44d330` | 157 |

The 678 recovered body bytes are compiled as separate canonical scratches.
The local VC6 linker produces a DLL container with `/noentry /nodefaultlib
/opt:noref`, using an explicitly supplied VC6 `MSVCRT.LIB` for runtime support.
The link has no unresolved symbols. Verification reads the resulting PE and
map, checks every function byte outside recorded relocation slots, and checks
all six REL32 destinations, including the Cross edge and runtime calls.

This is a source-object link feasibility check. It has no entry point, has
not been executed, does not reconstruct original global layout or audit every
linked data relocation, and does not receive public linked credit. Its runtime
imports are `MSVCRT.dll!__dllonexit`, `_onexit`, and `_ftol`; using this import
library does not claim it was the game's original runtime linkage.

Reproduce with an existing runtime import library:

```sh
UV_CACHE_DIR=/private/tmp/snail-decomp-uv uv run tools/match/link_path_math.py \
  --runtime-library /path/to/vc6/MSVCRT.LIB
```

The default output is ignored `artifacts/match/path-math/`. The receipt records
source/object identities, exact native checks, linker and runtime-library
hashes, linked addresses, imports, and verified call edges. The reference
MSVCRT.LIB used in this pass has SHA-256
`3efc3ddf045a459a2b6403f0b821be2cb7c316ffca67dddddb346cea7a9e4f63`.

## Next dependency boundaries

1. Extend the authored math API migration where complete-function checks
   permit it. A recorded Turnunder control replaces both `set_matrix_identity`
   and `cross_vectors` with the existing authored methods and is metric-neutral;
   it remains a probe. Other compatibility calls still prevent general linkage.
2. Close the trigonometry tables' storage ownership. Their exact initializer
   currently declares one-float-before array bases separately from the lookup
   helpers' canonical arrays. These declarations are address-compatible in the
   matcher but do not yet define one coherent linked storage owner.
3. Close `GetNodes`' tracked allocator and the mesh vertex/face allocation and
   texture-registry dependencies. Those are the next boundaries between this
   math group and an actual path-builder integration harness.
4. Continue the remaining curve and face-body source recovery with complete
   function controls. A local gain does not justify sharing a mesh helper
   across the family; earlier complete-body regressions remain relevant.
