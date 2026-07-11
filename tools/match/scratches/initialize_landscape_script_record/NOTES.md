# Exact match

`initialize_landscape_script_record` @ 0x408840 constructs one
0x124-byte `LandscapeScriptRecord` in `LandscapeManager::scripts[128]` at
subgame `+0xff81a4` (manager `+0x5a4`). The only emitted work is the no-op
`Color4f` constructor for the parsed fog color at `+0x110`, which matches the
shared record layout in `landscape_script.h`.
