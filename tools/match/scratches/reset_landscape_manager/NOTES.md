# reset_landscape_manager @ 0x4182e0

Clears `LandscapeManager::script_count` at receiver `+0x5a0`.

Startup calls this exact thiscall helper on the root-owned landscape bank at
`GameRoot +0x106c218`, then loads `Starmap.txt`, `Splash.txt`, and `Help.txt`
through the same owner. Constructor accounting now proves that this receiver
also owns the ten active entries at `+0x00` and all 128 script records at
`+0x5a4`, for the exact reported `0x97a4`-byte manager extent.

Focused match: 100%, 2/2 instructions, with no masked operands.

The 2026-07-13 owner-boundary pass now embeds this manager directly at
`SubgameRuntime +0xff7c00`. Its exact `0x97a4` extent ends at
the authored `Face` owner at `+0x10013a4`; a previewed Binary Ninja declaration
confirmed that boundary without changing the live database. This ownership
promotion is codegen-neutral at the exact focused baseline.

## 2026-07-24 durable reset ownership

The exact scratch and the adjacent loader already proved the reset contract,
but both tracked decompilers still rendered the native function as an
untyped fastcall over `receiver +0x5a0`. The shared landscape replay now
applies the missing `void __thiscall` `LandscapeManager*` ABI in Binary Ninja
and IDA, so the only store reads back as `manager->script_count = 0`.

The function manifest now records why this is the parsed-script count rather
than a generic manager flag: the ten-entry active bank ends exactly at
`+0x5a0`, the 128-record script bank begins at `+0x5a4`, and
`load_landscape_script_by_name` is the sole non-reset writer. Focused matching
remains exact at 2/2 instructions; this slice closes ownership without changing
source shape.

## 2026-07-27 mobile authored owner

Android and iOS retain this lifecycle boundary as
`cRLandscapeManager::Open()` in `Landscape.o`. Both methods begin by clearing
the manager-owned script count, then add a mobile-only `SpaceRed` backdrop
resource. Their `cRGame::Init1()` methods call `Open()` immediately before
importing `Starmap.txt`, `Starmappro.txt`, `Splash.txt`, and `Help.txt`;
Windows performs the same reset in its startup landscape-import phase before
the three scripts present in the desktop build.

This transfers the authored class and method name without claiming identical
platform bodies. The exact 2/2 Windows scratch remains the complete desktop
`Open()` projection.
