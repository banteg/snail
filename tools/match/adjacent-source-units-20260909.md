# Two exact functions from recovered adjacent source context

The native status increases from **593/662 to 595/662** port-relevant functions,
with **555 additional proof-grade bytes**. Both gains use unchanged canonical
C++ bodies and the standard `msvc6.5 /O2 /G5 /W3` profile.

| Function | Isolated baseline | Registered context | Positional references |
|---|---:|---:|---:|
| `play_subgoldy_shoot_sfx` | 89.13%, 96/88 instructions | 100%, 88/88 | 19 clean |
| `load_frontend_level_by_mode_and_index` | 81.36%, 61/57 instructions | 100%, 57/57 | 12 clean |

## Source ownership and the controlled change

The [Windows/mobile crosswalk](../../analysis/symbols/windows-mobile-gameplay-crosswalk.json)
assigns these four functions to `SubGame.o`. The two groups preserve native
address order and adjacency:

| First member | Next member | Ownership evidence |
|---|---|---|
| `begin_post_follow_carryover` / `cRSubGoldy::FallingInit`, `0x43af60` | `play_subgoldy_shoot_sfx`, `0x43afd0` | FallingInit's bounded Windows source run and Android owner; PlayShootSfx's verified mobile source object |
| `update_track_parcel` / `cRParcel::AI`, `0x4431d0` | `load_frontend_level_by_mode_and_index`, `0x443650` | Both verified mobile source-object mappings |

Compiling the available `SubGame.o` bodies together first exposed both gains.
Independent reductions retained only the actual preceding function for each.
The full 190-function aggregate was not promoted: other partial functions changed
code generation, so this report establishes only these two minimal groups.

`translation_units.json` composes each pair from existing scratch files. No
function body, parameter contract, compiler flag, dummy helper, or artificial
register constraint was introduced. The predecessor functions remain exact:
FallingInit is 20/20 instructions with no references; parcel AI is 312/312
with 35 clean references.

The [replayable controls](adjacent-source-units-20260909.json) compile every
member four ways: registered order, isolated, reversed order, and only its
peer's include directives. For both newly exact functions, isolated, reversed,
and headers-only builds restore the original partial result. Both predecessors
remain exact in every control. The observed effect is improved tail sharing:
the sound routine merges the lower-volume-clamp call tail, and the frontend
loader merges indexed filename-formatting tails. The precise VC6 internal
mechanism remains unproven.

## Proof and byte accounting

Every canonical member has equal instruction counts, a full exact normalized
prefix, and zero unresolved, mismatched, or unaudited references. Every audit
entry also has identical target/candidate instruction indices and offsets.
The loader's eight-entry switch table is covered by the local jump-table
reference audit; it is not treated as executable instructions.

The native extent and extracted COFF body have equal lengths for all four
members. The control script also compares every byte outside actual four-byte
i386 COFF relocation operands, including bytes beyond the last decoded
instruction. There are no unexplained trailing bytes or non-relocation byte
mismatches.

| Function | Body bytes | Non-relocation bytes compared exactly | COFF relocations | Raw unrelocated body identical |
|---|---:|---:|---:|---|
| FallingInit | 97 | 97 | 0 | yes |
| PlayShootSfx | 335 | 259 | 19 | no |
| Parcel AI | 1148 | 976 | 43 | no |
| Frontend level loader | 220 | 140 | 20 | no |

Raw body identity is separate from normalized exactness: unresolved COFF
addresses differ from linked native addresses. The parcel and loader bodies
each contain eight additional table-entry relocations beyond the instruction
reference count. This is not a claim of whole-executable byte identity or a
reconstructed game link.

The pinned original image is SHA-256
`d365acf3db5335dded4dfd944e876ee2f23156595503693e0bf1baee1c8c83e5`.
The JSON records source and body hashes, reference positions, relocation offsets,
byte counts, and all sixteen control results. Full assembly/reference exports
are reproducible with the canonical `snail match probe` commands below.

## Tool integration and validation

The compiler shares one locked physical object per group. Cache dependencies
include all peer bodies, configs, transitive headers, and manifest order. Batch
matching consumes the compiler-returned path, avoiding stale isolated objects.
Probes and mutations substitute only the selected body. Export recompilation
must reproduce the evaluated code identity, and exports retain the complete
compilation source. Listings select the extracted decorated symbol: the sound
routine's verified listing contains all 88 machine rows and 29 source spans.

Link inventory deduplicates definitions by physical object and raw symbol index,
preferring each function's selected native owner. It retains separate-object
COMDAT ambiguity. Link harnesses copy each physical object once and use that
same owner for relocation verification.

- **926 tests pass**, including peer cache invalidation, overlays, stale-object
  rejection in batch matching, symbol-specific listings, and link ownership.
- Full status: **595/662**, 137602/294937 proof-grade bytes (46.65%), no other
  function match or platform-helper regression.
- Strict experiment/spec audit passes. Changed code introduces no new Ruff
  findings; the existing `match.py` lint findings are unchanged.
- Link frontier: **783 physical objects / 785 selected functions**, 12271
  selected relocations, and 13 other image relocations. The existing D3D
  COMDAT ambiguity is unchanged. Three duplicate-tail relocations disappear;
  this is not three newly resolved dependencies.
- All eight existing runtime harnesses pass **226 positive checks**; each
  negative run reports exactly one intended failure. These harnesses validate
  link-tool regression behavior, not execution coverage of the two new matches.

Useful local receipts live under `artifacts/match/adjacent-unit-runtime-20260909/`,
`artifacts/match/adjacent-source-unit-link-frontier-20260909.json`,
`artifacts/match/shoot-sfx-adjacent-unit-20260909/`, and
`artifacts/match/frontend-load-adjacent-unit-final-20260909/`.

```sh
uv run tools/match/probe_translation_unit_context.py --out artifacts/match/unit-controls.json
uv run snail match probe play_subgoldy_shoot_sfx --source tools/match/scratches/play_subgoldy_shoot_sfx/scratch.cpp --export-dir artifacts/match/shoot-unit-export
uv run snail match probe load_frontend_level_by_mode_and_index --source tools/match/scratches/load_frontend_level_by_mode_and_index/scratch.cpp --export-dir artifacts/match/loader-unit-export
uv run snail match status --check -j 8 --write tools/match/STATUS.md
uv run snail match experiments --check --strict --check-specs
uv run pytest -q
```

The native loader, S-bend, and quaternion micro-oracles remain in the toolbox.
They provide behavioral comparisons on stated fixtures; these two promotions
come from native instruction, reference, and byte evidence.
