# initialize_active_landscape_entry @ 0x408820

Exact VC6 match: 100.00% (7/7 instructions, full prefix, two clean masked
operands).

## 2026-07-17 active-landscape ownership

The native constructor preserves ECX in ESI, calls the shared positioned-body
constructor, installs `g_active_landscape_entry_vtable`, returns ESI in EAX,
and uses a plain `ret`. `initialize_runtime_pools_and_path_template_bank`
constructs ten records at the independently observed 0x90-byte stride.

The exact `update_active_landscape_entry` consumer proves the complete tail:
state at `+0x80`, repeat-z span at `+0x88`, and a borrowed `RenderableBod*`
reference at `+0x8c`. Together those constraints prove:

```cpp
ActiveLandscapeEntry* __thiscall initialize_active_landscape_entry(
    ActiveLandscapeEntry* active_entry);
```

The canonical Binary Ninja and IDA replays now keep the constructor,
activation, clearing, and update methods on that same owner. No retained iOS
constructor name is claimed, and no matcher source or operand mask changed.
