# Input editor insertion and Home recovery

`border_input_text @ 0x4035b0` (`cRBorder::InputText`) improves from
**75.25423729% to 98.76265467%**, with **443/446 instructions**, prefix **6**,
and **eight clean references**. The previous candidate had 439 instructions.
This remains a partial source recovery: the opening flag-load width, two SIB
encodings and the completion publication differ from the Windows body.

The [complete receipt](border-input-insertion-home-owners-20260911.json)
contains both full sources and byte arrays, control sources and outcomes,
decompiler witnesses, local positional-reference and branch proofs, and the
native execution receipt. Compiler, flags, headers, ABI, function extent and
matcher are unchanged.

## Recovered source

Newline and ordinary-character insertion now converge on one terminal
publication: write the last displaced character, append the terminator and
increment the input length. The two insertion arms keep an explicit displaced
character before overwriting the current slot, then read the next slot before
publishing that character as both the loop carry and terminal output. This
recovers the register copies and shared branch destination in Windows.

Home movement now acquires its insertion pointer through the newly published
`input_cursor` field. The preceding removal and separator traversal stay in the
same order. Other movement, filtering, blink and completion behavior is retained,
including key 6 falling through to ordinary insertion when input flag bit 0 is
set. Mobile supports the rotation and editor sequence but has extra ordinary-path
capitalization behavior; it is not imported into Windows. A unique original
source spelling is not established.

| Reversal from retained source | Agreement | Candidate instructions |
| --- | ---: | ---: |
| Home insertion through prior local index | 85.4893% | 443 |
| Separate insertion terminal publications | 71.7949% | 451 |
| Earlier displaced-character lifetime | 95.3881% | 443 |
| Complete previous source | 75.2542% | 439 |

All four reversals retain eight clean references. The complete reversal restores
the baseline function fingerprint. The receipt preserves 56 forward observations:
54 distinct successful formal sources, one identical-source alias, and one
generated missing-parenthesis failure with its complete source/status. The
corrected control compiles. Three rejected switch controls each add one unaudited
candidate reference. Other successful controls have no reference debt.

Twelve later numeric-cleanup observations contain eleven distinct formal sources
and one unchanged-source alias. None improve agreement; the other score-neutral
source has the retained function fingerprint. The initial cleanup recipe was
rejected for including its unchanged baseline before any formal compilation or
recording; the deduplicated recipe is retained. These are bounded observations,
not a compiler limit.

## Positional encoded evidence

The native extent is `[0x4035b0, 0x403be0)`: **1,584 bytes**. The matcher compares
the complete **1,581-byte body** and excludes only three recognized terminal
padding bytes. There are no unexplained target ranges.

Four independent certificates establish **1,514 native body bytes**, with all
**eight positional references** and **98 local branches** checked. Offsets are
relative to the start of the function; intervals are half-open.

| Native byte range | Candidate byte range | Instructions | References | Branches |
| --- | --- | ---: | ---: | ---: |
| `[0, 12)` | `[0, 12)` | 6 | 1 | 0 |
| `[18, 1250)` | `[18, 1250)` | 348 | 1 | 86 |
| `[1264, 1493)` | `[1264, 1493)` | 66 | 3 | 11 |
| `[1540, 1581)` | `[1526, 1567)` | 12 | 3 | 1 |

Branch destinations outside each certificate are mapped to explicit instruction
boundaries. Such mappings grant no encoded equality to the destination block.
References are checked by same-position operand slot, kind and identity before
masking only their relocation fields. Encoded branch displacements are checked.

The larger normalized middle `[18,1493)` **does not have encoded equality**.
Instructions 355 and 356 use native SIB byte `31` and candidate `0e` at offsets
**1252 and 1259**. The two encodings exchange ECX and ESI as base/index with
scale one, so the effective address agrees while the bytes differ. Neither byte
is masked. The failed broad-equality diagnostic is retained, and those two
instructions are outside the final certificates.

Native body regions `[12,18)`, `[1250,1264)` and `[1493,1540)` remain outside
the certificates: **67 bytes**. They remain fully included in the matcher.
The opening native load reads a dword where the candidate reads a byte. At
completion, native retains a first-character load, a separate cleared-flags
store and a temporary copy absent from the candidate. No dummy load, volatile
access or register constraint is added to force those instructions.

The local certificates contribute **zero whole-function exact bytes**. Public
normalized and encoded-exact classifications remain unchanged.

## Native execution comparison

The new [runner](compare_border_input_native.py) links the recovered source and
an oracle copied from the original function against the same
[fixture harness](link/border_input_smoke.cpp). Complete source and oracle linked
bytes and all eight original references are verified before execution. The
receipt separately binds complete extracted candidate bytes to the matching
proof, avoiding ambiguity between extraction fingerprints with and without the
reference manifest.

All **35,568 cases** agree: **71,136 complete widget objects**, **130,036,608
object bytes**, and **100,930 ordered callbacks per implementation**. The full
records total **133,166,592 bytes**. The comparator checks framing, case identity,
callback order and unused slots, complete subject and OK-widget contents, and
two checked pointer identities represented by fixed tokens. Guard regions and
game storage are also verified by the harness.

Fixtures cover nine short strings, every cursor position, 19 keys, eight input
modes, and six blink/visibility patterns including threshold crossing, signed
zero and quiet NaN. Capacity, submit/OK flags, fill patterns and four OK-update
effects cycle deterministically; this is not their full Cartesian product.
A one-byte corruption in the first subject text buffer is detected as exactly
one differing byte in case zero. Comparator tests also reject identical corrupt
headers, truncation, trailing bytes, duplicate cases, invalid callback records
and pointer tokens, and detect the last byte of the second object.

Keyboard input, OK-widget updates, layout and teardown are explicit callback
seams. Layout and teardown do not mutate objects here. Short terminated strings
avoid leading separators, overflow and dangling pointers. This comparison does
not establish real UI layout, teardown, arbitrary-input safety or linked-game
behavior, and adds no matching credit. The initial Wibo run failed its required
stdout completion check; explicit `fflush(0)` fixed reporting, and the final
source/native run and corruption control pass.

Reproduce with:

```sh
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run tools/match/compare_border_input_native.py \
  --runtime-lib /Users/banteg/dev/banteg/crimson/tools/native/providers/build/vc6-sp6/vc98/lib/msvcrt.lib \
  --out artifacts/match/border-input-native-20260911
```

## Repository validation

All **1,104 tests** and **785 scratch checks** pass, with zero type findings.
The strict ledger has **2,516 records**, zero malformed/current errors and
**14/14 active specs runnable**, with no stale active specs. Full public refresh,
separate saved-evidence validation and `git diff --check` pass. The complete
receipt binds the canonical source/COFF to the public row and byte proof.
Core exact functions remain **606/662**; fuzzy agreement rises **93.85% to
93.97%** and the rounded residual gap falls **12,998 to 12,625 bytes**. The
source-weighted gain is **372.3733 bytes**. Public exact and linked credit do not
change; only this widget's ratio changes, with no range or identity changes.
