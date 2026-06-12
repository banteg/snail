# Residual diff — 91.43%, 17/18 insns

The helper is semantically pinned: it sets sprite flag `0x40` on the two cached
track-pair sprites at player offsets `+0x98` and `+0x9c`, then writes the same
payload into each sprite's `+0x50` lane and returns the second sprite pointer.

The only miss is a register-copy artifact before the second payload store. The
target copies the payload from `edx` to `ecx` and stores from `ecx`; VC6.5 emits
the equivalent direct store from `edx`. Do not force this with a semantic no-op.
