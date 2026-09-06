# Ghidra mobile decompile tools

## Local installation

Use the official [Ghidra 12.1.3 release](https://github.com/NationalSecurityAgency/ghidra/releases/tag/Ghidra_12.1.3_build).
The helpers use `--ghidra-dir` when supplied, then `GHIDRA_INSTALL_DIR`,
then `~/.local/opt/ghidra_12.1.3_PUBLIC` when installed, with
`/Applications/ghidra_12.1.3_PUBLIC` as the macOS fallback. Both the one-function
probe and batch exporter use this same selection.

On this Linux setup, `ghidra` launches the GUI and `ghidra-headless` launches
the headless analyzer from the user installation. The installation can be
shared by other projects; analysis databases remain local to each repository.
Ghidra needs a full JDK 21 or newer, not just a Java runtime. A user-local JDK
can be selected with `JAVA_HOME_OVERRIDE` in the installation's
`support/launch.properties`, without changing the system Java installation.

To decompile a Windows function by its native entry address:

```sh
uv run tools/ghidra/decompile_symbol.py artifacts/bin/SnailMail_unwrapped.exe 0x44ccf0
```

## Batch corpus export

`export_itanium_symbols.py` exports every Itanium C++ text/weak function selected
from the binary symbol table in one headless run. By default, the first run
imports and analyzes the binary into a persistent per-binary project under
`artifacts/ghidra/`; later runs reopen that program with `-process`. The index
keeps the mangled and demangled names, Ghidra entry point, function size,
parameter types, prototype, output path, per-function status, and project
provenance.

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

Pass `--fresh` to create, analyze, and delete a temporary clean-room project.
This is the reproducibility/second-opinion path; it does not mutate or replace
the persistent project. `--project-root` relocates the persistent project store.

## One-function probe

`decompile_symbol.py` is the bounded second-opinion path for Android, iOS, or
Windows functions. It defaults to Ghidra 12.1.3 and reuses the same isolated
per-binary persistent project and Ghidra home as the batch exporter. It does not
mutate the normal GUI profile. Pass `--fresh` for the former temporary-project
behavior.

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
Java probe writes that payload to a separate isolated file, so routine analyzer
startup logs are suppressed; a failed probe prints the script-error block when
available, otherwise only the bounded tail of Ghidra's diagnostics. This also
catches post-script failures because Ghidra may leave the headless launcher
status at zero.

## Persistent project safety

Each project is isolated by source-binary identity and guarded by a
non-blocking process lock. `metadata.json` records the source SHA-256 and size,
the Ghidra version and revision, and the stored program name. A later run refuses
to reuse the project if the binary or Ghidra build differs. Use `--fresh` to
inspect the changed input without touching the persistent database, or move the
stale project directory aside before building its replacement.

The projects remain ignored working artifacts. The symbol manifests, replay
scripts, headers, and exported decompile corpora remain the version-controlled
durable state.
