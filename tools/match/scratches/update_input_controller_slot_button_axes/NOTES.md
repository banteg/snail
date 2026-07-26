# update_input_controller_slot_button_axes @ 0x431ff0

Updates the two-slot input-controller state from button and axis inputs. Slot 0
merges button bits and only fills empty axis lanes; nonzero slots overwrite the
selected slot and refresh slot 1 authored X from slot 0 X with a 0.15 deadzone.

The axis arguments are stored as raw float bit patterns, so the scratch keeps
them as `int` parameters. Pointer locals for the dynamically selected nonzero
slot preserve the native button, X, Y store order.

2026-07-16 owner correction: constant slot-0 and slot-1 accesses now use the
separate 0x20-byte `g_input_controller_slot0` and
`g_input_controller_slot1` payloads, including the slot-1 authored-X write
after deadzone processing. The native 0x38 spacing is a stride, not a complete
array-element size: the slot-1 trailing stride overlaps the independently
authored `g_text_input_repeat_step` global. The result remains exact at 61/61
instructions with all 25 operands resolved.

The nonzero-slot path also proves a button producer: any low-byte controller
button in `0x10..0xf0` sets byte-one bit `0x40`, which is the shared
`INPUT_BUTTON_PRIMARY` value `0x4000`; otherwise it clears that bit. This joins
the pointer adapter as an independent producer for the primary-action flag.

## 2026-07-26 mobile RShell owner

Android retains this routine as
`RShellInputRegister(int, int, float, float)` in `RShell.o`. Its body
independently preserves the slot-0 button merge, fill-only-when-zero axis
stores, selected nonzero-slot overwrite, `0.15 / 0.85` deadzone projection
into slot 1 authored X, and the `0x4000` primary-button bridge. The mobile API
is void, and both Windows callsites discard the exit flags residue; the
existing void scratch remains exact at 61/61 instructions with all 25
operands resolved.

The matcher still carries the two float arguments as raw `int` bit patterns
to reproduce VC6's exact store scheduling. The analysis ABI is now correctly
typed as `float, float`; this is a compiler-harness detail, not uncertainty
about the authored signature.
