# initialize_salt_hazard_runtime @ 0x408630

Exact constructor wrapper for one authored `Salt` (`cRSalt` cross-port):
constructs the renderable-body prefix, installs the table at `0x497340`, and
returns the receiver. The table entry points directly to
`update_salt_hazard @ 0x441c10`, the preserved `cRSalt::AI()`.

`SaltManager` owns 40 inline 0x98-byte records whose exact 0x17c0 total matches
the native cRSaltManager ledger. The scratch remains exact at 7/7 instructions
with two clean operands.
