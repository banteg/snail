# Verified DDK compiler control and dependency tracking

The genuine build-9178 compiler does not improve the current path sources.
It reduces S-bend from 91.10% to 57.19%, changes its stack frame from 0x48
to 0x4c, and differs from the first instruction. The default VC6 profile is
retained. The test also exposed and repaired a cache dependency omission.

## Compiler identity

The [Rich component table](https://github.com/dishather/richprint/blob/master/comp_id.txt)
identifies build 9178 with the Windows XP SP1 DDK. The
[preserved DDK 5.1.2600.1106 package](https://github.com/KunYi/WDK_DDKArchive/releases/tag/DDK_5.1.2600.1106)
contains the expected servicing combination:

| Component | PE file version | SHA-256 |
| --- | --- | --- |
| CL.EXE | 13.0.9176.0 | `a99939878f19e0a6404e349824c163de8188a967a22e82867af935c040d1032c` |
| C1.DLL | 13.0.9176.0 | `bb7ffe0357f4fca0d0607ac9f8a2b2df3dacbf1cf821eb502e1e5a323e5c66dd` |
| C1XX.DLL | 13.0.9176.0 | `3a0cdfbccb2df87487da1d6c9e83ce781f7ef4eae025da35ec405cfebe7831a4` |
| C2.DLL | 13.0.9178.0 | `99860f0499e637520df383ffac0845cf027cbecb82c9980844c76e1698579add` |
| MSPDB70.DLL | 7.0.9210.0 | `636c6d5a7a57664796adc835203b905f98f4f3c64d8a4107d4e68efbe33b6795` |
| MSVCR70.DLL | 7.0.9210.0 | `c0116e144dfe70bdc4b617240029c182875461d15de2ec5d79a9b1b94980b259` |

Archive SHA-256:
`32ff9a3936911f5ba6a2edc77eb7dc2ccf01b09eb79c86ab6a72ee6fbd438bee`.
The compiler builds a C++ identity function under Wibo and emits COFF
`@comp.id = 0x001d23da`: product 29, build 9178, exactly the component ID
in the original executable. This verifies the object producer separately from
the package name and PE version strings. Hash pinning identifies the inspected
preservation artifact, not a Microsoft signature check.

The extractor uses original CAB/INF mappings and installs ten binaries plus
355 CRT headers as `msvc7.0-ddk9178`. It does not run the DDK installer or mix
VC6 headers into this profile. The proprietary files and the 365-file
`provenance.json` stay ignored. An initial probe without the CRT headers failed
on `stddef.h`; that setup failure remains in the ledger and was repaired before
the comparisons below.

## Unchanged-source controls

All use `/O2 /G5 /W3`. Each probe compiles its baseline and an identical source
overlay. The seven controls were repeated after the dependency fix with the
same results.

| Function | VC6 default | DDK 9178 | DDK / native instructions | DDK prefix | DDK references |
| --- | ---: | ---: | ---: | ---: | --- |
| S-bend | 91.10% | 57.19% | 582 / 579 | 0 | 39 clean |
| Snake | 88.19% | 67.89% | 656 / 652 | 0 | 40 clean |
| Sweep | 85.58% | 65.39% | 654 / 652 | 0 | 37 clean |
| Slalom | 80.66% | 55.62% | 692 / 696 | 0 | 39 clean, 2 unaudited |
| Twister | 86.94% | 67.16% | 678 / 677 | 1 | 49 clean |
| CalcLengthZ | 100.00% | 94.22% | 112 / 113 | 55 | 9 clean |
| GetNodes | 100.00% | 100.00% | 23 / 23 | 23 | 4 clean |

Slalom is not a clean-reference candidate. CalcLengthZ independently changes
address allocation and x87 comparison lowering, including `test ah, 1; je`
becoming `test ah, 5; jp`. The effects extend beyond the unresolved mesh tail.

Two further S-bend controls test VC6 processor scheduling: `/G6` gives 75.56%,
583 instructions and prefix 2; `/GB` produces the same extracted code identity
as default `/G5`. These controls do not identify the original flags.

## Library attribution narrows the Rich-header hypothesis

The pinned DirectX 8.1 D3DX8 archive has 134 C++ objects carrying `0x001d23da`.
Existing native full-body attribution has single compatible archive members
for 74 distinct objects, of which 66 carry that C++ ID. Following unique
external-symbol dependencies of those whole members adds `cd3dxresource.obj`,
`init.obj` and `ssefasttable.obj`. This closure contains exactly **67 build-9178
C++ objects**, matching the executable's aggregate count, and one of its four
build-9178 C contributions.

[The coverage receipt](../../analysis/ownership/rich-d3dx8-coverage.json) records
member IDs, representative native anchors and dependency edges. This is a
compatible explanation, not proof of the original linker selection: closure
includes references from unmatched or possibly discarded member functions.
It does not assign a compiler to Path.o. Together with the failed path controls,
it weakens the hypothesis that this Rich population explains the path mismatch.

## Cache correction

The old build key and experiment dependency graph included `CL.EXE` and quoted
project headers, but omitted compiler DLLs and angle-bracket headers. Replacing
a backend with an unchanged driver could reuse a stale object and retain an
incorrect dependency receipt.

The graph now includes bundled compiler DLLs and literal transitive headers
from compiler and project include directories. It follows `cl.sh` search order,
distinguishes quoted and angle-bracket includes, and caches resolved edges
separately for each compiler profile. Conditional literal includes are tracked
conservatively without evaluating the preprocessor.

Regression tests change only C2, C1XX, or a used compiler header and prove that
the cached object and dependency digest become stale while CL remains unchanged.
A shared-resolver test checks two profiles and include precedence. Existing
records remain historical evidence; expanded dependency coverage changes their
epochs without implying their machine code changed. There is no evidence that
the old omission affected the fresh DDK exports.

Validation: 177 focused tests pass; full default native checks retain 593/662
core and 114/120 platform proof-grade functions; strict experiment/spec audit
reports zero errors. New extraction/coverage scripts pass Ruff. Existing matcher
and test files retain their pre-existing lint findings; the changes add none.

## Source interaction controls

After the compiler controls, 45 further variants test whether earlier loop
lifetimes change the unresolved mesh tail. The S-bend recipe combines typed
sample, delta and vertex indexing with branch-local pointer/reference and
loop-local reference face owners (31 variants). Sweep and Snake each test the
seven vertex-index/face-owner combinations against their own surrounding code.

| Builder | Baseline | Best tested variant | Prefix | Result |
| --- | ---: | ---: | ---: | --- |
| S-bend | 91.10% | 91.10%, typed delta indexing only | 443 | Same normalized assembly, different raw/relocation fingerprint |
| Sweep | 85.58% | 84.97%, typed vertex indexing only | 32 | Rejected |
| Snake | 88.19% | 87.58%, typed vertex indexing only | 387 | Rejected |

All 45 compile and retain clean reference audits. Branch pointer and reference
forms also produce identical code to each other; neither improves any builder.
The neutral delta control has a different conservative code identity and is
not claimed byte-identical. Its diagnostic export reproduces the evaluated
fingerprint and its normalized assembly matches the default control exactly.
No source changes are retained. These results reject the tested interactions,
not other source shapes or the possibility of exact recovery. The native
branch-local face-address formation, texture-call continuations and UV register
allocation remain unresolved.

The complete recipes are tracked beside their append-only receipts:

- [S-bend phase and face owners](scratches/initialize_sbend_path_template_pair/phase-index-face-owner-coupling-20260908.json)
- [Sweep vertex and face owners](scratches/initialize_sweep_path_template_pair/vertex-index-face-owner-coupling-20260908.json)
- [Snake vertex and face owners](scratches/initialize_snake_path_template_pair/vertex-index-face-owner-coupling-20260908.json)

## Reproduce

After downloading the pinned release asset:

```sh
UV_CACHE_DIR=/private/tmp/snail-decomp-uv uv run tools/match/extract_xp_sp1_ddk.py /path/to/Microsoft.Windows.XP.DDK.5.1.2600.1106.7z
UV_CACHE_DIR=/private/tmp/snail-decomp-uv uv run snail match probe initialize_sbend_path_template_pair --source tools/match/scratches/initialize_sbend_path_template_pair/scratch.cpp --compiler msvc7.0-ddk9178 --json
UV_CACHE_DIR=/private/tmp/snail-decomp-uv uv run --no-project --python ../crimson/.venv/bin/python tools/ownership/trace_rich_compiler_members.py
```

The last command uses the pinned D3DX8 archive and sibling Crimson COFF parser
from the existing ownership workflow. Detailed exports remain under ignored
`artifacts/match/ddk9178-*` directories.
