# BuildLevel owners and guarded inline lookup tables

`populate_runtime_track_cells_from_segments` (`cRSubGame::BuildLevel`) now
scores **85.8815%**, with **1,244/1,246 candidate/native code instructions**,
a 76-instruction prefix, and **165 clean references with no reference debt**.
It remains partial: the reference audit is diagnostic alignment, and no
normalized-exact or encoded-body certificate is claimed for this function.

The same pass corrects inline byte-table decoding. With unchanged C++ source,
`game_window_proc` now has a complete normalized and encoded-body certificate:
**142 instructions, 39 positional references, and 508 native-owned code bytes**.

## Source recovery, separated from measurement

The old source scored 74.6988% under policy 4, which decoded glyph lookup bytes
as instructions. Under the corrected policy 5, that same source scores
75.8017%. Comparing source against source under policy 5 gives
**75.8017% to 85.8815%**, a gain of **509.63 fuzzy-weighted bytes**.
Those similarity weights are not newly certified code bytes.

Four ordinary source changes are retained:

- Completion segment selection uses one `if`/`else` for modes 0, 4, 1, 7, and 3.
  Native `0x435eb0+0x456..0x49f` tests the mode once through a single chain.
  The old two checks assigned scratch slot 1 for mode 3 and immediately replaced
  it with the last segment. Removing that redundant local assignment preserves
  the final selection. The separate non-mode-2 extension check stays outside
  the completion guard.
- Parcel-set selection reads `active_segment->rows[segment_row].parcel_set_id`.
  Native `+0x69c` reloads the row index, adds `0x25`, and forms the authored-row
  address with its 56-byte stride. This recovers the native row transfer and
  removes the four formerly unpaired model/parcel references.
- The `P`/`p` attachment path indexes `runtime_cells[build_row][lane]` for its
  template field. It restores the native indexed cell accesses; the borrowed
  `runtime_cell` pointer remains available for the stamped-row pointer stores.
- The stamp loop borrows the actual unsigned flags field by reference. The
  generated code now stores the primary/secondary flag before the corresponding
  cell pointer, as native does. This final change reverses only those two store
  pairs; the full assembly delta is retained in the evidence.

The Windows body and exact Android/iOS `BuildLevel` exports establish the
behavior and owners. The receipt includes their paths and hashes, full source
and assembly differences, all 165 current reference rows, stack diagnostics,
and the original-source evaluation under the same policy. The 68-byte frame
is unchanged. Two missing instructions, register choices, stack lifetimes,
and later scheduling still require analysis; no compiler limit is asserted.

## Inline byte-table proof

Recognition requires a contiguous unsigned `cmp`/`ja`, zero-extended byte
load, and indexed jump into an independently bounded local address table.
The native curated lookup size must equal the guarded range. Candidate COFF
requires a bounded local label, zero displacement addend, and no relocation
overlapping any lookup byte. Every byte must select a valid jump-table entry.
Branches into the guard interior, data, or preceding alignment reject the
interpretation. Rejected regions become ordinary code/unknown bytes again.

Byte entries are represented as `db.lookup`, kept out of instruction counts
and CFG blocks, and compared literally in the encoded digest. Public evidence
separately identifies lookup subsets. Resolved four-byte addresses and literal
byte ranges must cover all inline data without gaps, overlap, or masks.

BuildLevel's native table consists of 28 addresses at relative `[4836,4948)`
and 94 literal bytes at `[4948,5042)`. Its final 14 bytes are terminal padding.
The table bytes do not overlap the independent native code inventory.

For `game_window_proc`, data ranges are `[508,787)` and `[788,828)`;
the 255-byte lookup is `[532,787)`, and the address tables occupy 24 and
40 bytes. The alignment byte at 787 remains compared; terminal `[828,832)`
is excluded. All 39 references agree at the same instruction index and byte
offset. Its 828-byte encoded body has digest
`c1128a6f27a5186ec22c80c9661a9882a25980e9f90850048aca91ad2cfbe983`.
The code inventory credits 508 code bytes, excluding tables and alignment.

Only six status rows change: BuildLevel, `game_window_proc`,
`normalize_segment_glyph_for_track_flags`, `set_snail_weapon`, `set_blend_mode`,
and `configure_sprite_render_state`. Only BuildLevel changes C++ source.
The other three already-exact helpers retain normalized and encoded equality;
`set_snail_weapon` remains partial. All six have complete table-range receipts.

## Bounded controls and epoch correction

Two runnable mutation recipes record 13 controls against the final source.
None improves it. A flags pointer produces the same code/relocation identity.
Negative `if`/`else` selection and a `for` stamp loop preserve the metrics but
have different code/relocation identities. Other controls regress similarity
or reference alignment. The receipt retains every result; the findings apply
only to these tested forms and combinations.

Epoch v2 hashes matcher/scoring source, symbol logic, the dependency lock,
and decoder version as well as the prior source/build/image inputs. Old
measurements become historical even when their C++ source is unchanged.
The two final sweeps were rerun after this correction; earlier exploratory
records remain available as historical evidence.

## Public accounting and validation

Core fuzzy progress moves **91.27% to 91.46%**; exact core remains **600/662**.
Platform exact moves **112/120 to 113/120**. Native normalized credit moves
**711 owners / 164,402 bytes to 712 / 164,910**; encoded credit moves
**700 owners / 149,475 bytes to 701 / 149,983**, out of 2,261 owners and
596,823 code bytes. There are no exact regressions. The new 508 certified code
bytes come from correcting measurement of the unchanged window procedure.

Scoring policy changes from 4 to 5, so the public delta is explicitly a
measurement-baseline change. Target, inventory, ownership, and toolchain
identities stay fixed. Linked code remains zero; standalone data and final
image identity remain unmeasured.

All **1,077 tests pass**, including 31 additional lookup-proof cases. The full
785-scratch status sweep and source-bound public refresh pass. Strict ledger
validation accepts **2,460 records**, with zero errors and 13 active runnable
specifications. The [receipt](buildlevel-and-lookup-20260911.json) separates
the old and new policies, source progress, complete positional proof for exact
functions, diagnostic reference proof for partials, and public identities.
