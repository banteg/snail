# Mobile lineage and Windows-first multi-version work

**Use Wii, Android, and iPhone as additional constraints on the Windows source
recovery. Start a shared reference effort now; defer a complete second matching
target.** The fresh binary inspection below found useful evidence missing from
the active mobile decompile corpus. A full Wii rebuild is not required to use it.

The user's central hypothesis is sound: independent code generators preserve
different clues about the same C++. Intersect their constraints on expression
order, comparisons, types, ownership, and call structure. The intersection gets
more useful after separating actual source revisions from compiler and ABI
differences. It does not necessarily identify one unique original spelling.

## Fresh inspection

The [receipt](receipt.json) comes from direct ELF/Mach-O header, symbol-table,
relocation, and byte inspection. The mobile decompile indexes and old Windows
crosswalk are **not inputs** to that receipt. Additional Ghidra experiments used
new isolated projects for Android ARMv5, Android ARMv7, and iPhone 1.9 ARMv6.
The prior Wii RTTI addresses were discovery seeds; every recorded name pointer,
base list, and offset was checked again against the DOL.

| Retained build | Freshly observed evidence | Best role |
|---|---|---|
| Android `armeabi-v7a` | 1,082 named C++ function symbols; 42 named vtables; no named RTTI objects or DWARF sections; GCC 4.4.0 comments | Broad named gameplay coverage and hardware floating-point code |
| Android `armeabi` | The same 1,082 C++ symbols; software floating-point helpers in the sampled arithmetic | Additional code-generation view from the same APK |
| iPhone 1.5.0 ARMv6 | 970 named C++ function symbols; original source/object STABS records; 41 decoded `cR` RTTI records | Source ownership, class hierarchy, and older gameplay bodies |
| iPhone 1.9.0 ARMv6 and ARMv7 | 731 C++ symbols per slice, identical symbol sets between slices; 43 decoded `cR` RTTI records in ARMv6 | Additional outlined methods and a check on source evolution |
| iPad 1.0.6 | No recoverable named C++ function entries in this binary; no DWARF sections | Inventory only for now |

Counts describe surviving metadata, not original function counts, shared-code
percentages, or completeness. Constructor aliases and unrelated library code
are included in the C++ symbol totals. Symbol absence can result from inlining
or stripping. The alternate Android APK contains **byte-identical native
libraries** for both ABIs, so it is not another independent native build.

All inspected iOS slices have `cryptid = 0`. The iPad archive filename says
1.0.5, but its bundle metadata says **1.0.6**. It is a lower priority because it
is heavily stripped; this inspection does not establish that it shares less
implementation code. No further iPad body analysis was undertaken.

## What the old analysis was missing

### 1. Android's other ABI exposes useful operations

The active Android corpus uses only ARMv7. The APK also contains ARMv5 code for
the same named methods. In the quaternion constructor, it explicitly calls
`__aeabi_fcmpge`, `__aeabi_fcmpgt`, `__addsf3`, `__aeabi_fsub`, and the other
arithmetic helpers. These make the actual comparison operations and arithmetic
dependency chain visible without reconstructing VFP flag flow.

This is a useful extra view, not an independent source release or a third
compiler family. It is especially relevant to floating-point Windows blockers.
Native listings are [ARMv5](android-v5-native.asm) and
[ARMv7](android-v7-native.asm). Their addresses are ELF link-time virtual
addresses; the Ghidra imports add an image base of `0x10000`.

### 2. The existing Android `Sqrt` pseudocode has a wrong parameter location

Both fresh Ghidra imports assign `Sqrt(float)` a parameter in `s0` and an
unassigned return type. That produces `Sqrt(in_s0)` or `Sqrt(extraout_s0)` and
can hide the computed radicand and the clamp after a negative-value diagnostic.

The native ARMv7 helper at ELF `0x1830c` moves **r0 into s15**, computes the
result, and moves it back to **r0**. The ARMv5 helper at `0x19c10` passes through
the software float/double conversions using the same integer-register path.
The constructor callsites also explicitly supply r0.

