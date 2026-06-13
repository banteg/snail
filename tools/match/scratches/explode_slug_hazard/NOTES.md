# Structure-first scratch - 73.22%, 148/147 insns

`explode_slug_hazard` is recovered as the 70-particle slug goo burst spawned
by `kill_slug_hazard`. Each iteration allocates sprite texture `129`, sets
sprite flags `0x802`, seeds grayscale/scale/frame/gravity fields, builds a
velocity vector from the game track-center scale and random spread terms, then
offsets the sprite position from the slug world position by a random multiple
of that velocity.

Source-shape wins from the first pass:

- splitting the size expression into `random * 0.000030517578f`, then
  `* 0.75f + 0.25f`, preserves the native two-`fmul` size schedule;
- splitting the gravity expression keeps the native separate
  `track_center * track_center * -0.01 * 2.2` operations;
- staging `velocity` and `position` as `Vector3` aggregates improves the frame
  from `0x14` to `0x38` and recovers most of the native vector stack staging.

Known residuals:

- target frame is still `0x40` versus candidate `0x38`;
- flag update uses `ebx` where native uses `edx`;
- grayscale argument setup uses a local store then push, while native reserves
  the argument slot first and writes the float directly there;
- owner-game and random side/up locals use different registers/slots around
  the velocity block;
- final position y/z scheduling and the loop return differ; VC6 still emits a
  final `xor eax, eax` instead of returning the already-zero loop counter.

Do not force the remaining frame/register residuals with volatile, dummy
locals, or raw offset macros. This scratch is useful as a semantic map for the
slug death particle burst; exact matching needs a concrete source-shape lead.
