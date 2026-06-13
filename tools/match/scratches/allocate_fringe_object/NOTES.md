# Exact match

`allocate_fringe_object` allocates one 0x38-byte fringe object from the
7000-entry fringe-manager pool. It reports
`Too many Fringes increase RFRINGEMANAGER_NUMBER` and returns null when the
pool is full.

The exact source idiom is the natural post-increment subscript:
`return &objects[count++]`. VC6 emits the native schedule from that shape:
scale the old count, increment and store the pool cursor, then return the
old-count object address.
