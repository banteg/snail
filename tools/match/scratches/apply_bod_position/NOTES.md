# apply_bod_position @ 0x42f680

Exact 39/39-instruction `void cRBod::ApplyPos(tMatrix&)`. It walks the attached
`cRObject` vertex array, transforms each position through
`multiply_vector_by_matrix_copy`, and writes x/y/z back in place. The direct
member-call expression preserves VC6's native receiver lifetime; a named
source pointer changes the loop call setup.

Android and iOS independently preserve the authored owner, method name, void
return, and matrix-reference parameter. Live Windows inspection finds eight
callers, all of which discard EAX. Its terminal object value is loop residue,
so the previous pointer parameter and `cRObject*` result were inaccurate ABI
guesses rather than Windows evidence.

The helper's hidden-return compatibility call remains explicit because natural
named-value spellings change the generated loop. Ordinary float field copies
still compile to the exact dword moves; no bit-punning is required.
