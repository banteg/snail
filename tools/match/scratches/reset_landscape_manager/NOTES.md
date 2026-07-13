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
`SmtrackHeightfieldAnimator +0x10013a4`; a previewed Binary Ninja declaration
confirmed that boundary without changing the live database. This ownership
promotion is codegen-neutral at the exact focused baseline.
