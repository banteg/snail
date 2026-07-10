# Render-cache face helper

`append_track_cache_object` @ `0x433960` is the second distinct helper after
the public cache builder. It borrows source faces and position, writes into the
manager-owned family vertex/index staging buffers, emits one triangle for
triangle faces and two for quads, and delegates vertex identity to
`add_track_cache_vertex` before enforcing the family index capacity.

Binary Ninja confirms the unused `row_index` still occupies the first stack
slot and the function returns the resulting index count (or the error-report
result on overflow). Current result: 35.65%, 164/167, prefix 1/167, with five
clean operands. The remaining mismatch is code shape: native keeps source in
`esi`, byte face offset in `ebp`, and copies the local position only after the
nonempty-face check; straightforward VC6 source assigns those lifetimes
differently, so no register-shaped rewrite is retained.
