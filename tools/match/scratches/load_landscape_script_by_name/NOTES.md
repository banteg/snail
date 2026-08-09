# load_landscape_script_by_name / cRLandscapeManager::Import(char*) @ 0x4182f0

Structure-first recovery for the landscape script cache loader.

- `this+0x5a0` is the signed loaded-script count.
- Records start at `this+0x5a4` and are 0x124-byte `LandscapeScriptRecord`
  entries: id, name, texture id/path/split flag, object index, fog color, and
  distort.
- The preceding `0x5a0` bytes are ten constructed `ActiveLandscapeEntry`
  records. Together with the count and 128 scripts they form the exact
  `0x97a4`-byte `LandscapeManager`; this is not a standalone script bank.
- The two calls to `0x449c00` are the release-stripped debug-report stub:
  `"Loading backdrop texture %s"` and `"Landscape: %s imported\n"`.
- Missing `Picture:` intentionally skips only the texture block, then still
  parses `Landscape:` and `Distort:` before adding the script.

2026-06-20 exact match: the cache scan now keeps an explicit empty-count
precheck, then uses a `while (index < script_count)` loop. That preserves the
native `edi` index / `ebp` name-cursor ownership and avoids VC6's earlier
duplicated compare-call layout. Focused Wibo now reports 100.00%, 386/386
instructions, full prefix, and 63 clean masked operands.

2026-07-14 canonical DirectX owner: the landscape mesh import now reloads the
live `GameRoot* g_game` and calls its embedded `directx_loader` directly. The
loader remains exact at 386/386 instructions with all 63 operands clean.

## 2026-07-15 durable root-loader replay

The tracked IDA database now derives that same receiver from the shared exact
root graph: `DirectXLoader +0x48e00` spans `0x5e10` bytes and ends at
`Backdrop +0x4ec10`. The refreshed listing therefore retains
`&v23->directx_loader` without a raw `GameRoot +298496` cast. This is
analysis-only; the matching source remains exact at 386/386 instructions with
all 63 operands clean.

## 2026-07-18 landscape cache ownership replay

Both tracked databases now carry the exact
`int32_t __thiscall load_landscape_script_by_name(LandscapeManager*, char*)`
ABI. This promotes the receiver from Binja's `void*` and IDA's `char*` to the
existing exact `0x97a4`-byte manager, so the cache count and all parsed
`LandscapeScriptRecord` fields render through their real owners. The narrow
Binja replay is available through `--landscape-loader-only`; the focused match
remains 386/386 instructions with all 63 masked operands clean.

## 2026-07-27 mobile authored owner

Android and iOS export this method as
`cRLandscapeManager::Import(char*)` from `Landscape.o`. All three ports:

- cache `Backgrounds/<name>` records by manager-owned name and count;
- parse `ID:`, `Fog:`, `Picture:`, `Landscape:`, and `Distort:`;
- release the loaded file bytes; and
- return the cached or newly appended landscape index.

The storage differences are real and intentionally retained. Windows uses the
recovered 0x124-byte DirectX record, registers split backdrop textures, and
loads an X mesh for repeated landscape BODs. Mobile uses a 0x1ac-byte record
with additional `Portrait:`, `Width:`, `Height:`, and `Menu:Yes` fields. The
cross-port evidence therefore recovers the owner and original method name, not
a false shared struct layout.

## 2026-08-09 primary matcher owner

The matcher now spells the exact desktop loader as
`cRLandscapeManager::Import(char*)`, while retaining `LandscapeManager` as a
compatibility typedef and the stable scratch/manifest name. VC6 emits
`?Import@cRLandscapeManager@@QAEHPAD@Z`. This naming promotion does not import
the wider mobile record layout or change the exact Windows parser body.
