# Tracked allocation, mesh banks, and path-node runtime checks

The recovered `GetNodes → CalcLengthZ → free_tracked_allocations_to_mark`
dependency chain now links and executes. The largest integration executable
contains 31 exact, reference-clean recovered functions, representing 2,150
native bytes. It verifies 44 named call relocations, 45 named data relocations,
and the two body/path callback-table entries after linking. These are
integration executables, not a reconstructed game executable; public linked
credit remains zero.

## Source boundary fixed

`report_errorf` uses the existing `/TC` profile and exports `_report_errorf`.
Its C++ callers previously declared independently mangled `void` or `int`
versions. Its `debug_report_stub` callee was also compiled as C++ while the C
reporter expected `_debug_report_stub`. `include/rdebug.h` now supplies the
shared C declarations for these definitions and the allocator/mesh callers.
This is a consistent ABI for the recovered source, not a claim that the
original executable retained C linkage names.

The allocator API and total-byte scalar declarations now live with the
existing `TrackedAllocationStack` owner. Mesh callers use those declarations.
The changes preserve native instructions and resolved references. A recorded
reverse probe restores the original allocator declaration: both versions are
48/48 instructions with seven clean native references, but replacing the
linked allocator object with the old one produces:

```text
error LNK2001: unresolved external symbol "void __cdecl report_errorf(char *,...)" (?report_errorf@@YAXPADZZ)
```

The corrected group links without unresolved symbols, forced linking, or
replacement implementations. The no-op reporting sink is its real recovered
two-instruction body at `0x449c00`.

## Runtime evidence

| Group | Recovered functions | Native bytes | Positive checks | Fault control |
| --- | ---: | ---: | ---: | --- |
| `allocator` | 11 | 643 | 20 | Corrupted payload fails one check |
| `mesh-storage` | 21 | 1,270 | 21 | Corrupted vertex copy fails one check |
| `path-nodes` | 31 | 2,150 | 15 | Corrupted row span fails one check |

The groups overlap; do not add their function or byte counts. All positive
runs exit zero. Each separate negative run exits one and reports exactly one
failed check. The existing `rmath` group's 23 checks remain available.

Allocator checks cover zero-initialized payloads, both guard words, the eight
guard bytes in accounting, zero-length allocation, raw-pointer size lookup,
the missing-pointer diagnostic path, bookmark unwinding, repeated unwinding,
reuse, and the actual variadic reporting chain. Allocation failures, stack
overflow, and out-of-order frees are not claimed safe or repaired.

Mesh checks use the recovered `cRObject` constructor and `Init`, then exercise
vertex/colour allocation, copying, facequad growth and shrinkage, normal banks,
texture-group capacity, edge banks, and freeing all tracked storage. Eight
live banks account for 676 bytes including guards. The fixture keeps the
native behavior: colours receive white RGB while their zeroed alpha remains
zero; smaller vertex requests retain the old count; a zero facequad request
clears only the active count; later edge requests preserve the first bank.

Path checks exercise two 168-byte samples in each of the two banks, consuming
688 guarded bytes. They check inverse matrices, row-span calculation,
positive/negative bend clamps, mirroring, terminal-sample initialization, mesh
flags, the one-sample case, and release through the real tracked allocator.
The zero-sample case is excluded: native `CalcLengthZ` writes the terminal
sample unconditionally.

## Storage and lifecycle limits

The native table words at `0x497334` and `0x4974fc` both contain `0x407b50`,
the existing recovered no-op callback. The harness supplies these real code
pointers under the current compatibility-table declarations. The driver reads
the original PE table words and verifies the final linked pointers. This does
not yet replace the shared C++ projection with compiler-generated vtables or
exercise virtual dispatch.

The current path constructor projection remains a method. Constructing the
C++ fixture calls the two recovered base constructors; explicitly exercising
the path initializer calls those bases again. The harness checks this observed
count of four and does not claim the game's constructor lifecycle is restored.
The mesh fixture uses zero-backed global storage, consistent with its native
tracked allocation precondition.

Allocator backing storage is provided separately for integration. The native
stack header at `0x5108c0` remains bounded to 12 bytes in the reference manifest.
The current 15,000-record projection's final unknown word reaches the adjacent
music-buffer address; no full BSS ownership claim or overlapping BN type was
introduced. The harness tests valid LIFO allocations, with growth only while
the replaced facequad bank is the top allocation. It does not normalize the
native non-LIFO behavior or implement an object destructor.

CRT imports come from the supplied VC6 `MSVCRT.LIB`; that is a harness runtime
choice, not proof of the original game's runtime linkage. Wibo executes the
test programs. No game entry point, renderer, D3D context, texture registry, or
path-template generator is run. Unnamed/local data relocations absent from
the link map are explicitly listed as unverified in each receipt.

## Reproduce

```sh
UV_CACHE_DIR=/private/tmp/snail-decomp-uv uv run tools/match/link_path_math.py \
  --group path-nodes --run --out artifacts/match/path-nodes-run \
  --runtime-library /path/to/vc6/vc98/lib/msvcrt.lib
```

Use `--group allocator`, `--group mesh-storage`, or `--group rmath` for the
other positive/negative pairs, with a separate output directory. The driver
requires exact native bodies and clean reference audits before linking,
checks emitted code/relocations after linking, and requires the expected
runtime summaries and exit statuses. Object files, executables, logs, maps,
source/object/runtime hashes, and receipts stay under ignored `artifacts/`.

Validation: full native status check, strict experiment/spec audit, extern
lint, 158 matching/report tests, source-bound progress refresh, and whitespace
checks. Native exact totals are unchanged by this declaration/storage work.
