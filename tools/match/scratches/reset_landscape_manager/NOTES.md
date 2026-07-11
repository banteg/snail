# reset_landscape_manager @ 0x4182e0

Clears `LandscapeScriptBank::script_count` at receiver `+0x5a0`.

Startup calls this exact thiscall helper on the root-owned landscape bank at
`GameRoot +0x106c218`, then loads `Starmap.txt`, `Splash.txt`, and `Help.txt`
through the same owner. The former scratch-local `LandscapeManager` view was
therefore duplicate ownership and has been retired.

Focused match: 100%, 2/2 instructions, with no masked operands.
