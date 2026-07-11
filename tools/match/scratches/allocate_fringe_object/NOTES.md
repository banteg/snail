# Exact match

`allocate_fringe_object` is Windows `cRFringeManager::GetFringe()`: it
allocates one 0x38-byte authored `Fringe` from the
7000-entry fringe-manager pool. It reports
`Too many Fringes increase RFRINGEMANAGER_NUMBER` and returns null when the
pool is full.

The exact source idiom is the natural post-increment subscript:
`return &objects[count++]`. VC6 emits the native schedule from that shape:
scale the old count, increment and store the pool cursor, then return the
old-count object address.

The manager retains all 7000 objects inline; returned pointers are borrowed
until the next build/reset cycle. The shared return type is now `Fringe*`, and
focused matching remains exact at 14/14 with two clean operands.