An isolated, read-only experiment specifying a float parameter and return in
r0 restores `Sqrt(value)` and the zero clamp in both exports:

- ARMv7: [before](android-v7-abi-before.c), [after](android-v7-abi-after.c),
  [storage receipt](android-v7-abi-receipt.txt).
- ARMv5: [before](android-v5-abi-before.c), [after](android-v5-abi-after.c),
  [storage receipt](android-v5-abi-receipt.txt).

The experiment changes only that helper's signature in memory. Ghidra discards
the changes when closing the read-only project. The main corpora have not been
rewritten. Other inferred prototypes, including diagnostic varargs, remain
imperfect; this is a demonstrated repair, not a complete ABI audit.

### 3. iPhone 1.9 exposes bodies absent from the 1.5 corpus

The 1.9 binary has **172 C++ symbols absent from 1.5**. Of these, **34 game-method
signatures also exist in Android**, using the explicit `cR*`, `tVector`,
`tMatrix`, and `tQuaternian` owner filter recorded by the script. Examples:

- `cRSubGoldy::FallingInit()`, `DeathInit()`, `RessurectInit(int)`
- `cRSubGame::AddHealth(cRSubLoc*, cRSubGoldy*)` and `GetY(tVector)`
- `cRTime::Faster(int, int, int)` and `cRSubRingStar::Shower(cRSubGoldy*)`

These are opportunities to obtain another body for methods already known on
Android. Their absence from 1.5 is not proof they were absent from its source.
The old aggregate iOS name inventory already includes multiple releases, but
the active iOS **body corpus** is only the 1.5 executable.

Other 1.9 additions include networking and Game Center methods. Those establish
that source evolution matters; they must not be treated as compiler differences
in the Windows version.

### 4. RTTI gives stronger declarations than a list of type names

