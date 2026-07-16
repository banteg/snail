# Matching Islands

Function-level matching decompilation against the original image, in the style
of isledecomp/decomp.me: write candidate C++ for a contested function, compile
it with the original-era compiler, and diff normalized asm against the function
in `artifacts/bin/SnailMail_unwrapped.exe`. A 100% match is proof-grade ground
truth for porting — it ends ownership/semantics debates that decompile reading
cannot settle.

## Toolchain provenance

The Rich header of the unwrapped exe (see `snail inspect`) pins the original
build environment:

- game C/C++ objects: VC6 cl 12.00 builds 8168 (RTM), 8447 (service-pack era),
  8966 (Processor Pack); linked with link 6.0 on 2004-12-04
- statically linked VC6 CRT (MASM 6.13/6.14 + C objects)
- third-party objects built with VC7 build 9178: the D3DX8 static library from
  the DirectX 8.x SDK (plus zlib 1.2.1 / libpng 1.2.x) — link the original
  libs, never decompile these
- no RTTI, 25 C++ EH functions

**Project assumption: all game code compiles with `msvc6.5 /O2 /G5 /W3`.**
Established empirically — 147+ functions across every subsystem match at 100%
with exactly this configuration and nothing has required another one.
`scratch.conf` therefore only needs `FUNCTION` (plus `END`/`SYMBOL` when the
extent or symbol needs overriding); `COMPILER`/`CFLAGS` overrides still work
but are for experiments only, and the STATUS build column stays empty unless
a scratch deviates. When a function refuses to match, change the source shape,
not the flags — every flag-looking pattern so far (dual-slot float temps,
tail duplication, register pinning) turned out to be a source idiom.

## Setup

1. wibo runner. Put a current `wibo` binary on `PATH`, set
   `WIBO=/path/to/wibo`, or place it at `tools/match/bin/wibo`. The 1.1.0 and
   1.1.1 releases do not include the `kernel32!lstrcpynA` shim needed by some
   VC6 diagnostic paths, so build Wibo from main until a newer release contains
   decompals/wibo commit `af24a30` or later. On macOS/Apple Silicon, the
   release-macos build is an x86_64 binary that runs under Rosetta 2:

   ```sh
   git clone https://github.com/decompals/wibo.git ~/dev/decompals/wibo
   cmake --preset release-macos -S ~/dev/decompals/wibo
   cmake --build ~/dev/decompals/wibo/build/release --target wibo
   mkdir -p tools/match/bin
   cp ~/dev/decompals/wibo/build/release/wibo tools/match/bin/wibo
   ```

   On Linux, use the matching release preset and copy the built `wibo` binary
   into `tools/match/bin/wibo`.
2. Compilers (gitignored, ~40 MB each) — the decomp.me production bundles:

   ```sh
   cd tools/match/compilers
   for v in msvc6.0 msvc6.5 msvc6.5pp msvc6.6; do
     curl -sL -o $v.tar.gz https://github.com/OmniBlade/decomp.me/releases/download/msvcwin9x/$v.tar.gz
     mkdir -p $v && tar xzf $v.tar.gz -C $v && rm $v.tar.gz
   done
   ```

## Workflow

1. Create `scratches/<function>/` with:
   - `scratch.cpp` — candidate implementation; use a class member function to
     get thiscall, mirror struct layouts at native offsets
   - `scratch.conf` — `FUNCTION=<manifest name>`, optional `END`, `SYMBOL`,
     `COMPILER`, `CFLAGS`
2. Run `tools/match/match.sh scratches/<function>` (append `--full` for a
   side-by-side listing instead of a unified diff). The script is a thin
   wrapper around `uv run snail match scratch <directory>`, so focused work
   uses the same config parser, no-fakematching validation, compile cache,
   extent resolution, normalization, and operand audit as the status sweep.
3. Iterate the source until the diff is empty. Exit code 0 means 100%.

Useful analysis helpers:

- `uv run snail match diff <obj> <function> --regions` prints localized
  mismatch regions before the normal diff, so large functions can be worked by
  block instead of by the whole SequenceMatcher score.
- `snail match diff` also prints a masked-operand audit. Normalized `ADDR`
  operands still keep linker noise out of the score, but the audit compares
  target resolved references (function names, imports, strings, or raw image
  addresses) against candidate relocation symbols/string literals. A 100%
  normalized score is proof-grade only when this audit has no unresolved or
  mismatched entries.
- `uv run snail match audit --exact-only` groups unresolved/mismatched masked
  operands across all 100% scratches. Use it before editing the reference
  manifest so repeated target addresses and wrong aliases are visible together.
  Scratches that fail to compile are listed as audit failures and make the
  command exit non-zero; so does `snail match status --check`. Status and audit
  share cached detailed matches, while audit cache misses use the same `-j`
  worker bound as status.
- `uv run snail match status -j 8` bounds concurrent scratch compilation and
  matching (the default is the smaller of 8 and the host CPU count; use
  `-j 1` for a sequential diagnostic run). Build keys follow each scratch's
  transitive local includes, so editing one shared header rebuilds only its
  consumers instead of all scratches. Match-only `scratch.conf` changes reuse
  the compiled object while invalidating the detailed match through the parsed
  config key. Compilation uses threads around the Wibo subprocesses; CPU-heavy
  matching uses worker processes and falls back to sequential matching only
  when a restricted host cannot create them. A status or audit sweep parses
  each shared include edge once, including during cold parallel rebuilds, so
  cache checks do not repeatedly reread the same header graph for every
  consumer.
