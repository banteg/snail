# load_registered_texture_refs

Startup texture-registry loader at `0x412a00`. It allocates the Direct3D
texture slot array, walks the registered texture descriptor table, delegates
each entry to `load_registered_texture_ref`, and logs the signed `/ 1024`
texture-memory estimate as kilobytes.

Scratch result: 100%, 35/35 instructions, with all masked operands resolved.

2026-07-10 callee contract: the wrapper's argument is still forwarded at the
only native callsite for ABI fidelity, but `load_registered_texture_ref` never
reads it. Texture transparency/state selection comes from the loaded TGA
header's `bits_per_pixel` field instead. Renaming it as a legacy mode leaves
this wrapper exactly 100% while removing a false data dependency from the
per-entry loader.