The iPhone records are decoded using the external relocation to
`__class_type_info`, `__si_class_type_info`, or `__vmi_class_type_info`, followed
by verified name and base pointers. Thus record classification is supported by
the binary's runtime-type reference, not just its size or neighboring words.
The offset and access flags follow the
[Itanium RTTI layout](https://itanium-cxx-abi.github.io/cxx-abi/abi.html#rtti-layout).

For example, both iPhone builds establish:

```cpp
class cRGameInput : public cRBod, public cRInput;
class cRPlayer : public cRBodPos;
class cRBodPos : public cRBod;
```

These are inheritance skeletons, not complete class definitions.
`cRGameInput` has public, nonvirtual bases, with `cRInput` at **+0x2c**.
The Wii record places that base at **+0x30**. The current Windows representation
instead contains a `cRInput` member at **+0x38**. The mobile/Wii evidence makes
multiple inheritance a concrete Windows source hypothesis, but changing the
Windows declaration still requires Windows ABI and matching evidence.

The bounded Wii set and iPhone 1.5 have **37 class names in common**. Their
transitive ancestry agrees for **36**. The exception is `cRSubLoc`: Wii has an
additional `cRLoc` ancestor; iPhone reaches `cRBod` directly. This is another
reason to keep platform declarations separate. Neither RTTI set is asserted
to be a complete inventory of all game classes.

### 5. Whole function extents distinguish stable logic from layout changes

Three fresh iPhone 1.5/1.9 comparisons use original 1.5 STABS function extents
and independently matching next-symbol boundaries in both binaries. They
include embedded and trailing literal pools, not just decompiler bodies.

| Function | Full extent | All changed words accounted for |
|---|---:|---|
| Quaternion constructor | 644 bytes | 3 branches to the same named diagnostic function; 2 pointers to identical diagnostic strings |
| `cRPath::BuildSlalom` | 2,696 bytes | 32 branches to corresponding named functions; 2 pointers to identical allocation-label strings |
| `cRBorder::AddTextNumber` | 980 bytes | Exactly 2 instructions change the text-field displacement from `0x2c4` to `0x2d8` |

Every other word in each extent is byte-identical. There are **zero
unexplained changed words** in these three comparisons. This is direct evidence
of stable implementations across those iPhone releases, including a narrowly
isolated class-layout change. It does not establish runtime equivalence of the
called functions or a whole-game reuse percentage.

## How to organize the project

Keep **one repository and one shared function identity**, with separate build
identities and evidence. Add this alongside the existing Windows paths first;
avoid moving all matching sources or forcing shared headers during exploration.

- **Build registry:** exact executable hash, release/ABI, architecture,
  compiler evidence, original address convention, and analysis-image rebase.
  Android ARMv5 and ARMv7 are separate builds; iPhone 1.5 and both 1.9 slices are
  separate builds. Wii is a reference build until its matching toolchain exists.
- **Function relationships:** one-to-one, split/merged, inlined, or absent/
  unknown; attach native evidence and confidence. For example, a Windows
  bootstrap can correspond to several mobile `InitN` methods.
- **Shared source constraints:** expression grouping, branch/tie behavior,
  scalar signedness, owner and inheritance, literals, and call sequence. Store
  the supporting locations for each build and any contradictory evidence.
- **Per-build declarations and matching:** offsets, calling conventions,
  layouts, compiler settings, relocations, and exactness receipts stay separate.
  Promote shared C++ only after it fits each participating build's evidence.

For Windows-first work, choose a remaining Windows blocker, establish which
port bodies implement the same revision of its logic, and derive candidate C++
from those constraints. Compile and validate against VC6 immediately. Add Wii
compiler matching when identifying its toolchain and matching one of these
same candidates can settle a Windows ambiguity—not merely to start a second
independent progress counter.

The first worthwhile follow-up is repairing the Android ABI model and exporting
selected ARMv5/iPhone 1.9 counterparts of current Windows blockers. The new RTTI
graph can also guide narrow declaration experiments. iPad remains last priority.

## Reproduce and limits

From the repository root:

```sh
UV_CACHE_DIR=/private/tmp/snail-uv-cache uv run analysis/ports/lineage-20260910/raw_inventory.py
UV_CACHE_DIR=/private/tmp/snail-uv-cache uv run analysis/ports/lineage-20260910/compare_raw.py --out artifacts/mobile-audit-20260910/replayed-receipt.json
cmp analysis/ports/lineage-20260910/receipt.json artifacts/mobile-audit-20260910/replayed-receipt.json
UV_CACHE_DIR=/private/tmp/snail-uv-cache uv run analysis/ports/lineage-20260910/native_samples.py --out artifacts/mobile-audit-20260910/native-replay
```

The inventory writes raw tables and the two iPhone 1.9 executable slices under
ignored `artifacts/mobile-audit-20260910`. It supports these retained 32-bit
ARM inputs; it is an analysis script, not a general binary loader.

The fresh decompiler exports used the existing
`tools/ghidra/export_itanium_symbols.py`, with `--contains tQuaternian`,
`--ghidra-dir /Applications/ghidra_12.1.2_PUBLIC`, and an isolated project root
under that artifact directory. Twelve symbols exported successfully for each
Android ABI and two for iPhone 1.9 ARMv6. This includes additional quaternion
methods selected by the name fragment.

[ProbeMobileABI.java](ProbeMobileABI.java) reproduces the correction experiment.
Run it with Ghidra's `-process libsnailmail.so -readOnly -noanalysis` against the
isolated project, passing an output directory and the Ghidra constructor address
(`00029c24` for ARMv5 or `00028340` for ARMv7). Use this directory as `-scriptPath`.
The native listings retain original instruction bytes for the helper,
constructor, and input-update samples. They honor ELF `$a`/`$d` mapping symbols
so literal pools are shown as data, not decoded as instructions.

Raw-table/relocation assertions, complete-extent comparisons, deterministic
receipt replay, and Ruff checks pass. No matching sources, main analysis
databases, published progress metrics, or project dependencies were changed.
The report does not identify an exact mobile/Wii compiler configuration, prove
which release directly descended from which, or claim new Windows matches.