- `uv run snail match lint` cross-checks every `extern ... g_name; // data_xxx`
  annotation across headers and scratches. It flags the same identifier
  declared with different types at one address (a future C2040/C2373 compile
  break the moment header consolidation joins those TUs) and addresses used
  under names that are not curated aliases in
  `analysis/symbols/gameplay-references.json`. Scratch-local typed views are
  fine while exploring, but keep one canonical spelling per name; run the lint
  before promoting types or headers.
- `analysis/symbols/gameplay-references.json` is the curated escape hatch for
  recovered globals, offsets, and helper symbols that are not in the function
  manifest. Add entries only when a scratch note, decompiler label, or matched
  callsite explains the target address. `.rdata` float constants are compared
  by their four bytes, not by MSVC's generated `real@...` symbol spelling.
  Add `"size"` only for recovered object extents; the audit uses it to keep
  `symbol+offset` and end-pointer operands distinct from the next global at the
  same address.
- Use a gameplay function entry's `aliases` list when one native range has
  multiple stable source-level names, such as compiler-folded methods or an
  older scratch name retained during an ownership rename. Aliases resolve
  scratch configs, function extents, and masked call operands without creating
  another function or changing cluster totals; duplicate names are rejected.
- Set `"match_scope": "reference-only"` on proven third-party library bodies
  that must remain addressable for semantic scratches, call resolution, and
  neighboring function extents but are not authored gameplay matching targets.
  Status keeps their scratch results in a separate reference-only section and
  excludes their functions, bytes, and fuzzy scores from gameplay totals. The
  default scope is `"gameplay"`; do not use this field to hide difficult game
  code.
- `uv run snail match dump <obj> <function> --side target --start-offset 0x20`
  prints addressed normalized listings. Use this when a region involves jump
  tables, duplicated tails, or branch labels and the side-by-side diff is too
  lossy.
- `uv run snail match idioms --list` shows canned VC6 source-idiom probes.
  Running one or more cases compiles tiny standalone snippets with the same
  compiler flags and prints normalized asm.
- `uv run snail match types [Name ...]` scans scratch-local `struct`/`class`
  definitions and reports which names are ready, already covered, conflicted by
  field names, or too divergent for shared-header consolidation. Pass names
  such as `Game TrackRowCell` to focus a cleanup decision. `snail match status --write`
  includes a concise type-consolidation summary so this stays a regular pass
  while matching, not an end-of-project cleanup.

The differ (`snail match`, `src/snail/match.py`) normalizes both sides before
comparing: relocated immediates/displacements in the object and absolute-looking
VAs in both the image and candidate become `ADDR`, intra-function branch targets
become `L<offset>` labels, and untargeted terminal padding after a final `ret`
is ignored. Struct offsets, register allocation, and instruction scheduling all
still count — only link-time layout is forgiven. The CLI reports both the
whole-function score and the exact common instruction prefix before the first
normalized mismatch. It also audits every normalized-equal instruction with
masked operands. Do not invent extern symbols or other dummy relocation sources
just to hide constants; if a candidate symbol does not explain the target
function/string/global reference, the status stays audit-pending even when the
normalized instruction stream is 100%. Curated reference-manifest aliases and
byte-verified `.rdata` constants are allowed audit explanations; scratch-local
dummy externs are not.

Function extents come from the symbol manifest: start at the curated address,
end at the next curated address with int3/nop padding trimmed. When uncurated
functions sit in the gap, set `END=0x...` in `scratch.conf`. If the compiled
function symbol differs from `FUNCTION`, set `SYMBOL=<object symbol>` there too.
Do not use `MATCH_ARGS` in `scratch.conf`; the shell wrapper and Python status
path both consume explicit config keys so status generation and one-off diffs
stay in sync.

## No fakematching

A match is only useful if the scratch is plausible original source whose
*semantics* the compiler independently translates into the target bytes.
Anything that reproduces bytes without recovering semantics is fakematching
and is worth less than an honest 60%:

1. **No inline assembly.** `__asm`, `_asm`, `__declspec(naked)` — rejected
   mechanically by the harness (`validate_scratch_source`).
2. **No flag shopping.** The toolchain is fixed (`msvc6.5 /O2 /G5 /W3`).
   When a function refuses to match, change the source shape, not the flags.
3. **No normalizer gaming.** Don't invent extern symbols or other dummy
   relocation sources to turn a constant you can't explain into a masked
   `ADDR`; a symbol in a scratch must correspond to a real native global or
   function with a recovered meaning.
4. **No byte-shaped source.** Code must read like something a 2004 game
   programmer wrote: real control flow, named struct fields at recovered
   offsets, no unrolled or hand-scheduled statement sequences whose only
   justification is the disassembly.
5. **Honest percentages.** Score comes only from `snail match`; never edit
   STATUS.md by hand. Residuals get documented in the scratch's NOTES.md,
   not massaged away.

## Notes

- x87-heavy functions are the hardest to match; near-misses that differ only
  in fld/fstp scheduling are still strong evidence — record the residual diff
  in the scratch directory rather than forcing source contortions.
- A matched scratch is the porting reference for the Zig side; link it from
  the function's PORT comment and the relevant analysis note.
