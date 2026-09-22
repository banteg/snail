# Cache builder cell ownership — 2026-09-22

`build_track_render_caches @ 0x433220` now matches the complete encoded native
body after relocation auditing: **1,552 bytes, 476 instructions, 20 positional
references, 36 literal local branches and five ordered jump-table entries**.
There are no excluded or unexplained bytes. The prior normalized match still
had one incorrect SIB byte; normalized scores alone did not establish this result.

## Recovered source shape

The embedded `SegmentCache` traverses the subgame's owned runtime grid using
`runtime_cells[row_index][lane]`. For each fringe, it borrows `owner_subgame`
for the object and position passed into `append_track_cache_object`. After
that call, texture copying and fringe retirement read `owner_subgame` again.
The native instructions establish this lifetime:

```text
43330d  mov eax, [ebx+0x54]          ; owner_subgame before append
433310  mov edx, [eax+ebp]           ; fringe object
43333d  lea eax, [edi+eax+0x3bfad8]  ; owned cell position
433349  call 0x433960                ; append_track_cache_object
43334e  mov eax, [ebx+0x54]          ; fresh owner for texture read
433351  mov ecx, [eax+ebp]
433375  mov ecx, [ebx+0x54]          ; fresh owner for fringe retirement
433378  mov [ecx+ebp], 0
```

The borrow ends at the call. Extending a cached pointer across it is a different
source hypothesis and regresses. Existing shared types provide the grid,
position, flags, object and four fringe slots; no layout or ABI change is needed.
The retained source also replaces the fringe byte-offset/countdown with its
logical array index and writes the actual floating-point row-base field.
Those two cleanups preserve the complete match independently.

The coupling is measurable:

| Cell addressing | Pre-call owner used for fringe and position | Encoded body |
| --- | --- | --- |
| Original byte-offset cursor | No | One wrong SIB byte |
| Direct row/lane fields | No | Same wrong byte |
| Original byte-offset cursor | Yes | Same wrong byte |
| Direct row/lane fields | Yes | **Complete match** |

All four retain 100% normalized matching, 476/476 instructions and 20 clean
references. The final raw candidate differs from the old candidate at precisely
offset **287**, changing SIB `38` to native `07`. The instruction at offset 285
changes from `lea eax,[eax+edi+0x3bfad8]` to native
`lea eax,[edi+eax+0x3bfad8]`. No other candidate byte changes, including the table.

This is a sufficient source reconstruction, not proof of the original lexical
source. Mutable and const pre-call pointer values, and an object reference used
before the call, can produce the same result. A reference to the owner pointer
field or a borrow used only for the position does not close the byte.

## Independent encoded audit

The [checker](check_cache_cell_owners_20260922.py) decodes the first 1,532 bytes
directly with Capstone. It checks every instruction boundary and all 20
reference-bearing instructions at the same index, operand and byte offset.
It validates the native targets and COFF addends before masking those fields.
The indirect switch dispatch points to the final 20 bytes; all five table
relocations resolve to the ordered instruction offsets
`1439, 1449, 1459, 1469, 1479`.

Every relocation is consumed: 20 instruction fields plus five table entries.
All other bytes remain literal, including local branch displacements, the fixed
SIB, and the alignment NOP immediately before the table. The checker compares
the captured native body with the pinned executable and reads its strings and
floating-point constant independently. The relocation-audited full-body hash is
`c7ede2e2fd055992f5d0cbfaacd6584bf482862ce93247096d1250289518cabf`.

Nine corruption controls reject changed body, SIB, reference target, COFF
addend, table bytes, table destination, local branch, alignment and exactness
claim. This proves a function-body match after relocation auditing, not a linked
whole-image match.

## Controls and reproduction

The [receipt](cache-cell-owners-20260922.json) freezes the baseline at
`f336ea4f6d1bda4736d2c2c9d2aeaba3c90bdbd8`, 74 source observations, 112 build inputs,
source reconstruction recipes, forward/reverse probes, and full native/candidate
bytes with positional references and relocations. All 74 controls recompile to
their recorded results. The official forward probe has no metric tradeoffs;
the reverse probe reproduces the old non-exact body. No compiler flags, shared
headers, native extent, reference identities or matching rules changed.

```sh
uv run tools/match/check_cache_cell_owners_20260922.py
uv run tools/match/check_cache_cell_owners_20260922.py --replay-all
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/cache-cell-owners-20260922.json \
  --batch final --label formatted --replay
```

The preserving C2 observer now reports instruction counts through the matcher's
code-only counters. Its old line count included the five jump-table entries as
instructions (481 instead of 476). A fresh baseline observer run retains whole
COFF equality apart from timestamps, rejects a missing stream and changes no
compiler decisions. Its recorded body remains non-exact; the observer correction
does not supply or relax any part of the encoded proof above.

Validation: all 785 scratches checked, 1,140 pytest tests passed, exact-reference
audit and extern lint are clean, and the strict experiment ledger has zero
errors with 14/14 active specifications runnable. The refreshed report passes
its separate freshness/consistency check. Only the cache builder's encoded
proof and exactness flag change among function rows, apart from COFF timestamps.

Full-executable encoded progress increases from **730 to 731 functions** and
**195,637 to 197,168 code bytes**. The report credits the 1,531 owned instruction
bytes; the audited table and alignment byte do not earn code credit.
Normalized progress remains **734/2,261 functions**
and **204,674/596,823 bytes (34.29%)** because this function was already
normalized-exact. `STATUS.md` likewise remains unchanged.
