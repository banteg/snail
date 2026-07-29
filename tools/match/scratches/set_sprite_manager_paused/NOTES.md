# set_sprite_manager_paused

Small sprite-runtime mutator at 0x44e540. Writes the global sprite manager
pause byte.

Exact match: 100.00%, 3/3 instructions, no masked operands.

## 2026-07-29 authored method and ABI

Android and iOS independently export
`void cRSpriteManager::Pause(bool)`. All six direct Windows callsites pass zero
or one and discard AL. Replacing the analytical `char` return and argument
with the authored void/bool contract remains byte-identical: VC6 loads the
stack byte into AL for the store and incidentally leaves it there on return.
The owner-qualified decorated alias maps the compiled member back to the stable
matcher target.
