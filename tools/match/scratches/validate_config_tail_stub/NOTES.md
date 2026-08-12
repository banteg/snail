# validate_config_tail_stub

Tiny config-tail helper at `0x42f5b0`, called by
`game_startup_and_main_loop` immediately after `load_config_file("SnailMail.cfg",
&g_config_blob)`.

Raw image disassembly:

```asm
0042f5b0  mov al, 1
0042f5b2  ret
```

The argument is ignored in this build. The helper is modeled as an ordinary
cdecl function returning true; the padding before `is_bod_after_sprites` stays
with the target image and is not recreated in source.

Focused Wibo result: 100.00%, 2/2 instructions, no masked operands.

2026-08-12 authored identity recovery: Android keeps
`gRegisterTestRegisterKey(char*)` inside its bounded Register.o run and compiles
the same unconditional `return 1` body while ignoring the key pointer. Windows
startup passes the loaded config validation tail to this one-argument helper;
iOS omits the disabled registration test from its otherwise STABS-marked
Register.cpp unit. The exact symbol, signature, behavior, and source run recover
the original owner without reviving any registration/platform logic.
