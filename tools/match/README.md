# Matching Islands

Function-level matching decompilation against the original image, in the style
of isledecomp/decomp.me: write candidate C++ for a contested function, compile
it with the original-era compiler, and diff normalized asm against the function
in `artifacts/bin/SnailMail_unwrapped.exe`. A 100% match is proof-grade ground
truth for reconstruction — it ends ownership/semantics debates that decompile
reading cannot settle.

## Toolchain provenance

The canonical image has a checksum-valid Rich header. Run
`uv run snail inspect artifacts/bin/SnailMail_unwrapped.exe` for its ordered
numeric records, XOR key, checksum result, PE fields, sections, directories,
and imports. The durable interpretation is deliberately narrower than the old
one:

- product IDs 10/11 record ordinary VC6 C/C++ contributions from build
  families 8168, 8447, and 8966; 8966 is the normal SP5 backend/object family,
  not the Processor Pack;
- product IDs 28/29 record a C++-dominated VC7.0-family build-9178 population,
  while product ID 96 records one VC7.1-family build-4035 contribution;
- MASM 6.13/6.14, alias-object, resource, old-linker/library, and import-library
  contributions are present, but their owning libraries are not encoded;
- no standard Processor Pack C/C++ rows (product IDs 48/49, build 9044) appear;
  this is aggregate provenance evidence against Processor Pack inputs; and
- the PE optional header reports linker version 6.0 and its unauthenticated
  timestamp field decodes to 2004-12-04 22:38:32 UTC. The current image has no
  debug-directory entry; that does not prove that no PDB, MAP, or DBG existed.

Rich records aggregate the `@comp.id` values of included objects and static
library members. They do not map builds to addresses, identify authored game
translation units, name the final linker build, or prove that MASM objects are
CRT and build-9178 objects are D3DX8/zlib/libpng. The three D3DX8 matrix bodies
and the libpng 1.2.5 boundary remain independently identified by their
interfaces, implementation semantics, call relationships, and library API
fingerprints; their exact compiler-build-to-object mapping remains unknown.

The project-standard reproduction baseline is `msvc6.5 /O2 /G5 /W3`.
`msvc6.5` is a project nickname for a historically coherent SP5-style VC6
component set: the 12.00.8804 driver invokes C++ frontend 8964 and ordinary
backend 8966. Hundreds of exact functions make it a strong empirical baseline,
not proof that every original game translation unit used one component set.
`scratch.conf` therefore only needs `FUNCTION` (plus `END`/`SYMBOL` when the
extent or symbol needs overriding). `RECOVERY` and `RESIDUAL` record reviewed
non-exact recovery state without affecting compilation. `COMPILER`/`CFLAGS`
overrides still work but are for experiments only, and the STATUS build column
stays empty unless a scratch deviates.
When a function refuses to match, pursue native-backed source shape before
flags. An alternate profile needs independent provenance, ABI, or language
evidence; a better fuzzy score is not compiler provenance.

