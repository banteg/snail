# Ghidra reference analysis tools

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

## Wii reference database

The local Wii setup uses `/Applications/ghidra_12.1.2_PUBLIC` with
[GameCubeLoader release 1.3.1](https://github.com/Cuyler36/Ghidra-GameCube-Loader/releases/tag/1.3.1)
(the distribution filename identifies its internal version as 1.3.0).
The official `GameCubeLoader-1.3.0-921504c-Ghidra_12.1.zip` SHA-256 is
`9892f28fc1e7f19bb3fcec7cfb4ad2ab7504503b571d93de8b142a6f7bec8ed0`.
It is installed under the application's `Ghidra/Extensions/GameCubeLoader`,
so both GUI and headless sessions can use the language. Its bundled Sleigh
source has been compiled with the installation's `support/sleigh` command.

The stable input is `artifacts/wii/reference/SnailMail-USA.dol`, SHA-256
`523f848f2a0b8ef8c9dfe2714744bf0479a4feec79b25f0d1f5e035a6487c096`.
It is the decompressed original DOL, not the earlier synthetic ELF. See the
[Wii provenance receipt](../match/quaternion-wii-dispatch-20260909.json) for
its compressed source identity and extraction evidence. Input bytes and the
analysis database remain ignored local artifacts.

```sh
# Import once; subsequent calls reopen the same program without reanalysis.
uv run tools/ghidra/wii.py
uv run tools/ghidra/wii.py 0x8000a968

# Rerun analyzers only when intentionally requested.
uv run tools/ghidra/wii.py --analyze
```

The default selector is the recovered `initialize_quaternion_from_matrix`.
Names and address selectors use the same rules as `decompile_symbol.py`.
`--ghidra-dir`, `--binary`, and `--project-root` provide explicit overrides.
The local 12.1.2 fallback is used only when the shared configured/default
Ghidra installation is absent.

The persistent GUI project is:

```text
artifacts/ghidra/SnailMail-USA.dol-fba1665a73de/project/SnailMailAnalysis.gpr
```

Open that `.gpr` with Ghidra 12.1.2, then open `SnailMail-USA.dol`. Close the
GUI's project before running headless commands against it; Ghidra itself
locks the database, and the wrapper additionally locks concurrent wrapper runs.
The earlier synthetic-ELF project is preserved separately.

The [setup receipt](wii-setup-20260910.json) records 3,458 discovered functions,
3,051 decoded paired-single instructions, all ten byte-verified initialized
sections, and successful reuse with the same inventory and recovered name.
These are analyzer counts, not proof-grade function matches.

The wrapper explicitly selects the DOL loader and
`PowerPC:BE:32:Gekko_Broadway` language, disables interactive map-file prompts,
and enables the extension's SDA/GQR analyzer. Settings, temporary files, and
Ghidra's filesystem cache live inside the per-binary project directory. Each
successful run writes `wii-verification.json`, `decompile.txt`, and
`headless.log` there. Verification checks every initialized DOL section against
its loaded bytes, the entry-established r2/r13 values, paired-single decoding,
and the quaternion's known 768-byte extent.

`metadata.json` pins the input and Ghidra build; `wii-loader.json` additionally
pins the extension's loader and language sources. A mismatch refuses reuse;
choose a separate `--project-root` to analyze with changed inputs or tooling.
The wrapper seeds only the already verified quaternion function name and
preserves subsequent analyst names and comments. It does not replace the
project on repeated calls. Dolphin is deferred until runtime evidence is
needed; IDA remains available for an independent decompiler comparison.
