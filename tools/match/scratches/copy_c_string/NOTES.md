# Matched

`copy_c_string` matches exactly with the post-increment source idiom:
copy `*source` to `*destination++`, then test and advance `source` in the loop
condition. This preserves the native duplicated source-byte load while keeping
the source pointer in `eax` for the returned advanced pointer and destination
in `ecx`.
