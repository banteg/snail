# spawn_golb_impact_sprite @ 0x415d80

Current match: 63.64%, 43/45 candidate instructions, 3/45 prefix.

This scratch maps the short-lived Golb impact sprite producer used by terminal
projectile collision paths:

- skips all work unless global render/effect flag bit `0x10` is set;
- allocates sprite id `0x21` for the owning player slot;
- sets draw flag `0x800`;
- seeds progress, velocity, size endpoints, lifetime, and gravity lanes for the
  impact burst; and
- copies the caller-provided impact world position into the sprite position.

The accepted source uses a real `Vector3` velocity temporary because the native
function reserves a 12-byte stack vector. Caching the owner slot before
`allocate_sprite` and spelling the velocity fields explicitly improved the call
setup and stack-vector locality from 54.55% to 63.64%. The remaining residual is
codegen shape: native saves `esi`, stores the velocity Y constant through the
middle stack lane, uses `esi` for the zero velocity lanes, and copies velocity
X/Y before the progress/size constants while delaying velocity Z. The current
VC6 source preserves the stack vector but emits a cleaner temporary copy and
uses `ecx` for the zero lanes.

Rejected source-shaped probes:

- direct scalar velocity stores improved instruction locality but removed the
  native stack-vector frame, scoring 51.28%;
- explicit pointer aliases to the temporary vector compiled identically to the
  scalar-store form; and
- moving the velocity copy before the progress/size stores regressed
  to 45.45%.
- 2026-06-16 BN cross-check: the odd `strncpy`-looking decompile is only BN
  grouping adjacent constants for lifetime/progress lanes, not evidence for a
  string or packed subobject. Keep modeling the real stack `Vector3` temporary:
  velocity lands at sprite words `0x15..0x17`, size at `0x18/0x19`, progress at
  `0x1a`, progress/lifetime steps at `0x1b/0x1d`, lifetime at `0x1c`, and
  gravity at `0x1e`.

Keep this as a structure-first map unless a stronger source idiom explains the
native saved-`esi` velocity-copy schedule.
