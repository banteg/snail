# append_bod_to_end @ 0x411420

Out-of-line tail insertion on the same `BodList` owner at `GameRoot +0x5a8`.
The root initializer uses it for the border/UI node at `GameRoot +0xb4c`, while
other startup nodes are inserted at the front by `add_bod_to_front`.

The function walks `list_next` to the tail, installs both directional links,
clears the new tail's `list_next`, and marks `list_flags & 0x200`. Duplicate
ownership reports the distinct `"List ADDend"` diagnostic.
