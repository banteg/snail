# Wii DOL tool comparison — 2026-09-10

Use **Ghidra as the primary Wii reference**, **Binary Ninja as the interactive
second opinion**, and **IDA/Hex-Rays for selected cross-checks** with the current
installed versions. This is a local workflow recommendation from five sampled
functions, not a general decompiler ranking or a whole-program correctness claim.

The Binary Ninja DOL tooling was committed as `fc8c6dc8f`; the earlier persistent
Ghidra tooling is `107318e26`.

## Input and method

All tools used `artifacts/wii/reference/SnailMail-USA.dol`, SHA-256
`523f848f2a0b8ef8c9dfe2714744bf0479a4feec79b25f0d1f5e035a6487c096`.
The DOL has ten initialized regions and three BSS fragments after subtracting
initialized ranges. The loaders checked initialized memory against the file.
No mobile or Windows structures were imported into these Wii comparisons.
Ghidra's quaternion name is an analyst annotation, not an original Wii symbol.

| Tool | Setup actually tested | Result and limitation |
|---|---|---|
| Ghidra 12.1.2 | GameCubeLoader, `PowerPC:BE:32:Gekko_Broadway`, verified r2/r13 and GQR startup values, saved project reopened read-only | All five decompiled. Small-data references resolve to concrete addresses. Best current Wii setup, but register-save helpers and paired-single prologues still pollute larger functions and inferred signatures. |
| Binary Ninja 6.1.10626-dev | Our validated DOL view, `ppc_ps`, standalone SVR4 platform, live saved BNDB | All five produced HLIL. Convenient native references and explicit comparison/flag operations. r2/r13 are still unresolved; larger functions acquire spurious floating-point parameters and quantize/dequantize prologue operations. |
| IDA 9.4 / Hex-Rays 9.4.0.260714 | DOL regions mapped through the same Python header parser; big-endian 32-bit PPC, paired-single option | All five decompiled after reopening. Paired-single mnemonics decode, but some remain inline assembly in pseudocode. SDA setup is incomplete; applying its GUI options crashed twice. |

Samples (end addresses exclusive):

| Start | End | Selection reason |
|---|---|---|
| `8000a968` | `8000ac68` | Known quaternion constructor and previously successful cross-port recovery |
| `800092e0` | `80009304` | Small floating-point conversion helper |
| `800444e8` | `80044a98` | Function referencing Galaxy configuration text |
| `80052a00` | `80052d60` | Function near the Hotspot string reference |
| `80075cc8` | `80076284` | Function near the IntroText string reference |

Ghidra and IDA report these same five function extents. Binary Ninja's exports
identify the same starts. The descriptive string labels are selection clues,
not verified recovered C++ names. Function counts and pseudocode line counts
are deliberately not treated as coverage or quality scores.

The raw outputs are [ghidra.json](ghidra.json),
[binary-ninja.json](binary-ninja.json), and [ida.json](ida.json). Native assembly
must arbitrate differences: even Ghidra's readable quaternion pseudocode
normalizes the branch tree, whereas the actual PPC compares established the
source ordering needed by the Windows compiler.

## IDA GUI outcome

The installed IDA has a PPC processor and Hex-Rays PPC decompiler, but no DOL
loader. Automatic direct import selected COFF incorrectly. The experimental
headless adapter used raw binary import, mapped the DOL sections with the shared
parser, and checked every initialized byte. It is an evaluation database, not a
finished IDA loader plugin.

The first quaternion decompile returned `INTERR 50735`; reopening headlessly
then decompiled all five. This transient failure does not count as permanent
lack of quaternion support.

Options → General → Analysis → Processor specific analysis options confirmed
PS (Paired Singles/Gekko) selected and both SDA bases unset. The values verified
from startup are r2 `808fc860` and r13 `808fb720`. Two attempts to apply them
through the GUI ended in crashes; one explicitly showed IDA's signal-11 alert.
The first macOS crash report includes `flush_buffers`, `term_database`, and
`qexit`; the precise root cause is not established. This does not prove the
values are wrong or that the problem affects other IDA builds.

Both packed and unpacked files were preserved before recovery. Unpacked
recovery reported an empty database. A fresh copy of the packed baseline was
successfully opened, and the quaternion pseudocode was verified in the GUI:
`artifacts/ida/wii/SnailMail-USA.reference.i64`.
Use that reference copy; the `.dol` and `.gui` recovery attempts are retained as
diagnostic artifacts. The exported IDA comparison remains the baseline with
unresolved r2/r13, not a claim of successful SDA configuration.

## Does this DOL contain better types?

It retains useful runtime class metadata. A bounded extraction found **41 named
descriptors**, starting from cR-prefixed names in the observed small-data record
range and recursively following base entries. This is not a complete census.
[The receipt](type-metadata.json) records names, descriptor addresses, base-list
entries, and references.

For example:

- `cRPlayer`: descriptor `808f3728`, name `8015e640`, base list `80166868`,
  referencing `cRBod` and `cRBodPos` at offset zero.
- `cRBodPos`: its own base list references `cRBod`, so the player's list contains
  transitive ancestry; it must not be read as two independent direct bases.
- `cRGameInput`: its base entries include `cRBod` at zero and `cRInput` with
  offset word `30` hex. This is Wii layout evidence, not a Windows field offset.
- The player vtable at `8016685c` begins with descriptor `808f3728`, zero,
  function pointer `80019644`. Native code materializes this vtable at
  `800813a8` and installs it with `stw r17,44(r18)` at `800813b8`.

This pointer chain and native installation support interpreting the records as
RTTI/vtable metadata rather than mere diagnostic names. Exact null-terminated
`cRPlayer`, `cRBod`, `cRGameInput`, and `cRPath` strings were absent from the
Windows reference `artifacts/bin/SnailMail_unwrapped.exe`.

These records help with class identity, ancestry, subobject placement, and
virtual-function ownership. They do **not** provide complete struct definitions,
member names, full method prototypes, or transferable Windows offsets. The
existing named Android/iOS symbols remain useful complementary evidence.

## Should we start a second Wii decompilation?

A focused Wii reference effort is worthwhile now. Cross-pollination has already
worked: [the quaternion recovery](../../../tools/match/quaternion-wii-dispatch-20260909.md)
used the Wii axis-selection tree to obtain a Windows match with 186/186
instructions, a 186-instruction exact prefix, and all 23 masked reference fields
explained. That is normalized instruction/reference exactness; the unlinked
COFF body still contains unresolved relocation bytes.

Maintain one shared semantic model with separate platform layouts and matching
receipts. Map the remaining Windows blockers to Wii functions, use Wii RTTI and
control flow to constrain plausible C++, and test every promoted hypothesis
with the Windows VC6 matcher and runtime checks. Windows recovered names and
behavior can in turn label the Wii database.

A complete independent Wii matching target would additionally require compiler
and linker identification, a reproducible PowerPC toolchain, library ownership,
and a separate denominator. That can be a later project. It is not necessary
to obtain the next Windows exact matches, and no new Wii matching target or
public coverage percentage was created here.
