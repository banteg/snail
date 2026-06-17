# initialize_object_list

ObjectList initializer at `0x42f990`.

- Clears the live count and stores the requested capacity.
- Allocates `capacity * 0xdc` bytes under the `"Object List"` allocation label.
- Runs `initialize_object` across every backing slot before runtime callers
  start handing out objects with `add_object_to_list`.
