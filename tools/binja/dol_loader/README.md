# Nintendo DOL loader for Binary Ninja

Loads GameCube/Wii DOL executables as big-endian `ppc_ps`, including Gekko and
Broadway paired-single instructions. Written in this repository; no dependency
on the older community DOL plugin. Requires Binary Ninja 6 with `ppc_ps` and
Python 3.10 or newer.

## Install and open

From the repository root on this Mac:

```sh
uv run tools/binja/install_dol_loader.py \
  --plugin-dir "$HOME/Library/Application Support/Binary Ninja/plugins"
```

The installer adds `snail_nintendo_dol.py`, a small startup shim pointing at this
checkout. It refuses to overwrite a different file. Keep the checkout at that
path, or remove the shim and reinstall after moving it. No packages or global
Binary Ninja settings are changed.

After restarting Binary Ninja, use **Plugins → Nintendo DOL → Open...**. The
loader is also registered for ordinary file loading, but BN 6.1.10626-dev
misidentifies this game's DOL as an LZMA container *before* selecting a loader.
The DOL command bypasses container transforms for that one open operation.
The global `files.container.mode` remains `Full`.

For the current session, the same native file picker can be invoked in the
Binary Ninja GUI console:

```python
import dol_loader.gui

dol_loader.gui.open_dol(bv)
```

Save and reopen `.bndb` files normally. The loader must remain installed to reopen
databases using its `Nintendo DOL` view. The verified local database is
`artifacts/binary_ninja/SnailMail-USA.dol.bndb`.

## Mapping contract

- Read the complete 256-byte header and all 7 text / 11 data slots, including
  populated slots after empty ones. Preserve slot numbers in section names.
- Reject payloads inside the header, truncated extents, file or initialized
  memory overlaps, unsupported memory ranges, and unaligned/out-of-text entries.
- Support MEM1 and Wii MEM2 cached/uncached address ranges. Each declared virtual
  region is mapped independently; the loader does not emulate alias coherence.
- Map exactly the declared sizes; retain trailing file padding only in Raw view.
  Text is RX and data is RW. DOL has no per-section protection metadata.
- Subtract initialized regions from the declared BSS interval. Zero-filled
  segments never extend outside BSS or mask initialized small data.
- Keep the loader class and ctypes callbacks alive in the imported module and
  the Binary Ninja module. Re-import/reload retains the registered class; restart
  to apply changes to its implementation.

`format.py` is independent of Binary Ninja and does not allocate from section
sizes. `view.py` maps the validated layout. `gui.py` implements the native file
picker with a per-open container override. `verify.py` compares a live view to
the source file, including offsets, extents, permissions, every initialized byte,
and every BSS byte. Binary Ninja's extra `.synthetic_builtins` region is reported
separately and must not overlap DOL memory.

## Validation

```sh
uv run pytest -q tests/test_dol_loader.py
uv run ruff check tools/binja/dol_loader tools/binja/install_dol_loader.py tests/test_dol_loader.py
```

The 36 parser cases cover sparse slots, both memory banks and aliases, malformed
headers, overflow/bounds/overlap cases, and BSS subtraction including sections
beyond the BSS end. The real-file checks are recorded in
[`validation-20260910.json`](validation-20260910.json):

- DOL SHA-256 `523f848f2a0b8ef8c9dfe2714744bf0479a4feec79b25f0d1f5e035a6487c096`.
- Ten initialized sections: 1,614,080 bytes verified.
- Three BSS intervals: 7,767,568 zero bytes verified.
- GUI opened successfully on BN 6.1.10626-dev Personal; analysis found 4,166
  functions. This is an analysis count, not a verified function inventory.
- Quaternion at `0x8000a968` produces HLIL. Database save/reopen preserves all
  mapped bytes, extents, and availability of that decompilation.

The loader does not infer SDA (`r2`/`r13`) or GQR values, import game-specific
symbols, or certify the decompiler's paired-single semantics. Those require
separate startup/code evidence. Ghidra's configured Wii project remains a useful
cross-check.

Format references: Dolphin's
[DOL header](https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/Core/Boot/DolReader.h)
and [reader](https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/Core/Boot/DolReader.cpp).
Binary Ninja documents its
[container loading controls](https://binary.ninja/2026/03/31/container-transforms.html)
and exposes [FileContext](https://github.com/Vector35/binaryninja-api/blob/dev/ui/filecontext.h)
for presenting an already loaded view. The format facts inform this independent
implementation; emulator loading code is not included.
