# initialize_game_window_and_input_wrapper

Small cdecl wrapper at `0x4119c0`, called by `game_startup_and_main_loop` with
the `"SnailMail"` window title. It forwards the single argument to the real
window/input initializer body at `0x4119d0`.

Raw image disassembly:

```asm
004119c0  mov eax, [esp+4]
004119c4  push eax
004119c5  call 0x4119d0
004119ca  add esp, 4
004119cd  ret
```

Focused Wibo result: 100.00%, 5/5 instructions, 1 clean masked operand.

2026-07-16 replay closure:

- The exact wrapper and the window/input body now have persistent
  `int __cdecl(char* window_name)` declarations in both decompiler lanes.
- This removes an unrelated `PresentationWeaponChannel` type that had leaked
  onto the IDA parameter and made Hex-Rays reject the startup call at
  `0x406ef6`. The wrapper disassembly, its `"SnailMail"` caller, and the
  forwarded callee argument jointly prove the narrow string ownership.
