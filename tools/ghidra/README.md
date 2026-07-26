# Ghidra mobile decompile tools

## Batch corpus export

`export_itanium_symbols.py` exports every Itanium C++ text/weak function selected
from the binary symbol table in one headless analysis run. The index keeps the
mangled and demangled names, Ghidra entry point, function size, parameter types,
prototype, output path, and per-function status.

```sh
uv run tools/ghidra/export_itanium_symbols.py \
  artifacts/android/unpacked/com.sandlotgames.snailmail.1/lib/armeabi-v7a/libsnailmail.so \
  analysis/decompile/android \
  --strict

uv run tools/ghidra/export_itanium_symbols.py \
  "artifacts/ios/unpacked/Snail Mail/Payload/iSM.app/iSM" \
  analysis/decompile/ios \
  --strict
```

Selection is keyed by the binary's mangled symbol-table entries. The Ghidra
script resolves the imported symbol object rather than treating the `nm`
address as a Ghidra function entry, which avoids ARM Thumb-bit address
ambiguity. Mach-O's extra leading underscore is normalized in `mangled` while
the original spelling is retained in `binary_symbol`.

Use `--contains BuildSlalom` or `--limit 5` for a bounded smoke export. A run is
staged next to the requested corpus and only replaces the prior tree after
Ghidra writes a structurally complete index. Without `--strict`, individual
decompiler failures are recorded in the index and successful functions are
still installed. The default 300-second timeout and 256 MiB response budget
cover giant mobile functions such as `cRGame::LoadPaths()`; both are
configurable.

## One-function probe

`decompile_symbol.py` is the bounded second-opinion path for Android, iOS, or
Windows functions. It currently defaults to Ghidra 12.1.2 and creates both the
project and Ghidra user home under a temporary directory, so headless analysis
does not mutate the normal GUI profile.

Prefer a unique demangled-name fragment over a raw address. ELF image bases,
Thumb entry bits, and port-specific layouts make raw cross-port addresses easy
to misapply. Use an exact hexadecimal entry address when the loader does not
import a local symbol, as can happen with Mach-O linker symbols:

```sh
uv run tools/ghidra/decompile_symbol.py \
  artifacts/android/unpacked/com.sandlotgames.snailmail.1/lib/armeabi-v7a/libsnailmail.so \
  SetShootFlags

uv run tools/ghidra/decompile_symbol.py \
  "artifacts/ios/unpacked/Snail Mail/Payload/iSM.app/iSM" \
  0x5f620
```

The probe fails closed when a name fragment is absent or ambiguous, or when no
function starts at an exact address. It prints the Ghidra version, selected
fully qualified function, entry point, and clean decompiled C on success. The
Java probe writes that payload to an isolated temporary file, so routine
analyzer startup logs are suppressed; a failed probe prints the script-error
block when available, otherwise only the bounded tail of Ghidra's diagnostics.
This also catches post-script failures because Ghidra may leave the headless
launcher status at zero.
