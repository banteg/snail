# RText void contract and executable source group

`RTextExtractString(char**, char*)` now uses its recovered void API and the
shared `rtext.h`. Its previous pointer return was a register-allocation
workaround that prevented the actual caller from linking to its definition.
Two direct cursor loops reproduce the same **60 bytes / 27 instructions**
without that workaround. Merely removing the return from the former source
gave 22.22%; changing the source structure is what preserves the exact body.

The emitted symbol is now `?RTextExtractString@@YAXPAPADPAD@Z`. The canonical
COFF inventory confirms that the `load_object_definition` relocation resolves
to this exact external definition. Explicit alias mismatch edges fall from
12 to 11; no manifest alias or caller change is needed.

The new `rtext` group links all seven recovered RShell text helpers, totaling
**518 native body bytes**, and exercises each through the shared declarations.
The 22 assertions cover token output, cursor position, untouched output bytes,
CRLF traversal, integer/fraction parsing, copy/append, and prefix comparison.
They preserve shipped quirks: tabs are token content; a CR yields an empty
token without advancing; float parsing leaves a leading plus unconsumed;
newline scanning advances once past a terminating NUL. Test inputs supply the
required delimiters. These cases do not establish bounded-input safety.

All 22 assertions pass. A separate process deliberately corrupts the final
token and fails exactly one assertion. Replacing only the recovered token
object with its old pointer-return version fails the link with one unresolved
void symbol. All source code/data sections are verified after linking; none
remain unverified. The [receipt summary](rtext-void-and-runtime-20260909.json)
binds the native image, source/object identities, compiler dependencies, linker,
runtime, executable, map, and runtime outcomes. This is source integration
evidence, with no original-TU, complete-game, or public linked-credit claim.

Reproduce using an existing VC6 runtime import library:

```sh
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run tools/match/link_path_math.py \
  --group rtext --run --out artifacts/match/rtext-runtime-20260909 \
  --runtime-library /path/to/vc6/MSVCRT.LIB
```

Validation: all 886 tests pass after updating the former ABI exception in the
ownership test; native status, exact-reference audit, extern lint, strict
experiment/spec checks, and focused Ruff checks pass. The port board remains
593/662 exact functions: this repairs an already-exact body's source contract.
