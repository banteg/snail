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

## 2026-07-18 analyzer owner closure

Both analyzer replays now use the authored `Fringe*` result directly and type
the manager's inline array as `Fringe objects[7000]`. The replay rejects any
database where the element is not 0x38 bytes or the full manager does not close
at 0x5fb44, so the borrowed result cannot silently drift into an anonymous
same-sized record.
