# Exact match

`allocate_fringe_object` is Windows `cRFringeManager::GetFringe()`: it
allocates one 0x38-byte authored `cRFringe` from the
7000-entry fringe-manager pool. It reports
`Too many Fringes increase RFRINGEMANAGER_NUMBER` and returns null when the
pool is full.

The exact source idiom is the natural post-increment subscript:
`return &objects[count++]`. VC6 emits the native schedule from that shape:
scale the old count, increment and store the pool cursor, then return the
old-count object address.

The manager retains all 7000 objects inline; returned pointers are borrowed
until the next build/reset cycle. `Fringe*` remains compatibility vocabulary
for the primary `cRFringe*` result, and focused matching remains exact at 14/14
with two clean operands.

## 2026-07-18 analyzer owner closure

Both analyzer replays now use the authored `Fringe*` result directly and type
the manager's inline array as `Fringe objects[7000]`. The replay rejects any
database where the element is not 0x38 bytes or the full manager does not close
at 0x5fb44, so the borrowed result cannot silently drift into an anonymous
same-sized record.

## 2026-08-09 primary cRFringeManager::GetFringe ownership

The matcher now defines `cRFringeManager::GetFringe()` returning `cRFringe*`
and binds the exact VC6 symbol
`?GetFringe@cRFringeManager@@QAEPAVcRFringe@@XZ`. Live Windows xrefs are the
four directional allocation calls at `0x434d43`, `0x434e47`, `0x434f4b`, and
`0x43504f`, all inside `cRSubGame::FringeEdgeTrack()`. Android independently
verifies the same authored manager method with high confidence; no iOS body is
claimed. The body remains exact at 14/14 with both references clean.

The returned pointer is borrowed from the inline manager array. This leaf does
not construct, link, color, or render the object, and the compact Android
layout is not used to reinterpret the Windows 0x38-byte record.
