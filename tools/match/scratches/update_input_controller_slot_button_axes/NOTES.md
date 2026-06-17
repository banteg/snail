# update_input_controller_slot_button_axes @ 0x431ff0

Updates the two-slot input-controller state from button and axis inputs. Slot 0
merges button bits and only fills empty axis lanes; nonzero slots overwrite the
selected slot and refresh slot 1 authored X from slot 0 X with a 0.15 deadzone.

The axis arguments are stored as raw float bit patterns, so the scratch keeps
them as `int` parameters and reuses the shared lane arrays. Pointer locals for
the nonzero slot preserve the native button, X, Y store order.
