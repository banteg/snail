# initialize_keyboard_input @ 0x44b7d0

Initializes keyboard DirectInput after `release_input_controllers`, then clears
the two 0x100-byte keyboard state buffers.

`DirectInput8Create` is `__stdcall`; using the default C calling convention
adds a non-native stack cleanup after the call.

The static interface identifier and system-keyboard identifier are complete
0x10-byte DirectInput GUID owners, while the installed keyboard format is the
SDK 0x18-byte `DIDATAFORMAT`. These records are borrowed by the API calls; they
are not one-byte address anchors.

## 2026-07-16 shared DirectInput state ownership

The parent/device COM pointers and previous/current key buffers are now
process-owned globals in `direct_input_view.h`. Both buffers have the proven
256-key SDK extent, so initialization derives its two clear sizes from the
owners instead of repeating `0x100`. The function remains exact at 55/55
instructions with all 15 operands clean.
