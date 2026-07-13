# update_input_controller_slot_button_axes @ 0x431ff0

Updates the two-slot input-controller state from button and axis inputs. Slot 0
merges button bits and only fills empty axis lanes; nonzero slots overwrite the
selected slot and refresh slot 1 authored X from slot 0 X with a 0.15 deadzone.

The axis arguments are stored as raw float bit patterns, so the scratch keeps
them as `int` parameters. Pointer locals for the dynamically selected nonzero
slot preserve the native button, X, Y store order.

2026-07-13 owner closure: constant slot-0 and slot-1 accesses now use the
complete `g_input_controller_slots[2]` records, including the slot-1 authored-X
write after deadzone processing. The result remains exact at 61/61 instructions
with all 25 operands resolved.
