# BOD linkage and allocator storage ownership

Exact function comparison had hidden another incompatible source boundary:
`BodList` declared the C++ `report_errorf(char*, ...)`, while the recovered
reporter is compiled as C and exports `_report_errorf`. The shared list header
now includes `rerror.h`, and the redundant declaration in the removal scratch
is gone. The native instruction comparison and operand audit are unchanged.

The narrow header matters: exposing all of `rdebug.h` through the list header
also introduced its variadic debug-sink declaration into existing fixed-arity
overloads in `construct_game_runtime` and `display_score_stats`, causing
compilation errors. Replacing the constructor's existing calls with direct
variadic calls compiled but regressed it from 268 to 298 instructions and
89.75% matching, so that control was rejected. Keeping only the error
formatter in `rerror.h` preserves both original sources: the constructor is
268/268 with 120 clean references and score display is 67/67 with 16. The
remaining debug-sink spellings are visible as future linkage work.

The three BOD methods have identical before/after raw object function bytes.
Only four call relocations change from `?report_errorf@@YAHPADZZ` to
`_report_errorf`: one in front insertion, one in tail insertion, and two in
removal. These are source ABI corrections, not new exact functions or a claim
about original executable symbol names.

Replacing only the corrected front-insertion object in the successful link
with its saved preceding object fails with `LNK2001`, naming that original
C++ reporting symbol, and `LNK1120: 1 unresolved externals`. This establishes
that matching native call destinations alone had concealed a real linker
failure. The [evidence receipt](bod-list-abi-evidence-20260908.json) binds the
before/after bodies and object identities, symbol changes, reverse-link log,
and runtime results.

## Intrusive ownership exercised

The `bod-list` integration group links five recovered functions: front
insertion, tail insertion, removal, the variadic reporter, and its real no-op
sink. They cover 421 curated native-extent bytes. The driver verifies nine
call and seven data relocations after linking. The function extents remain
distinct from encoded object-body byte counts.

Twenty-one runtime checks cover empty and occupied list insertion, duplicate
insertion guards, middle/tail/head removal, the linked and saved-next guards,
free-stack order, reuse after fixture detachment, independent list owners,
and preservation of unrelated flags, callback fields, and the unknown owner
word. The native stale `list_prev` value after removal is checked rather than
cleared. The positive process reports `21/0` and exits zero; a separate process
corrupts a final free-chain link, reports `21/1`, and exits one.

The fixture supplies its own nodes and two list owners. It does not establish
the placement of a game-global BOD pool, recover a pool allocator, or exercise
constructors, virtual dispatch, or destructors. Public game-linked credit
remains zero.

```sh
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run tools/match/link_path_math.py \
  --group bod-list --run --out artifacts/match/bod-list-run \
  --runtime-library /path/to/vc6/vc98/lib/msvcrt.lib
```

## Allocation records start at the third word

Independent inspection of the original Windows image and both local Android
ELFs supports the corrected allocation owner: an eight-byte Windows header
followed by 15,000 twelve-byte records. A record contains an unidentified
first word, a pointer at `+4`, and guarded size at `+8`.

Windows `push_tracked_allocation` stores at owner `+0x10 + 12*index` for size
and owner `+0x0c + 12*index` for pointer. Its pop and size-lookup helpers use
the same pointer lane. The final valid pointer is at `0x53c7e0`, its size is
at `0x53c7e4`, and the whole owner ends at `0x53c7e8`. That last address is
independently written by the archive initializer as the result of a
`0x64000`-byte allocation labeled `Music Memory Buffer`.

Both actual Android ELF symbol tables give `RShellMemory` size `0x2bf2c`.
Their native methods store record pointer/size four bytes later, maintain a
high-water value at owner `+4`, and store the bookmark at `+8`. Removing that
extra mobile header word yields the Windows extent `0x2bf28`, exactly the
distance to the neighboring music-buffer owner. This resolves the previous
projection's four-byte overlap without inventing a role for the unknown
record word.

The [allocator evidence receipt](allocator-ownership-evidence-20260908.json)
contains the native input hashes, Windows instruction bytes, actual Android
dynamic-symbol sizes and method bytes, neighboring-owner initializer, and
boundary arithmetic. The Android addresses come from those actual files;
the older decompiler export uses a different address snapshot.

The post-store native overflow check is preserved. A 15,001st record can
already write out of bounds before reporting an error; this work claims the
valid owner extent and does not repair native overflow behavior. Integration
storage is still placed by the integration linker, independently of original
Windows BSS addresses.
