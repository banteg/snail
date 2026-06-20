# load_registered_texture_refs

Startup texture-registry loader at `0x412a00`. It allocates the Direct3D
texture slot array, walks the registered texture descriptor table, delegates
each entry to `load_registered_texture_ref`, and logs the signed `/ 1024`
texture-memory estimate as kilobytes.

Scratch result: 100%, 35/35 instructions, with all masked operands resolved.
