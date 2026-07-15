# destroy_star_field @ 0x434270

Destroys all allocated star sprites, clears each entry's active flag, then
sets the star-field lifecycle `state` to `0`.

The authored `cRStarManager::UnInit()` member is `void`: its sole Windows
caller in `update_star_field` discards EAX and immediately stores state `0`.
The loop's repeated `count` load still happens to remain in EAX at return, but
that register residue is loop control rather than an owned result. Removing the
synthetic return preserves the exact 28-instruction body.
