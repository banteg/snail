# spawn_golb_impact_sprite @ 0x415d80

Current match: 54.55%, 43/45 candidate instructions, 3/45 prefix.

This scratch maps the short-lived Golb impact sprite producer used by terminal
projectile collision paths:

- skips all work unless global render/effect flag bit `0x10` is set;
- allocates sprite id `0x21` for the owning player slot;
- sets draw flag `0x800`;
- seeds progress, velocity, scale, lifetime, and gravity lanes for the
  impact burst; and
- copies the caller-provided impact world position into the sprite position.

The accepted source uses a real `Vector3` velocity aggregate because the native
function reserves a 12-byte stack vector. The remaining residual is codegen
shape: native saves `esi`, stores the velocity Y constant through the middle
stack lane, uses `esi` for the zero velocity lanes, and copies velocity X/Y
before the progress/scale constants while delaying velocity Z. The current VC6
source preserves the stack vector but emits a cleaner aggregate copy and uses
`ecx` for the zero lanes.

Rejected source-shaped probes:

- direct scalar velocity stores improved instruction locality but removed the
  native stack-vector frame, scoring 51.28%;
- explicit pointer aliases to the temporary vector compiled identically to the
  scalar-store form; and
- moving the aggregate velocity copy before the progress/scale stores regressed
  to 45.45%.

Keep this as a structure-first map unless a stronger source idiom explains the
native saved-`esi` velocity-copy schedule.