Reference basis: the [Microsoft PE/COFF specification](https://learn.microsoft.com/en-us/windows/win32/debug/pe-format),
the [Rich-header object aggregation study](https://www.virusbulletin.com/virusbulletin/2020/01/vb2019-paper-rich-headers-leveraging-mysterious-artifact-pe-format/),
the community-maintained [component/build table](https://github.com/dishather/richprint/blob/master/comp_id.txt),
Microsoft's archived [VC6 SP3 component inventory](https://helparchive.huntertur.net/document/104797),
and the contemporary [VC6 optimization guide](https://www.cs.cmu.edu/~rbd/doc/optcode.htm).
Product names and servicing mappings from community Rich tables are evidence,
not an official Microsoft Rich-header specification.

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
     `COMPILER`, `CFLAGS`, `RECOVERY`, `RESIDUAL`
2. Run `tools/match/match.sh scratches/<function>` (append `--full` for a
   side-by-side listing instead of a unified diff). The script is a thin
   wrapper around `uv run snail match scratch <directory>`, so focused work
   uses the same config parser, no-fakematching validation, compile cache,
   extent resolution, normalization, and operand audit as the status sweep.
3. Iterate the source until the diff is empty. Exit code 0 means 100%.

Useful analysis helpers:

- `uv run snail match mobile <function>` prints the Binary Ninja Windows
  decompile followed by the verified Android and iOS source bodies. Pass
  `--windows-tool ida` to use the IDA corpus or `--paths-only` to print just
  the artifact paths. When a port has no verified mapping, the command labels
  its mechanically ranked names as **unverified candidates** instead of
  silently treating the best score as provenance. Refresh the complete
  785-function coverage file and exact cross-port name transfers with
  `uv run tools/sync_mobile_crosswalk.py`; `--check` verifies that both tracked
  crosswalk files are current.
- `uv run snail match triage --state wip --sort unexplored` joins every
  port-relevant manifest function by native address to its best scratch,
  recorded probe/mutation history, and verified Android/iOS mapping. Use
  `--sort fuzzy-gap` for the largest remaining fuzzy-byte gaps; combine
  `--recovery`, `--residual`, `--mobile`, `--min-bytes`, and `--limit` to
  select a work queue. `--json` exposes the same rows and aggregate exact,
  fuzzy, candidate, recovery, and mobile coverage for automation.
- `uv run snail match diff <obj> <function> --regions` prints localized
  mismatch regions before the normal diff, so large functions can be worked by
  block instead of by the whole SequenceMatcher score.
- `uv run snail match inspect <scratch>` reports the target/candidate prologue
  allocation once, then aligns conservative basic-block pairs and localized
  mismatch regions. The frame delta is a diagnostic clue, not a byte count of
  missing locals: compiler temporaries and stack-slot coloring contribute to
  the allocation. Add `--source-lines` to generate a proven-equivalent compiler
  listing and attach the candidate `scratch.cpp` lines scheduled in each
  mismatch's changed instruction span. Those lines describe only candidate scheduling; they do not
  recover native local names or lifetimes. CFG edges are checked only through a monotonic backbone of
  unique exact blocks within 5% normalized order distance. Duplicate or
  displaced exact blocks and similar blocks remain visible as heuristic pairs,
  but cannot manufacture anchored edge conflicts. `anchors=` is therefore the
  trusted subset of `exact=`. None of these diagnostics change the canonical
  instruction match or masked-reference audit.
- `uv run snail match listing <scratch>` recompiles the selected VC profile
  with `/FAsc` in isolation and writes its mixed source/assembly listing under
  the ignored match cache. It refuses to publish unless the extracted function,
  including relocations, equals the canonical build. The adjacent JSON records
  object and function hashes, source-line spans, machine offsets, compiler stack
  aliases, reused slots, and generated temporaries. Those names and lifetimes
  describe only the reconstructed candidate compilation; they do not recover
  native local names. Use `--output /tmp/function.cod --json` for an explicit
  artifact.
- `uv run snail match probe <scratch> --source <probe.cpp>` compiles a complete
  source overlay without changing the tracked `scratch.cpp`, then reports its
  metric deltas against one baseline compile. This is useful for larger
  controlled hypotheses such as same-TU neighbors or alternate recovered type
  definitions that do not fit one bounded replacement. Add `--record` to
  preserve the source hash and complete result in `experiments.jsonl`;
  `--stdin` accepts a generated overlay.
- `uv run snail match mutate <scratch> --spec <plan.json>` evaluates bounded
  source-shape alternatives without editing the tracked scratch. A schema-1
  plan names exact, non-overlapping source spans and their plausible
  replacements:

  ```json
  {
    "schema": 1,
    "sites": [{
      "name": "sum-order",
      "find": "entry.x + offset.x",
      "replacements": [
        {"name": "commuted", "text": "offset.x + entry.x"}
      ]
    }]
  }
  ```

  When a replacement only compiles with another choice, encode that relation
  rather than scheduling known-invalid variants. Object replacements accept
  `requires` and `conflicts` arrays of `site/replacement` keys; invalid
  combinations are excluded from both the plan and its possible-variant count:

  ```json
  {
    "name": "reuse-shared",
    "text": "return shared",
    "requires": ["owner/declare-shared"],
    "conflicts": ["qualifier/make-const"]
  }
  ```

  Sites must match exactly once unless they specify a one-based
  `"occurrence"`. The default sweep changes one site at a time; use
  `--max-changes` for interactions and `--max-variants` or `--time-budget` to
  bound the search. Every variant compiles in an isolated temporary directory
  and is ranked by proof state, canonical score, reference debt, exact prefix,
  and instruction-count shape. `--record` appends the full sweep and its
  canonical baseline epoch to the scratch's `experiments.jsonl`. The epoch
  hashes the source/build inputs, target image, and curated symbol/reference
  manifests so older experiments stay useful without masquerading as current
  evidence. `--write-best` writes only an improving winner and refuses to
  overwrite the tracked `scratch.cpp`.

  Add `--hypothesis "why this code shape is worth testing" --record` to retain
  the reasoning alongside the recipe and scores. `code_groups` in the JSON
  report groups identical extracted function bytes **and relocation evidence**;
  equal fuzzy scores or masked assembly alone never establish equivalence.
  Text output shows repeated identities and identities shared with the baseline.

  To inspect a neutral or degrading candidate, pass its exact evaluated label:

  ```sh
  uv run snail match mutate <scratch> --spec <plan.json> \
    --export-candidate 'site/replacement' --export-dir /tmp/diagnostic-candidate
  ```

  The destination must be new. The bundle contains `candidate.cpp`,
  `source.diff`, `assembly.diff`, target/candidate assembly and `report.json`
  with the baseline epoch, compiler profile, score, CFG diagnostics and complete
  reference audit. Export recompilation must reproduce the evaluated code
  identity. Compile failures export source plus the error, without invented
  assembly. Exporting a candidate does not promote it or require an improvement;
  `--write-best` and `--require-improvement` retain their existing behavior.

- `uv run snail match contracts <scratch>` gathers native return-contract
  evidence without changing source declarations. It shows the current source
  declaration excerpt when locatable, direct call sites, the first EAX read or
  overwrite after each call, native return windows, and verified mobile mappings.
  Use `--json` for full coverage and decode limitations. This is a conservative
  straight-line EAX audit: branches, subsequent calls, forwarded returns and
  conditional writes remain unknown. Partial writes do not discard the whole
  register. Manifest ranges can include uncurated code, and indirect calls are
  not covered. Caller non-use does not prove `void`; mobile mangled names often
  omit return types. Use the report to formulate and check a source-contract
  hypothesis against native control flow, ownership and other return registers.
- `uv run snail match experiments --search 'return-contract' --limit 10`
  searches individual receipt labels, hypotheses and recipe edits. Add
  `--scratch <name>` to narrow the search or use `--details` to browse without
  a query. `--json` includes scores, tradeoffs, epochs and physical ledger line
  numbers. Edits are shown only when a saved recipe's SHA-256 matches the receipt
  and its named choices agree. Missing or edited recipes are marked unavailable;
  snippets are not claimed to reconstruct the full historical source. Old epochs
  remain useful evidence, not proof of exhaustion. Search is separate from the
  summary validation flags below.
- `uv run snail match experiments` summarizes the append-only
  `experiments.jsonl` ledgers created by recorded probes and mutation sweeps.
  It reports improving/neutral/degrading variants, repeated source/compiler
  combinations and specs, metric tradeoffs, and exact winners. Current,
  historical, and legacy unversioned records are reported separately;
  incomplete or errored current sweeps are explicitly inconclusive. Experiment
  counts never close or reclassify a scratch. Repeat `--scratch <name>` to
  restrict the report, or run
  `uv run snail match experiments --check --strict --check-specs` for
  repository-wide validation. `--check` rejects malformed ledger records;
  `--strict` also rejects current-baseline evaluation errors. `--check-specs`
  treats a mutation plan whose exact current digest already appears in that
  scratch's ledger as historical, while an unreceipted current digest is an
  active input whose schema and exact `find` anchors must still resolve against
  `scratch.cpp`. Run the combined gate after changing scratch sources or
  mutation plans, and before committing matcher slices that rename owners or
  otherwise rewrite source anchors.
  Do not label a lane `stalled`, `exhausted`, or `frozen` from an experiment
  count. Record the tested forms and technical residual instead; rewrite old
  stopping claims when encountered.

  If manual review proves that compile failures came from an invalid mutation
  plan, append a digest-bound audit rather than deleting or rewriting history:

  ```sh
  uv run snail match experiment-audit tools/match/scratches/example \
    --record 12 --reason "replacement referenced an undeclared local"
  ```

  The errors remain visible and the sweep remains inconclusive, but the audited
  plan error no longer fails `experiments --strict`. Do not use this for
  compiler, environment, or unexplained evaluation failures; repair and rerun
  those instead.
- `snail match diff` also prints a masked-operand audit. Normalized `ADDR`
  operands still keep linker noise out of the score, but the audit compares
  target resolved references (function names, imports, strings, or raw image
  addresses) against candidate relocation symbols/string literals. On partial
  matches, reference-bearing instructions that sequence alignment could not
  pair are reported separately as `unaudited`; they are not assumed to be
  mismatches. A 100% normalized score is proof-grade only when this audit has
  no unresolved, mismatched, or unaudited entries.
- `uv run snail match audit --exact-only` groups unresolved/mismatched masked
  operands across all 100% scratches. Use it before editing the reference
  manifest so repeated target addresses and wrong aliases are visible together.
  Alignment canonicalizes intersecting manifest alias sets before pairing
  repeated `CALL ADDR` instructions, so a source-spelled relocation stays with
  its native canonical callee rather than a nearby call of the same shape.
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
  same address. An `"allowed_prebase_offsets"` list may name exact byte
  displacements when compiler-generated affine indexing deliberately relocates
  against addresses before that recovered object. It requires `"size"` and
  permits only the listed offsets, never the intervening range.
  Likewise, `"allowed_postbase_offsets"` permits explicitly evidenced offsets
  beyond `"size"`, such as a compiler-derived sentinel across separately owned
  strided payloads. Each offset must exceed the recovered size; it does not
  extend object ownership or permit other addresses in the gap.
- Use a gameplay function entry's `aliases` list when one native range has
  multiple stable source-level names, such as compiler-folded methods or an
  older scratch name retained during an ownership rename. Aliases resolve
  scratch configs, function extents, and masked call operands without creating
  another function or changing cluster totals; duplicate names are rejected.
- Every function has a `port_scope`:
  - `"core"` (the default) is authored portable behavior that a future
    implementation must preserve.
  - `"boundary"` is an authored content, input, audio, or rendering contract
    whose behavior still matters across the eventual platform seam.
  - `"replaceable-platform"` is a concrete Win32, Direct3D, DirectInput, BASS,
    or legacy RShell/file/archive backend implementation that future platform
    glue replaces.
  - `"third-party"` is a proven library body that should be linked or replaced,
    not decompiled.
  Status counts `core` and `boundary` functions in reconstruction-relevant totals and
  keeps the last two scopes visible in separate excluded sections for call,
  semantic, and extent context. Scope by implementation ownership and
  cross-platform evidence, never by match difficulty; uncertain authored code
  stays `"core"`.
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
  such as `Game cRSubLoc` to focus a cleanup decision. `snail match status --write`
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

Local jump tables are checked as ordered destination lists. A destination is
accepted only when its function-relative offset is exact or its instruction is
paired by the normalized whole-function alignment; table length and case order
must still agree. This permits honest block-size and instruction-scheduling
shifts without treating a reordered or unproven switch as matched.

Function extents come from the symbol manifest: start at the curated address,
end at the next curated address with int3/nop padding trimmed. When uncurated
functions sit in the gap, set `END=0x...` in `scratch.conf`. If the compiled
function symbol differs from `FUNCTION`, set `SYMBOL=<object symbol>` there too.
Do not use `MATCH_ARGS` in `scratch.conf`; the shell wrapper and Python status
path both consume explicit config keys so status generation and one-off diffs
stay in sync.

`scratch.conf` parsing is strict: unknown fields, malformed or duplicate
assignments, and unsupported recovery metadata fail rather than being silently
ignored. For a reviewed non-exact scratch, set
`RECOVERY=incomplete|semantic-complete`; exact matches report `exact`
automatically. Set `RESIDUAL` to a comma-separated subset of
`analysis,compiler,references` so behavioral recovery remains distinct from
source-shape, toolchain, and masked-reference debt. Recovery metadata is a
manual evidence-review result, never an inference from experiment count, and
must not be used as a stopping rule for a non-exact scratch.

Normalized memory operands canonicalize scale-one SIB encodings when both
registers use the DS default segment. In that bounded case, x86 computes the
same `base + index` address whichever register occupies the SIB base field.
Other EBP/ESP forms stay distinct because exchanging the architectural base
can change the default segment; non-unit scales stay distinct as well.

## Resuming a partial

Start with `status --check`, `experiments --check --strict --check-specs`, and
`triage --state wip --sort fuzzy-gap`. The function-count headline is not byte
coverage; aggregate related builders before spending another session on tiny
near matches. Use `inspect --source-lines` and the actual instruction diff to
identify a particular owner, branch, or expression to recover.

`historical-only` includes legacy experiments with no recorded baseline
identity. It does not prove that their source changed or that their search is
irrelevant. Conversely, a neutral result on one source does not establish a
compiler limitation on a later source: inlining and register allocation couple
otherwise distant expressions. Retest a selected rejected hypothesis when a
relevant owner or helper changes; do not replay the entire old mutation grid.

Keep whole-function source hypotheses available alongside local mutations.
Decompiler byte cursors, flattened tail recursion, and integer casts for float
copies are candidates to investigate, not recovered original source by
default. Preserve native behavior and references and compare the full diff.
A score, prefix, or instruction-count change is a diagnostic; none independently
proves or disproves an authored source shape.
In particular, a changed branch destination offset can move the first mismatch
earlier even when the first changed computation is much later in the function.
Do not change the exact-match standard to make these partials disappear.

When a globally degrading variant makes a native region exact, preserve its
source as a diagnostic seed outside `scratch.cpp`. Check whether the remaining
diff is consistent register or stack-slot recoloring, then cross the relevant
counter, cursor, expression, and scope changes. For repeated patterns, test the
same recovery across all homologous regions; for up to five binary sites, test
all non-empty combinations rather than only single-site mutations. Record the
fixed assumptions and untested interactions before making a negative claim.
This is the lesson of Crimson's `grim_state_init` recovery: a 64.71% probe
exposed exchanged stack homes, and coordinated changes across five atlas loops
produced exact matches (sibling commit `a416f82aa`).

Non-exact port-relevant scratches have been reset to `RESIDUAL=analysis`
(plus `references` where applicable). This supersedes older compiler-only or
exhaustion claims in their notes without deleting the underlying observations.
`RECOVERY=semantic-complete` remains a reviewed claim about represented
behavior, not original source identity or completion of matching. A compiler
attribution needs affirmative evidence that distinguishes it from untested
source shapes; repeated failures, equal instruction counts, and similar
semantics do not provide that evidence.

## No fakematching

A match is only useful if the scratch is plausible original source whose
*semantics* the compiler independently translates into the target bytes.
Anything that reproduces bytes without recovering semantics is fakematching
and is worth less than an honest 60%:

1. **No inline assembly.** `__asm`, `_asm`, `__declspec(naked)` — rejected
   mechanically by the harness (`validate_scratch_source`).
2. **No score-driven flag shopping.** Use the project-standard reproduction
   baseline (`msvc6.5 /O2 /G5 /W3`). An override needs independent native or
   provenance evidence; a better score alone is not evidence of the original
   toolchain.
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
- A matched scratch is the implementation reference for that behavior; link it
  from the relevant analysis note.
